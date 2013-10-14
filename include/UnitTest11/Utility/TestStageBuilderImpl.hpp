#ifndef UNITTEST11_utility_TESTSTAGEBUILDERIMPL_HPP
#define UNITTEST11_utility_TESTSTAGEBUILDERIMPL_HPP

#include "TestStageImpl.hpp"
#include "TestStageBuilder.hpp"

#include <vector>
#include <memory>

namespace ut11
{
	namespace utility
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
			void MoveStagesOntoFinishedStages(std::vector<ut11::utility::TestStageImpl>&, std::vector<ut11::utility::TestStageImpl>&);

			std::vector<std::pair<TestStepType, TestStep>> m_steps;
		};
	}
}

#endif // UNITTEST11_utility_TESTSTAGEBUILDERIMPL_HPP
