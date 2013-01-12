#include <UnitTest11/Will/Throw.hpp>

#include <UnitTest++/UnitTest++.h>

TEST(WillThrowSuccessTest)
{
    CHECK(ut11::Will::Throw<int>()([]() { throw 5; }));
}

TEST(WillThrowFailsWithUnknownExceptionTest)
{
    auto function = []() { throw "std::bad_exception()"; };
    auto thrower = ut11::Will::Throw<int>();
    CHECK(!thrower(function));

    std::stringstream stream;
    stream << "Expected " << typeid(int).name() << " to be thrown, but an unknown exception was thrown instead";

    std::string expectedErrorMessage = stream.str();
    CHECK_EQUAL(expectedErrorMessage, thrower.GetErrorMessage(function));
}

TEST(WillThrowFailsWithStdExceptionTest)
{
    auto function = []() { throw std::bad_exception(); };
    auto thrower = ut11::Will::Throw<int>();
    CHECK(!thrower(function));

    std::stringstream stream;
    stream << "Expected " << typeid(int).name() << " to be thrown, but std::exception was thrown instead (what: " << std::bad_exception().what() << ")";

    std::string expectedErrorMessage = stream.str();
    CHECK_EQUAL(expectedErrorMessage, thrower.GetErrorMessage(function));
}


TEST(WillThrowFailsNoExceptionTest)
{
    auto function = []() { };
    auto thrower = ut11::Will::Throw<int>();
    CHECK(!thrower(function));

    std::stringstream stream;
    stream << "Expected " << typeid(int).name() << " to be thrown, but no exception was thrown";

    std::string expectedErrorMessage = stream.str();
    CHECK_EQUAL(expectedErrorMessage, thrower.GetErrorMessage(function));
}

TEST(WillThrowIsOperand)
{
    CHECK( ut11::Utility::IsOperand <ut11::Operands::WillThrow<int> >::value );
}

