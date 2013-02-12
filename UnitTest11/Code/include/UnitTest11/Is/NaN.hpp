#ifndef UNITTEST11_IS_NAN_HPP
#define UNITTEST11_IS_NAN_HPP

#include "../Utility/BaseOperand.hpp"

namespace ut11
{
    namespace Operands
    {
        struct IsNaN : public Utility::BaseOperand
        {
            template<typename U> bool operator()(const U& value) const
            {
                return value != value;
            }

            template<typename U> inline std::string getErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected NaN but was " << ut11::Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        extern Operands::IsNaN NaN;

        namespace Not
        {
            extern Utility::NotOperand<Operands::IsNaN> NaN;
        }
    }
}

#endif // UNITTEST11_IS_NAN_HPP
