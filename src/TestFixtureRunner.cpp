#include <UnitTest11/TestFixtureRunner.hpp>
#include <iostream>

void ut11::TestFixtureRunner::AddFixture(std::shared_ptr<TestFixtureAbstract> fixture)
{
    m_fixtures.insert(std::make_pair(fixture->GetName(), std::move(fixture)));
}

int ut11::TestFixtureRunner::Run(Output& output)
{
    output.Begin();

    TestFixtureResults results;
    for(auto fixtureKeyValue : m_fixtures)
    {
    	auto fixture = fixtureKeyValue.second;
        auto result = fixture->Run(output);

        results.ran += result.ran;
        results.succeeded += result.succeeded;
    }

    output.Finish(results.ran, results.succeeded);
    return results.ran - results.succeeded;
}
