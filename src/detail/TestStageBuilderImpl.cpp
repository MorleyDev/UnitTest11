#include <UnitTest11/detail/TestStageBuilderImpl.hpp>

ut11::detail::TestStageBuilderImpl::~TestStageBuilderImpl()
{
}

void ut11::detail::TestStageBuilderImpl::PushGiven(TestStep given)
{
	m_steps.push_back(std::make_pair(TestStepType::Given, given));
}

void ut11::detail::TestStageBuilderImpl::PushWhen(TestStep when)
{
	m_steps.push_back(std::make_pair(TestStepType::When, when));
}

void ut11::detail::TestStageBuilderImpl::PushThen(TestStep then)
{
	m_steps.push_back(std::make_pair(TestStepType::Then, then));
}

void ut11::detail::TestStageBuilderImpl::PushFinally(TestStep finally)
{
	m_steps.push_back(std::make_pair(TestStepType::Finally, finally));
}

std::vector< std::shared_ptr<ut11::detail::TestStage> > ut11::detail::TestStageBuilderImpl::Build()
{
	std::vector<ut11::detail::TestStageImpl> finallylessStages, finishedStages;

	ut11::detail::TestStep given, when;
	for (auto stepTypePair : m_steps)
	{
		switch (stepTypePair.first)
		{
		case TestStepType::Given:
			given = stepTypePair.second;
			when = TestStep();
			break;

		case TestStepType::When:
			when = stepTypePair.second;
			break;

		case TestStepType::Then:
			finallylessStages.push_back(TestStageImpl(given, when, stepTypePair.second, TestStep()));
			break;

		case TestStepType::Finally:
			PopulateStagesWithFinally(finallylessStages, stepTypePair.second);
			MoveStagesOntoFinishedStages(finishedStages, finallylessStages);

			given = TestStep();
			when = TestStep();
			break;
		}
	}
	m_steps.clear();

	MoveStagesOntoFinishedStages(finishedStages, finallylessStages);

	std::vector<std::shared_ptr<TestStage>> stages;
	for (auto step : finishedStages)
		stages.push_back(std::make_shared<TestStageImpl>(step));
	return stages;
}

void ut11::detail::TestStageBuilderImpl::MoveStagesOntoFinishedStages(std::vector<TestStageImpl>& finishedStages, std::vector<TestStageImpl>& finallylessStages)
{
	for (auto stage : finallylessStages)
		finishedStages.push_back(stage);

	finallylessStages.clear();
}

void ut11::detail::TestStageBuilderImpl::PopulateStagesWithFinally(std::vector<TestStageImpl>& finallylessStages, TestStep finally)
{
	for (auto& stage : finallylessStages)
		stage.m_finally = finally;
}
