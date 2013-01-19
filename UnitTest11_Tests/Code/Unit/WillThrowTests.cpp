#include <UnitTest11.hpp>

class WillThrowTests : public ut11::TestFixture
{
private:
    bool m_result;
    std::string m_errorMessage;

public:
    virtual void Run()
    {
        Then("Will::Throw is an Operand", []() {

            AssertThat(ut11::Utility::IsOperand<decltype(ut11::Will::Throw<int>())>::value, ut11::Is::True);
        });

        Then("Will::Throw when throwing an int is true", []() {

            AssertThat(ut11::Will::Throw<int>()([]() { throw 5; }), ut11::Is::True);
        });

        When("Will::Throw with unknown exception", [&]() {

            auto willThrow = ut11::Will::Throw<int>();

            m_result = willThrow([](){ throw "std::bad_exception()"; });
            m_errorMessage = willThrow.getErrorMessage([](){ });
        });

        Then("the result is as expected", [&]() {

            AssertThat(m_result, ut11::Is::False);
        });

        Then("the error message is as expected", [&]() {

            std::stringstream stream;
            stream << "Expected " << typeid(int).name() << " to be thrown, but an unknown exception was thrown instead";

            AssertThat(m_errorMessage, ut11::Is::EqualTo(stream.str()));
        });

        When("Will::Throw with unexpected exception thrown", [&]() {

            auto willThrow = ut11::Will::Throw<int>();

            m_result = willThrow([](){ throw std::bad_exception(); });
            m_errorMessage = willThrow.getErrorMessage([](){ });
        });

        Then("the result is as expected", [&]() {

            AssertThat(m_result, ut11::Is::False);
        });

        Then("the error message is as expected", [&]() {

            std::stringstream stream;
            stream << "Expected " << typeid(int).name() << " to be thrown, but std::exception was thrown instead (what: " << std::bad_exception().what() << ")";

            AssertThat(m_errorMessage, ut11::Is::EqualTo(stream.str()));
        });

        When("Will::Throw with no exception thrown", [&]() {

            auto willThrow = ut11::Will::Throw<int>();

            m_result = willThrow([](){ });
            m_errorMessage = willThrow.getErrorMessage([](){ });
        });

        Then("the result is as expected", [&]() {

            AssertThat(m_result, ut11::Is::False);
        });

        Then("the error message is as expected", [&]() {

            std::stringstream stream;
            stream << "Expected " << typeid(int).name() << " to be thrown, but no exception was thrown";

            AssertThat(m_errorMessage, ut11::Is::EqualTo(stream.str()));
        });
    }
};
DeclareFixture(WillThrowTests);