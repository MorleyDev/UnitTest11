/*
 * DeclareTestFixtureWithArgumentsTests.cpp
 *
 *  Created on: 25 May 2013
 *      Author: Jason
 */

#include <UnitTest11.hpp>

class DeclareTestFixtureWithArgumentsTests : public ut11::TestFixture
{
private:
	ut11::Mock<void (int, std::string, int)> m_mockConstructor;
public:
	DeclareTestFixtureWithArgumentsTests(int a, std::string b, int c)
		: m_mockConstructor()
	{
		m_mockConstructor(a,b,c);
	}

	virtual void Run()
	{
		Then("the expected arguments were passed to the constructor", [&]() {
			MockVerify(m_mockConstructor, 1, "hello", 3);
		});
	}
};
DeclareFixture(DeclareTestFixtureWithArgumentsTests, 1, "hello", 3);
