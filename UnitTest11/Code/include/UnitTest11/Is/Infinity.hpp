#ifndef UNITTEST11_IS_INFINITY_HPP
#define UNITTEST11_IS_INFINITY_HPP

#include "../Utility/BaseOperand.hpp"
#include <cmath>

namespace ut11
{
    namespace Operands
    {
        struct IsInfinity : public Utility::BaseOperand
        {
            template<typename U> bool operator()(const U& value) const
            {
                return  std::isinf(value);
            }

            template<typename U> inline std::string getErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected infinity but was " << ut11::Utility::ToString(actual);
                return errorMessage.str();
            }
        };

        struct IsPositiveInfinity : public Utility::BaseOperand
        {
            template<typename U> bool operator()(const U& value) const
            {
                return  std::isinf(value) && value >= 0;
            }

            template<typename U> inline std::string getErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected positive infinity but was " << ut11::Utility::ToString(actual);
                return errorMessage.str();
            }
        };

        struct IsNegativeInfinity : public Utility::BaseOperand
        {
            template<typename U> bool operator()(const U& value) const
            {
                return  std::isinf(value) && value <= 0;
            }

            template<typename U> inline std::string getErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected negative infinity but was " << ut11::Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        extern Operands::IsInfinity Infinity;
        extern Operands::IsPositiveInfinity PositiveInfinity;
        extern Operands::IsNegativeInfinity NegativeInfinity;

        namespace Not
        {
            extern Utility::NotOperand<Operands::IsInfinity> Infinity;
            extern Utility::NotOperand<Operands::IsPositiveInfinity> PositiveInfinity;
            extern Utility::NotOperand<Operands::IsNegativeInfinity> NegativeInfinity;
        }
    }
}

#endif // UNITTEST11_IS_INFINITY_HPP
