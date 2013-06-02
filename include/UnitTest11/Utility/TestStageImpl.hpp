#ifndef UNITTEST11_UTILITY_TESTSTAGEIMPL_HPP
#define UNITTEST11_UTILITY_TESTSTAGEIMPL_HPP

#include "TestStage.hpp"
#include "TestStep.hpp"
#include "../TestFailedException.hpp"

#include <string>
#include <functional>

namespace ut11
{
    namespace Utility
    {
        class TestStageImpl : public TestStage
        {
        public:
            TestStep m_given, m_when, m_then, m_finally;

            TestStageImpl();
            TestStageImpl(TestStep given, TestStep when, TestStep then, TestStep finally);
            virtual ~TestStageImpl();

            virtual bool Run(Output& output);

            virtual void Given(Output& output);
            virtual void When(Output& output);
            virtual void Then(Output& output);
            virtual void Finally(Output& output);
        };
    }
}

#endif // UNITTEST11_UTILITY_TESTSTAGEIMPL_HPP
