/*
 * EquivalentTo.hpp
 *
 *  Created on: 23 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_IS_ITERABLE_EQUIVALENTTO_HPP_INCLUDED
#define UT11_IS_ITERABLE_EQUIVALENTTO_HPP_INCLUDED

#include "../../Utility/BaseOperand.hpp"
#include "../../Utility/ToString.hpp"
#include "../../Utility/AreEqual.hpp"

#include <sstream>
#include <list>

namespace ut11
{
	namespace Operands
	{
		template<typename T>
		struct IsIterableEquivalentTo : public Utility::BaseOperand
		{
			const T& m_expected;

			IsIterableEquivalentTo(const T& expected)
				: m_expected(expected)
			{
			}

			template<typename U> bool operator()(const U& actual) const
			{
				auto actualIterators = CreateIteratorListFromInput(actual);
				auto expectedIterators = CreateIteratorListFromInput(m_expected);

				while(!actualIterators.empty() || !expectedIterators.empty() )
				{
					if  (CompareListsAndRemoveFirstDuplicate(expectedIterators, actualIterators))
						continue;

					return false;
				}
				return true;
			}

            template<typename U> inline std::string GetErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected equivalent of " << Utility::ToString(m_expected) << " but was type " << Utility::ToString(actual);
                return errorMessage.str();
            }

		private:
			template<typename A, typename B> static bool CompareListsAndRemoveFirstDuplicate(A& a, B& b)
			{
				for(auto i = a.begin(); i != a.end(); ++i)
					for(auto j = b.begin(); j != b.end(); ++j)
						if ( Utility::AreEqual(**i, **j) )
						{
							a.erase(i);
							b.erase(j);
							return true;
						}

				return false;
			}

			template<typename U> static std::list< decltype(std::declval<const U&>().begin()) > CreateIteratorListFromInput(const U& input)
			{
				std::list< decltype(std::declval<const U&>().begin()) > iterators;
				for(auto i = input.begin(); i != input.end(); ++i)
					iterators.push_back(i);
				return iterators;
			}
		};
	}

	namespace Is
	{
		namespace Iterable
		{
			/*! \brief Takes an expected and actual iterable (has ::begin and ::end functions) and returns true if the contents of those iterables are the same, ignoring order */
			template<typename T> Operands::IsIterableEquivalentTo<T> EquivalentTo(const T& expected)
			{
				return Operands::IsIterableEquivalentTo<T>(expected);
			}

			namespace Not
			{
				/*! \brief Takes an expected and actual iterable (has ::begin and ::end functions) and returns true if the contents of those iterables are not the same, ignoring order */
				template<typename T> Utility::NotOperand< Operands::IsIterableEquivalentTo<T> > EquivalentTo(const T& expected)
				{
					return Utility::NotOperand< Operands::IsIterableEquivalentTo<T> >(expected);
				}
			}
		}
	}
}


#endif /* UT11_IS_ITERABLE_EQUIVALENTTO_HPP_INCLUDED */
