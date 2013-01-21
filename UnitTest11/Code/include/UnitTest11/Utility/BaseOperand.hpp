#ifndef UNITTEST11_UTILITY_BASEOPERAND_HPP
#define UNITTEST11_UTILITY_BASEOPERAND_HPP

#include <type_traits>
#include <string>

namespace ut11
{
    namespace Utility
    {
        struct BaseOperand { };

        template<typename Operand> struct IsOperand
        {
			enum { value = std::is_base_of< BaseOperand, Operand >::value };
        };

        template<typename Operand> struct NotOperand : public BaseOperand
        {
            Operand m_original;

            template<typename... ARGS> NotOperand(const ARGS&... o) : m_original(o...) { }

            template<typename... ARGS> bool operator()(const ARGS&... args) const { return !m_original(args...); }
            template<typename... ARGS> std::string getErrorMessage(const ARGS&... args) const { return "Not " + m_original.getErrorMessage(args...); }
        };
    }
}

#endif // UNITTEST11_UTILITY_BASEOPERAND_HPP
