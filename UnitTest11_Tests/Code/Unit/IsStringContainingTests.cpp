#include <UnitTest11.hpp>

class IsStringContainingTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("string containing desired string is true", [&]() {
			AssertThat(ut11::Is::String::Containing("Hell")("Hello"), ut11::Is::True);
		});

		Then("string not containing desired string is false", [&]() {
			AssertThat(ut11::Is::String::Containing("World")("Hello"), ut11::Is::False);
		});

        Then("Is::String::Containing is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::String::Containing("world")) >::value, ut11::Is::True);
        });

        Then("Is::EqualTo has an error message", []() {
            AssertThat(ut11::Is::String::Containing("world").GetErrorMessage("piano"), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsStringContainingTests);


class IsNotStringContainingTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("string not containing desired string is true", [&]() {
			AssertThat(ut11::Is::Not::String::Containing("Wor")("Hello"), ut11::Is::True);
		});

		Then("string containing desired string is false", [&]() {
			AssertThat(ut11::Is::Not::String::Containing("Wor")("World"), ut11::Is::False);
		});

        Then("Is::Not::String::Containing is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::String::Containing("world")) >::value, ut11::Is::True);
        });

        Then("Is::Not::EqualTo has an error message", []() {
            AssertThat(ut11::Is::Not::String::Containing("world").GetErrorMessage("world"), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsNotStringContainingTests);
