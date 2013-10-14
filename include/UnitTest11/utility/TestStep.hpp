#ifndef UNITTEST11_utility_TESTSTEP_HPP
#define UNITTEST11_utility_TESTSTEP_HPP

#include <string>
#include <functional>

namespace ut11
{
	namespace utility
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

#endif // UNITTEST11_utility_TESTSTEP_HPP
