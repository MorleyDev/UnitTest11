#include <UnitTest11.hpp>

class IsTrueTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::True(true) is true", []() {
            AssertThat(ut11::Is::True(true), ut11::Is::Not::False);
        });

        Then("Is::True(false) is false", []() {
            AssertThat(ut11::Is::True(false), ut11::Is::False);
        });

        Then("Is::Not::True(true) is false", []() {
            AssertThat(ut11::Is::Not::True(true), ut11::Is::False);
        });

        Then("Is::Not::True(false) is true", []() {
            AssertThat(ut11::Is::Not::True(false), ut11::Is::Not::False);
        });

        Then("Is::True returns an Operand", []() {
            AssertThat( ut11::Utility::IsOperand<decltype(ut11::Is::True)>::value, ut11::Is::Not::False );
        });

        Then("Is::Not::True returns an Operand", []() {
            AssertThat( ut11::Utility::IsOperand<decltype(ut11::Is::Not::True)>::value, ut11::Is::Not::False );
        });
    }
};
DeclareFixture(IsTrueTests);
