#include <UnitTest11/Is/Infinity.hpp>

ut11::Operands::IsInfinity ut11::Is::Infinity;
ut11::utility::NotOperand< ut11::Operands::IsInfinity > ut11::Is::Not::Infinity = !ut11::Is::Infinity;

ut11::Operands::IsPositiveInfinity ut11::Is::PositiveInfinity;
ut11::utility::NotOperand< ut11::Operands::IsPositiveInfinity > ut11::Is::Not::PositiveInfinity = !ut11::Is::PositiveInfinity;

ut11::Operands::IsNegativeInfinity ut11::Is::NegativeInfinity;
ut11::utility::NotOperand< ut11::Operands::IsNegativeInfinity > ut11::Is::Not::NegativeInfinity = !ut11::Is::NegativeInfinity;
