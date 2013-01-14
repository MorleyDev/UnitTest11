#ifndef UNITTEST11_UTILITY_TESTSTAGE_HPP
#define UNITTEST11_UTILITY_TESTSTAGE_HPP

#include "../IOutput.hpp"
#include "../TestFailedException.hpp"

#include <string>
#include <functional>

namespace ut11
{
    namespace Utility
    {
        struct TestStep
        {
            TestStep() : description(), logic() { }
            TestStep(std::string d, std::function<void(void)> l) : description(d), logic(l) { }
            TestStep(const TestStep& step) : description(step.description), logic(step.logic) { }
            TestStep& operator=(const TestStep& step) { description = step.description; logic = step.logic; return *this; }
            TestStep(TestStep&& step) : description(std::move(step.description)), logic(std::move(step.logic)) { }
            TestStep& operator=(TestStep&& step) { description = std::move(step.description); logic = std::move(step.logic); return *this; }
            ~TestStep() { }

            std::string description;
            std::function<void(void)> logic;
        };

        class ITestStage
        {
        public:
            virtual ~ITestStage();

            virtual bool Run(IOutput& output) = 0;
        };

        class TestStage : public ITestStage
        {
        public:
            TestStep m_given, m_when, m_then, m_finally;

            TestStage();
            TestStage(TestStep given, TestStep when, TestStep then, TestStep finally);
            TestStage(const TestStage& stage);

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
