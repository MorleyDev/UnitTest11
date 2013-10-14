#ifndef UT11_IS_STRING_BEGINNINGWITH_HPP_INCLUDED
#define UT11_IS_STRING_BEGINNINGWITH_HPP_INCLUDED

#include "../../utility/BaseOperand.hpp"

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		struct IsStringBeginningWith : public ut11::utility::BaseOperand<IsStringBeginningWith>
		{
			std::string m_expected;

			explicit IsStringBeginningWith(const std::string& expected)
				: m_expected(expected)
			{
			}

			inline bool operator()(const std::string& actual) const
			{
				return ( actual.length() >= m_expected.length() && actual.substr(0, m_expected.length()) == m_expected);
			}

			inline std::string GetErrorMessage(const std::string& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected string BeginningWith " << m_expected << " but was " << actual;
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		namespace String
		{
			/*! \brief Operand returns true if string begins with expected string, otherwise returns false */
			inline Operands::IsStringBeginningWith BeginningWith(std::string expected)
			{
				return Operands::IsStringBeginningWith(expected);
			}

			namespace Not
			{
				/*! \brief Operand returns false if string begins with expected string, otherwise returns true */
				inline utility::NotOperand<Operands::IsStringBeginningWith> BeginningWith(std::string expected)
				{
					return !Operands::IsStringBeginningWith(expected);
				}
			}
		}
	}
}


#endif /* UT11_IS_STRING_BEGINNINGWITH_HPP_INCLUDED */
