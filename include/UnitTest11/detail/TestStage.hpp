#ifndef UNITTEST11_DETAIL_TESTSTAGE_HPP
#define UNITTEST11_DETAIL_TESTSTAGE_HPP

#include "../out/Output.hpp"

namespace ut11
{
	namespace detail
	{
		class TestStage
		{
		public:
			virtual ~TestStage();

			virtual bool Run(out::Output& output) = 0;
		};
	}
}

#endif // UNITTEST11_DETAIL_TESTSTAGE_HPP
