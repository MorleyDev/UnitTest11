#ifndef UNITTEST11_GLOBAL_HPP
#define UNITTEST11_GLOBAL_HPP

#include "TestFixture.hpp"
#include "Output.hpp"

#include "Utility/ToString.hpp"

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

    void PushFixture(std::shared_ptr<TestFixtureAbstract>);

    template<typename T>
    struct DeclareFixtureObj
    {
    private:
    	std::string m_name;

    public:
    	 explicit DeclareFixtureObj(std::string name)
    	 	 : m_name(name)
    	 {
    	 }

        template<typename... ARGS>
        int operator()(ARGS&&... args)
        {
            std::unique_ptr<T> fixture( new T(std::forward<ARGS>(args)...) );
            fixture->SetName(m_name + "(" + GetString(args...));
            PushFixture(std::move(fixture));

            return 0;
        }

    private:
        static std::string GetString()
        {
        	return ")";
        }

        template<typename V, typename... ARGS>
        static std::string GetString(const V& value, const ARGS&... args)
        {
        	return Utility::ToString(value) + ", " + GetString(args...);
        }
    };
}

#endif // UNITTEST11_GLOBAL_HPP
