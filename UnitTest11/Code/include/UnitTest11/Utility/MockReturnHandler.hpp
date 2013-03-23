#ifndef UNITTEST11_UTILITY_MOCKRETURNER_HPP
#define UNITTEST11_UTILITY_MOCKRETURNER_HPP

#include "DefaultValue.hpp"
#include <functional>

namespace ut11
{
    namespace Utility
    {
        template<typename T, typename... ARGS> class MockReturnHandler
        {
        public:
            inline MockReturnHandler()
                : m_isReturnCallbackMode(false),
				 m_returnCallback(),
                  m_returnValue(DefaultValue<T>()())
            {
            }

            inline ~MockReturnHandler()
            {
            }

            inline void SetReturn(std::function<T (const ARGS&...)> callback)
            {
				m_isReturnCallbackMode = true;
                m_returnCallback = callback;
            }

            inline void SetReturn(T value)
            {
				m_isReturnCallbackMode = false;
                m_returnValue = value;
            }

            inline T operator()(const ARGS&... args)
            {
                return m_isReturnCallbackMode
                        ? m_returnCallback(args...)
                        : m_returnValue;
            }

		private:
			bool m_isReturnCallbackMode;
            std::function<T (const ARGS&...)> m_returnCallback;
            T m_returnValue;
        };

        template<typename... ARGS> class MockReturnHandler<void, ARGS...>
        {
        public:
            MockReturnHandler() : m_returnCallback() { }
            ~MockReturnHandler() { }

            void SetReturn(std::function<void (const ARGS&...)> callback) { m_returnCallback = callback; }
            void SetReturn() { m_returnCallback = std::function<void (const ARGS&...)>(); }
            void operator()(const ARGS&... args) { if ( m_returnCallback ) m_returnCallback(args...); }

        private:
            std::function<void (ARGS...)> m_returnCallback;
        };
    }
}

#endif // UNITTEST11_UTILITY_MOCKRETURNER_HPP
