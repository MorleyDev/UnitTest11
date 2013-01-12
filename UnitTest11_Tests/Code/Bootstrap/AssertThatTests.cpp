#include <UnitTest11/Assert/That.hpp>
#include <UnitTest11/TestFailedException.hpp>
#include <UnitTest11/Utility/BaseOperand.hpp>
#include <UnitTest++/UnitTest++.h>
#include <string>

template<bool Succeeds, typename U>
struct TestOperand : public ut11::Utility::BaseOperand
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
        CHECK_EQUAL(m_expectedValue, actual);
        return Succeeds;
    }

    template<typename T> inline std::string GetErrorMessage(const T& actual) const
    {
        CHECK_EQUAL(m_expectedValue, actual);
        return m_expectedErrorMessage;
    }
};

TEST(AssertThatFailsTest)
{
    std::size_t line = 132;
    std::string file = "some file";
    std::string message = "some message";

    int expectedValue = 5;

    try
    {
        ut11::Assert::That(line, file, expectedValue, TestOperand<false, int>(message, expectedValue));
    }
    catch(const ut11::TestFailedException& ex)
    {
        CHECK_EQUAL(line, ex.getLine());
        CHECK_EQUAL(file, ex.getFile());
        CHECK_EQUAL(message, ex.getMessage());
        return;
    }

    CHECK(false);
}

TEST(AssertThatSucceedsWithCustomMessageTest)
{
    std::size_t line = 132;
    std::string file = "some file";
    std::string message = "some message";

    char expectedValue = 'A';

    ut11::Assert::That(line, file, expectedValue, TestOperand<true, char>(message, expectedValue));
}

TEST(AssertThatFailsWithCustomMessageTest)
{
    std::size_t line = 132;
    std::string file = "some file";
    std::string message = "some message";

    int expectedValue = 5;

    try
    {
        ut11::Assert::That(line, file, message, expectedValue, TestOperand<false, int>("not the message", expectedValue));
    }
    catch(const ut11::TestFailedException& ex)
    {
        CHECK_EQUAL(line, ex.getLine());
        CHECK_EQUAL(file, ex.getFile());
        CHECK_EQUAL(message, ex.getMessage());
        return;
    }

    CHECK(false);
}

TEST(AssertThatSucceedsTest)
{
    std::size_t line = 132;
    std::string file = "some file";
    std::string message = "some message";

    char expectedValue = 'A';

    ut11::Assert::That(line, file, message, expectedValue, TestOperand<true, char>("not the message", expectedValue));
}




