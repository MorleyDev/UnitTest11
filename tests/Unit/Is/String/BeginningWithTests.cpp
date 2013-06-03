/*
 * IsStringBeginningWith.cpp
 *
 *  Created on: 22 Apr 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

class IsStringBeginningWithTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("string BeginningWith desired string is true", [&]() {
			AssertThat(ut11::Is::String::BeginningWith("Hell")("HelloAvsdaasdagf"), ut11::Is::True);
		});

		Then("AssertThat using BeginningWith works as expected", [&]() {
			AssertThat("Pianos and Pies", ut11::Is::String::BeginningWith("Pianos"));
		});

		Then("string not BeginningWith desired string is false", [&]() {
			AssertThat(ut11::Is::String::BeginningWith("Hell")("AvsdaHelloasdagf"), ut11::Is::False);
		});

		Then("string smaller than the desired string is false", [&]() {
			AssertThat(ut11::Is::String::BeginningWith("Hell")("He"), ut11::Is::False);
		});

        Then("Is::String::BeginningWith is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::String::BeginningWith("world")) >::value, ut11::Is::True);
        });

        Then("Is::String::BeginningWith has an error message", []() {
            AssertThat(ut11::Is::String::BeginningWith("world").GetErrorMessage("piano"), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsStringBeginningWithTests)();


class IsNotStringBeginningWithTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("string not BeginningWith desired string is true", [&]() {
			AssertThat(ut11::Is::String::Not::BeginningWith("Wor")("AvsdaWoroasdagf"), ut11::Is::True);
		});

		Then("string BeginningWith desired string is false", [&]() {
			AssertThat(ut11::Is::String::Not::BeginningWith("Wor")("World"), ut11::Is::False);
		});

		Then("AssertThat using Not BeginningWith works as expected", [&]() {
			AssertThat("Pianos and Pies", ut11::Is::String::Not::BeginningWith("Pies"));
		});

        Then("Is::Not::String::BeginningWith is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::String::Not::BeginningWith("world")) >::value, ut11::Is::True);
        });

        Then("Is::Not::String::BeginningWith has an error message", []() {
            AssertThat(ut11::Is::String::Not::BeginningWith("world").GetErrorMessage("world"), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsNotStringBeginningWithTests)();
