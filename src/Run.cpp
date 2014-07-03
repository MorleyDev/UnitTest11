#include <UnitTest11/Run.hpp>
#include <UnitTest11/out/StdOutput.hpp>
#include "detail/GetRunner.hpp"

namespace
{
	inline std::vector<std::string> ExtractCategoriesFromArguments(std::vector<std::string> arguments)
	{
		std::vector<std::string> categories;
		for (auto argument : arguments)
		{
			std::string keyName = "category=";
			if (argument.size() > keyName.size())
			{
				auto keyLength = keyName.size();
				auto category = argument.substr(keyName.size(), argument.size() - keyLength);
				categories.push_back(category);
			}
		}
		return categories;
	}
}

int ut11::Run()
{
	ut11::out::StdOutput stdOutput;

	return Run(stdOutput);
}

int ut11::Run(const int argumentCount, const char* const* arguments)
{
	ut11::out::StdOutput stdOutput;

	return Run(stdOutput, argumentCount, arguments);
}

int ut11::Run(out::Output& output, const int argumentCount, const char* const* arguments)
{
	std::vector<std::string> argumentVector;
	for (auto i = 1; i < argumentCount; ++i)
		argumentVector.push_back(arguments[i]);

	auto categories = ExtractCategoriesFromArguments(argumentVector);
	if (!categories.empty())
		return RunCategories(output, categories);

	return Run(output);
}

int ut11::Run(out::Output& output)
{
	return ut11::detail::GetRunner()->Run(output);
}

int ut11::RunCategories(out::Output& output, std::vector<std::string> fixtures)
{
	return ut11::detail::GetRunner()->RunCategories(output, fixtures);
}
