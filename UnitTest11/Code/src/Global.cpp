#include <UnitTest11/Global.hpp>
#include <UnitTest11/TestFixtureRunner.hpp>
#include <UnitTest11/StdOutput.hpp>

namespace
{
    std::unique_ptr<ut11::TestFixtureRunner> g_runner;
}

inline void InitialiseRunner()
{
    if ( !g_runner )
        g_runner = std::move(std::unique_ptr<ut11::TestFixtureRunner>(new ut11::TestFixtureRunner()));
}

void ut11::PushFixture(std::unique_ptr<ITestFixture> fixture)
{
    InitialiseRunner();

    g_runner->AddFixture(std::move(fixture));
}

int ut11::Run()
{
    ut11::StdOutput stdOutput;
    return Run(stdOutput);
}

int ut11::Run(IOutput& output)
{
    InitialiseRunner();

    return g_runner->Run(output);
}
