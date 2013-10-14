/*
 * Item.hpp
 *
 *  Created on: 28 Apr 2013
 *	  Author: Jason
 */

#ifndef UT11_IS_ITERABLE_CONTAINING_ITEM_HPP_INCLUDED
#define UT11_IS_ITERABLE_CONTAINING_ITEM_HPP_INCLUDED

#include "../../../utility/BaseOperand.hpp"
#include "../../../utility/AreEqual.hpp"
#include "../../../utility/ToString.hpp"
#include <string>

namespace ut11
{
	namespace Operands
	{
		template<typename T> struct IsIterableContainingItem : public utility::BaseOperand<IsIterableContainingItem<T>>
		{
			const T& m_expected;

			explicit IsIterableContainingItem(const T& expected)
				: m_expected(expected)
			{
			}

			template<typename U> inline bool operator()(const U& actual) const
			{
				for(const auto& i : actual)
					if ( utility::AreEqual(m_expected, i) )
						return true;

				return false;
			}

			template<typename U> inline std::string GetErrorMessage(const U& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected iterable containing " << utility::ToString(m_expected) << " but was " << utility::ToString(actual);
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
				/*! \brief Passes if the given iterable contains at least one of the given item */
				template<typename T> inline Operands::IsIterableContainingItem<T> Item(const T& expected)
				{
					return Operands::IsIterableContainingItem<T>(expected);
				}
			}

			namespace Not
			{
				namespace Containing
				{
					/*! \brief Passes if the given iterable does not contain at least one of the given item */
					template<typename T> inline utility::NotOperand< Operands::IsIterableContainingItem<T> > Item(const T& expected)
					{
						return !Operands::IsIterableContainingItem<T>(expected);
					}
				}
			}
		}
	}
}


#endif /* UT11_IS_ITERABLE_CONTAINING_ITEM_HPP_INCLUDED */
