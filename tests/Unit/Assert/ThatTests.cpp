#include <UnitTest11.hpp>
#include <string>

template<bool Succeeds, typename U>
struct TestOperand : public ut11::Utility::BaseOperand<TestOperand<Succeeds,U>>
{
private:
    std::string m_expectedErrorMessage;
    U m_expectedValue;

public:
    TestOperand(std::string expectedErrorCode, U expectedValue)
        : m_expectedErrorMessage(expectedErrorCode),
          m_expectedValue(expectedValue)
    {
    }

    template<typename T> inline bool operator()(const T& actual) const
    {
        AssertThat(actual, ut11::Is::EqualTo(m_expectedValue));
        return Succeeds;
    }

    template<typename T> inline std::string GetErrorMessage(const T& actual) const
    {
        AssertThat(actual, ut11::Is::EqualTo(m_expectedValue));
        return m_expectedErrorMessage;
    }
};

class AssertThatTests : public ut11::TestFixture
{
private:
    std::size_t line;
    std::string file;
    std::string message;
    int expectedValue;

    ut11::TestFailedException caughtException;

public:
    virtual void Run()
    {
        Given("a line, file, message and expected value", [&]()
        {
            caughtException = ut11::TestFailedException();

            line = 132;
            file = "some file";
            message = "some message";
            expectedValue = 5;
        });
        When("calling assert that against the test operand that returns false", [&]()
        {
            try
            {
                ut11::Assert::That(line, file, expectedValue, TestOperand<false, int>(message, expectedValue));
            }
            catch(const ut11::TestFailedException& ex)
            {
                caughtException = ex;
            }
        });
        Then("the expected test failed exception was thrown with the expected line", [&]()
        {
            AssertThat(caughtException.GetLine(), ut11::Is::EqualTo(line));
        });
        Then("the expected test failed exception was thrown with the expected file", [&]()
        {
            AssertThat(caughtException.GetFile(), ut11::Is::EqualTo(file));
        });
        Then("the expected test failed exception was thrown with the expected message", [&]()
        {
            AssertThat(caughtException.GetMessage(), ut11::Is::EqualTo(message));
        });
        Then("calling assert that against the test operand that returns true does nothing", [&]()
        {
            ut11::Assert::That(line, file, expectedValue, TestOperand<true, int>(message, expectedValue));
        });
        When("calling assert with a custom message that against the test operand that returns false", [&]()
        {
            try
            {
                ut11::Assert::That(line, file, message, expectedValue, TestOperand<false, int>("other message", expectedValue));
            }
            catch(const ut11::TestFailedException& ex)
            {
                caughtException = ex;
            }
        });
        Then("the expected test failed exception was thrown with the expected line", [&]()
        {
            AssertThat(caughtException.GetLine(), ut11::Is::EqualTo(line));
        });
        Then("the expected test failed exception was thrown with the expected file", [&]()
        {
            AssertThat(caughtException.GetFile(), ut11::Is::EqualTo(file));
        });
        Then("the expected test failed exception was thrown with the expected message", [&]()
        {
            AssertThat(caughtException.GetMessage(), ut11::Is::EqualTo(message));
        });
        Then("calling assert that against the test operand that returns true with a custom message does nothing", [&]()
        {
            ut11::Assert::That(line, file, expectedValue, TestOperand<true, int>("other not message", expectedValue));
        });

    }
};
DeclareFixture(AssertThatTests)(ut11::Category("unit"));
