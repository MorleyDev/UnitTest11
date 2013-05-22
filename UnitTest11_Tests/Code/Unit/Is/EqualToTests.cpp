#include <UnitTest11.hpp>

class IsEqualToTests : public ut11::TestFixtureImpl
{
public:
    virtual void Run()
    {
        Then("Is::EqualTo succeeds", []() {
            AssertThat(ut11::Is::EqualTo(7)(7), ut11::Is::True);
        });

        Then("Is::EqualTo fails", []() {
            AssertThat(ut11::Is::EqualTo(7)(15), ut11::Is::Not::True);
        });

        Then("Is::EqualTo is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::EqualTo(7)) >::value, ut11::Is::True);
        });

        Then("Is::EqualTo has an error message", []() {
            AssertThat(ut11::Is::EqualTo(false).GetErrorMessage(true), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsEqualToTests);

class IsNotEqualToTests : public ut11::TestFixtureImpl
{
public:
    virtual void Run()
    {
        Then("Is::Not::EqualTo fails", []() {
            AssertThat(ut11::Is::Not::EqualTo(7)(25), ut11::Is::True);
        });

        Then("Is::Not::EqualTo succeeds", []() {
            AssertThat(ut11::Is::Not::EqualTo(15)(15), ut11::Is::Not::True);
        });

        Then("Is::Not::EqualTo is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::EqualTo(7)) >::value, ut11::Is::True);
        });

        Then("Is::Not::EqualTo has an error message", []() {
            AssertThat(ut11::Is::Not::EqualTo(true).GetErrorMessage(true), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotEqualToTests);
