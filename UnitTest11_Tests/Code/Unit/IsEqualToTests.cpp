#include <UnitTest11.hpp>

class IsEqualToTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::EqualTo succeeds", []()
        {
            AssertThat(ut11::Is::EqualTo(7)(7), ut11::Is::True);
        });

        Then("Is::EqualTo fails", []()
        {
            AssertThat(ut11::Is::EqualTo(7)(15), ut11::Is::Not::True);
        });
    }
};
DeclareFixture(IsEqualToTests);

class IsNotEqualToTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Not::EqualTo fails", []()
        {
            AssertThat(ut11::Is::Not::EqualTo(7)(25), ut11::Is::True);
        });

        Then("Is::Not::EqualTo succeeds", []()
        {
            AssertThat(ut11::Is::Not::EqualTo(15)(15), ut11::Is::Not::True);
        });
    }
};
DeclareFixture(IsNotEqualToTests);
