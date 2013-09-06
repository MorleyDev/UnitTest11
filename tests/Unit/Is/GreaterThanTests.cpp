#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/GreaterThan.hpp>

class IsGreaterThanTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::GreaterThan(5)(12) is True", []()
		{
			AssertThat(ut11::Is::GreaterThan(5)(12), ut11::Is::True);
		});

		Then("Is::GreaterThan(5)(5) is False", []()
		{
			AssertThat(ut11::Is::GreaterThan(5)(5), ut11::Is::False);
		});

		Then("Is::GreaterThan(5)(3) is False", []()
		{
			AssertThat(ut11::Is::GreaterThan(5)(3), ut11::Is::False);
		});

		Then("Is::GreaterThan is an operand", []()
		{
			AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::GreaterThan(5)) >::value, ut11::Is::True);
		});

		Then("Is::GreaterThan has an error message", []() {
			AssertThat(ut11::Is::GreaterThan(5).GetErrorMessage(3), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsGreaterThanTests)(ut11::Category("unit"));

class IsNotGreaterThanTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::Not::GreaterThan(5)(12) is Not::True", []()
		{
			AssertThat(ut11::Is::Not::GreaterThan(5)(12), ut11::Is::Not::True);
		});

		Then("Is::Not::GreaterThan(5)(5) is Not::False", []()
		{
			AssertThat(ut11::Is::Not::GreaterThan(5)(5), ut11::Is::Not::False);
		});

		Then("Is::Not::GreaterThan(5)(3) is Not::False", []()
		{
			AssertThat(ut11::Is::Not::GreaterThan(5)(3), ut11::Is::Not::False);
		});

		Then("Is::Not::GreaterThan is an operand", []()
		{
			AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::GreaterThan(5)) >::value, ut11::Is::True);
		});

		Then("Is::Not::GreaterThan has an error message", []() {
			AssertThat(ut11::Is::Not::GreaterThan(5).GetErrorMessage(5), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsNotGreaterThanTests)(ut11::Category("unit"));
