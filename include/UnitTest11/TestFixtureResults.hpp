#ifndef UT11_TESTFIXTURERESULTS_HPP_INCLUDED
#define UT11_TESTFIXTURERESULTS_HPP_INCLUDED

#include <cstdlib>

namespace ut11
{
	struct TestFixtureResults
	{
		TestFixtureResults() : ran(0), succeeded(0) { }

		std::size_t ran;
		std::size_t succeeded;
	};
}

#endif // UT11_TESTFIXTURERESULTS_HPP_INCLUDED