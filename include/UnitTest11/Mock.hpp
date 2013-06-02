#ifndef UNITTEST11_MOCK_HPP
#define UNITTEST11_MOCK_HPP

#include "Utility/MockArgumentHandler.hpp"
#include "Utility/MockReturnHandler.hpp"
#include "Assert/Fail.hpp"

#include <memory>

namespace ut11
{
    template<typename T> class Mock;
    template<typename R, typename... ARGS> class Mock<R (ARGS...)>
    {
    public:
    	Mock()
    		: m_callbackHandler(),
    		  m_argumentHandler(),
    		  m_returnHandler()
		{
		}

    	~Mock()
    	{
    	}

        R operator()(ARGS... args)
        {
            if ( m_callbackHandler )
                m_callbackHandler(args...);

            m_argumentHandler.AddCall(args...);
            return m_returnHandler(args...);
        }

        void SetCallback(std::function<void (const ARGS&...)> callback)
        {
            m_callbackHandler = callback;
        }

        template<typename V> void SetReturn(V value) { m_returnHandler.SetReturn(value); }

        void VerifyAny(std::size_t line, std::string file) const
        {
            if ( m_argumentHandler.TotalCount() == 0 )
                Assert::Fail(line, file, GetVerifyFailMessage());
        }

        template<typename... Expectations> void Verify(std::size_t line, std::string file, const Expectations&... expectations) const
        {
            if ( m_argumentHandler.CountCalls(expectations...) == 0 )
                Assert::Fail(line, file, GetVerifyFailMessage());
        }

        template<typename... Expectations> void VerifyTimes(std::size_t line, std::string file, std::size_t count, const Expectations&... expectations) const
        {
        	auto actual = m_argumentHandler.CountCalls(expectations...);
            if ( actual != count )
                Assert::Fail(line, file, GetVerifyFailTimesMessage(count, actual));
        }

    private:
        std::string GetVerifyFailMessage() const
        {
            return "Expected function call was not found";
        }

        std::string GetVerifyFailTimesMessage(std::size_t expected, std::size_t actual) const
        {
        	std::stringstream output;
        	output << "Expected function to be called " << expected << " times was actually called " << actual << " times";
        	return output.str();
        }

        std::function<void (const ARGS&...)> m_callbackHandler;
        Utility::MockArgumentHandler<ARGS...> m_argumentHandler;
        Utility::MockReturnHandler<R, ARGS...> m_returnHandler;
    };
}


#endif // UNITTEST11_MOCK_HPP
