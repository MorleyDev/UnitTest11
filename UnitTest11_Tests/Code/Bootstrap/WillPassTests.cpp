#include <UnitTest11/Will/Pass.hpp>

#include <UnitTest++/UnitTest++.h>

TEST(WillPassCallsThePredicate)
{
    int expected = 10;
    CHECK( ut11::Will::Pass([=](int actual) { CHECK_EQUAL(expected, actual); return true; })(expected) );
    CHECK( !ut11::Will::Pass([=](int actual) { CHECK_EQUAL(expected, actual); return false; })(expected) );
}

TEST(OperandsWillPassIsOperand)
{
    CHECK( ut11::Utility::IsOperand< ut11::Operands::WillPass<int> >::value );
}

TEST(WillNotPassCallsThePredicate)
{
    int expected = 10;
    CHECK( !ut11::Will::Not::Pass([=](int actual) { CHECK_EQUAL(expected, actual); return true; })(expected) );
    CHECK( ut11::Will::Not::Pass([=](int actual) { CHECK_EQUAL(expected, actual); return false; })(expected) );
}

TEST(OperandsWillNotPassIsOperand)
{
    CHECK( ut11::Utility::IsOperand<ut11::Utility::NotOperand<ut11::Operands::WillPass<int>>>::value );
}
