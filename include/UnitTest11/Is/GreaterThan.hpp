#ifndef UNITTEST11_IS_GREATERTHAN_HPP
#define UNITTEST11_IS_GREATERTHAN_HPP

#include "../Utility/BaseOperand.hpp"
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		template<typename U>
		struct IsGreaterThan : public Utility::BaseOperand<IsGreaterThan<U>>
		{
			const U& low;

			explicit IsGreaterThan(const U& low) 
				: low(low) 
			{
			}

			template<typename T> inline bool operator()(const T& value) const
			{
				return value > low; 
			}

			template<typename Q> inline std::string GetErrorMessage(const Q& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected greater than " << ut11::Utility::ToString(low) << " but was " << ut11::Utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual is greater than Expected, otherwise false */
		template<typename U> inline Operands::IsGreaterThan<U> GreaterThan(const U& low)
		{
			return Operands::IsGreaterThan<U>(low);
		}

		namespace Not
		{
			/*! \brief Operand returns true if Actual is not greater than Expected, otherwise false */
			template<typename U> inline Utility::NotOperand< Operands::IsGreaterThan<U> > GreaterThan(const U& low)
			{
				return !Operands::IsGreaterThan<U>(low);
			}
		}
	}
}

#endif // UNITTEST11_IS_GREATERTHAN_HPP
