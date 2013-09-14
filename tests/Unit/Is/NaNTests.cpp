#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/NaN.hpp>
#include <cmath>
#include <limits>

class IsNaNTests : public ut11::TestFixture
{
private:
	template<typename T> void ThenIsNanXIsFalse(T value)
	{
		Then(std::string("Is::NaN(") + std::string(typeid(T).name()) + ": " + ut11::Utility::ToString(value) + std::string(") is False"), [value]() {
			AssertThat(ut11::Is::NaN(value), ut11::Is::False);
		});
	}

	template<typename T> void ThenIsNanXIsTrue(T value)
	{
		Then(std::string("Is::NaN(") + std::string(typeid(T).name()) + ": " + ut11::Utility::ToString(value) + std::string(") is True"), [value]() {
			AssertThat(ut11::Is::NaN(value), ut11::Is::True);
		});
	}

public:
	virtual void Run()
	{
		Then("Is::NaN is Operand", []() {
			AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::NaN) >::value, ut11::Is::True);
		});

		ThenIsNanXIsFalse<float>(0.0f);
		ThenIsNanXIsFalse<int>(124);
		ThenIsNanXIsFalse<char>('x');

		ThenIsNanXIsTrue<float>(std::numeric_limits<float>::quiet_NaN());
		ThenIsNanXIsTrue<double>(std::numeric_limits<double>::quiet_NaN());
		ThenIsNanXIsTrue<long double>(std::numeric_limits<long double>::quiet_NaN());

		struct NotANumber { const char* v; } notNumber = { nullptr };
		ThenIsNanXIsTrue<NotANumber>(notNumber);

		Then("Is::NaN has an error message", []() {
			AssertThat(ut11::Is::NaN.GetErrorMessage(5), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsNaNTests)(ut11::Category("unit"));

class IsNotNaNTests : public ut11::TestFixture
{
private:
	template<typename T> void ThenIsNotNanXIsNotFalse(T value)
	{
		Then(std::string("Is::Not::NaN(") + std::string(typeid(T).name()) + ": " + ut11::Utility::ToString(value) + std::string(") is Not False"), [value]() {
			AssertThat(ut11::Is::Not::NaN(value), ut11::Is::Not::False);
		});
	}

	template<typename T> void ThenIsNotNanXIsNotTrue(T value)
	{
		Then(std::string("Is::Not::NaN(") + std::string(typeid(T).name()) + ": " + ut11::Utility::ToString(value) + std::string(") is Not True"), [value]() {
			AssertThat(ut11::Is::Not::NaN(value), ut11::Is::Not::True);
		});
	}

public:
	virtual void Run()
	{
		Then("Is::Not::NaN is Operand", []() {
			AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::NaN) >::value, ut11::Is::True);
		});

		ThenIsNotNanXIsNotFalse<float>(0.0f);
		ThenIsNotNanXIsNotFalse<int>(124);
		ThenIsNotNanXIsNotFalse<char>('x');

		ThenIsNotNanXIsNotTrue<float>(std::numeric_limits<float>::quiet_NaN());
		ThenIsNotNanXIsNotTrue<double>(std::numeric_limits<double>::quiet_NaN());
		ThenIsNotNanXIsNotTrue<long double>(std::numeric_limits<long double>::quiet_NaN());

		struct NotANumber { const char* v; } notNumber = { nullptr };
		ThenIsNotNanXIsNotTrue<NotANumber>(notNumber);

		Then("Is::Not::NaN has an error message", []() {
			AssertThat(ut11::Is::Not::NaN.GetErrorMessage(0), ut11::Is::Not::EqualTo(""));
		});

	}
};
DeclareFixture(IsNotNaNTests)(ut11::Category("unit"));
