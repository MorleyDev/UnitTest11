#ifndef UNITTEST11_utility_TESTSTAGE_HPP
#define UNITTEST11_utility_TESTSTAGE_HPP

#include "../out/Output.hpp"

namespace ut11
{
	namespace utility
	{
		class TestStage
		{
		public:
			virtual ~TestStage();

			virtual bool Run(out::Output& output) = 0;
		};
	}
}

#endif // UNITTEST11_utility_TESTSTAGE_HPP
