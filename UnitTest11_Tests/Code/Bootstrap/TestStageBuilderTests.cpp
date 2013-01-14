#include <UnitTest11/Utility/TestStageBuilder.hpp>
#include <UnitTest11/Mock.hpp>
#include <UnitTest++/UnitTest++.h>

TEST(TestStageBuilderTests)
{
    ut11::Utility::TestStep steps[11] =
    {
        {"0", [](){}}, {"1", [](){}}, {"2", [](){}}, {"3", [](){}},
        {"4", [](){}}, {"5", [](){}}, {"6", [](){}}, {"7", [](){}},
        {"8", [](){}}, {"9", [](){}}, {"10", [](){}}
    };

    ut11::Utility::TestStageBuilder builder;

    builder.pushGiven(steps[0]);
    builder.pushWhen(steps[1]);
    builder.pushThen(steps[2]);
    builder.pushThen(steps[3]);
    builder.pushWhen(steps[4]);
    builder.pushThen(steps[5]);
    builder.pushFinally(steps[6]);
    builder.pushWhen(steps[9]);
    builder.pushThen(steps[10]);
    builder.pushGiven(steps[7]);
    builder.pushThen(steps[8]);

    auto istages = builder.stage();
    if ( istages.size() != 5 )
    {
        CHECK(false);
        return;
    }

    std::vector< std::shared_ptr<ut11::Utility::TestStage> > stages;
    for(int i = 0; i < 5; ++i)
        stages.push_back(std::static_pointer_cast<ut11::Utility::TestStage>(istages[i]));

    CHECK_EQUAL(steps[0].description, stages[0]->m_given.description);
    CHECK_EQUAL(steps[1].description, stages[0]->m_when.description);
    CHECK_EQUAL(steps[2].description, stages[0]->m_then.description);
    CHECK_EQUAL(steps[6].description, stages[0]->m_finally.description);

    CHECK_EQUAL(steps[0].description, stages[1]->m_given.description);
    CHECK_EQUAL(steps[1].description, stages[1]->m_when.description);
    CHECK_EQUAL(steps[3].description, stages[1]->m_then.description);
    CHECK_EQUAL(steps[6].description, stages[1]->m_finally.description);

    CHECK_EQUAL(steps[0].description, stages[2]->m_given.description);
    CHECK_EQUAL(steps[4].description, stages[2]->m_when.description);
    CHECK_EQUAL(steps[5].description, stages[2]->m_then.description);
    CHECK_EQUAL(steps[6].description, stages[2]->m_finally.description);

    CHECK_EQUAL("",                   stages[3]->m_given.description);
    CHECK_EQUAL(steps[9].description, stages[3]->m_when.description);
    CHECK_EQUAL(steps[10].description,stages[3]->m_then.description);
    CHECK_EQUAL("",                   stages[3]->m_finally.description);

    CHECK_EQUAL(steps[7].description, stages[4]->m_given.description);
    CHECK_EQUAL("",                   stages[4]->m_when.description);
    CHECK_EQUAL(steps[8].description, stages[4]->m_then.description);
    CHECK_EQUAL("",                   stages[4]->m_finally.description);
}
