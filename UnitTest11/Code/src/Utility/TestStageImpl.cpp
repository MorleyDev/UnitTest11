#include <UnitTest11/Utility/TestStageImpl.hpp>

ut11::Utility::TestStageImpl::TestStageImpl()
    : m_given(),
      m_when(),
      m_then(),
      m_finally()
{
}

ut11::Utility::TestStageImpl::TestStageImpl(TestStep given, TestStep when, TestStep then, TestStep finally)
    : m_given(given),
      m_when(when),
      m_then(then),
      m_finally(finally)
{
}

ut11::Utility::TestStageImpl::TestStageImpl(const TestStageImpl& Stage)
    : m_given(Stage.m_given),
      m_when(Stage.m_when),
      m_then(Stage.m_then),
      m_finally(Stage.m_finally)
{
}

ut11::Utility::TestStageImpl::~TestStageImpl()
{
}


bool ut11::Utility::TestStageImpl::Run(Output& output)
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

void ut11::Utility::TestStageImpl::Given(Output& output)
{
    if ( !m_given.logic )
        return;

    output.BeginGiven(m_given.description);
    m_given.logic();
    output.EndGiven(m_given.description);
}

void ut11::Utility::TestStageImpl::When(Output& output)
{
    if ( !m_when.logic )
        return;

    output.BeginWhen(m_when.description);
    m_when.logic();
    output.EndWhen(m_when.description);
}

void ut11::Utility::TestStageImpl::Then(Output& output)
{
    if ( !m_then.logic )
        return;

    output.BeginThen(m_then.description);
    m_then.logic();
    output.EndThen(m_then.description);
}

void ut11::Utility::TestStageImpl::Finally(Output& output)
{
    if ( !m_finally.logic )
        return;

    output.BeginFinally(m_finally.description);
    m_finally.logic();
    output.EndFinally(m_finally.description);
}
