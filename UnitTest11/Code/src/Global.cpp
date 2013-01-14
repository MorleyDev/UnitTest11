#include <UnitTest11/Global.hpp>
#include <UnitTest11/TestFixtureRunner.hpp>
#include <UnitTest11/StdOutput.hpp>

namespace
{
    ut11::TestFixtureRunner g_runner;
}

void ut11::PushFixture(std::unique_ptr<ITestFixture> fixture)
{
    g_runner.addFixture(std::move(fixture));
}

int ut11::Run()
{
    ut11::StdOutput stdOutput;
    return Run(stdOutput);
}

int ut11::Run(IOutput& output)
{
    return g_runner.Run(output);
}
