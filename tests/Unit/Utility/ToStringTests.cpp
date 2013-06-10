/*
 * ToStringTests.cpp
 *
 *  Created on: 25 May 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

class ToStringTests : public ut11::TestFixture
{
public:
    virtual void Run() {

        Then("ToString a string returns the string", []() {
            AssertThat(ut11::Utility::ToString(std::string("string")), ut11::Is::EqualTo("string"));
        });
        Then("ToString an integer returns the string of that integer", []() {
            AssertThat(ut11::Utility::ToString(1), ut11::Is::EqualTo("1"));
        });
        Then("ToString an iterable returns the string of the set of data in that iterable", []() {
            AssertThat(ut11::Utility::ToString(std::vector<int>({1,2,3,4,5})), ut11::Is::EqualTo("{ 1 2 3 4 5 }"));
        });

        Then("ToString a pointer returns value of the value pointed to", []() {
            std::unique_ptr<int> ptr(new int(5));
            AssertThat(ut11::Utility::ToString(ptr.get()), ut11::Is::EqualTo("pointer:5"));
        });
        Then("ToString a void pointer returns the address of that pointer", []() {
            std::unique_ptr<int> ptr(new int(5));
            std::stringstream ptrString; ptrString << ptr.get();

            AssertThat(ut11::Utility::ToString(static_cast<void*>(ptr.get())), ut11::Is::EqualTo(std::string("void_pointer:") + ptrString.str()));
        });

        Then("ToString a unique pointer returns value of the value pointed to", []() {
            std::unique_ptr<int> ptr(new int(5));

            AssertThat(ut11::Utility::ToString(ptr), ut11::Is::EqualTo("unique_ptr:5"));
        });

        Then("ToString a shared pointer returns value of the value pointed to", []() {
            std::shared_ptr<int> ptr(new int(5));

            AssertThat(ut11::Utility::ToString(ptr), ut11::Is::EqualTo("shared_ptr:5"));
        });
        Then("ToString a shared void pointer returns the address of that pointer", []() {
            std::shared_ptr<int> ptr(new int(5));
            std::stringstream ptrString; ptrString << ptr.get();

            AssertThat(ut11::Utility::ToString(std::static_pointer_cast<void>(ptr)), ut11::Is::EqualTo(std::string("shared_ptr<void>:") + ptrString.str()));
        });
        Then("ToString a non-stream-writable object returns the name of that object's class", []() {

            struct NotStreamWritable { };

            std::stringstream className;
            className << "[" << typeid(NotStreamWritable).name() << "]";

            AssertThat(ut11::Utility::ToString(NotStreamWritable()), ut11::Is::EqualTo(className.str()));
        });
    }
};
DeclareFixture(ToStringTests)(ut11::Category("unit"));
