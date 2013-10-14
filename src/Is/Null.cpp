#include <UnitTest11/Is/Null.hpp>

ut11::Operands::IsNull ut11::Is::Null;
ut11::utility::NotOperand<ut11::Operands::IsNull> ut11::Is::Not::Null = !ut11::Is::Null;

