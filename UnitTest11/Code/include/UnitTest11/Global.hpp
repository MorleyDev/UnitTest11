#ifndef UNITTEST11_GLOBAL_HPP
#define UNITTEST11_GLOBAL_HPP

#include "TestFixture.hpp"
#include "Output.hpp"

namespace ut11
{
	/*! \brief Runs all test fixtures with the default std::cout output
	 *
	 * \return The number of fixtures that failed
	 */
	int Run();

	/*! \brief Runs all test fixtures using the passed output to report tests being ran, success and failures.
	 *
	 * \return The number of fixtures that failed
	 */
	int Run(Output&);

    void PushFixture(std::shared_ptr<TestFixture>);

    template<typename T>
    struct DeclareFixtureObj
    {
        template<typename... ARGS>
        explicit DeclareFixtureObj(std::string name, ARGS&&... args)
        {
            std::unique_ptr<T> fixture( new T(std::forward<ARGS>(args)...) );
            fixture->SetName(name);
            PushFixture(std::move(fixture));
        }
    };
}

#endif // UNITTEST11_GLOBAL_HPP
