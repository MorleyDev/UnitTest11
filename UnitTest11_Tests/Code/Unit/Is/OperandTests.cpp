#include <UnitTest11.hpp>

struct Operand : public ut11::Utility::BaseOperand { };

class IsOperandTests : public ut11::TestFixtureImpl
{
public:
    virtual void Run()
    {
        Then("IsOperand<Operand>::value is true", []() {
            AssertThat(ut11::Utility::IsOperand<Operand>::value, ut11::Is::True);
        });

        Then("IsOperand<int>::value is false", []() {
            AssertThat(ut11::Utility::IsOperand<int>::value, ut11::Is::False);
        });

        Then("IsOperand< NotOperand<Operand> >::value is true", []() {
            AssertThat(ut11::Utility::IsOperand< ut11::Utility::NotOperand<Operand> >::value, ut11::Is::True);
        });
    }
};
DeclareFixture(IsOperandTests);
