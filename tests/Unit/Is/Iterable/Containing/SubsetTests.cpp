/*
 * SubsetTests.cpp
 *
 *  Created on: 28 Apr 2013
 *      Author: Jason
 */

#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/True.hpp>
#include <UnitTest11/Is/False.hpp>
#include <UnitTest11/Is/Empty.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/Iterable/Containing/Subset.hpp>

class IsIterableContainingSubsetTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("a vector containing the passed subset is true", []() {
            AssertThat(ut11::Is::Iterable::Containing::Subset(std::vector<int>({4,2}))(std::vector<int>({1,2,3,4,5})), ut11::Is::True);
        });

        Then("a vector containing an equivalent set of the passed set is true", []() {
            AssertThat(ut11::Is::Iterable::Containing::Subset(std::vector<int>({1,2,3,4,5}))(std::vector<int>({1,2,3,4,5})), ut11::Is::True);
        });

        Then("a vector containing a subset of the passed set is false", []() {
            AssertThat(ut11::Is::Iterable::Containing::Subset(std::vector<int>({1,2,3,4,5,6}))(std::vector<int>({1,2,3,4,5})), ut11::Is::False);
        });

        Then("a vector not containing the passed subset is false", []() {
            AssertThat(ut11::Is::Iterable::Containing::Subset(std::vector<int>({4,8}))(std::vector<int>({1,2,3,4,5})), ut11::Is::False);
        });

        Then("Is::Iterable::Containing::Subset() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::Containing::Subset(5)) >::value, ut11::Is::True);
        });

        Then("Is::Iterable::Containing::Subset() has an error message", []() {
            AssertThat(ut11::Is::Iterable::Containing::Subset(5).GetErrorMessage(std::vector<int>()), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsIterableContainingSubsetTests)(ut11::Category("unit"));

class IsIterableNotContainingSubsetTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("a vector containing the passed int is not true", []() {
            AssertThat(ut11::Is::Iterable::Not::Containing::Subset(std::vector<int>({4,2}))(std::vector<int>({1,2,3,4,5})), ut11::Is::Not::True);
        });

        Then("a vector containing an equivalent set of the passed set is not true", []() {
            AssertThat(ut11::Is::Iterable::Not::Containing::Subset(std::vector<int>({1,2,3,4,5}))(std::vector<int>({1,2,3,4,5})), ut11::Is::Not::True);
        });

        Then("a vector not containing the passed int is not false", []() {
            AssertThat(ut11::Is::Iterable::Not::Containing::Subset(std::vector<int>({4,8}))(std::vector<int>({1,2,3,4,5})), ut11::Is::Not::False);
        });

        Then("a vector containing a subset of the passed set is not false", []() {
            AssertThat(ut11::Is::Iterable::Not::Containing::Subset(std::vector<int>({1,2,3,4,5,6}))(std::vector<int>({1,2,3,4,5})), ut11::Is::Not::False);
        });

        Then("Is::Iterable::Containing::Subset() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::Not::Containing::Subset(5)) >::value, ut11::Is::True);
        });

        Then("Is::Iterable::Containing::Subset() has an error message", []() {
            AssertThat(ut11::Is::Iterable::Not::Containing::Subset(5).GetErrorMessage(std::vector<int>()), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsIterableNotContainingSubsetTests)(ut11::Category("unit"));
