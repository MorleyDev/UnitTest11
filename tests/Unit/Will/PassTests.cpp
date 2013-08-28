#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Will/Pass.hpp>
#include <functional>

class WillPassTests : public ut11::TestFixture
{
private:
    int m_expected;
    int m_actual;
    bool m_result;

public:
    virtual void Run()
    {
        m_expected = 10;

        Then("Will::Pass returns an Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Will::Pass(std::function<bool(int)>())) >::value, ut11::Is::True);
        });

        Then("Will::Not::Pass returns an Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Will::Not::Pass(std::function<bool(int)>())) >::value, ut11::Is::True);
        });

        When("calling Will::Pass with a predicate that passes", [&]() {
            m_result = ut11::Will::Pass([=](int actual) { m_actual = actual; return true; })(m_expected);
        });

        Then("the expected value is passed in to the predicate", [&]() {
            AssertThat(m_actual, ut11::Is::EqualTo(m_expected));
        });

        Then("the expected result is returned", [&]() {
            AssertThat(m_result, ut11::Is::True);
        });

        When("calling Will::Pass with a predicate that fails", [&]() {
            m_result = ut11::Will::Pass([=](int actual) { m_actual = actual; return false; })(m_expected);
        });

        Then("the expected value is passed in to the predicate", [&]() {
            AssertThat(m_actual, ut11::Is::EqualTo(m_expected));
        });

        Then("the expected result is returned", [&]() {
            AssertThat(m_result, ut11::Is::False);
        });
    }
};
DeclareFixture(WillPassTests)(ut11::Category("unit"));
