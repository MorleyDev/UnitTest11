#include <UnitTest11/TestFixture.hpp>

namespace ut11
{
    ITestFixture::~ITestFixture()
    {
    }

    TestFixture::TestFixture()
        : m_name(),
          m_StageBuilder(new ut11::Utility::TestStageBuilder)
    {
    }

    TestFixture::TestFixture(std::string name)
        : m_name(name),
          m_StageBuilder(new ut11::Utility::TestStageBuilder)
    {
    }

    TestFixture::TestFixture(std::string name, std::unique_ptr<ut11::Utility::ITestStageBuilder> builder)
        : m_name(name),
          m_StageBuilder(std::move(builder))
    {
    }

    TestFixture::~TestFixture()
    {
    }

    void TestFixture::Given(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushGiven(Utility::TestStep(description, logic));
    }

    void TestFixture::When(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushWhen(Utility::TestStep(description, logic));
    }

    void TestFixture::Then(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushThen(Utility::TestStep(description, logic));
    }

    void TestFixture::Finally(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushFinally(Utility::TestStep(description, logic));
    }

    TestFixtureResults TestFixture::Run(IOutput& output)
    {
        output.BeginFixture(m_name);
        Run();

        TestFixtureResults counter;
        auto Stages = m_StageBuilder->Stage();
        for(auto Stage : Stages)
        {
            ++counter.ran;

            if ( Stage->Run(output) )
                ++counter.succeeded;
        }
        output.EndFixture(m_name);
        return counter;
    }

    void TestFixture::Run()
    {
    }
}
