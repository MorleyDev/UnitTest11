#include <UnitTest11/Is/Zero.hpp>

ut11::Operands::IsZero ut11::Is::Zero;
ut11::utility::NotOperand<ut11::Operands::IsZero> ut11::Is::Not::Zero = !ut11::Is::Zero;
