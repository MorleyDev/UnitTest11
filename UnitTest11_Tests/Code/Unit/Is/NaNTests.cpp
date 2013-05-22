#include <UnitTest11.hpp>
#include <cmath>

#ifndef NAN
	static const uint32_t __nan[2] = {0xffffffff, 0x7fffffff};
    #define NAN (*(const float *) __nan)
#endif

class IsNaNTests : public ut11::TestFixtureImpl
{
public:
    virtual void Run()
    {
        Then("Is::NaN(0.0f) is False", []() {
            AssertThat(ut11::Is::NaN(0.0f), ut11::Is::False);
        });

        Then("Is::NaN(NaN) is True", []() {
            AssertThat(ut11::Is::NaN(NAN), ut11::Is::True);
        });

        Then("Is::NaN(struct) is True", []() {

        	struct NotANumber { const char* v; } notNumber;

            AssertThat(ut11::Is::NaN(notNumber), ut11::Is::True);
        });

        Then("Is::NaN(int) is False", []() {

            AssertThat(ut11::Is::NaN(5), ut11::Is::False);
        });

        Then("Is::NaN is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::NaN) >::value, ut11::Is::True);
        });

        Then("Is::NaN has an error message", []() {
            AssertThat(ut11::Is::NaN.GetErrorMessage(5), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNaNTests);

class IsNotNaNTests : public ut11::TestFixtureImpl
{
public:
    virtual void Run()
    {
        Then("Is::Not::NaN(0.0f) is Not::False", []() {
            AssertThat(ut11::Is::Not::NaN(0.0f), ut11::Is::Not::False);
        });

        Then("Is::Not::NaN(NaN) is Not::True", []() {
            AssertThat(ut11::Is::Not::NaN(NAN), ut11::Is::Not::True);
        });

        Then("Is::Not::NaN is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::NaN) >::value, ut11::Is::True);
        });

        Then("Is::Not::NaN(struct) is Not::True", []() {

        	struct NotANumber { const char* v; } notNumber;

            AssertThat(ut11::Is::Not::NaN(notNumber), ut11::Is::Not::True);
        });

        Then("Is::Not::NaN(int) is Not::False", []() {

            AssertThat(ut11::Is::Not::NaN(5), ut11::Is::Not::False);
        });

        Then("Is::Not::NaN has an error message", []() {
            AssertThat(ut11::Is::Not::NaN.GetErrorMessage(0), ut11::Is::Not::EqualTo(""));
        });

    }
};
DeclareFixture(IsNotNaNTests);
