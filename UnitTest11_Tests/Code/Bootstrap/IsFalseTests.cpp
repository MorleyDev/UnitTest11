#include <UnitTest11/Is/False.hpp>
#include <UnitTest++/UnitTest++.h>

TEST(IsFalseSuccessTest)
{
    CHECK( ut11::Is::False(false) );
}

TEST(IsFalseFailsTest)
{
    CHECK( !ut11::Is::False(true) );
}

TEST(IsNotFalseSuccessTest)
{
    CHECK( ut11::Is::Not::False(true) );
}

TEST(IsNotFalseFailsTest)
{
    CHECK( !ut11::Is::Not::False(false) );
}

