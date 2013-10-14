#ifndef UT11_SRC_GETRUNNER_HPP_INCLUDED
#define UT11_SRC_GETRUNNER_HPP_INCLUDED

#include "UnitTest11/TestFixtureRunner.hpp"
#include <memory>

namespace ut11
{
	namespace detail
	{
		extern std::unique_ptr<ut11::detail::TestFixtureRunner>& GetRunner();
	}
}

#endif // UT11_SRC_GETRUNNER_HPP_INCLUDED
