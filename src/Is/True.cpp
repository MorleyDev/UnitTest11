#include <UnitTest11/Is/True.hpp>

ut11::Operands::TrueOperand ut11::Is::True;
ut11::Utility::NotOperand<ut11::Operands::TrueOperand> ut11::Is::Not::True = !ut11::Is::True;
