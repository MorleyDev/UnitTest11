#include <UnitTest11.hpp>

class IsBetweenTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Between(5,10)(7) is True", []()
        {
            AssertThat(ut11::Is::Between(5, 10)(7), ut11::Is::True);
        });

        Then("Is::Between(5,10)(12) is False", []()
        {
            AssertThat(ut11::Is::Between(5, 10)(12), ut11::Is::False);
        });

        Then("Is::Between(5,10)(3) is False", []()
        {
            AssertThat(ut11::Is::Between(5, 10)(3), ut11::Is::False);
        });

        Then("Is::Between is an operand", []()
        {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Between(5,10)) >::value, ut11::Is::True);
        });

        Then("Is::Between has an error message", []() {
            AssertThat(ut11::Is::Between(5, 10).GetErrorMessage(12), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsBetweenTests)(ut11::Category("unit"));

class IsNotBetweenTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Not::Between(5,10)(7) is Not::True", []()
        {
            AssertThat(ut11::Is::Not::Between(5, 10)(7), ut11::Is::Not::True);
        });

        Then("Is::Not::Between(5,10)(12) is Not::False", []()
        {
            AssertThat(ut11::Is::Not::Between(5, 10)(12), ut11::Is::Not::False);
        });

        Then("Is::Not::Between(5,10)(3) is Not::False", []()
        {
            AssertThat(ut11::Is::Not::Between(5, 10)(3), ut11::Is::Not::False);
        });

        Then("Is::Not::Between is an operand", []()
        {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::Between(5,10)) >::value, ut11::Is::True);
        });

        Then("Is::Not::Between has an error message", []() {
            AssertThat(ut11::Is::Not::Between(5, 10).GetErrorMessage(3), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotBetweenTests)(ut11::Category("unit"));
