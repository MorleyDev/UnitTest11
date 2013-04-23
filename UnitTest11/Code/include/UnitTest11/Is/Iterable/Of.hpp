/*
 * Of.hpp
 *
 *  Created on: 23 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_IS_ITERABLE_OF_HPP_INCLUDED
#define UT11_IS_ITERABLE_OF_HPP_INCLUDED

#include "../../Utility/BaseOperand.hpp"
#include "../../Utility/Meta/IsIterableOfType.hpp"

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		template<typename T>
		struct IsIteratorOf : public ut11::Utility::BaseOperand
		{
			template<typename U> inline bool operator()(const U& actual) const
			{
				return Utility::Meta::IsIterableOfType<U, T>::value;
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
			template<typename T> inline Operands::IsIteratorOf<T> Of()
			{
				return Operands::IsIteratorOf<T>();
			}

			namespace Not
			{
				template<typename T> inline Utility::NotOperand< Operands::IsIteratorOf<T> > Of()
				{
					return Utility::NotOperand<Operands::IsIteratorOf<T>>();
				}
			}
		}
	}
}

#endif /* UT11_IS_ITERABLE_OF_HPP_INCLUDED */
