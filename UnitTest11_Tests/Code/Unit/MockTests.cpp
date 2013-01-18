#include <UnitTest11.hpp>

class MockTest : public ut11::TestFixture
{
private:
    ut11::Mock<int (char)> m_mock;

    char m_expectedParameter;
    int m_expectedReturn;

    char m_actualParameter;
    int m_actualReturn;

public:
    virtual void Run()
    {
        Given("a Mock", [&]() {
            m_mock = ut11::Mock<int (char)>();

        });

        Then("VerifyAny fails as expected", [&]() {
            AssertThat([&]() { m_mock.VerifyAny(__LINE__, __FILE__); }, ut11::Will::Throw<ut11::TestFailedException>());
        });

        When("calling the Mock", [&]() {

            m_expectedParameter = 'A';

            m_mock(m_expectedParameter);

        });

        Then("the Mock verifies with the expected parameters as expected", [&]() {
            m_mock.VerifyAny(__LINE__, __FILE__);
            m_mock.Verify(__LINE__, __FILE__, m_expectedParameter);
            m_mock.VerifyTimes(__LINE__, __FILE__, 1, m_expectedParameter);
        });

        Then("the Mock verifies fails as expected when with the wrong parameters", [&]() {

            AssertThat([&]() { m_mock.Verify(__LINE__, __FILE__, '\n'); }, ut11::Will::Throw<ut11::TestFailedException>());
        });

        Then("the Mock verifies fails as expected when with the wrong VerifyTimes", [&]() {

            AssertThat([&]() { m_mock.VerifyTimes(__LINE__, __FILE__, 2, m_expectedParameter); }, ut11::Will::Throw<ut11::TestFailedException>());
        });

        When("setting a callback calling the Mock", [&]() {

            m_expectedParameter = 'A';

            m_mock.setCallback([&](char c)
            {
                m_actualParameter = c;
            });

            m_mock(m_expectedParameter);
        });

        Then("the expected parameter was passed in to the callback", [&]() {
            AssertThat(m_actualParameter, ut11::Is::EqualTo(m_expectedParameter));
        });

        When("setting a return value, calling the Mock", [&]() {

            m_expectedReturn = 5;

            m_mock.setReturn(m_expectedReturn);

            m_actualReturn = m_mock('P');
        });

        Then("the expected return value was returned", [&]() {
            AssertThat(m_actualReturn, ut11::Is::EqualTo(m_expectedReturn));
        });
    }
};
DeclareFixture(MockTest);

class MockVoidTest : public ut11::TestFixture
{
private:
    ut11::Mock<void (void)> m_mock;

public:
    virtual void Run()
    {
        Given("a Mock that takes no arguments and returns void", [&]() {
            m_mock = ut11::Mock<void (void)>();
        });

        When("the Mock is called", [&]() {
            m_mock();
        });

        Then("the mock verifies as expected", [&]() {
            m_mock.VerifyAny(__LINE__, __FILE__);
            m_mock.Verify(__LINE__, __FILE__);
            m_mock.VerifyTimes(__LINE__, __FILE__, 1);
        });

        Then("verifying the wrong number of times causes a failure", [&]() {
            AssertThat([&]() { m_mock.VerifyTimes(__LINE__, __FILE__, 2); }, ut11::Will::Throw<ut11::TestFailedException>());
        });
    }
};
DeclareFixture(MockVoidTest);
