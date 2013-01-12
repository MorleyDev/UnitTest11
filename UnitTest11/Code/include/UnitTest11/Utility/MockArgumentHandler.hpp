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
        static typename std::enable_if< IsOperand<U>::value, bool >::type CompareWithOperandOrEquality(const T& arg, const U& expectation)
        {
            return expectation(arg);
        }

        template<typename T, typename U>
        static typename std::enable_if< !(IsOperand<U>::value), bool >::type CompareWithOperandOrEquality(const T& arg, const U& expectation)
        {
            return AreEqual(expectation, arg);
        }

        template<typename... ARGS> class MockArgumentHandler
        {
        public:
            virtual ~MockArgumentHandler() { }

            inline void AddCall(ARGS... args)
            {
                m_arguments.push_back( std::make_tuple( std::forward<ARGS>(args)... ) );
            }

            template<typename... Expectations> inline std::size_t CountCalls(Expectations... expectations) const
            {
                static_assert(sizeof...(Expectations) == sizeof...(ARGS), "Expectations and Arguments must match");

                std::size_t counter = 0;

                std::tuple<Expectations...> expectationTuple(expectations...);
                for(const std::tuple<ARGS...>& actual : m_arguments)
                {
                    if ( MatchTuples(actual, expectationTuple) )
                        ++counter;
                }
                return counter;
            }

            inline std::size_t TotalCount() const { return m_arguments.size(); }

        protected:
            template<int I = 0, typename... Expectations>
            typename std::enable_if< I < sizeof...(ARGS), bool >::type MatchTuples(const std::tuple<ARGS...>& arguments, const std::tuple<Expectations...>& expectations) const
            {
                return CompareWithOperandOrEquality(std::get<I>(arguments), std::get<I>(expectations)) && MatchTuples<I+1>(arguments, expectations);
            }

            template<int I = 0, typename... Expectations>
            typename std::enable_if< I == sizeof...(ARGS), bool >::type MatchTuples(const std::tuple<ARGS...>&, const std::tuple<Expectations...>&) const
            {
                return true;
            }

        private:
            std::list< std::tuple<ARGS...> > m_arguments;
        };
    }
}

#endif // UNITTEST11_UTILITY_MOCKARGUMENTHANDLER_HPP
