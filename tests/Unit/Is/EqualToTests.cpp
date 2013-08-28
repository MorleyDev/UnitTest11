#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/EqualTo.hpp>

class IsEqualToTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::EqualTo succeeds", []() {
            AssertThat(ut11::Is::EqualTo(7)(7), ut11::Is::True);
        });

        Then("Is::EqualTo fails", []() {
            AssertThat(ut11::Is::EqualTo(7)(15), ut11::Is::Not::True);
        });

        Then("Is::EqualTo is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::EqualTo(7)) >::value, ut11::Is::True);
        });

        Then("Is::EqualTo has an error message", []() {
            AssertThat(ut11::Is::EqualTo(false).GetErrorMessage(true), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsEqualToTests)(ut11::Category("unit"));

class IsNotEqualToTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Not::EqualTo fails", []() {
            AssertThat(ut11::Is::Not::EqualTo(7)(25), ut11::Is::True);
        });

        Then("Is::Not::EqualTo succeeds", []() {
            AssertThat(ut11::Is::Not::EqualTo(15)(15), ut11::Is::Not::True);
        });

        Then("Is::Not::EqualTo is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::EqualTo(7)) >::value, ut11::Is::True);
        });

        Then("Is::Not::EqualTo has an error message", []() {
            AssertThat(ut11::Is::Not::EqualTo(true).GetErrorMessage(true), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotEqualToTests)(ut11::Category("unit"));

class IsEqualToIterableTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::EqualTo equal iterables succeeds", []() {
			AssertThat(ut11::Is::EqualTo(std::vector<int>({ 1, 2, 3 }))(std::vector<int>({ 1, 2, 3 })), ut11::Is::True);
		});

		Then("Is::EqualTo not equal iterable fails", []() {
			AssertThat(ut11::Is::EqualTo(std::vector<int>({ 1, 2, 7 }))(std::vector<int>({ 12, 2, 15 })), ut11::Is::Not::True);
		});

		Then("Is::EqualTo iterable is an operand", []() {
			AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::EqualTo(std::vector<int>({ 1, 2, 3 }))) >::value, ut11::Is::True);
		});

		Then("Is::EqualTo not equal iterable has an error message", []() {
			AssertThat(ut11::Is::EqualTo(std::vector<int>({ 1, 2, 3 })).GetErrorMessage(std::vector<int>({ 3, 2, 1 })), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsEqualToIterableTests)(ut11::Category("unit"));

class IsNotEqualToIterableTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("Is::Not::EqualTo equal iterables fails", []() {
			AssertThat(ut11::Is::Not::EqualTo(std::vector<int>({ 1, 2, 3 }))(std::vector<int>({ 1, 2, 3 })), ut11::Is::Not::True);
		});

		Then("Is::Not::EqualTo not equal iterable succeeds", []() {
			AssertThat(ut11::Is::Not::EqualTo(std::vector<int>({ 1, 2, 7 }))(std::vector<int>({ 12, 2, 15 })), ut11::Is::True);
		});

		Then("Is::Not::EqualTo iterable is an operand", []() {
			AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::EqualTo(std::vector<int>({ 1, 2, 3 }))) >::value, ut11::Is::True);
		});

		Then("Is::Not::EqualTo not equal iterable has an error message", []() {
			AssertThat(ut11::Is::Not::EqualTo(std::vector<int>({ 1, 2, 3 })).GetErrorMessage(std::vector<int>({ 3, 2, 1 })), ut11::Is::Not::EqualTo(""));
		});
	}
};
DeclareFixture(IsNotEqualToIterableTests)(ut11::Category("unit"));
