#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/True.hpp>

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

		Then("Is::True has an error message", []() {
			AssertThat(ut11::Is::True.GetErrorMessage(false), ut11::Is::Not::EqualTo(""));
		});

		Then("Is::Not::True(true) is false", []() {
			AssertThat(ut11::Is::Not::True(true), ut11::Is::False);
		});

		Then("Is::Not::True(false) is true", []() {
			AssertThat(ut11::Is::Not::True(false), ut11::Is::Not::False);
		});

		Then("Is::True returns an Operand", []() {
			AssertThat( ut11::detail::IsOperand<decltype(ut11::Is::True)>::value, ut11::Is::Not::False );
		});

		Then("Is::Not::True returns an Operand", []() {
			AssertThat( ut11::detail::IsOperand<decltype(ut11::Is::Not::True)>::value, ut11::Is::Not::False );
		});

		Then("Is::Not::True has an error message", []() {
			AssertThat(ut11::Is::Not::True.GetErrorMessage(true), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsTrueTests)(ut11::Category("unit"));
