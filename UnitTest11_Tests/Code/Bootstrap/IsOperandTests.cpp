#include <UnitTest11/Utility/BaseOperand.hpp>
#include <UnitTest++/UnitTest++.h>

struct Operand : public ut11::Utility::BaseOperand { };

TEST(IsOperandTest)
{
    CHECK( ut11::Utility::IsOperand<Operand>::value );
}

TEST(IsNotOperandTest)
{
    CHECK( !ut11::Utility::IsOperand<int>::value );
}

