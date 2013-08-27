#include <UnitTest11.hpp>

namespace
{
	template<typename T> struct MockOperand : public ut11::Utility::BaseOperand<MockOperand<T>>
	{
	private:
		mutable ut11::Mock< bool (T) >* m_mock;

	public:
		MockOperand(ut11::Mock<bool (T) >& mock) 
			: m_mock(&mock) 
		{
		}

		bool operator()(const T& input) const
		{
			return (*m_mock)(input);
		}
		
		inline std::string GetErrorMessage(const T& actual) const
		{
			return "error message";
		}
	};
}

class AndOperandTests : public ut11::TestFixture
{
private:
	ut11::Mock < bool (int) > m_mockOperandA, m_mockOperandB;
	int m_input;
	bool m_result;

	void GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(bool first, bool second, bool expectedResult)
	{
		auto firstDescription = std::string("the first operand ") + (first ? "succeeds" : "fails");
		auto secondDescription = std::string("the second operand ") + (first ? "succeeds" : "fails");

		Given(std::string("two operands and ") + firstDescription + " and " + secondDescription, [&, first, second]()
		{
			m_mockOperandA = ut11::Mock < bool (int) >();
			m_mockOperandA.SetReturn(first);

			m_mockOperandB = ut11::Mock < bool (int) >();
			m_mockOperandB.SetReturn(second);
		});
		When("calculating the result using an AndOperand", [&]()
		{
			m_input = 1234;
			m_result = ut11::Utility::AndOperand < MockOperand<int>, MockOperand<int> >(MockOperand<int>(m_mockOperandA), MockOperand<int>(m_mockOperandB))(m_input);
		});
		Then("the first operand was called with the expected input", [&]()
		{
			MockVerify(m_mockOperandA)(m_input);
		});
		if ( first ) Then("the second operand was called with the expected input", [&]()
		{
			MockVerify(m_mockOperandB)(m_input);
		});
		else Then("the second operand was not called", [&]()
		{
			MockVerifyTimes(0, m_mockOperandB)(ut11::Is::Any<int>());
		});
		Then(std::string("the result is ") + (expectedResult ? "true" : "false"), [&, expectedResult]()
		{
			AssertThat(m_result, ut11::Is::EqualTo(expectedResult));
		});
		Then("there is an error message", [&]() 
		{
			AssertThat(ut11::Utility::AndOperand < MockOperand<int>, MockOperand<int> >(MockOperand<int>(m_mockOperandA), MockOperand<int>(m_mockOperandB)).GetErrorMessage(m_input),
					   ut11::Is::Not::Empty);
		});
	}

public:
	virtual void Run()
	{
		Then("AndOperand is an Operand", [&]()
		{
			AssertThat(ut11::Utility::IsOperand < ut11::Utility::AndOperand < MockOperand<int>, MockOperand<int> >> ::value, ut11::Is::True);
		});

		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(true, true, true);
		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(false, true, false);
		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(true, false, false);
		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(false, false, false);
	}
};
DeclareFixture(AndOperandTests)(ut11::Category("unit"));

class OrOperandTests : public ut11::TestFixture
{
private:
	ut11::Mock < bool (int) > m_mockOperandA, m_mockOperandB;
	int m_input;
	bool m_result;

	void GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(bool first, bool second, bool expectedResult)
	{
		auto firstDescription = std::string("the first operand ") + (first ? "succeeds" : "fails");
		auto secondDescription = std::string("the second operand ") + (first ? "succeeds" : "fails");

		Given(std::string("two operands and ") + firstDescription + " and " + secondDescription, [&, first, second]()
		{
			m_mockOperandA = ut11::Mock < bool (int) >();
			m_mockOperandA.SetReturn(first);

			m_mockOperandB = ut11::Mock < bool (int) >();
			m_mockOperandB.SetReturn(second);
		});
		When("calculating the result using an OrOperand", [&]()
		{
			m_input = 1234;
			m_result = ut11::Utility::OrOperand < MockOperand<int>, MockOperand<int> >(MockOperand<int>(m_mockOperandA), MockOperand<int>(m_mockOperandB))(m_input);
		});
		Then("the first operand was called with the expected input", [&]()
		{
			MockVerify(m_mockOperandA)(m_input);
		});
		if ( !first ) Then("the second operand was called with the expected input", [&]()
		{
			MockVerify(m_mockOperandB)(m_input);
		});
		else Then("the second operand was not called", [&]()
		{
			MockVerifyTimes(0, m_mockOperandB)(ut11::Is::Any<int>());
		});
		Then(std::string("the result is ") + (expectedResult ? "true" : "false"), [&, expectedResult]()
		{
			AssertThat(m_result, ut11::Is::EqualTo(expectedResult));
		});
		Then("there is an error message", [&]() 
		{
			AssertThat(ut11::Utility::OrOperand < MockOperand<int>, MockOperand<int> >(MockOperand<int>(m_mockOperandA), MockOperand<int>(m_mockOperandB)).GetErrorMessage(m_input),
					   ut11::Is::Not::Empty);
		});
	}

public:
	virtual void Run()
	{
		Then("OrOperand is an Operand", [&]()
		{
			AssertThat(ut11::Utility::IsOperand < ut11::Utility::OrOperand < MockOperand<int>, MockOperand<int> >>::value, ut11::Is::True);
		});

		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(true, true, true);
		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(false, true, true);
		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(true, false, true);
		GivenTwoOperandsWhenResultOfFirstIsXAndResultOfSecondIsYThenResultIsZ(false, false, false);
	}
};
DeclareFixture(OrOperandTests)(ut11::Category("unit"));

class NotOperandTests : public ut11::TestFixture
{
private:
	ut11::Mock < bool (int) > m_mockOperandA;
	int m_input;
	bool m_result;

	void GivenOperandWhenResultOfOperandIsXThenResultIsZ(bool first, bool expectedResult)
	{
		Given(std::string("an operand that ") + (first ? "succeeds" : "fails"), [&, first]()
		{
			m_mockOperandA = ut11::Mock < bool (int) >();
			m_mockOperandA.SetReturn(first);

		});
		When("calculating the result using a NotOperand", [&]()
		{
			m_input = 1234;

			m_result = ut11::Utility::NotOperand < MockOperand<int> >(MockOperand<int>(m_mockOperandA))(m_input);
		});
		Then("the operand was called with the expected input", [&]()
		{
			MockVerify(m_mockOperandA)(m_input);
		});
		Then(std::string("the result is ") + (expectedResult ? "true" : "false"), [&, expectedResult]()
		{
			AssertThat(m_result, ut11::Is::EqualTo(expectedResult));
		});
		Then("there is an error message", [&]()
		{
			AssertThat(ut11::Utility::NotOperand < MockOperand<int> >(MockOperand<int>(m_mockOperandA)).GetErrorMessage(m_input), ut11::Is::Not::Empty);
		});
	}

public:
	virtual void Run()
	{
		Then("NotOperand is an Operand", [&]()
		{
			AssertThat(ut11::Utility::IsOperand < ut11::Utility::NotOperand < MockOperand<int> >> ::value, ut11::Is::True);
		});

		GivenOperandWhenResultOfOperandIsXThenResultIsZ(true, false);
		GivenOperandWhenResultOfOperandIsXThenResultIsZ(false, true);
	}
};
DeclareFixture(NotOperandTests)(ut11::Category("unit"));
