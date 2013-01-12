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
        inline R operator()(ARGS... args)
        {
            m_argumentHandler.AddCall(args...);
            return m_returnHandler(args...);
        }

        template<typename V> inline void setReturn(V value) { m_returnHandler.setReturn(value); }

        template<typename... Expectations> inline void Verify(std::size_t line, std::string file, const Expectations&... expectations) const
        {
            if ( m_argumentHandler.CountCalls(expectations...) == 0 )
                Assert::Fail(line, file, getVerifyFailMessage());
        }

        template<typename... Expectations> inline void VerifyTimes(std::size_t line, std::string file, std::size_t count, const Expectations&... expectations) const
        {
            if ( m_argumentHandler.CountCalls(expectations...) != count )
                Assert::Fail(line, file, getVerifyFailMessage());
        }

    private:
        inline std::string getVerifyFailMessage() const
        {
            return "Expected function call was not found";
        }

        Utility::MockArgumentHandler<ARGS...> m_argumentHandler;
        Utility::MockReturnHandler<R, ARGS...> m_returnHandler;
    };
}


#endif // UNITTEST11_MOCK_HPP
