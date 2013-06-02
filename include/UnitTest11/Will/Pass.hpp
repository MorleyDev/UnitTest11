#ifndef UNITTEST11_WILL_PASS_HPP
#define UNITTEST11_WILL_PASS_HPP

#include "../Utility/BaseOperand.hpp"
#include <string>

namespace ut11
{
    namespace Operands
    {
        template<typename CALLBACK>
        class WillPass : public Utility::BaseOperand
        {
        private:
            CALLBACK m_predicate;

        public:
            explicit WillPass(CALLBACK predicate)
                : m_predicate(predicate)
            {
            }

            template<typename T> inline bool operator()(const T& value) const
            {
                return m_predicate(value);
            }

            template<typename T>
            inline std::string GetErrorMessage(const T&) const { return "Expected predicate to return true"; }
        };
    }

    namespace Will
    {
    	/*! \brief Operand will return true if the passed predicate returns true when called with the Actual value, otherwise returns false */
        template<typename CALLBACK> Operands::WillPass<CALLBACK> Pass(CALLBACK predicate)
        {
            return Operands::WillPass<CALLBACK>(predicate);
        }

        namespace Not
        {
        	/*! \brief Operand will return true if the passed predicate returns false when called with the Actual value, otherwise returns false */
            template<typename CALLBACK> Utility::NotOperand< Operands::WillPass<CALLBACK> > Pass(CALLBACK predicate)
            {
                return Utility::NotOperand< Operands::WillPass<CALLBACK> >(predicate);
            }
        }
    }
}

#endif // UNITTEST11_WILL_PASS_HPP
