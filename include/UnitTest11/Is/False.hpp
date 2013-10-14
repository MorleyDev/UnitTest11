#ifndef UNITTEST11_IS_FALSE_HPP
#define UNITTEST11_IS_FALSE_HPP

#include "../utility/BaseOperand.hpp"
#include "../utility/ToString.hpp"

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		struct FalseOperand : public utility::BaseOperand<FalseOperand>
		{
			template<typename T> bool operator()(const T& value) const 
			{
				return !static_cast<bool>(value); 
			}

			template<typename T> inline std::string GetErrorMessage(const T& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected false but was " << utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual is false, otherwise false */
		extern Operands::FalseOperand False;

		namespace Not
		{
			/*! \brief Operand returns true if Actual is true, otherwise false */
			extern utility::NotOperand<Operands::FalseOperand> False;
		}
	}
}

#endif // UNITTEST11_IS_FALSE_HPP
