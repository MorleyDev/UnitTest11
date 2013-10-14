#include "GetRunner.hpp"

std::unique_ptr<ut11::detail::TestFixtureRunner>& ut11::detail::GetRunner()
{
	static std::unique_ptr<ut11::detail::TestFixtureRunner> g_TestFixtureRunner;
	if (!g_TestFixtureRunner)
		g_TestFixtureRunner = std::unique_ptr<ut11::detail::TestFixtureRunner>(new ut11::detail::TestFixtureRunner());

	return g_TestFixtureRunner;
}
