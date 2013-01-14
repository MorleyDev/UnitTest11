#include <UnitTest11/Is/True.hpp>
#include <UnitTest++/UnitTest++.h>

TEST(IsTrueSuccessTest)
{
    CHECK( ut11::Is::True(true) );
}

TEST(IsTrueFailsTest)
{
    CHECK( !ut11::Is::True(false) );
}

TEST(IsNotTrueSuccessTest)
{
    CHECK( !ut11::Is::Not::True(true) );
}

TEST(IsNotTrueFailsTest)
{
    CHECK( ut11::Is::Not::True(false) );
}
