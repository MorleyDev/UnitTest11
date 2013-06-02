#ifndef UNITTEST11_UTILITY_TESTSTAGEBUILDERIMPL_HPP
#define UNITTEST11_UTILITY_TESTSTAGEBUILDERIMPL_HPP

#include "TestStageImpl.hpp"
#include "TestStageBuilder.hpp"

#include <vector>
#include <memory>

namespace ut11
{
    namespace Utility
    {
        class TestStageBuilderImpl : public TestStageBuilder
        {
        private:
            void FlushToFinished();

        public:
            virtual ~TestStageBuilderImpl();

            virtual void PushGiven(TestStep given);
            virtual void PushWhen(TestStep when);
            virtual void PushThen(TestStep then);
            virtual void PushFinally(TestStep finally);
            virtual std::vector< std::shared_ptr<TestStage> > Stage();

        private:
            TestStep m_given, m_when;

            std::vector<TestStageImpl> m_finallylessStages;
            std::vector< std::shared_ptr<TestStage> > m_finishedStages;
        };
    }
}

#endif // UNITTEST11_UTILITY_TESTSTAGEBUILDERIMPL_HPP
