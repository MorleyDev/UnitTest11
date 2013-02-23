#include <UnitTest11.hpp>
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
            AssertThat(ut11::Is::Infinity(1.0f / 0.0f), ut11::Is::True);
        });

        Then("Is::Infinity is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Infinity) >::value, ut11::Is::True);
        });

        Then("Is::Infinity is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Infinity) >::value, ut11::Is::True);
        });

        Then("Is::Infinity has an error message", []() {
            AssertThat(ut11::Is::Infinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsInfinityTests);

class IsNotInfinityTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Not::Infinity(0.0f) is Not::False", []() {
            AssertThat(ut11::Is::Not::Infinity(0.0f), ut11::Is::Not::False);
        });

        Then("Is::Not::Infinity(Infinity) is Not::True", []() {
            AssertThat(ut11::Is::Not::Infinity(1.0f / 0.0f), ut11::Is::Not::True);
        });

        Then("Is::Not::Infinity is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::Infinity) >::value, ut11::Is::True);
        });

        Then("Is::Not::Infinity has an error message", []() {
            AssertThat(ut11::Is::Not::Infinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
        });

    }
};
DeclareFixture(IsNotInfinityTests);

class IsPositiveInfinityTests : public ut11::TestFixture
{
public:
    virtual void Run() {
        Then("Is::PositiveInfinity(0.0f) is False", []() {
            AssertThat(ut11::Is::PositiveInfinity(0.0f), ut11::Is::False);
        });

        Then("Is::PositiveInfinity(+Infinity) is True", []() {
            AssertThat(ut11::Is::PositiveInfinity(1.0f / 0.0f), ut11::Is::True);
        });

        Then("Is::PositiveInfinity(-Infinity) is False", []() {
            AssertThat(ut11::Is::PositiveInfinity(-1.0f / 0.0f), ut11::Is::False);
        });

        Then("Is::PositiveInfinity is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::PositiveInfinity) >::value, ut11::Is::True);
        });

        Then("Is::PositiveInfinity has an error message", []() {
            AssertThat(ut11::Is::PositiveInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsPositiveInfinityTests);

class IsNotPositiveInfinityTests : public ut11::TestFixture
{
public:
    virtual void Run() {
        Then("Is::Not::PositiveInfinity(0.0f) is Not::False", []() {
            AssertThat(ut11::Is::Not::PositiveInfinity(0.0f), ut11::Is::Not::False);
        });

        Then("Is::Not::PositiveInfinity(+Infinity) is Not::", []() {
            AssertThat(ut11::Is::Not::PositiveInfinity(1.0f / 0.0f), ut11::Is::Not::True);
        });

        Then("Is::Not::PositiveInfinity(-Infinity) is Not::False", []() {
            AssertThat(ut11::Is::Not::PositiveInfinity(-1.0f / 0.0f), ut11::Is::Not::False);
        });

        Then("Is::Not::PositiveInfinity is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::PositiveInfinity) >::value, ut11::Is::True);
        });

        Then("Is::Not::PositiveInfinity has an error message", []() {
            AssertThat(ut11::Is::Not::PositiveInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotPositiveInfinityTests);


class IsNegativeInfinityTests : public ut11::TestFixture
{
public:
    virtual void Run() {
        Then("Is::NegativeInfinity(0.0f) is False", []() {
            AssertThat(ut11::Is::NegativeInfinity(0.0f), ut11::Is::False);
        });

        Then("Is::NegativeInfinity(-Infinity) is True", []() {
            AssertThat(ut11::Is::NegativeInfinity(-1.0f / 0.0f), ut11::Is::True);
        });

        Then("Is::NegativeInfinity(+Infinity) is False", []() {
            AssertThat(ut11::Is::NegativeInfinity(1.0f / 0.0f), ut11::Is::False);
        });

        Then("Is::NegativeInfinity is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::NegativeInfinity) >::value, ut11::Is::True);
        });

        Then("Is::NegativeInfinity has an error message", []() {
            AssertThat(ut11::Is::NegativeInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNegativeInfinityTests);

class IsNotNegativeInfinityTests : public ut11::TestFixture
{
public:
    virtual void Run() {
        Then("Is::Not::NegativeInfinity(0.0f) is Not::False", []() {
            AssertThat(ut11::Is::Not::NegativeInfinity(0.0f), ut11::Is::Not::False);
        });

        Then("Is::Not::NegativeInfinity(-Infinity) is Not::True", []() {
            AssertThat(ut11::Is::Not::NegativeInfinity(-1.0f / 0.0f), ut11::Is::Not::True);
        });

        Then("Is::Not::NegativeInfinity(+Infinity) is Not::False", []() {
            AssertThat(ut11::Is::Not::NegativeInfinity(1.0f / 0.0f), ut11::Is::Not::False);
        });

        Then("Is::Not::NegativeInfinity is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::NegativeInfinity) >::value, ut11::Is::True);
        });

        Then("Is::Not::NegativeInfinity has an error message", []() {
            AssertThat(ut11::Is::Not::NegativeInfinity.GetErrorMessage(0.0f), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotNegativeInfinityTests);
