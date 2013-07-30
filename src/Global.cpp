#include <UnitTest11/Global.hpp>
#include <UnitTest11/TestFixtureRunner.hpp>
#include <UnitTest11/StdOutput.hpp>

namespace
{
    std::unique_ptr<ut11::TestFixtureRunner> g_runner;
}

inline void InitialiseRunner()
{
    if ( !g_runner )
        g_runner = std::move(std::unique_ptr<ut11::TestFixtureRunner>(new ut11::TestFixtureRunner()));
}

void ut11::PushFixture(std::shared_ptr<TestFixtureAbstract> fixture)
{
    InitialiseRunner();

    g_runner->AddFixture(std::move(fixture));
}

int ut11::Run()
{
    ut11::StdOutput stdOutput;

    return Run(stdOutput);
}

inline std::vector<std::string> ExtractCategoriesFromArguments(std::vector<std::string> arguments)
{
	std::vector<std::string> categories;
	for(auto argument : arguments)
	{
		std::string keyName = "category=";
		if ( argument.size() > keyName.size() )
		{
			auto keyLength = keyName.size();
			auto category = argument.substr(keyName.size(), argument.size() - keyLength);
			categories.push_back(category);
		}
	}
	return categories;
}

int ut11::Run(const int argumentCount, const char** arguments)
{
    ut11::StdOutput stdOutput;

    return Run(stdOutput, argumentCount, arguments);
}

int ut11::Run(Output& output, const int argumentCount, const char** arguments)
{
	std::vector<std::string> argumentVector;
	for(auto i = 1; i < argumentCount; ++i)
		argumentVector.push_back(arguments[i]);

    auto categories = ExtractCategoriesFromArguments(argumentVector);
    if ( !categories.empty() )
    	return RunCategories(output, categories);

    return Run(output);
}

int ut11::Run(Output& output)
{
    InitialiseRunner();

    return g_runner->Run(output);
}

int ut11::RunCategories(Output& output, std::vector<std::string> fixtures)
{
    InitialiseRunner();

    return g_runner->RunCategories(output, fixtures);
}
