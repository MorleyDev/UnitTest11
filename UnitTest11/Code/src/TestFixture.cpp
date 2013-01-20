#include <UnitTest11/TestFixture.hpp>

namespace ut11
{
    ITestFixture::~ITestFixture()
    {
    }

    TestFixture::TestFixture()
        : m_name(),
          m_stageBuilder(new ut11::Utility::TestStageBuilder)
    {
    }

    TestFixture::TestFixture(std::string name)
        : m_name(name),
          m_stageBuilder(new ut11::Utility::TestStageBuilder)
    {
    }

    TestFixture::TestFixture(std::string name, std::unique_ptr<ut11::Utility::ITestStageBuilder> builder)
        : m_name(name),
          m_stageBuilder(std::move(builder))
    {
    }

    TestFixture::~TestFixture()
    {
    }

    void TestFixture::Given(std::string description, std::function<void(void)> logic)
    {
        m_stageBuilder->pushGiven(Utility::TestStep(description, logic));
    }

    void TestFixture::When(std::string description, std::function<void(void)> logic)
    {
        m_stageBuilder->pushWhen(Utility::TestStep(description, logic));
    }

    void TestFixture::Then(std::string description, std::function<void(void)> logic)
    {
        m_stageBuilder->pushThen(Utility::TestStep(description, logic));
    }

    void TestFixture::Finally(std::string description, std::function<void(void)> logic)
    {
        m_stageBuilder->pushFinally(Utility::TestStep(description, logic));
    }

    TestFixtureResults TestFixture::Run(IOutput& output)
    {
        output.BeginFixture(m_name);
        Run();

        TestFixtureResults counter;
        auto stages = m_stageBuilder->stage();
        for(auto stage : stages)
        {
            ++counter.ran;

            if ( stage->Run(output) )
                ++counter.succeeded;
        }
        output.EndFixture(m_name);
        return counter;
    }

    void TestFixture::Run()
    {
    }
}
