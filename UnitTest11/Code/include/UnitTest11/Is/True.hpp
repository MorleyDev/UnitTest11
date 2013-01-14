#ifndef UNITTEST11_IS_TRUE_HPP
#define UNITTEST11_IS_TRUE_HPP

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"

#include <string>
#include <sstream>

namespace ut11
{
    namespace Operands
    {
        struct TrueOperand
        {
            template<typename T> bool operator()(const T& value) const { return static_cast<bool>(value); }

            template<typename T> inline std::string getErrorMessage(const T& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected true but was " << Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        extern Operands::TrueOperand True;
        namespace Not { extern Utility::NotOperand<Operands::TrueOperand> True; }
    }
}

#endif // UNITTEST11_IS_TRUE_HPP
