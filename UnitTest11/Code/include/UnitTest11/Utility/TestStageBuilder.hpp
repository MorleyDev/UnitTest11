#ifndef UNITTEST11_UTILITY_TESTSTAGEBUILDER_HPP
#define UNITTEST11_UTILITY_TESTSTAGEBUILDER_HPP

#include "TestStage.hpp"
#include "ITestStage.hpp"
#include "ITestStageBuilder.hpp"

#include <vector>
#include <memory>

namespace ut11
{
    namespace Utility
    {
        class TestStageBuilder : public ITestStageBuilder
        {
        private:
            void FlushToFinished();

        public:
            virtual ~TestStageBuilder();

            virtual void PushGiven(TestStep given);
            virtual void PushWhen(TestStep when);
            virtual void PushThen(TestStep then);
            virtual void PushFinally(TestStep finally);
            virtual std::vector< std::shared_ptr<ITestStage> > Stage();

        private:
            TestStep m_given, m_when;

            std::vector<TestStage> m_finallylessStages;
            std::vector< std::shared_ptr<ITestStage> > m_finishedStages;
        };
    }
}

#endif // UNITTEST11_UTILITY_TESTSTAGEBUILDER_HPP
