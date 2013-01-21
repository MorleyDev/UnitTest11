#include <UnitTest11.hpp>

class MockArgumentHandlerTest : public ut11::TestFixture
{
private:
    ut11::Utility::MockArgumentHandler<int> m_argumentHandler;
    int m_expectedCalls[2] = { 5, 7 };

public:
    virtual void Run()
    {
        Given("a MockArgumentHandler with added calls", [&]()
        {
            m_argumentHandler = ut11::Utility::MockArgumentHandler<int>();
            m_argumentHandler.AddCall(m_expectedCalls[0]);
            m_argumentHandler.AddCall(m_expectedCalls[0]);
            m_argumentHandler.AddCall(m_expectedCalls[0]);
            m_argumentHandler.AddCall(m_expectedCalls[1]);
        });

        Then("the TotalCount() is as expected", [&]()
        {

            AssertThat(m_argumentHandler.TotalCount(), ut11::Is::EqualTo(4u));
        });

        Then("the expected calls are as expected for direct argument comparisons", [&]()
        {
            AssertThat(m_argumentHandler.CountCalls(m_expectedCalls[0]), ut11::Is::EqualTo(3u));
            AssertThat(m_argumentHandler.CountCalls(m_expectedCalls[1]), ut11::Is::EqualTo(1u));
            AssertThat(m_argumentHandler.CountCalls(12), ut11::Is::EqualTo((std::size_t)0));
        });

        Then("the expected calls are as expected for operand argument comparisons", [&]()
        {
            AssertThat(m_argumentHandler.CountCalls(ut11::Is::EqualTo(m_expectedCalls[0])), ut11::Is::EqualTo(3u));
            AssertThat(m_argumentHandler.CountCalls(ut11::Is::EqualTo(m_expectedCalls[1])), ut11::Is::EqualTo(1u));
            AssertThat(m_argumentHandler.CountCalls(ut11::Is::EqualTo(23)), ut11::Is::EqualTo(0u));
        });
    }
};
DeclareFixture(MockArgumentHandlerTest);
