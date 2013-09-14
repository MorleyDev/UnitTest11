#ifndef UNITTEST11_IS_NAN_HPP
#define UNITTEST11_IS_NAN_HPP

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"

#include <sstream>
#include <type_traits>
#include <cmath>

namespace ut11
{
	namespace Utility
	{
		namespace detail
		{
			template<typename T, bool IsFloating = std::is_floating_point<T>::value, bool IsIntegral = std::is_integral<T>::value>
			struct NanHelper
			{
				inline bool operator()(const T& value)
				{
					return std::isnan(value);
				}
			};

			template<typename T>
			struct NanHelper<T, false, true> // Not Float but Integer so Is Number
			{
				inline bool operator()(const T&)
				{
					return false;
				}
			};

			template<typename T>
			struct NanHelper<T,false,false> // Not Float or Integer so Not Number
			{
				inline bool operator()(const T&)
				{
					return true;
				}
			};
		}

		/*! \brief Can be partially specialised to handle custom cases when comparing for NaN
		 *
		 * \tparam T The type being checked for NaN
		 */
		template<typename T> struct IsNotANumber
		{
			bool operator()(const T& value) const
			{
				return detail::NanHelper<T>()(value);
			}
		};
	}

	namespace Operands
	{

		struct IsNaN : public Utility::BaseOperand<IsNaN>
		{
			template<typename U> bool operator()(const U& value) const
			{
				return Utility::IsNotANumber<U>()(value);
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
