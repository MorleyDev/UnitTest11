#include <UnitTest11.hpp>

class TestStageBuilderTests : public ut11::TestFixture
{
private:
    std::vector<ut11::Utility::TestStep> m_steps;
    ut11::Utility::TestStageBuilder m_builder;

    std::vector< std::shared_ptr<ut11::Utility::TestStage> > m_Stages;

public:
    virtual void Run()
    {
        Given("TestSteps and a TestStageBuilder", [&](){
            m_steps = {
                {"0", [](){}}, {"1", [](){}}, {"2", [](){}}, {"3", [](){}},
                {"4", [](){}}, {"5", [](){}}, {"6", [](){}}, {"7", [](){}},
                {"8", [](){}}, {"9", [](){}}, {"10", [](){}}
            };

            m_builder = ut11::Utility::TestStageBuilder();

            m_Stages = std::vector< std::shared_ptr<ut11::Utility::TestStage> >();
        });

        When("Stages are pushed to a builder and it is Stages", [&]() {

            m_builder.PushGiven(m_steps[0]);
            m_builder.PushWhen(m_steps[1]);
            m_builder.PushThen(m_steps[2]);
            m_builder.PushThen(m_steps[3]);
            m_builder.PushWhen(m_steps[4]);
            m_builder.PushThen(m_steps[5]);
            m_builder.PushFinally(m_steps[6]);
            m_builder.PushWhen(m_steps[9]);
            m_builder.PushThen(m_steps[10]);
            m_builder.PushGiven(m_steps[7]);
            m_builder.PushThen(m_steps[8]);

            auto iStages = m_builder.Stage();

            for(std::size_t i = 0; i < iStages.size(); ++i)
                m_Stages.push_back(std::static_pointer_cast<ut11::Utility::TestStage>(iStages[i]));

        });

        Then("the expected amount of Stages are returned", [&]() {
            AssertThat(m_Stages.size(), ut11::Is::EqualTo(std::size_t(5)));
        });

        Then("the Stages are the expected Stages", [&]() {

            AssertThat(m_steps[0].description, ut11::Is::EqualTo(m_Stages[0]->m_given.description));
            AssertThat(m_steps[1].description, ut11::Is::EqualTo(m_Stages[0]->m_when.description));
            AssertThat(m_steps[2].description, ut11::Is::EqualTo(m_Stages[0]->m_then.description));
            AssertThat(m_steps[6].description, ut11::Is::EqualTo(m_Stages[0]->m_finally.description));

            AssertThat(m_steps[0].description, ut11::Is::EqualTo(m_Stages[1]->m_given.description));
            AssertThat(m_steps[1].description, ut11::Is::EqualTo(m_Stages[1]->m_when.description));
            AssertThat(m_steps[3].description, ut11::Is::EqualTo(m_Stages[1]->m_then.description));
            AssertThat(m_steps[6].description, ut11::Is::EqualTo(m_Stages[1]->m_finally.description));

            AssertThat(m_steps[0].description, ut11::Is::EqualTo(m_Stages[2]->m_given.description));
            AssertThat(m_steps[4].description, ut11::Is::EqualTo(m_Stages[2]->m_when.description));
            AssertThat(m_steps[5].description, ut11::Is::EqualTo(m_Stages[2]->m_then.description));
            AssertThat(m_steps[6].description, ut11::Is::EqualTo(m_Stages[2]->m_finally.description));

            AssertThat("",                     ut11::Is::EqualTo(m_Stages[3]->m_given.description));
            AssertThat(m_steps[9].description, ut11::Is::EqualTo(m_Stages[3]->m_when.description));
            AssertThat(m_steps[10].description,ut11::Is::EqualTo(m_Stages[3]->m_then.description));
            AssertThat("",                     ut11::Is::EqualTo(m_Stages[3]->m_finally.description));

            AssertThat(m_steps[7].description, ut11::Is::EqualTo(m_Stages[4]->m_given.description));
            AssertThat("",                     ut11::Is::EqualTo(m_Stages[4]->m_when.description));
            AssertThat(m_steps[8].description, ut11::Is::EqualTo(m_Stages[4]->m_then.description));
            AssertThat("",                     ut11::Is::EqualTo(m_Stages[4]->m_finally.description));
        });
    }
};
DeclareFixture(TestStageBuilderTests);
