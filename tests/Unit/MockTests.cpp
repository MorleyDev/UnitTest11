#include <UnitTest11/Core.hpp>
#include <UnitTest11/detail/TestFailedException.hpp>
#include <UnitTest11/Is/Any.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Will/Throw.hpp>
#include <UnitTest11/Will/Pass.hpp>
#include <UnitTest11/Mock.hpp>

class MockTest : public ut11::TestFixture
{
private:
	ut11::Mock<int (char)> m_mock;

	char m_expectedParameter;
	int m_expectedReturn;

	char m_actualParameter;
	int m_actualReturn;

public:
	virtual void Run()
	{
		Given("a Mock", [&]() {
			m_mock = ut11::Mock<int (char)>();

		});

		Then("VerifyAny fails as expected", [&]() {
			AssertThat([&]() { MockVerify(m_mock)(ut11::Is::Any<char>()); }, ut11::Will::Throw<ut11::detail::TestFailedException>());
		});

		When("calling the Mock", [&]() {

			m_expectedParameter = 'A';

			m_mock(m_expectedParameter);

		});

		Then("the Mock verifies with the expected parameters as expected", [&]() {
			MockVerify(m_mock)(ut11::Is::Any<char>());
			MockVerify(m_mock)(m_expectedParameter);
			MockVerifyTimes(1, m_mock)(m_expectedParameter);
		});
		Then("the Mock verifies passes as expected when with an operand", [&]() {

			std::size_t v = 0;
			auto lambda = [&](std::size_t t)
							{
								v = t;
								return true;
							};
			MockVerifyTimes(ut11::Will::Pass(lambda), m_mock)(m_expectedParameter);
			AssertThat(v, ut11::Is::EqualTo(1));
		});

		Then("the Mock verifies fails as expected when with the wrong parameters", [&]() {

			AssertThat([&]() { MockVerify(m_mock)('\n'); }, ut11::Will::Throw<ut11::detail::TestFailedException>());
		});

		Then("the Mock verifies fails as expected when with the wrong VerifyTimes", [&]() {

			AssertThat([&]() { MockVerifyTimes(2, m_mock)(m_expectedParameter); }, ut11::Will::Throw<ut11::detail::TestFailedException>());
		});
		Then("the Mock verifies fails as expected when with an operand", [&]() {

			std::size_t v = 0;
			auto lambda = [&](std::size_t t)
						{
							AssertThat(v, ut11::Is::EqualTo(1));
							return false;
						};

			AssertThat([&]() { MockVerifyTimes(ut11::Will::Pass(lambda), m_mock)(m_expectedParameter); }, ut11::Will::Throw<ut11::detail::TestFailedException>());
		});

		When("setting a callback calling the Mock", [&]() {

			m_expectedParameter = 'A';

			m_mock.SetCallback([&](char c)
			{
				m_actualParameter = c;
			});

			m_mock(m_expectedParameter);
		});

		Then("the expected parameter was passed in to the callback", [&]() {
			AssertThat(m_actualParameter, ut11::Is::EqualTo(m_expectedParameter));
		});

		When("setting a return value, calling the Mock", [&]() {

			m_expectedReturn = 5;

			m_mock.SetReturn(m_expectedReturn);

			m_actualReturn = m_mock('P');
		});

		Then("the expected return value was returned", [&]() {
			AssertThat(m_actualReturn, ut11::Is::EqualTo(m_expectedReturn));
		});
	}
};
DeclareFixture(MockTest)(ut11::Category("unit"));

class MockVoidTest : public ut11::TestFixture
{
private:
	ut11::Mock<void (void)> m_mock;

public:
	virtual void Run()
	{
		Given("a Mock that takes no arguments and returns void", [&]() {
			m_mock = ut11::Mock<void (void)>();
		});

		When("the Mock is called", [&]() {
			m_mock();
		});

		Then("the mock verifies as expected", [&]() {
			MockVerify(m_mock)();
			MockVerifyTimes(1, m_mock)();
		});

		Then("verifying the wrong number of times causes a failure", [&]() {
			AssertThat([&]() { MockVerifyTimes(2, m_mock)(); }, ut11::Will::Throw<ut11::detail::TestFailedException>());
		});
	}
};
DeclareFixture(MockVoidTest)(ut11::Category("unit"));
