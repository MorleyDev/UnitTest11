#include <UnitTest11.hpp>

class IsFalseTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::False(false) is true", []() {
            AssertThat(ut11::Is::False(false), ut11::Is::True);
        });

        Then("Is::False(true) is not true", []() {
            AssertThat(ut11::Is::False(true), ut11::Is::Not::True);
        });

        Then("Is::Not::False(true) is true", []() {
            AssertThat(ut11::Is::Not::False(true), ut11::Is::True);
        });

        Then("Is::Not::False(false) is not true", []() {
            AssertThat(ut11::Is::Not::False(false), ut11::Is::Not::True);
        });
    }
};
DeclareFixture(IsFalseTests);
