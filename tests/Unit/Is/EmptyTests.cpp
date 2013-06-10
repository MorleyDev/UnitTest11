/*
 * EmptyTests.cpp
 *
 *  Created on: 27 Apr 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

class IsEmptyTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("an empty string is empty", []() {
            AssertThat(ut11::Is::Empty(""), ut11::Is::True);
            AssertThat(ut11::Is::Empty(std::string("")), ut11::Is::True);
        });
        Then("an empty vector is empty", []() {
            AssertThat(ut11::Is::Empty(std::vector<int>()), ut11::Is::True);
        });

        Then("a string with content is not empty", []() {
            AssertThat(ut11::Is::Empty("String With Content"), ut11::Is::False);
            AssertThat(ut11::Is::Empty(std::string("String With Content")), ut11::Is::False);
        });
        Then("an empty vector is empty", []() {
            AssertThat(ut11::Is::Empty(std::vector<int>({1,2,3})), ut11::Is::False);
        });

        Then("Is::Empty is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Empty) >::value, ut11::Is::True);
        });

        Then("Is::Empty has an error message", []() {
            AssertThat(ut11::Is::Empty.GetErrorMessage("12"), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsEmptyTests)(ut11::Category("unit"));

class IsNotEmptyTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("an empty string is empty", []() {
            AssertThat(ut11::Is::Not::Empty(""), ut11::Is::False);
            AssertThat(ut11::Is::Not::Empty(std::string("")), ut11::Is::False);
        });
        Then("an empty vector is empty", []() {
            AssertThat(ut11::Is::Not::Empty(std::vector<int>()), ut11::Is::False);
        });

        Then("a string with content is not empty", []() {
            AssertThat(ut11::Is::Not::Empty("String With Content"), ut11::Is::True);
            AssertThat(ut11::Is::Not::Empty(std::string("String With Content")), ut11::Is::True);
        });
        Then("an empty vector is empty", []() {
            AssertThat(ut11::Is::Not::Empty(std::vector<int>({1,2,3})), ut11::Is::True);
        });

        Then("Is::Empty is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::Empty) >::value, ut11::Is::True);
        });

        Then("Is::Empty has an error message", []() {
            AssertThat(ut11::Is::Not::Empty.GetErrorMessage(""), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotEmptyTests)(ut11::Category("unit"));
