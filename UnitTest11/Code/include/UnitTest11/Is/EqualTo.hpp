#ifndef UNITTEST11_IS_EQUALTO_HPP
#define UNITTEST11_IS_EQUALTO_HPP

#include "../Utility/AreEqual.hpp"
#include "../Utility/ToString.hpp"
#include "../Utility/BaseOperand.hpp"

#include <string>
#include <sstream>

namespace ut11
{
    namespace Operands
    {
        template<typename U> struct EqualTo : public Utility::BaseOperand
        {
        private:
            const U& m_expected;

        public:
            inline explicit EqualTo(const U& expected) : m_expected(expected) { }

            template<typename T> inline bool operator()(const T& actual) const
            {
                return Utility::AreEqual(m_expected, actual);
            }

            template<typename T> inline std::string GetErrorMessage(const T& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected " << Utility::ToString(m_expected) << " but was " << Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        template<typename U> inline Operands::EqualTo<U> EqualTo(const U& expected) { return Operands::EqualTo<U>(expected); }

        namespace Not
        {
            template<typename U> inline Utility::NotOperand< Operands::EqualTo<U> > EqualTo(const U& expected) { return Utility::NotOperand< Operands::EqualTo<U> >(expected); }
        }
    }
}


#endif // UNITTEST11_IS_EQUALTO_HPP
