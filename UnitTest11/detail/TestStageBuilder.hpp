#ifndef UNITTEST11_DETAIL_TESTSTAGEBUILDER_HPP
#define UNITTEST11_DETAIL_TESTSTAGEBUILDER_HPP

#include "TestStep.hpp"
#include "TestStage.hpp"

#include <memory>
#include <vector>

namespace ut11
{
	namespace detail
	{
		class TestStageBuilder
		{
		public:
			virtual ~TestStageBuilder();

			virtual void PushGiven(TestStep given) = 0;
			virtual void PushWhen(TestStep when) = 0;
			virtual void PushThen(TestStep then) = 0;
			virtual void PushFinally(TestStep finally) = 0;
			virtual std::vector< std::shared_ptr<TestStage> > Build() = 0;
		};
	}
}


#endif // UNITTEST11_DETAIL_TESTSTAGEBUILDER_HPP
