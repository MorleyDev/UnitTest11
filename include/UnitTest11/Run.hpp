#ifndef UT11_RUN_HPP_INCLUDED
#define UT11_RUN_HPP_INCLUDED

#include "out/Output.hpp"
#include <vector>
#include <string>

namespace ut11
{
	/*! \brief Runs all test fixtures with the default std::cout output
	*
	* \return The number of fixtures that failed
	*/
	int Run();

	/*! \brief Runs test fixtures with the default std::cout output, using the passes arguments to deduce the fixtures to run
	*
	* \return The number of fixtures that failed
	*/
	int Run(const int argumentCount, const char* const* arguments);

	/*! \brief Runs all test fixtures using the passed output to report tests being ran, success and failures.
	*
	* \return The number of fixtures that failed
	*/
	int Run(out::Output&);

	/*! \brief Runs test fixtures with the given output, using the passes arguments to deduce the fixtures to run
	*
	* \return The number of fixtures that failed
	*/
	int Run(out::Output&, const int argumentCount, const char* const* arguments);

	/*! \brief Runs all test fixtures that have a category that matches one of the given names
	*
	* \return The number of fixtures that failed
	*/
	int RunCategories(out::Output&, std::vector<std::string> fixtures);
}
#endif // !UT11_RUN_HPP_INCLUDED
