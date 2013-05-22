#include <UnitTest11.hpp>

class Class { };
class DifferentClass { };

class Base { };
class Derived : public Base { };

class IsAnyTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Any<int>() when given an int is true", []() {

            int value(5);
            AssertThat(ut11::Is::Any<int>()(value), ut11::Is::True);
        });

        Then("Is::Any<int>() when given an implicitally castable type is true", []() {

            std::size_t value(5);
            AssertThat(ut11::Is::Any<int>()(value), ut11::Is::True);
        });

        Then("Is::Any<int>() when given a non-implicitally castable type is false", []() {

            std::string value("hkdskhkja");
            AssertThat(ut11::Is::Any<int>()(value), ut11::Is::False);
        });

        Then("Is::Any<Class>() when given the same class is true", []() {

            Class value;
            AssertThat(ut11::Is::Any<Class>()(value), ut11::Is::True);
        });

        Then("Is::Any<Class>() when given a different class is false", []() {

            DifferentClass value;
            AssertThat(ut11::Is::Any<Class>()(value), ut11::Is::False);
        });

        Then("Is::Any<Base>() when given a class that inherits from Base is true", []() {

            Derived value;
            AssertThat(ut11::Is::Any<Base>()(value), ut11::Is::True);
        });

        Then("Is::Any<Class>() is operand", []() {

            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Any<Class>()) >::value, ut11::Is::True);
        });

        Then("Is::Any<Class> has an error message", []() {

            DifferentClass value;
            AssertThat(ut11::Is::Any<Class>().GetErrorMessage(value), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsAnyTests);

class IsNotAnyTests : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("Is::Not::Any<int>() when given an int is false", []() {

            int value(5);
            AssertThat(ut11::Is::Not::Any<int>()(value), ut11::Is::False);
        });

        Then("Is::Not::Any<int>() when given an implicitally castable type is false", []() {

            std::size_t value(5);
            AssertThat(ut11::Is::Not::Any<int>()(value), ut11::Is::False);
        });

        Then("Is::Not::Any<int>() when given a non-implicitally castable type is true", []() {

            std::string value("hkdskhkja");
            AssertThat(ut11::Is::Not::Any<int>()(value), ut11::Is::True);
        });

        Then("Is::Not::Any<Class>() when given the same class is false", []() {

            Class value;
            AssertThat(ut11::Is::Not::Any<Class>()(value), ut11::Is::False);
        });

        Then("Is::Not::Any<Class>() when given a different class is true", []() {

            DifferentClass value;
            AssertThat(ut11::Is::Not::Any<Class>()(value), ut11::Is::True);
        });

        Then("Is::Not::Any<Base>() when given a class that inherits from Base is false", []() {

            Derived value;
            AssertThat(ut11::Is::Not::Any<Base>()(value), ut11::Is::False);
        });

        Then("Is::Not::Any<Class>() is operand", []() {

            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::Any<Class>()) >::value, ut11::Is::True);
        });

        Then("Is::Not::Any<Class> has an error message", []() {

            Derived value;
            AssertThat(ut11::Is::Not::Any<Class>().GetErrorMessage(value), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNotAnyTests);
