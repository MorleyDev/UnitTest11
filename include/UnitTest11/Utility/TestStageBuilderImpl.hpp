#ifndef UNITTEST11_UTILITY_TESTSTAGEBUILDERIMPL_HPP
#define UNITTEST11_UTILITY_TESTSTAGEBUILDERIMPL_HPP

#include "TestStageImpl.hpp"
#include "TestStageBuilder.hpp"

#include <vector>
#include <memory>

namespace ut11
{
	namespace Utility
	{
		class TestStageBuilderImpl : public TestStageBuilder
		{
		private:
			enum class TestStepType
			{
				Given,
				When,
				Then,
				Finally
			};

		public:
			virtual ~TestStageBuilderImpl();

			virtual void PushGiven(TestStep given);
			virtual void PushWhen(TestStep when);
			virtual void PushThen(TestStep then);
			virtual void PushFinally(TestStep finally);

			virtual std::vector< std::shared_ptr<TestStage> > Build();

		private:
			void PopulateStagesWithFinally(std::vector<TestStageImpl>& finallylessStages, TestStep finally);
			void MoveStagesOntoFinishedStages(std::vector<ut11::Utility::TestStageImpl>&, std::vector<ut11::Utility::TestStageImpl>&);

			std::vector<std::pair<TestStepType, TestStep>> m_steps;
		};
	}
}

#endif // UNITTEST11_UTILITY_TESTSTAGEBUILDERIMPL_HPP
