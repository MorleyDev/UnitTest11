#include <UnitTest11/utility/TestStageBuilderImpl.hpp>

ut11::utility::TestStageBuilderImpl::~TestStageBuilderImpl()
{
}

void ut11::utility::TestStageBuilderImpl::PushGiven(TestStep given)
{
	m_steps.push_back(std::make_pair(TestStepType::Given, given));
}

void ut11::utility::TestStageBuilderImpl::PushWhen(TestStep when)
{
	m_steps.push_back(std::make_pair(TestStepType::When, when));
}

void ut11::utility::TestStageBuilderImpl::PushThen(TestStep then)
{
	m_steps.push_back(std::make_pair(TestStepType::Then, then));
}

void ut11::utility::TestStageBuilderImpl::PushFinally(TestStep finally)
{
	m_steps.push_back(std::make_pair(TestStepType::Finally, finally));
}

std::vector< std::shared_ptr<ut11::utility::TestStage> > ut11::utility::TestStageBuilderImpl::Build()
{
	std::vector<ut11::utility::TestStageImpl> finallylessStages, finishedStages;

	ut11::utility::TestStep given, when;
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

void ut11::utility::TestStageBuilderImpl::MoveStagesOntoFinishedStages(std::vector<TestStageImpl>& finishedStages, std::vector<TestStageImpl>& finallylessStages)
{
	for (auto stage : finallylessStages)
		finishedStages.push_back(stage);

	finallylessStages.clear();
}

void ut11::utility::TestStageBuilderImpl::PopulateStagesWithFinally(std::vector<TestStageImpl>& finallylessStages, TestStep finally)
{
	for (auto& stage : finallylessStages)
		stage.m_finally = finally;
}
