#include <UnitTest11/Core.hpp>
#include <UnitTest11/TestFailedException.hpp>
#include <UnitTest11/Is/EqualTo.hpp>

class AssertFailTests : public ut11::TestFixture
{
private:
	ut11::TestFailedException m_exception;

	std::size_t line;
	std::string file;
	std::string message;

public:
	virtual void Run()
	{
		When("calling Assert Fail", [&]()
		{
			line = 132;
			file = "some file";
			message = "some message";

			try
			{
				ut11::Assert::Fail(line, file, message);
			}
			catch(const ut11::TestFailedException& ex)
			{
				m_exception = ex;
				return;
			}
		});

		Then("the expected exception is thrown", [&]()
		{
			AssertThat(line, ut11::Is::EqualTo(m_exception.GetLine()));
			AssertThat(file, ut11::Is::EqualTo(m_exception.GetFile()));
			AssertThat(message, ut11::Is::EqualTo(m_exception.GetMessage()));
		});
	}
};
DeclareFixture(AssertFailTests)(ut11::Category("unit"));
