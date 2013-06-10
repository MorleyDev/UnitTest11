/*
 * Subset.hpp
 *
 *  Created on: 28 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_IS_ITERABLE_CONTAINING_SUBSET_HPP_INCLUDED
#define UT11_IS_ITERABLE_CONTAINING_SUBSET_HPP_INCLUDED

#include "../../../Utility/BaseOperand.hpp"
#include "../../../Utility/AreEqual.hpp"

namespace ut11
{
    namespace Operands
    {
        template<typename T> struct IsIterableContainingSubset : public Utility::BaseOperand
        {
            const T& m_expected;

            IsIterableContainingSubset(const T& expected)
                : m_expected(expected)
            {
            }

            template<typename U> inline std::string GetErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected iterable containing subset" << Utility::ToString(m_expected) << " but was " << Utility::ToString(actual);
                return errorMessage.str();
            }

            template<typename U> bool operator()(const U& actual) const
            {
                auto actualIterators = CreateIteratorListFromInput(actual);
                auto expectedIterators = CreateIteratorListFromInput(m_expected);

                while( !expectedIterators.empty() )
                {
                    if  (CompareListsAndRemoveFirstDuplicate(expectedIterators, actualIterators))
                        continue;

                    return false;
                }
                return true;
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
            namespace Containing
            {
                /*! \brief Passes if the given iterable does contains the given subset of items */
                template<typename T> inline Operands::IsIterableContainingSubset<T> Subset(const T& expected)
                {
                    return Operands::IsIterableContainingSubset<T>(expected);
                }
            }

            namespace Not
            {
                namespace Containing
                {
                    /*! \brief Passes if the given iterable does not contain the given subset of items */
                    template<typename T> inline Utility::NotOperand< Operands::IsIterableContainingSubset<T> > Subset(const T& expected)
                    {
                        return Utility::NotOperand< Operands::IsIterableContainingSubset<T> >(expected);
                    }
                }
            }
        }
    }
}


#endif /* UT11_IS_ITERABLE_CONTAINING_SUBSET_HPP_INCLUDED */
