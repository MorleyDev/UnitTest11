#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest++/UnitTest++.h>
#include <string>

TEST(IsEqualToSucceedsTest)
{
    CHECK(ut11::Is::EqualTo(5)(5));
}

TEST(IsEqualToFailsTest)
{
    CHECK(!ut11::Is::EqualTo(5)(10));
}

TEST(IsEqualToErrorMessageTest)
{
    std::string expectedError = "Expected 10 but was 5";
    CHECK_EQUAL(expectedError, ut11::Is::EqualTo(10).GetErrorMessage(5));
}

TEST(OperandsEqualToIsOperand)
{
    CHECK( ut11::Utility::IsOperand< ut11::Operands::EqualTo<int> >::value );
}
