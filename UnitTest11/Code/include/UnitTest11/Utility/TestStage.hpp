#ifndef UNITTEST11_UTILITY_TESTSTAGE_HPP
#define UNITTEST11_UTILITY_TESTSTAGE_HPP

#include "ITestStage.hpp"
#include "TestStep.hpp"
#include "../TestFailedException.hpp"

#include <string>
#include <functional>

namespace ut11
{
    namespace Utility
    {
        class TestStage : public ITestStage
        {
        public:
            TestStep m_given, m_when, m_then, m_finally;

            TestStage();
            TestStage(TestStep given, TestStep when, TestStep then, TestStep finally);
            TestStage(const TestStage& Stage);

            virtual ~TestStage();

            virtual bool Run(IOutput& output);

            virtual void Given(IOutput& output);
            virtual void When(IOutput& output);
            virtual void Then(IOutput& output);
            virtual void Finally(IOutput& output);
        };
    }
}

#endif // UNITTEST11_UTILITY_TESTSTAGE_HPP
