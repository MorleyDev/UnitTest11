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

            std::string description;
            std::function<void(void)> logic;
        };
    }
}

#endif // UNITTEST11_UTILITY_TESTSTEP_HPP
