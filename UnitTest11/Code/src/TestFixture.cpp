#include <UnitTest11/TestFixture.hpp>

namespace ut11
{
    TestFixture::~TestFixture()
    {
    }

    TestFixtureImpl::TestFixtureImpl()
        : m_name(),
          m_StageBuilder(new ut11::Utility::TestStageBuilderImpl)
    {
    }

    TestFixtureImpl::TestFixtureImpl(std::string name)
        : m_name(name),
          m_StageBuilder(new ut11::Utility::TestStageBuilderImpl)
    {
    }

    TestFixtureImpl::TestFixtureImpl(std::string name, std::unique_ptr<ut11::Utility::TestStageBuilder> builder)
        : m_name(name),
          m_StageBuilder(std::move(builder))
    {
    }

    TestFixtureImpl::~TestFixtureImpl()
    {
    }

    void TestFixtureImpl::Given(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushGiven(Utility::TestStep(description, logic));
    }

    void TestFixtureImpl::When(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushWhen(Utility::TestStep(description, logic));
    }

    void TestFixtureImpl::Then(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushThen(Utility::TestStep(description, logic));
    }

    void TestFixtureImpl::Finally(std::string description, std::function<void(void)> logic)
    {
        m_StageBuilder->PushFinally(Utility::TestStep(description, logic));
    }

    TestFixtureResults TestFixtureImpl::Run(Output& output)
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

    void TestFixtureImpl::Run()
    {
    }
}
