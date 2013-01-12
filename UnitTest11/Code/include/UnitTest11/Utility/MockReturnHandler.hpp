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
            MockReturnHandler()
                : m_returnCallback(),
                  m_returnValue(DefaultValue<T>()())
            {
            }

            ~MockReturnHandler()
            {
            }

            void setReturn(std::function<T (const ARGS&...)> callback)
            {
                m_returnCallback = callback;
            }

            void setReturn(T value)
            {
                m_returnCallback = std::function<T (const ARGS&...)>();
                m_returnValue = value;
            }

            T operator()(const ARGS&... args)
            {
                return m_returnCallback
                        ? m_returnCallback(args...)
                        : m_returnValue;
            }

        private:
            std::function<T (ARGS...)> m_returnCallback;
            T m_returnValue;
        };

        template<typename... ARGS> class MockReturnHandler<void, ARGS...>
        {
        public:
            MockReturnHandler() : m_returnCallback() { }
            ~MockReturnHandler() { }

            void setReturn(std::function<void (const ARGS&...)> callback) { m_returnCallback = callback; }
            void setReturn() { m_returnCallback = std::function<void (const ARGS&...)>(); }
            void operator()(const ARGS&... args) { if ( m_returnCallback ) m_returnCallback(args...); }

        private:
            std::function<void (ARGS...)> m_returnCallback;
        };
    }
}

#endif // UNITTEST11_UTILITY_MOCKRETURNER_HPP
