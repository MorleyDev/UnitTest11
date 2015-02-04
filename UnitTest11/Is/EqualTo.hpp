#ifndef UNITTEST11_IS_EQUALTO_HPP
#define UNITTEST11_IS_EQUALTO_HPP

#include "../utility/AreEqual.hpp"
#include "../utility/ToString.hpp"
#include "../detail/BaseOperand.hpp"

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		template<typename U> struct EqualTo : public detail::BaseOperand<EqualTo<U>>
		{
		private:
			const U& m_expected;

		public:
			explicit EqualTo(const U& expected) 
				: m_expected(expected)
			{
			}

			template<typename T> inline bool operator()(const T& actual) const
			{
				return utility::AreEqual(m_expected, actual);
			}

			template<typename T> inline std::string GetErrorMessage(const T& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected " << utility::ToString(m_expected) << " but was " << utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual == Expected, otherwise false */
		template<typename U> inline Operands::EqualTo<U> EqualTo(const U& expected)
		{
			return Operands::EqualTo<U>(expected);
		}

		namespace Not
		{
			/*! \brief Operand returns true if Actual != Expected, otherwise false */
			template<typename U> inline detail::NotOperand< Operands::EqualTo<U> > EqualTo(const U& expected) 
			{
				return !Operands::EqualTo<U>(expected); 
			}
		}
	}
}


#endif // UNITTEST11_IS_EQUALTO_HPP
