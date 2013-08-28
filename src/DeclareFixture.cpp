#include <UnitTest11/DeclareFixture.hpp>
#include "GetRunner.hpp"

void ut11::PushFixture(std::shared_ptr<TestFixtureAbstract> fixture)
{
	GetRunner()->AddFixture(std::move(fixture));
}
