/*
 * Item.hpp
 *
 *  Created on: 28 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_IS_ITERABLE_CONTAINING_ITEM_HPP_INCLUDED
#define UT11_IS_ITERABLE_CONTAINING_ITEM_HPP_INCLUDED

#include "../../../Utility/BaseOperand.hpp"
#include "../../../Utility/AreEqual.hpp"

namespace ut11
{
	namespace Operands
	{
		template<typename T> struct IsIterableContainingItem : public Utility::BaseOperand
		{
			const T& m_expected;

			IsIterableContainingItem(const T& expected)
				: m_expected(expected)
			{
			}

			template<typename U> inline bool operator()(const U& actual) const
			{
				for(const auto& i : actual)
					if ( Utility::AreEqual(m_expected, i) )
						return true;
				return false;
			}

            template<typename U> inline std::string GetErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected iterable containing " << Utility::ToString(m_expected) << " but was " << Utility::ToString(actual);
                return errorMessage.str();
            }
		};
	}

	namespace Is
	{
		namespace Iterable
		{
			namespace Containing
			{
				template<typename T> inline Operands::IsIterableContainingItem<T> Item(const T& expected)
				{
					return Operands::IsIterableContainingItem<T>(expected);
				}
			}

			namespace Not
			{
				namespace Containing
				{
					template<typename T> inline Utility::NotOperand< Operands::IsIterableContainingItem<T> > Item(const T& expected)
					{
						return Utility::NotOperand< Operands::IsIterableContainingItem<T> >(expected);
					}
				}
			}
		}
	}
}


#endif /* UT11_IS_ITERABLE_CONTAINING_ITEM_HPP_INCLUDED */
