#include <UnitTest11/Utility/TestStageBuilder.hpp>

ut11::Utility::TestStageBuilder::~TestStageBuilder()
{
}


void ut11::Utility::TestStageBuilder::PushGiven(TestStep given)
{
    FlushToFinished();
    m_given = given;
}

void ut11::Utility::TestStageBuilder::PushWhen(TestStep when)
{
    m_when = when;
}

void ut11::Utility::TestStageBuilder::PushThen(TestStep then)
{
    m_finallylessStages.push_back(TestStage(m_given, m_when, then, TestStep()));
}

void ut11::Utility::TestStageBuilder::PushFinally(TestStep finally)
{
    for(auto& step : m_finallylessStages)
        step.m_finally = finally;

    FlushToFinished();
}

std::vector< std::shared_ptr<ut11::Utility::ITestStage> > ut11::Utility::TestStageBuilder::Stage()
{
    FlushToFinished();

    return m_finishedStages;
}

void ut11::Utility::TestStageBuilder::FlushToFinished()
{
    m_given = TestStep();
    m_when = TestStep();

    for(auto step : m_finallylessStages)
        m_finishedStages.push_back(std::make_shared<TestStage>(step));
    m_finallylessStages.clear();
}
