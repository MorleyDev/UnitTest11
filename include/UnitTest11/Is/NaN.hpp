#ifndef UNITTEST11_IS_NAN_HPP
#define UNITTEST11_IS_NAN_HPP

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"

#include <sstream>
#include <type_traits>

namespace ut11
{
	namespace Utility
	{
		template<typename T, bool IsFloating = std:: is_floating_point<T>::value || std::is_integral<T>::value>
		struct NanHelper
		{
			inline bool operator()(const T& value)
			{
				return value != value;
			}
		};

		template<typename T>
		struct NanHelper<T,false>
		{
			inline bool operator()(const T&)
			{
				return true;
			}
		};
	}

	namespace Operands
	{

		struct IsNaN : public Utility::BaseOperand<IsNaN>
		{
			template<typename U> bool operator()(const U& value) const
			{
				return Utility::NanHelper<U>()(value);
			}

			template<typename U> inline std::string GetErrorMessage(const U& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected NaN but was " << ut11::Utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual has a value that is Not A Number, otherwise false */
		extern Operands::IsNaN NaN;

		namespace Not
		{
			/*! \brief Operand returns true if Actual has a value that is a number, otherwise false */
			extern Utility::NotOperand<Operands::IsNaN> NaN;
		}
	}
}

#endif // UNITTEST11_IS_NAN_HPP
