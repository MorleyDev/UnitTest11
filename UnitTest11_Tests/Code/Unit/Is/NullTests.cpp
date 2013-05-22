#include <UnitTest11.hpp>

class IsNullTests : public ut11::TestFixtureImpl
{
public:
    virtual void Run()
    {
        Then("Is::Null(nullptr) is True", []() {
            AssertThat(ut11::Is::Null(nullptr), ut11::Is::True);
        });

        Then("Is::Null(std::shared_ptr(nullptr)) is True", []() {
            AssertThat(ut11::Is::Null(std::shared_ptr<void>()), ut11::Is::True);
        });

        Then("Is::Null(std::unique_ptr(nullptr)) is True", []() {
            AssertThat(ut11::Is::Null(std::unique_ptr<int>()), ut11::Is::True);
        });

        Then("Is::Null(weak_ptr(nullptr)) is True", []() {

            AssertThat(ut11::Is::Null(std::weak_ptr<int>()), ut11::Is::True);
        });
        Then("Is::Null(pointer) is False", []() {
            int value;
            AssertThat(ut11::Is::Null(&value), ut11::Is::False);
        });

        Then("Is::Null(shared_ptr(pointer)) is False", []() {
            AssertThat(ut11::Is::Null(std::make_shared<int>(10)), ut11::Is::False);
        });

        Then("Is::Null(unique_ptr(pointer)) is False", []() {
            std::unique_ptr<int> ptr(new int(5));
            AssertThat(ut11::Is::Null(ptr), ut11::Is::False);
        });

        Then("Is::Null(weak_ptr(pointer)) is False", []() {

            auto ptr = std::make_shared<int>(10);
            AssertThat(ut11::Is::Null(std::weak_ptr<int>(ptr)), ut11::Is::False);
        });

        Then("Is::Null(weak_ptr(dead pointer)) is True", []() {

            auto ptr = std::make_shared<int>(10);
            std::weak_ptr<int> weakptr(ptr);
            ptr = std::shared_ptr<int>();

            AssertThat(ut11::Is::Null(weakptr), ut11::Is::True);
        });

        Then("Is::Null is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Null) >::value, ut11::Is::True);
        });

        Then("Is::Null has an error message", []() {
            std::unique_ptr<int> ptr(new int(5));
            AssertThat(ut11::Is::Null.GetErrorMessage(ptr.get()), ut11::Is::Not::EqualTo(""));
        });
    }
};
DeclareFixture(IsNullTests);

class IsNotNullTests : public ut11::TestFixtureImpl
{
public:
    virtual void Run()
    {
        Then("Is::Not::Null(nullptr) is Not::True", []() {
            AssertThat(ut11::Is::Not::Null(nullptr), ut11::Is::Not::True);
        });

        Then("Is::Not::Null(std::shared_ptr(nullptr)) is Not::True", []() {
            AssertThat(ut11::Is::Not::Null(std::shared_ptr<void>()), ut11::Is::Not::True);
        });

        Then("Is::Not::Null(std::unique_ptr(nullptr)) is Not::True", []() {
            AssertThat(ut11::Is::Not::Null(std::unique_ptr<int>()), ut11::Is::Not::True);
        });

        Then("Is::Not::Null(weak_ptr(nullptr)) is Not::True", []() {

            AssertThat(ut11::Is::Not::Null(std::weak_ptr<int>()), ut11::Is::Not::True);
        });
        Then("Is::Not::Null(pointer) is Not::False", []() {
            int value;
            AssertThat(ut11::Is::Not::Null(&value), ut11::Is::Not::False);
        });

        Then("Is::Not::Null(shared_ptr(pointer)) is Not::False", []() {
            AssertThat(ut11::Is::Not::Null(std::make_shared<int>(10)), ut11::Is::Not::False);
        });

        Then("Is::Not::Null(unique_ptr(pointer)) is Not::False", []() {
            std::unique_ptr<int> ptr(new int(5));
            AssertThat(ut11::Is::Not::Null(ptr), ut11::Is::Not::False);
        });

        Then("Is::Not::Null(weak_ptr(pointer)) is Not::False", []() {

            auto ptr = std::make_shared<int>(10);
            AssertThat(ut11::Is::Not::Null(std::weak_ptr<int>(ptr)), ut11::Is::Not::False);
        });

        Then("Is::Not::Null(weak_ptr(dead pointer)) is Not::True", []() {

            auto ptr = std::make_shared<int>(10);
            std::weak_ptr<int> weakptr(ptr);
            ptr = std::shared_ptr<int>();

            AssertThat(ut11::Is::Not::Null(weakptr), ut11::Is::Not::True);
        });

        Then("Is::Not::Null is Operand", []() {
            AssertThat(ut11::Utility::IsOperand< decltype(ut11::Is::Not::Null) >::value, ut11::Is::True);
        });

        Then("Is::Not::Null has an error message", []() {
            AssertThat(ut11::Is::Not::Null.GetErrorMessage(static_cast<void*>(nullptr)), ut11::Is::Not::EqualTo(""));
        });

    }
};
DeclareFixture(IsNotNullTests);
