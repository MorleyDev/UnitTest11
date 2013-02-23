#ifndef UNITTEST11_UTILITY_ITESTSTAGEBUILDER_HPP
#define UNITTEST11_UTILITY_ITESTSTAGEBUILDER_HPP

#include "TestStep.hpp"
#include "ITestStage.hpp"
#include <memory>
#include <vector>

namespace ut11
{
    namespace Utility
    {
        class ITestStageBuilder
        {
        public:
            virtual ~ITestStageBuilder();

            virtual void PushGiven(TestStep given) = 0;
            virtual void PushWhen(TestStep when) = 0;
            virtual void PushThen(TestStep then) = 0;
            virtual void PushFinally(TestStep finally) = 0;
            virtual std::vector< std::shared_ptr<ITestStage> > Stage() = 0;
        };
    }
}


#endif // UNITTEST11_UTILITY_ITESTSTAGEBUILDER_HPP
