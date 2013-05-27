#ifndef UNITTEST11_UTILITY_MOCKARGUMENTHANDLER_HPP
#define UNITTEST11_UTILITY_MOCKARGUMENTHANDLER_HPP

#include "BaseOperand.hpp"
#include "AreEqual.hpp"

#include <tuple>
#include <list>

namespace ut11
{
    namespace Utility
    {
        template<typename T, typename U>
        static inline typename std::enable_if< IsOperand<U>::value, bool >::type CompareWithOperandOrEquality(const T& arg, const U& expectation)
        {
            return expectation(arg);
        }

        template<typename T, typename U>
        static inline typename std::enable_if< !(IsOperand<U>::value), bool >::type CompareWithOperandOrEquality(const T& arg, const U& expectation)
        {
            return AreEqual(expectation, arg);
        }

        template<typename... ARGS> class MockArgumentHandler
        {
        public:
            void AddCall(ARGS... args)
            {
                m_arguments.push_back( std::make_tuple( std::forward<ARGS>(args)... ) );
            }

            template<typename... Expectations> std::size_t CountCalls(Expectations... expectations) const
            {
                static_assert(sizeof...(Expectations) == sizeof...(ARGS), "Expectations and Arguments must match");

                std::size_t counter = 0;

                std::tuple<Expectations...> expectationTuple(expectations...);
                for(const std::tuple<ARGS...>& actual : m_arguments)
                {
                    if ( MatchTuples<0, sizeof...(ARGS)>(actual, expectationTuple) )
                        ++counter;
                }
                return counter;
            }

            std::size_t TotalCount() const { return m_arguments.size(); }

        protected:
            template<int I, int Limit, typename Arguments, typename Expectations>
            typename std::enable_if< (I < Limit), bool >::type MatchTuples(const Arguments& arguments, const Expectations& expectations) const
            {
                return CompareWithOperandOrEquality(std::get<I>(arguments), std::get<I>(expectations)) && MatchTuples<I+1, Limit>(arguments, expectations);
            }

            template<int I, int Limit, typename Arguments, typename Expectations>
            typename std::enable_if< (I >= Limit), bool >::type MatchTuples(const Arguments&, const Expectations&) const
            {
                return true;
            }

        private:
            std::list< std::tuple<ARGS...> > m_arguments;
        };
    }
}

#endif // UNITTEST11_UTILITY_MOCKARGUMENTHANDLER_HPP
