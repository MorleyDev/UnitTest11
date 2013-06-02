#include <UnitTest11.hpp>

namespace ut11 { namespace Utility { template<> struct DefaultValue<int> { inline int operator()() const { return 8; } }; } }

class MockReturnHandlerTest : public ut11::TestFixture
{
private:
    ut11::Utility::MockReturnHandler<int, char> m_returner;
    int m_expectedReturnValue;
    int m_expectedArgument;

    int m_actualArgument;
    int m_returnedValue;

public:
    virtual void Run(){

        Given("a MockReturnHandler", [&]() {

            m_returner = ut11::Utility::MockReturnHandler<int, char>();
        });

        When("calling the MockReturnHandler", [&]() {

            m_expectedReturnValue = ut11::Utility::DefaultValue<int>()();

            m_returnedValue = m_returner.operator ()('A');
        });

        Then("the return value is the expected value", [&]() {

            AssertThat(m_returnedValue, ut11::Is::EqualTo(m_expectedReturnValue));
        });

        When("setting the value to be returned and calling the MockReturnHandler", [&]() {

            m_expectedReturnValue = 32;
            m_returner.SetReturn(m_expectedReturnValue);

            m_returnedValue = m_returner.operator ()('A');

        });

        Then("the return value is the expected value", [&]() {

            AssertThat(m_returnedValue, ut11::Is::EqualTo(m_expectedReturnValue));
        });


        When("setting the a return function and calling the MockReturnHandler", [&]() {

            m_expectedReturnValue = 32;
            m_expectedArgument = 'Z';

            m_returner.SetReturn([&](char actual)
            {
                m_actualArgument = actual;
                return m_expectedReturnValue;
            });

            m_returnedValue = m_returner.operator ()(m_expectedArgument);

        });

        Then("the return value is the expected value", [&]() {

            AssertThat(m_returnedValue, ut11::Is::EqualTo(m_expectedReturnValue));
        });


        Then("the argument passed in to the return function is the expected value", [&]() {

            AssertThat(m_actualArgument, ut11::Is::EqualTo(m_expectedArgument));
        });

        When("setting the a return value, overriding that with a return function and calling the MockReturnHandler", [&]() {

            m_expectedReturnValue = 32;
            m_expectedArgument = 'Z';

            m_returner.SetReturn('A');
            m_returner.SetReturn([&](char actual)
            {
                m_actualArgument = actual;
                return m_expectedReturnValue;
            });

            m_returnedValue = m_returner.operator ()(m_expectedArgument);

        });

        Then("the return value is the expected value", [&]() {

            AssertThat(m_returnedValue, ut11::Is::EqualTo(m_expectedReturnValue));
        });


        Then("the argument passed in to the return function is the expected value", [&]() {

            AssertThat(m_actualArgument, ut11::Is::EqualTo(m_expectedArgument));
        });

        When("setting the a return function, overriding that with a return value and calling the MockReturnHandler", [&]() {

            m_expectedReturnValue = 32;

            m_returner.SetReturn([&](char) { return 21; });
            m_returner.SetReturn(m_expectedReturnValue);

            m_returnedValue = m_returner.operator ()(m_expectedArgument);

        });

        Then("the return value is the expected value", [&]() {

            AssertThat(m_returnedValue, ut11::Is::EqualTo(m_expectedReturnValue));
        });
    }
};
DeclareFixture(MockReturnHandlerTest);
