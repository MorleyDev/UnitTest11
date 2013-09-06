#include <UnitTest11/Utility/TestStageBuilderImpl.hpp>

ut11::Utility::TestStageBuilderImpl::~TestStageBuilderImpl()
{
}


void ut11::Utility::TestStageBuilderImpl::PushGiven(TestStep given)
{
	FlushToFinished();
	m_given = given;
}

void ut11::Utility::TestStageBuilderImpl::PushWhen(TestStep when)
{
	m_when = when;
}

void ut11::Utility::TestStageBuilderImpl::PushThen(TestStep then)
{
	m_finallylessStages.push_back(TestStageImpl(m_given, m_when, then, TestStep()));
}

void ut11::Utility::TestStageBuilderImpl::PushFinally(TestStep finally)
{
	for(auto& step : m_finallylessStages)
		step.m_finally = finally;

	FlushToFinished();
}

std::vector< std::shared_ptr<ut11::Utility::TestStage> > ut11::Utility::TestStageBuilderImpl::Stage()
{
	FlushToFinished();

	return m_finishedStages;
}

void ut11::Utility::TestStageBuilderImpl::FlushToFinished()
{
	m_given = TestStep();
	m_when = TestStep();

	for(auto step : m_finallylessStages)
		m_finishedStages.push_back(std::make_shared<TestStageImpl>(step));
	m_finallylessStages.clear();
}
