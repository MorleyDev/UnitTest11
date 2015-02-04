#ifndef UNITTEST11_IS_TRUE_HPP
#define UNITTEST11_IS_TRUE_HPP

#include "../detail/BaseOperand.hpp"
#include "../utility/ToString.hpp"

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		struct TrueOperand : public detail::BaseOperand<TrueOperand>
		{
			template<typename T> bool operator()(const T& value) const 
			{
				return static_cast<bool>(value); 
			}

			template<typename T> inline std::string GetErrorMessage(const T& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected true but was " << utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual is true, otherwise false */
		extern Operands::TrueOperand True;

		namespace Not
		{
			/*! \brief Operand returns true if Actual is false, otherwise false */
			extern detail::NotOperand<Operands::TrueOperand> True;
		}
	}
}

#endif // UNITTEST11_IS_TRUE_HPP
