#include <UnitTest11/TestFixtureRunner.hpp>

void ut11::TestFixtureRunner::AddFixture(std::unique_ptr<ITestFixture> fixture)
{
    m_fixtures.push_back(std::move(fixture));
}

int ut11::TestFixtureRunner::Run(IOutput& output)
{
    output.Begin();

    TestFixtureResults results;

    while(!m_fixtures.empty())
    {
        std::unique_ptr<ITestFixture> fixture = std::move(m_fixtures.front());
        m_fixtures.pop_front();

        TestFixtureResults result = fixture->Run(output);
        results.ran += result.ran;
        results.succeeded += result.succeeded;
    }

    output.Finish(results.ran, results.succeeded);
    return results.ran - results.succeeded;
}
