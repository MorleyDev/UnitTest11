/*
 * OfTests.cpp
 *
 *  Created on: 23 Apr 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

namespace
{
    struct BaseClass { };
    struct ChildClass : public BaseClass { };
}

class IsIterableOfTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("a vector of type int is iterable of int", [&]() {
            AssertThat(ut11::Is::Iterable::Of<int>()(std::vector<int>()), ut11::Is::True);
        });

        Then("a vector of type string is not iterable of int", [&]() {

            AssertThat(ut11::Is::Iterable::Of<int>()(std::vector<std::string>()), ut11::Is::False);
        });

        Then("an int is not iterable of int", [&]() {
            AssertThat(ut11::Is::Iterable::Of<int>()(1), ut11::Is::False);
        });

        Then("a vector of a child is iterable of base class", [&]() {
            AssertThat(ut11::Is::Iterable::Of<BaseClass>()(std::vector<ChildClass>()), ut11::Is::True);
        });

        Then("Is::Iterable::Of<T>() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::Of<int>()) >::value, ut11::Is::True);
        });

        Then("Is::EqualTo has an error message", []() {
            AssertThat(ut11::Is::Iterable::Of<int>().GetErrorMessage(0), ut11::Is::Not::EqualTo(""));
        });

    }
};
DeclareFixture(IsIterableOfTests)(ut11::Category("unit"));

class IsIterableNotOfTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("a vector of type int is iterable of int so false", [&]() {
            AssertThat(ut11::Is::Iterable::Not::Of<int>()(std::vector<int>()), ut11::Is::False);
        });

        Then("an int is not iterable of int so true", [&]() {
            AssertThat(ut11::Is::Iterable::Not::Of<int>()(1), ut11::Is::True);
        });

        Then("a vector of type string not is iterable of int so true", [&]() {
            AssertThat(ut11::Is::Iterable::Not::Of<int>()(std::vector<std::string>()), ut11::Is::True);
        });

        Then("a vector of a child is iterable of base class so false", [&]() {
            AssertThat(ut11::Is::Iterable::Not::Of<BaseClass>()(std::vector<ChildClass>()), ut11::Is::False);
        });

        Then("Is::Iterable::Of<T>() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::Not::Of<int>()) >::value, ut11::Is::True);
        });

        Then("Is::EqualTo has an error message", []() {
            AssertThat(ut11::Is::Iterable::Not::Of<int>().GetErrorMessage(std::vector<int>()), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsIterableNotOfTests)(ut11::Category("unit"));

