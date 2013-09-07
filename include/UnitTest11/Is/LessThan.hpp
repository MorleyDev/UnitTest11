#ifndef UNITTEST11_IS_LESSTHAN_HPP
#define UNITTEST11_IS_LESSTHAN_HPP

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		template<typename U>
		struct IsLessThan : public Utility::BaseOperand<IsLessThan<U>>
		{
			const U& high;

			explicit IsLessThan(const U& high) 
				: high(high) 
			{
			}

			template<typename T> inline bool operator()(const T& value) const 
			{
				return value < high; 
			}

			template<typename Q> inline std::string GetErrorMessage(const Q& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected less than " << ut11::Utility::ToString(high) << " but was " << ut11::Utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual is less than the Expected, otherwise false */
		template<typename U> inline Operands::IsLessThan<U> LessThan(const U& high)
		{
			return Operands::IsLessThan<U>(high);
		}

		namespace Not
		{
			/*! \brief Operand returns false if Actual is not less than the Expected, otherwise false */
			template<typename U> inline Utility::NotOperand< Operands::IsLessThan<U> > LessThan(const U& high)
			{
				return !Operands::IsLessThan<U>(high);
			}
		}
	}
}

#endif // UNITTEST11_IS_LESSTHAN_HPP
