#include <UnitTest11/Core.hpp>
#include <UnitTest11/out/StdOutput.hpp>
#include <UnitTest11/Is/EqualTo.hpp>

class StdOutputTests : public ut11::TestFixture
{
private:
	std::stringstream m_actualOutput;
	std::unique_ptr<ut11::out::StdOutput> m_output;

public:
	virtual void Run()
	{
		Given("an output stream and output", [&]()
		{
			m_actualOutput.str("");
			m_output = std::unique_ptr<ut11::out::StdOutput>(new ut11::out::StdOutput(m_actualOutput));
		});
		When("begin and end without running any tests", [&]()
		{
			m_output->Begin();
			m_output->Finish(10, 7);
		});
		Then("the output is as expected", [&]()
		{
			AssertThat(m_actualOutput.str(), ut11::Is::EqualTo("\nFinished!\nRan: 10\nSucceeded: 7\n"));
		});

		When("running a test fixture with just a Then", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 1);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\t\t\tThen: then \n\nFinished!\nRan: 1\nSucceeded: 1\n"));
		});

		When("running two test fixtures with just a Then", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->BeginFixture("fixture2");
			m_output->BeginTest();
			m_output->BeginThen("then2");
			m_output->EndThen("then2");
			m_output->EndTest();
			m_output->EndFixture("fixture2");
			m_output->Finish(2, 2);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			startOfTime = stringVal.find('[');
			endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\t\t\tThen: then \nFixture: fixture2\n\t\t\tThen: then2 \n\nFinished!\nRan: 2\nSucceeded: 2\n"));
		});

		When("running a test fixture with just a When and Then", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 1);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\t\tWhen: when\n\t\t\tThen: then \n\nFinished!\nRan: 1\nSucceeded: 1\n"));
		});

		When("running a test fixture with a Given When and Then", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 1);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\t\tWhen: when\n\t\t\tThen: then \n\nFinished!\nRan: 1\nSucceeded: 1\n"));
		});

		When("running a test fixture with a Given When Then Finally", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 1);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\t\tWhen: when\n\t\t\tThen: then \n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 1\n"));
		});

		When("running a test fixture with multiple tests with a Given When Then Finally where the Given and Whens repeat", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then2");
			m_output->EndThen("then2");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 1);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			startOfTime = stringVal.find('[');
			endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\t\tWhen: when\n\t\t\tThen: then \n\t\t\tThen: then2 \n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 1\n"));
		});

		When("running a test fixture with a When Then Finally", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 1);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\t\tWhen: when\n\t\t\tThen: then \n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 1\n"));
		});

		When("running a test fixture with a Then Finally", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginThen("then");
			m_output->EndThen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 1);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			auto endOfTime = stringVal.find(']');
			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\t\t\tThen: then \n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 1\n"));
		});

		When("running a test fixture with a Given When Then Finally and the Then fails with an std::exception", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->OnError(std::runtime_error("error"));
			m_output->EndThen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 0);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			startOfTime = stringVal.substr(startOfTime + 1).find('[') + startOfTime;

			auto endOfTime = stringVal.find(']');
			endOfTime = stringVal.substr(endOfTime + 1).find(']') + endOfTime + 1;

			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\t\tWhen: when\n\t\t\tThen: then\n\tFailed: std::exception was thrown [what(): error]\n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 0\n"));
		});

		When("running a test fixture with a Given When Then Finally and the Then fails with an unknown error", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->OnUnknownError();
			m_output->EndThen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 0);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			startOfTime = stringVal.substr(startOfTime + 1).find('[') + startOfTime;

			auto endOfTime = stringVal.find(']');
			endOfTime = stringVal.substr(endOfTime + 1).find(']') + endOfTime + 1;

			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\t\tWhen: when\n\t\t\tThen: then\n\tFailed: Unknown Error\n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 0\n"));
		});

		When("running a test fixture with a Given When Then Finally and the Then fails", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->EndWhen("then");
			m_output->BeginThen("then");
			m_output->OnError(10, "file", "error");
			m_output->EndThen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 0);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			startOfTime = stringVal.substr(startOfTime + 1).find('[') + startOfTime;

			auto endOfTime = stringVal.find(']');
			endOfTime = stringVal.substr(endOfTime + 1).find(']') + endOfTime + 1;

			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\t\tWhen: when\n\t\t\tThen: then\n\tFailed: [10:file] error\n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 0\n"));
		});


		When("running a test fixture with a Given When Finally and the When fails", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginWhen("when");
			m_output->OnError(10, "file", "error");
			m_output->EndWhen("then");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 0);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			startOfTime = stringVal.substr(startOfTime + 1).find('[') + startOfTime;

			auto endOfTime = stringVal.find(']');
			endOfTime = stringVal.substr(endOfTime + 1).find(']') + endOfTime + 1;

			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\t\tWhen: when\n\tFailed: [10:file] error\n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 0\n"));
		});


		When("running a test fixture with a Given Finally and the Given fails", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->OnError(10, "file", "error");
			m_output->EndGiven("given");
			m_output->BeginFinally("finally");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 0);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			startOfTime = stringVal.substr(startOfTime + 1).find('[') + startOfTime;

			auto endOfTime = stringVal.find(']');
			endOfTime = stringVal.substr(endOfTime + 1).find(']') + endOfTime + 1;

			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\tFailed: [10:file] error\n\tFinally: finally\n\nFinished!\nRan: 1\nSucceeded: 0\n"));
		});

		When("running a test fixture with a Given Finally and the Finally fails", [&]()
		{
			m_output->Begin();
			m_output->BeginFixture("fixture");
			m_output->BeginTest();
			m_output->BeginGiven("given");
			m_output->EndGiven("given");
			m_output->BeginFinally("finally");
			m_output->OnError(10, "file", "error");
			m_output->EndFinally("finally");
			m_output->EndTest();
			m_output->EndFixture("fixture");
			m_output->Finish(1, 0);
		});
		Then("the output is as expected", [&]()
		{
			auto stringVal = m_actualOutput.str();
			auto startOfTime = stringVal.find('[');
			startOfTime = stringVal.substr(startOfTime + 1).find('[') + startOfTime;

			auto endOfTime = stringVal.find(']');
			endOfTime = stringVal.substr(endOfTime + 1).find(']') + endOfTime + 1;

			stringVal = stringVal.erase(startOfTime, endOfTime - startOfTime + 1);

			AssertThat(stringVal, ut11::Is::EqualTo("Fixture: fixture\n\tGiven: given\n\tFinally: finally\n\tFailed: [10:file] error\n\nFinished!\nRan: 1\nSucceeded: 0\n"));
		});
	}
};
DeclareFixture(StdOutputTests)(ut11::Category("unit"));
