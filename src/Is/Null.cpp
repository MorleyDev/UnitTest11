#include <UnitTest11/Is/Null.hpp>

ut11::Operands::IsNull ut11::Is::Null;
ut11::detail::NotOperand<ut11::Operands::IsNull> ut11::Is::Not::Null = !ut11::Is::Null;

