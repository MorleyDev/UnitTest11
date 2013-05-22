#include <UnitTest11/TestFixtureRunner.hpp>

void ut11::TestFixtureRunner::AddFixture(std::shared_ptr<TestFixture> fixture)
{
    m_fixtures.push_back(std::move(fixture));
}

int ut11::TestFixtureRunner::Run(Output& output)
{
    output.Begin();

    TestFixtureResults results;

    while(!m_fixtures.empty())
    {
        std::shared_ptr<TestFixture> fixture = std::move(m_fixtures.front());
        m_fixtures.pop_front();

        TestFixtureResults result = fixture->Run(output);
        results.ran += result.ran;
        results.succeeded += result.succeeded;
    }

    output.Finish(results.ran, results.succeeded);
    return results.ran - results.succeeded;
}
