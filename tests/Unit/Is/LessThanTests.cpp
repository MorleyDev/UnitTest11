#include <UnitTest11.hpp>

class IsLessThanTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::LessThan(5)(3) is True", []()
        {
            AssertThat(ut11::Is::LessThan(5)(3), ut11::Is::True);
        });

        Then("Is::LessThan(5)(5) is False", []()
        {
            AssertThat(ut11::Is::LessThan(5)(5), ut11::Is::False);
        });

        Then("Is::LessThan(5)(12) is False", []()
        {
            AssertThat(ut11::Is::LessThan(5)(12), ut11::Is::False);
        });

        Then("Is::LessThan is an operand", []()
        {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::GreaterThan(5)) >::value, ut11::Is::True);
        });

        Then("Is::LessThan has an error message", []() {
            AssertThat(ut11::Is::LessThan(2).GetErrorMessage(4), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsLessThanTests)();

class IsNotLessThanTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Not::LessThan(5)(3) is Not::True", []()
        {
            AssertThat(ut11::Is::Not::LessThan(5)(3), ut11::Is::Not::True);
        });

        Then("Is::Not::LessThan(5)(5) is Not::False", []()
        {
            AssertThat(ut11::Is::Not::LessThan(5)(5), ut11::Is::Not::False);
        });

        Then("Is::Not::LessThan(5)(12) is Not::False", []()
        {
            AssertThat(ut11::Is::Not::LessThan(5)(12), ut11::Is::Not::False);
        });

        Then("Is::Not::LessThan is an operand", []()
        {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::GreaterThan(5)) >::value, ut11::Is::True);
        });

        Then("Is::Not::LessThan has an error message", []() {
            AssertThat(ut11::Is::Not::LessThan(5).GetErrorMessage(4), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotLessThanTests)();

