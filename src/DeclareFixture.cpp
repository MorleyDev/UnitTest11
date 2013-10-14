#include <UnitTest11/DeclareFixture.hpp>
#include "GetRunner.hpp"

void ut11::detail::PushFixture(std::shared_ptr<ut11::detail::TestFixtureAbstract> fixture)
{
	ut11::detail::GetRunner()->AddFixture(std::move(fixture));
}
