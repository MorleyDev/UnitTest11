#include "GetRunner.hpp"

std::unique_ptr<ut11::TestFixtureRunner>& ut11::GetRunner()
{
	static std::unique_ptr<ut11::TestFixtureRunner> g_TestFixtureRunner;
	if (!g_TestFixtureRunner)
		g_TestFixtureRunner = std::unique_ptr<ut11::TestFixtureRunner>(new ut11::TestFixtureRunner());

	return g_TestFixtureRunner;
}
