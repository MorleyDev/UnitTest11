#include <UnitTest11/Is/NaN.hpp>

ut11::Operands::IsNaN ut11::Is::NaN;
ut11::utility::NotOperand<ut11::Operands::IsNaN> ut11::Is::Not::NaN = !ut11::Is::NaN;
