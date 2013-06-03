/*
 * IsStringEndingWith.cpp
 *
 *  Created on: 22 Apr 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

class IsStringEndingWithTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("string EndingWith desired string is true", [&]() {
			AssertThat(ut11::Is::String::EndingWith("Hell")("oAvsdaasdagfHell"), ut11::Is::True);
		});

		Then("string equal to desired string is true", [&]() {
			AssertThat(ut11::Is::String::EndingWith("Hell")("Hell"), ut11::Is::True);
		});

		Then("AssertThat using EndingWith works as expected", [&]() {
			AssertThat("Pianos and Pies", ut11::Is::String::EndingWith("Pies"));
		});

		Then("string not EndingWith desired string is false", [&]() {
			AssertThat(ut11::Is::String::EndingWith("Hell")("AvsdaHelloasdagf"), ut11::Is::False);
		});

		Then("string small than desired string is false", [&]() {
			AssertThat(ut11::Is::String::EndingWith("Hell")("He"), ut11::Is::False);
		});

        Then("Is::String::EndingWith is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::String::EndingWith("world")) >::value, ut11::Is::True);
        });

        Then("Is::String::EndingWith has an error message", []() {
            AssertThat(ut11::Is::String::EndingWith("world").GetErrorMessage("piano"), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsStringEndingWithTests)();


class IsNotStringEndingWithTests : public ut11::TestFixture
{
public:
	virtual void Run()
	{
		Then("string not EndingWith desired string is true", [&]() {
			AssertThat(ut11::Is::String::Not::EndingWith("Wor")("AvsdaWoroasdagf"), ut11::Is::True);
		});

		Then("string EndingWith desired string is false", [&]() {
			AssertThat(ut11::Is::String::Not::EndingWith("Wor")("ldWor"), ut11::Is::False);
		});

		Then("AssertThat using Not EndingWith works as expected", [&]() {
			AssertThat("Pianos and Pies", ut11::Is::String::Not::EndingWith("Piano"));
		});

        Then("Is::Not::String::EndingWith is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::String::Not::EndingWith("world")) >::value, ut11::Is::True);
        });

        Then("Is::Not::String::EndingWith has an error message", []() {
            AssertThat(ut11::Is::String::Not::EndingWith("world").GetErrorMessage("world"), ut11::Is::Not::EqualTo(""));
        });
	}
};
DeclareFixture(IsNotStringEndingWithTests)();
