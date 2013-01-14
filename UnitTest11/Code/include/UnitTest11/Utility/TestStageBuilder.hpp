#ifndef UNITTEST11_UTILITY_TESTSTAGEBUILDER_HPP
#define UNITTEST11_UTILITY_TESTSTAGEBUILDER_HPP

#include "TestStage.hpp"
#include <vector>
#include <memory>

namespace ut11
{
    namespace Utility
    {
        class ITestStageBuilder
        {
        public:
            virtual ~ITestStageBuilder() { }

            virtual void pushGiven(TestStep given) = 0;
            virtual void pushWhen(TestStep when) = 0;
            virtual void pushThen(TestStep then) = 0;
            virtual void pushFinally(TestStep finally) = 0;
            virtual std::vector< std::shared_ptr<ITestStage> > stage() = 0;
        };

        class TestStageBuilder : public ITestStageBuilder
        {
        private:
            void flushToFinished()
            {
                m_given = TestStep();
                m_when = TestStep();

                for(auto step : m_finallylessStages)
                    m_finishedStages.push_back(std::make_shared<TestStage>(step));
                m_finallylessStages.clear();
            }

        public:
            virtual ~TestStageBuilder() { }

            virtual void pushGiven(TestStep given)
            {
                flushToFinished();
                m_given = given;
            }

            virtual void pushWhen(TestStep when)
            {
                m_when = when;
            }

            virtual void pushThen(TestStep then)
            {
                m_finallylessStages.push_back(TestStage(m_given, m_when, then, TestStep()));
            }

            virtual void pushFinally(TestStep finally)
            {
                for(auto& step : m_finallylessStages)
                    step.m_finally = finally;

                flushToFinished();
            }

            virtual std::vector< std::shared_ptr<ITestStage> > stage()
            {
                flushToFinished();

                return m_finishedStages;
            }

        private:
            TestStep m_given, m_when;

            std::vector<TestStage> m_finallylessStages;
            std::vector< std::shared_ptr<ITestStage> > m_finishedStages;
        };
    }
}

#endif // UNITTEST11_UTILITY_TESTSTAGEBUILDER_HPP
