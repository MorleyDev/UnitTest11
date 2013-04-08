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

    	Mock(const Mock& orig)
    		: m_callbackHandler(orig.m_callbackHandler),
    		  m_argumentHandler(orig.m_argumentHandler),
    		  m_returnHandler(orig.m_returnHandler)
    	{
    	}

    	Mock& operator=(const Mock& orig)
    	{
    		m_callbackHandler = orig.m_callbackHandler;
    		m_argumentHandler = orig.m_argumentHandler;
    		m_returnHandler = orig.m_returnHandler;
    		return *this;
    	}

    	~Mock()
    	{
    	}

        inline R operator()(ARGS... args)
        {
            if ( m_callbackHandler )
                m_callbackHandler(args...);

            m_argumentHandler.AddCall(args...);
            return m_returnHandler(args...);
        }

        inline void SetCallback(std::function<void (const ARGS&...)> callback)
        {
            m_callbackHandler = callback;
        }

        template<typename V> inline void SetReturn(V value) { m_returnHandler.SetReturn(value); }

        inline void VerifyAny(std::size_t line, std::string file) const
        {
            if ( m_argumentHandler.TotalCount() == 0 )
                Assert::Fail(line, file, GetVerifyFailMessage());
        }

        template<typename... Expectations> inline void Verify(std::size_t line, std::string file, const Expectations&... expectations) const
        {
            if ( m_argumentHandler.CountCalls(expectations...) == 0 )
                Assert::Fail(line, file, GetVerifyFailMessage());
        }

        template<typename... Expectations> inline void VerifyTimes(std::size_t line, std::string file, std::size_t count, const Expectations&... expectations) const
        {
            if ( m_argumentHandler.CountCalls(expectations...) != count )
                Assert::Fail(line, file, GetVerifyFailMessage());
        }

    private:
        inline std::string GetVerifyFailMessage() const
        {
            return "Expected function call was not found";
        }

        std::function<void (const ARGS&...)> m_callbackHandler;
        Utility::MockArgumentHandler<ARGS...> m_argumentHandler;
        Utility::MockReturnHandler<R, ARGS...> m_returnHandler;
    };
}


#endif // UNITTEST11_MOCK_HPP
