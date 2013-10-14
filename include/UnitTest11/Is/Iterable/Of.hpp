/*
 * Of.hpp
 *
 *  Created on: 23 Apr 2013
 *	  Author: Jason
 */

#ifndef UT11_IS_ITERABLE_OF_HPP_INCLUDED
#define UT11_IS_ITERABLE_OF_HPP_INCLUDED

#include "../../utility/BaseOperand.hpp"
#include "../../utility/Meta/IsIterableOfType.hpp"

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		template<typename T>
		struct IsIteratorOf : public ut11::utility::BaseOperand<IsIteratorOf<T>>
		{
			template<typename U> inline bool operator()(const U& actual) const
			{
				return utility::Meta::IsIterableOfType<U, T>::value;
			}

			template<typename U> inline std::string GetErrorMessage(const U&) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected iterable of " << typeid(T).name() << " but was type " << typeid(U).name();
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		namespace Iterable
		{
			/*! \brief Passes if the actual is an iterable (has begin and end functions) whose items are of type T, or descended from type T */
			template<typename T> inline Operands::IsIteratorOf<T> Of()
			{
				return Operands::IsIteratorOf<T>();
			}

			namespace Not
			{
				/*! \brief Passes if the actual is not an iterable (has begin and end functions) whose items are of type T, or descended from type T */
				template<typename T> inline utility::NotOperand< Operands::IsIteratorOf<T> > Of()
				{
					return !Operands::IsIteratorOf<T>();
				}
			}
		}
	}
}

#endif /* UT11_IS_ITERABLE_OF_HPP_INCLUDED */
