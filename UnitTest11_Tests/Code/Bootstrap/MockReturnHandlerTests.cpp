#include <UnitTest11/Utility/MockReturnHandler.hpp>
#include <UnitTest11/Utility/DefaultValue.hpp>
#include <UnitTest++/UnitTest++.h>

namespace ut11 { namespace Utility { template<> struct DefaultValue<int> { inline int operator()() const { return 8; } }; } }

TEST(DefaultValueReturnsDefaultTest)
{
    ut11::Utility::DefaultValue<int> functor;
    int expectedValue = functor.operator ()();
    char expectedArgument = 'A';

    ut11::Utility::MockReturnHandler<int, char> returner;

    CHECK_EQUAL(expectedValue, returner.operator ()(expectedArgument));
}

TEST(MockReturnHandlerSetValueReturnsExpectedTest)
{
    int expectedValue = 12;
    char expectedArgument = 'A';

    ut11::Utility::MockReturnHandler<int, char> returner;
    returner.setReturn(expectedValue);

    CHECK_EQUAL(expectedValue, returner.operator ()(expectedArgument));
}

TEST(MockReturnHandlerSetCallbackReturnsExpectedTest)
{
    int expectedValue = 12;
    char expectedArgument = 'A';

    ut11::Utility::MockReturnHandler<int, char> returner;
    returner.setReturn([&](char actualArgument)
    {
        CHECK_EQUAL(expectedArgument, actualArgument);
        return expectedValue;
    });

    CHECK_EQUAL(expectedValue, returner.operator ()(expectedArgument));
}

TEST(MockReturnHandlerSetCallbackOverridesSetReturnsTest)
{
    int expectedValue = 12;
    char expectedArgument = 'A';

    ut11::Utility::MockReturnHandler<int, char> returner;
    returner.setReturn(85);
    returner.setReturn([&](char actualArgument)
    {
        CHECK_EQUAL(expectedArgument, actualArgument);
        return expectedValue;
    });

    CHECK_EQUAL(expectedValue, returner.operator ()(expectedArgument));
}

TEST(MockReturnHandlerSetReturnOverridesSetCallbackTest)
{
    int expectedValue = 12;
    char expectedArgument = 'A';

    ut11::Utility::MockReturnHandler<int, char> returner;
    returner.setReturn([&](char actualArgument)
    {
        CHECK_EQUAL(expectedArgument, actualArgument);
        return 96;
    });
    returner.setReturn(expectedValue);

    CHECK_EQUAL(expectedValue, returner.operator ()(expectedArgument));
}
