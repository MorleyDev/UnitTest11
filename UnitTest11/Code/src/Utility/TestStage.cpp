#include <UnitTest11/Utility/TestStage.hpp>

ut11::Utility::TestStage::TestStage()
    : m_given(),
      m_when(),
      m_then(),
      m_finally()
{
}

ut11::Utility::TestStage::TestStage(TestStep given, TestStep when, TestStep then, TestStep finally)
    : m_given(given),
      m_when(when),
      m_then(then),
      m_finally(finally)
{
}

ut11::Utility::TestStage::TestStage(const TestStage& Stage)
    : m_given(Stage.m_given),
      m_when(Stage.m_when),
      m_then(Stage.m_then),
      m_finally(Stage.m_finally)
{
}

ut11::Utility::TestStage::~TestStage()
{
}


bool ut11::Utility::TestStage::Run(IOutput& output)
{
    try
    {
        Given(output);
        When(output);
        Then(output);
        Finally(output);
        return true;
    }
    catch(const ut11::TestFailedException& ex)
    {
        output.OnError(ex.GetLine(), ex.GetFile(), ex.GetMessage());
        return false;
    }
    catch(const std::exception& ex)
    {
        output.OnError(ex);
        return false;
    }
    catch(...)
    {
        output.OnUnknownError();
        return false;
    }
}

void ut11::Utility::TestStage::Given(IOutput& output)
{
    if ( !m_given.logic )
        return;

    output.BeginGiven(m_given.description);
    m_given.logic();
    output.EndGiven(m_given.description);
}

void ut11::Utility::TestStage::When(IOutput& output)
{
    if ( !m_when.logic )
        return;

    output.BeginWhen(m_when.description);
    m_when.logic();
    output.EndWhen(m_when.description);
}

void ut11::Utility::TestStage::Then(IOutput& output)
{
    if ( !m_then.logic )
        return;

    output.BeginThen(m_then.description);
    m_then.logic();
    output.EndThen(m_then.description);
}

void ut11::Utility::TestStage::Finally(IOutput& output)
{
    if ( !m_finally.logic )
        return;

    output.BeginFinally(m_finally.description);
    m_finally.logic();
    output.EndFinally(m_finally.description);
}
