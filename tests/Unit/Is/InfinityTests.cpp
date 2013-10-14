#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/Infinity.hpp>
#include <numeric>
#include <cmath>

class IsInfinityTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::Infinity(0.0f) is False", []() {
			AssertThat(ut11::Is::Infinity(0.0f), ut11::Is::False);
		});

		Then("Is::Infinity(Infinity) is True", []() {
			AssertThat(ut11::Is::Infinity(std::numeric_limits<float>::infinity()), ut11::Is::True);
			AssertThat(ut11::Is::Infinity(-std::numeric_limits<float>::infinity()), ut11::Is::True);
		});

		Then("Is::Infinity is Operand", []() {
			AssertThat(ut11::utility::IsOperand< decltype(ut11::Is::Infinity) >::value, ut11::Is::True);
		});

		Then("Is::Infinity has an error message", []() {
			AssertThat(ut11::Is::Infinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsInfinityTests)(ut11::Category("unit"));

class IsNotInfinityTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::Not::Infinity(0.0f) is Not::False", []() {
			AssertThat(ut11::Is::Not::Infinity(0.0f), ut11::Is::Not::False);
		});

		Then("Is::Not::Infinity(Infinity) is Not::True", []() {
			AssertThat(ut11::Is::Not::Infinity(std::numeric_limits<float>::infinity()), ut11::Is::Not::True);
			AssertThat(ut11::Is::Not::Infinity(-std::numeric_limits<float>::infinity()), ut11::Is::Not::True);
		});

		Then("Is::Not::Infinity is Operand", []() {
			AssertThat(ut11::utility::IsOperand< decltype(ut11::Is::Not::Infinity) >::value, ut11::Is::True);
		});

		Then("Is::Not::Infinity has an error message", []() {
			AssertThat(ut11::Is::Not::Infinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
		});

	}
};
DeclareFixture(IsNotInfinityTests)(ut11::Category("unit"));

class IsPositiveInfinityTests : public ut11::TestFixture
{
public:
	virtual void Run() {
		Then("Is::PositiveInfinity(0.0f) is False", []() {
			AssertThat(ut11::Is::PositiveInfinity(0.0f), ut11::Is::False);
		});

		Then("Is::PositiveInfinity(+Infinity) is True", []() {
			AssertThat(ut11::Is::PositiveInfinity(std::numeric_limits<float>::infinity()), ut11::Is::True);
		});

		Then("Is::PositiveInfinity(-Infinity) is False", []() {
			AssertThat(ut11::Is::PositiveInfinity(-std::numeric_limits<float>::infinity()), ut11::Is::False);
		});

		Then("Is::PositiveInfinity is Operand", []() {
			AssertThat(ut11::utility::IsOperand< decltype(ut11::Is::PositiveInfinity) >::value, ut11::Is::True);
		});

		Then("Is::PositiveInfinity has an error message", []() {
			AssertThat(ut11::Is::PositiveInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsPositiveInfinityTests)(ut11::Category("unit"));

class IsNotPositiveInfinityTests : public ut11::TestFixture
{
public:
	virtual void Run() {
		Then("Is::Not::PositiveInfinity(0.0f) is Not::False", []() {
			AssertThat(ut11::Is::Not::PositiveInfinity(0.0f), ut11::Is::Not::False);
		});

		Then("Is::Not::PositiveInfinity(+Infinity) is Not::", []() {
			AssertThat(ut11::Is::Not::PositiveInfinity(std::numeric_limits<float>::infinity()), ut11::Is::Not::True);
		});

		Then("Is::Not::PositiveInfinity(-Infinity) is Not::False", []() {
			AssertThat(ut11::Is::Not::PositiveInfinity(-std::numeric_limits<float>::infinity()), ut11::Is::Not::False);
		});

		Then("Is::Not::PositiveInfinity is Operand", []() {
			AssertThat(ut11::utility::IsOperand< decltype(ut11::Is::Not::PositiveInfinity) >::value, ut11::Is::True);
		});

		Then("Is::Not::PositiveInfinity has an error message", []() {
			AssertThat(ut11::Is::Not::PositiveInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsNotPositiveInfinityTests)(ut11::Category("unit"));


class IsNegativeInfinityTests : public ut11::TestFixture
{
public:
	virtual void Run() {
		Then("Is::NegativeInfinity(0.0f) is False", []() {
			AssertThat(ut11::Is::NegativeInfinity(0.0f), ut11::Is::False);
		});

		Then("Is::NegativeInfinity(-Infinity) is True", []() {
			AssertThat(ut11::Is::NegativeInfinity(-std::numeric_limits<float>::infinity()), ut11::Is::True);
		});

		Then("Is::NegativeInfinity(+Infinity) is False", []() {
			AssertThat(ut11::Is::NegativeInfinity(std::numeric_limits<float>::infinity()), ut11::Is::False);
		});

		Then("Is::NegativeInfinity is Operand", []() {
			AssertThat(ut11::utility::IsOperand< decltype(ut11::Is::NegativeInfinity) >::value, ut11::Is::True);
		});

		Then("Is::NegativeInfinity has an error message", []() {
			AssertThat(ut11::Is::NegativeInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsNegativeInfinityTests)(ut11::Category("unit"));

class IsNotNegativeInfinityTests : public ut11::TestFixture
{
public:
	virtual void Run() {
		Then("Is::Not::NegativeInfinity(0.0f) is Not::False", []() {
			AssertThat(ut11::Is::Not::NegativeInfinity(0.0f), ut11::Is::Not::False);
		});

		Then("Is::Not::NegativeInfinity(-Infinity) is Not::True", []() {
			AssertThat(ut11::Is::Not::NegativeInfinity(-std::numeric_limits<float>::infinity()), ut11::Is::Not::True);
		});

		Then("Is::Not::NegativeInfinity(+Infinity) is Not::False", []() {
			AssertThat(ut11::Is::Not::NegativeInfinity(std::numeric_limits<float>::infinity()), ut11::Is::Not::False);
		});

		Then("Is::Not::NegativeInfinity is Operand", []() {
			AssertThat(ut11::utility::IsOperand< decltype(ut11::Is::Not::NegativeInfinity) >::value, ut11::Is::True);
		});

		Then("Is::Not::NegativeInfinity has an error message", []() {
			AssertThat(ut11::Is::Not::NegativeInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsNotNegativeInfinityTests)(ut11::Category("unit"));
