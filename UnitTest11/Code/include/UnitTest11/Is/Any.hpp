#ifndef UNITTEST11_IS_ANY_HPP
#define UNITTEST11_IS_ANY_HPP

#include "../Utility/BaseOperand.hpp"
#include <type_traits>
#include <typeinfo>
#include <sstream>

namespace ut11
{
    namespace Operands
    {
        template<typename T>
        struct IsAny : public ut11::Utility::BaseOperand
        {
            bool operator()(const T&) const
            {
                return true;
            }

            template<typename U> bool operator()(const U&) const
            {
                return std::is_base_of<T,U>::value || std::is_convertible<U,T>::value;
            }

            template<typename U> inline std::string getErrorMessage(const U&) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected any of class " << (typeid(T).name()) << " or derived but was " << (typeid(U).name());
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        template<typename U> inline Operands::IsAny<U> Any()
        {
            return Operands::IsAny<U>();
        }

        namespace Not
        {
            template<typename U> inline Utility::NotOperand< Operands::IsAny<U> > Any()
            {
                return Utility::NotOperand< Operands::IsAny<U> >();
            }
        }
    }
}

#endif // UNITTEST11_IS_ANY_HPP
