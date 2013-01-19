#include <UnitTest11.hpp>
#include <cmath>

class IsNaNTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::NaN(0.0f) is False", []() {
            AssertThat(ut11::Is::NaN(0.0f), ut11::Is::False);
        });

        Then("Is::NaN(NaN) is True", []() {
            AssertThat(ut11::Is::NaN(0.0f / 0.0f), ut11::Is::True);
        });

        Then("Is::NaN is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::NaN) >::value, ut11::Is::True);
        });
    }
};
DeclareFixture(IsNaNTests);

class IsNotNaNTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Not::NaN(0.0f) is Not::False", []() {
            AssertThat(ut11::Is::Not::NaN(0.0f), ut11::Is::Not::False);
        });

        Then("Is::Not::NaN(NaN) is Not::True", []() {
            AssertThat(ut11::Is::Not::NaN(0.0f / 0.0f), ut11::Is::Not::True);
        });

        Then("Is::Not::NaN is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::NaN) >::value, ut11::Is::True);
        });

    }
};
DeclareFixture(IsNotNaNTests);
