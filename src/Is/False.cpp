#include <UnitTest11/Is/False.hpp>

ut11::Operands::FalseOperand ut11::Is::False;
ut11::detail::NotOperand<ut11::Operands::FalseOperand> ut11::Is::Not::False = !ut11::Is::False;
