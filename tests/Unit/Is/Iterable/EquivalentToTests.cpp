/*
 * EquivalentToTests.cpp
 *
 *  Created on: 23 Apr 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

class IsIterableEquivalentToTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("a vector and list with same content in the same order are equivalent", []() {
            AssertThat(ut11::Is::Iterable::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({1,2,3,4,5,6,7,8})), ut11::Is::True);
        });

        Then("a vector and list with same content in a different order are equivalent", []() {
            AssertThat(ut11::Is::Iterable::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({7,8,5,1,4,3,2,6})), ut11::Is::True);
        });

        Then("a vector and list with different content are not equivalent", []() {
            AssertThat(ut11::Is::Iterable::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({17,28,35,41})), ut11::Is::False);
        });

        Then("a vector and list with different but overlapping content are not equivalent", []() {
            AssertThat(ut11::Is::Iterable::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({7,8,5,1})), ut11::Is::False);
        });

        Then("a vector and list with different content with same size are not equivalent", []() {
            AssertThat(ut11::Is::Iterable::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({0,1,2,3,4,5,6,7})), ut11::Is::False);
        });

        Then("Is::Iterable::EquivalentTo() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::EquivalentTo(std::vector<int>())) >::value, ut11::Is::True);
        });

        Then("Is::EqualTo has an error message", []() {
            AssertThat(ut11::Is::Iterable::EquivalentTo(std::vector<int>()).GetErrorMessage(0), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsIterableEquivalentToTests)(ut11::Category("unit"));

class IsIterableNotEquivalentToTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("a vector and list with same content in the same order are equivalent", []() {
            AssertThat(ut11::Is::Iterable::Not::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({1,2,3,4,5,6,7,8})), ut11::Is::False);
        });

        Then("a vector and list with same content in a different order are equivalent", []() {
            AssertThat(ut11::Is::Iterable::Not::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({7,8,5,1,4,3,2,6})), ut11::Is::False);
        });

        Then("a vector and list with different content are not equivalent", []() {
            AssertThat(ut11::Is::Iterable::Not::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({17,28,35,41})), ut11::Is::True);
        });

        Then("a vector and list with different but overlapping content are not equivalent", []() {
            AssertThat(ut11::Is::Iterable::Not::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({7,8,5,1})), ut11::Is::True);
        });


        Then("a vector and list with different content with same size are not equivalent", []() {
            AssertThat(ut11::Is::Iterable::Not::EquivalentTo(std::vector<int>({1,2,3,4,5,6,7,8}))(std::list<int>({0,1,2,3,4,5,6,7})), ut11::Is::True);
        });

        Then("Is::Iterable::EquivalentTo() is an operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Iterable::EquivalentTo(std::vector<int>())) >::value, ut11::Is::True);
        });

        Then("Is::EqualTo has an error message", []() {
            AssertThat(ut11::Is::Iterable::EquivalentTo(std::vector<int>()).GetErrorMessage(0), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsIterableNotEquivalentToTests)(ut11::Category("unit"));
