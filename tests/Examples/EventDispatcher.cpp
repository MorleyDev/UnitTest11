#include <functional>
#include <map>
#include <list>
#include <memory>

namespace ed
{
	class EventDispatcher;

	namespace detail
	{
		struct EventDispatcherHandlerIterator
		{
		public:
			typedef std::map < const std::type_info*, std::list < std::function < void(std::shared_ptr<void>) >> >::iterator MapIterator;
			typedef std::list<std::function<void(std::shared_ptr<void>)>>::iterator ListIterator;

			EventDispatcherHandlerIterator()
				: m_mapIterator(), m_listIterator()
			{
			}

			EventDispatcherHandlerIterator(MapIterator mapIt, ListIterator listIt)
				: m_mapIterator(mapIt), m_listIterator(listIt)
			{
			}

			ListIterator getListIterator() const { return m_listIterator; }
			MapIterator getMapIterator() const { return m_mapIterator; }

		private:
			ListIterator m_listIterator;
			MapIterator m_mapIterator;
		};
	}

	struct EventDispatcherHandler
	{
	private:
		EventDispatcher* dispatcher;
		detail::EventDispatcherHandlerIterator iterator;

		inline EventDispatcherHandler(const EventDispatcherHandler&);
		inline EventDispatcherHandler& operator=(const EventDispatcherHandler&);

		void removeFromDispatcher();

	public:
		inline EventDispatcherHandler() : dispatcher(nullptr), iterator() { }
		inline EventDispatcherHandler(EventDispatcher* disp, detail::EventDispatcherHandlerIterator it) : dispatcher(disp), iterator(it) { }
		inline ~EventDispatcherHandler() { removeFromDispatcher();  }


		inline EventDispatcherHandler(EventDispatcherHandler&& orig)
			: dispatcher(orig.dispatcher),
			iterator(std::move(orig.iterator))
		{
			orig.dispatcher = nullptr;
		}

		inline EventDispatcherHandler& operator=(EventDispatcherHandler&& orig)
		{
			removeFromDispatcher();

			dispatcher = orig.dispatcher;
			orig.dispatcher = nullptr;
			iterator = std::move(orig.iterator);
			return *this;
		}

		inline detail::EventDispatcherHandlerIterator getIterator() const { return iterator; }

		bool isValid() const { return dispatcher != nullptr; }
	};

	class EventDispatcher
	{
	public:
		template<typename TEvent> EventDispatcherHandler addHandler(std::function<void(TEvent)> handler)
		{
			std::function<void(std::shared_ptr<void>)> realHandler([handler](std::shared_ptr<void> eventPtr)
			{
				handler(*std::static_pointer_cast<TEvent>(eventPtr));
			});

			auto mapIt = m_handlerMap.find(&typeid(TEvent));
			if (mapIt == m_handlerMap.end())
				mapIt = m_handlerMap.insert(std::make_pair(&typeid(TEvent), std::list<std::function<void(std::shared_ptr<void>)>>())).first;

			auto& list = mapIt->second;
			return EventDispatcherHandler(this, detail::EventDispatcherHandlerIterator(mapIt, list.insert(list.begin(), realHandler)));
		}

		template<typename TEvent> void dispatch(const TEvent& e)
		{
			for (auto handler : m_handlerMap[&typeid(e)])
				handler(std::make_shared<TEvent>(e));
		}

		void _removeHandler(const detail::EventDispatcherHandlerIterator& iterator)
		{
			iterator.getMapIterator()->second.erase(iterator.getListIterator());
		}

	private:
		std::map<const std::type_info*, std::list<std::function<void(std::shared_ptr<void>)>>> m_handlerMap;
	};


	void EventDispatcherHandler::removeFromDispatcher()
	{
		if (dispatcher != nullptr)
			dispatcher->_removeHandler(iterator);
	}
}

#include <UnitTest11/Core.hpp>
#include <UnitTest11/Mock.hpp>
#include <UnitTest11/Is/Any.hpp>
#include <memory>

template<int _> struct TestEvent
{
	TestEvent() = default;
	TestEvent(int v) : value(v) { }
	int value;

	inline bool operator==(const TestEvent<_>& other) const { return value == other.value; }
};

class EventDispatcherTests : public ut11::TestFixture
{
private:
	std::unique_ptr<ed::EventDispatcher> m_eventDispatcher;

	ut11::Mock<void(TestEvent<1>)> m_mockTestEvent1Handler[2];
	ed::EventDispatcherHandler m_eventHandler[2];

	int m_expectedValue;

public:
	virtual void Run()
	{
		Given("event dispatcher with attached handlers", [&]()
		{
			m_eventHandler[0] = ed::EventDispatcherHandler();
			m_eventHandler[1] = ed::EventDispatcherHandler();

			m_mockTestEvent1Handler[0] = ut11::Mock<void(TestEvent<1>)>();
			m_mockTestEvent1Handler[1] = ut11::Mock<void(TestEvent<1>)>();

			m_eventDispatcher = std::unique_ptr<ed::EventDispatcher>(new ed::EventDispatcher());
	
			m_eventHandler[0] = m_eventDispatcher->addHandler(std::function<void(TestEvent<1>)>(std::ref(m_mockTestEvent1Handler[0])));
			m_eventHandler[1] = m_eventDispatcher->addHandler(std::function<void(TestEvent<1>)>(std::ref(m_mockTestEvent1Handler[1])));
		});
		Then("dispatching an event that has no related handlers is valid", [&]()
		{
			m_eventDispatcher->dispatch(TestEvent<2>(m_expectedValue));
		});
		When("dispatching an event that has multiple related handlers", [&]()
		{
			m_expectedValue = 5;

			m_eventDispatcher->dispatch(TestEvent<1>(m_expectedValue));
		});
		Then("the expected handlers were called", [&]()
		{
			MockVerifyTimes(1, m_mockTestEvent1Handler[0])(TestEvent<1>(m_expectedValue));
			MockVerifyTimes(1, m_mockTestEvent1Handler[1])(TestEvent<1>(m_expectedValue));
		});
		When("removing and handler and dispatching an event that had that related handlers", [&]()
		{
			m_eventHandler[0] = ed::EventDispatcherHandler();

			m_expectedValue = 5;

			m_eventDispatcher->dispatch(TestEvent<1>(m_expectedValue));
		});
		Then("the removed handler was not called", [&]()
		{
			MockVerifyTimes(0, m_mockTestEvent1Handler[0])(ut11::Is::Any<TestEvent<1>>());
			MockVerifyTimes(1, m_mockTestEvent1Handler[1])(TestEvent<1>(m_expectedValue));
		});
		When("adding a handler where the handler deconstructs before the event is dispatched", [&]()
		{
			m_eventHandler[0] = ed::EventDispatcherHandler();
			{ auto otherHandler = m_eventDispatcher->addHandler(std::function<void(TestEvent<1>)>(std::ref(m_mockTestEvent1Handler[0]))); }

			m_expectedValue = 5;

			m_eventDispatcher->dispatch(TestEvent<1>(m_expectedValue));
		});
		Then("the handler was not called", [&]()
		{
			MockVerifyTimes(0, m_mockTestEvent1Handler[0])(ut11::Is::Any<TestEvent<1>>());
			MockVerifyTimes(1, m_mockTestEvent1Handler[1])(TestEvent<1>(m_expectedValue));
		});
	}
};
DeclareFixture(EventDispatcherTests)(ut11::Category("example"));
