#ifndef UNITTEST11_IS_NULL_HPP
#define UNITTEST11_IS_NULL_HPP

#include "../Utility/BaseOperand.hpp"
#include <memory>

namespace ut11
{
    namespace Operands
    {
        struct IsNull : public Utility::BaseOperand
        {
            template<typename U> bool operator()(std::weak_ptr<U> value) const
            {
                return value.lock() == std::shared_ptr<U>(nullptr);
            }

            template<typename U> bool operator()(const U& value) const
            {
                return value == U(nullptr);
            }
        };
    }

    namespace Is
    {
        extern Operands::IsNull Null;

        namespace Not
        {
            extern Utility::NotOperand<Operands::IsNull> Null;
        }
    }
}

#endif // UNITTEST11_IS_NULL_HPP
