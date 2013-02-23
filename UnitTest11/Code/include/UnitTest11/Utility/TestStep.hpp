#ifndef UNITTEST11_UTILITY_TESTSTEP_HPP
#define UNITTEST11_UTILITY_TESTSTEP_HPP

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
    }
}

#endif // UNITTEST11_UTILITY_TESTSTEP_HPP
