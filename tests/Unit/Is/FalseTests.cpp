#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/EqualTo.hpp>

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

		Then("Is::False has an error message", []() {
			AssertThat(ut11::Is::False.GetErrorMessage(true), ut11::Is::Not::EqualTo(""));
		});

		Then("Is::Not::False(true) is true", []() {
			AssertThat(ut11::Is::Not::False(true), ut11::Is::True);
		});

		Then("Is::Not::False(false) is not true", []() {
			AssertThat(ut11::Is::Not::False(false), ut11::Is::Not::True);
		});

		Then("Is::False returns an Operand", []() {
			AssertThat( ut11::Utility::IsOperand<decltype(ut11::Is::False)>::value, ut11::Is::True );
		});

		Then("Is::Not::False returns an Operand", []() {
			AssertThat( ut11::Utility::IsOperand<decltype(ut11::Is::Not::False)>::value, ut11::Is::True );
		});

		Then("Is::Not::False has an error message", []() {
			AssertThat(ut11::Is::Not::False.GetErrorMessage(false), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsFalseTests)(ut11::Category("unit"));
