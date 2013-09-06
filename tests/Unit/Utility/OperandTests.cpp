#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/Any.hpp>

namespace
{
	struct Operand : public ut11::Utility::BaseOperand<Operand> 
	{
		template<typename T> bool operator()(const T& actual) const { return true; }

		template<typename T> std::string GetErrorMessage(const T& actual) const { return ""; }
	};

	struct OtherOperand : public ut11::Utility::BaseOperand<OtherOperand>
	{
		template<typename T> bool operator()(const T& actual) const { return true; }

		template<typename T> std::string GetErrorMessage(const T& actual) const { return ""; }
	};
}

class IsOperandTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("IsOperand<Operand>::value is true", []() {
			AssertThat(ut11::Utility::IsOperand<Operand>::value, ut11::Is::True);
		});

		Then("IsOperand<int>::value is false", []() {
			AssertThat(ut11::Utility::IsOperand<int>::value, ut11::Is::False);
		});

		Then("IsOperand< NotOperand<Operand> >::value is true", []() {
			AssertThat(ut11::Utility::IsOperand< ut11::Utility::NotOperand<Operand> >::value, ut11::Is::True);
		});
	}
};
DeclareFixture(IsOperandTests)(ut11::Category("unit"));

class BaseOperandTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("operand && operand gives an AndOperand", [&]() 
		{
			AssertThat(Operand() && OtherOperand(), ut11::Is::Any < ut11::Utility::AndOperand<Operand, OtherOperand> >());
		});

		Then("operand || operand gives an OrOperand", [&]()
		{
			AssertThat(Operand() || OtherOperand(), ut11::Is::Any < ut11::Utility::OrOperand<Operand, OtherOperand> >());
		});

		Then("!operand operand gives a NotOperand", [&]()
		{
			AssertThat(!Operand(), ut11::Is::Any < ut11::Utility::NotOperand<Operand> >());
		});
	}
};
DeclareFixture(BaseOperandTests)(ut11::Category("unit"));
