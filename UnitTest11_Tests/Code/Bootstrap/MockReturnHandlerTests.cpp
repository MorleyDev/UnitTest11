#include <UnitTest11/Utility/MockReturnHandler.hpp>
#include <UnitTest11/Utility/DefaultValue.hpp>
#include <UnitTest++/UnitTest++.h>

TEST(DefaultValueReturnsDefaultTest)
{
    int expectedValue = ut11::Utility::DefaultValue<int>()();
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
