#include <set>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <exception>

namespace ecs
{
	struct EntityNotFoundException : public std::exception
	{
		EntityNotFoundException(std::string description) throw() : description(description) { }
		~EntityNotFoundException() throw () { }
		
		virtual const char* what() const throw()
		{
			return description.c_str();
		}
		
	private:
		std::string description;
	};
	
	struct ComponentNotFoundException : public std::exception
	{
		ComponentNotFoundException(std::string description) throw() : description(description) { }
		~ComponentNotFoundException() throw () { }
		
		virtual const char* what() const throw()
		{
			return description.c_str();
		}
		
	private:
		std::string description;
	};

	template<typename TEntityId> class EntityComponentStore
	{
	private:
		static void ProcessToStringStream(std::ostream& stream) { return; }

		template<typename T, typename... ARGS> static void ProcessToStringStream(std::ostream& stream, T&& arg, ARGS&&... args)
		{
			ProcessToStringStream(stream << arg, std::forward<ARGS>(args)...);
		}

		template<typename... ARGS> static std::string CreateString(ARGS&&... args)
		{
			std::stringstream stream;
			ProcessToStringStream(stream, std::forward<ARGS>(args)...);
			return stream.str();
		}

	public:
		inline void addEntity(TEntityId id) 
		{ 
			entities.push_back(id);
			entityComponentMap.insert(std::make_pair(id, std::map<TypeInfo, std::shared_ptr<void>>()));
		}

		inline std::vector<TEntityId> getAllEntities() const { return entities; }

		template<typename TComponent> inline void addComponent(TEntityId id, TComponent component)
		{
			auto componentName = GetNameOfComponent<TComponent>();

			componentEntityMap.insert(std::make_pair(componentName, id));
			entityComponentMap[id].insert(std::make_pair(componentName, MakeComponentPtr(component)));
		}

		template<typename TComponent> inline std::vector<TEntityId> getAllEntitiesFor() const
		{
			std::vector<TEntityId> result;

			auto name = GetNameOfComponent<TComponent>();
			auto range = componentEntityMap.equal_range(name);
			for (auto i = range.first; i != range.second; ++i)
				result.push_back(i->second);

			return result;
		}

		template<typename TComponent> inline TComponent getComponentOfEntity(TEntityId entityId) const
		{
			auto componentsOfEntity = entityComponentMap.find(entityId);
			if (componentsOfEntity == entityComponentMap.end())
				throw EntityNotFoundException(CreateString(entityId, " does not exist in store"));

			auto componentName = GetNameOfComponent<TComponent>();
			auto componentIt = componentsOfEntity->second.find(componentName);
			if (componentIt == componentsOfEntity->second.end())
				throw ComponentNotFoundException(CreateString(componentName, " does not exist on ", entityId));

			return *std::static_pointer_cast<TComponent>(componentIt->second);
		}

	private:
		typedef std::string TypeInfo;

		template<typename TComponent> inline static std::shared_ptr<void> MakeComponentPtr(TComponent component)
		{
			return std::static_pointer_cast<void>(std::make_shared<TComponent>(component));
		}

		template<typename TComponent> inline static TypeInfo GetNameOfComponent()
		{ 
			return TypeInfo( typeid(TComponent).name() );
		}

		std::vector<TEntityId> entities;
		std::map<TEntityId, std::map<TypeInfo, std::shared_ptr<void>>> entityComponentMap;
		std::multimap<TypeInfo, TEntityId> componentEntityMap;
	};
}

#include <UnitTest11.hpp>

class EntityComponentStoreTests : public ut11::TestFixture
{
private:
	ecs::EntityComponentStore<int> m_entityComponentStore;
	std::vector<int> m_entities;
	std::vector<int> m_actualEntities;
	std::vector<int> m_entitiesWithStringComponent;
	std::vector<int> m_entitiesWithIntComponent;

	std::string m_expectedStringComponentValue;
	int m_expectedIntComponentValue;

public:
	virtual void Run()
	{
		Given("an entity component store with added entities and with components", [&]() 
		{
			m_entityComponentStore = ecs::EntityComponentStore<int>();
			m_actualEntities = std::vector<int>();

			m_entities = { 1, 2, 3, 4, 5 };
			for (auto entity : m_entities)
				m_entityComponentStore.addEntity(entity);

			m_entitiesWithStringComponent.push_back(m_entities[2]);
			m_entitiesWithIntComponent.push_back(m_entities[2]);
			m_entitiesWithIntComponent.push_back(m_entities[3]);

			m_expectedStringComponentValue = std::string("test_component1");
			m_expectedIntComponentValue = 7;

			for (auto entity : m_entitiesWithStringComponent)
				m_entityComponentStore.addComponent(entity, m_expectedStringComponentValue);

			for (auto entity : m_entitiesWithIntComponent)
				m_entityComponentStore.addComponent(entity, m_expectedIntComponentValue);
		});
		Then("getting the string component of an entity gives the expected value", [&]()
		{
			std::string component = m_entityComponentStore.getComponentOfEntity<std::string>(m_entitiesWithStringComponent[0]);
			AssertThat(component, ut11::Is::EqualTo(m_expectedStringComponentValue));
		});
		Then("getting the int component of an entity gives the expected value", [&]()
		{
			int component = m_entityComponentStore.getComponentOfEntity<int>(m_entitiesWithIntComponent[0]);
			AssertThat(component, ut11::Is::EqualTo(m_expectedIntComponentValue));
		});
		Then("getting a component of an entity that does not exist throws the expected exception", [&]()
		{
			AssertThat([&]() { m_entityComponentStore.getComponentOfEntity<std::string>(100); }, ut11::Will::Throw<ecs::EntityNotFoundException>());
		});
		Then("getting a component of an entity that does not have that component throws the expected exception", [&]()
		{
			AssertThat([&]() { m_entityComponentStore.getComponentOfEntity<std::string>(m_entities[4]); }, ut11::Will::Throw<ecs::ComponentNotFoundException>());
		});
		When("getting all entities", [&]() 
		{
			m_actualEntities = m_entityComponentStore.getAllEntities();
		});
		Then("the expected entities are returned", [&]() 
		{
			AssertThat(m_actualEntities, ut11::Is::Iterable::EquivalentTo(m_entities));
		});
		When("getting all entities with string components", [&]()
		{
			m_actualEntities = m_entityComponentStore.getAllEntitiesFor<std::string>();
		});
		Then("the expected entities are returned", [&]()
		{
			AssertThat(m_actualEntities, ut11::Is::Iterable::EquivalentTo(m_entitiesWithStringComponent));
		});
		When("getting all entities with int components", [&]()
		{
			m_actualEntities = m_entityComponentStore.getAllEntitiesFor<int>();
		});
		Then("the expected entities are returned", [&]()
		{
			AssertThat(m_actualEntities, ut11::Is::Iterable::EquivalentTo(m_entitiesWithIntComponent));
		});
	}
};
DeclareFixture(EntityComponentStoreTests)(ut11::Category("example"));
