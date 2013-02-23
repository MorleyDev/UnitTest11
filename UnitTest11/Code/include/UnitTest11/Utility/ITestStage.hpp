#ifndef UNITTEST11_UTILITY_ITESTSTAGE_HPP
#define UNITTEST11_UTILITY_ITESTSTAGE_HPP

#include "../IOutput.hpp"

namespace ut11
{
    namespace Utility
    {
        class ITestStage
        {
        public:
            virtual ~ITestStage();

            virtual bool Run(IOutput& output) = 0;
        };
    }
}

#endif // UNITTEST11_UTILITY_ITESTSTAGE_HPP
