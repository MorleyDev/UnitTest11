#ifndef UNITTEST11_GLOBAL_HPP
#define UNITTEST11_GLOBAL_HPP

#include "TestFixture.hpp"
#include "Output.hpp"
#include "Category.hpp"
#include "Utility/ToString.hpp"

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
    int Run(const int argumentCount, const char** arguments);

    /*! \brief Runs all test fixtures using the passed output to report tests being ran, success and failures.
     *
     * \return The number of fixtures that failed
     */
    int Run(Output&);

    /*! \brief Runs test fixtures with the given output, using the passes arguments to deduce the fixtures to run
     *
     * \return The number of fixtures that failed
     */
    int Run(Output&, const int argumentCount, const char** arguments);

    /*! \brief Runs all test fixtures that have a category that matches one of the given regular expressions
     *
     * \return The number of fixtures that failed
     */
    int RunCategories(Output&, std::vector<std::string> regex);

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

        template<typename... ARGS> int operator()(ARGS&&... args)
        {
            std::unique_ptr<T> fixture( new T(std::forward<ARGS>(args)...) );
            fixture->SetName(m_name + "(" + GetString(args...));
            PushFixture(std::move(fixture));

            return 0;
        }

        template<typename... ARGS> int operator()(Category category, ARGS&&... args)
        {
            std::unique_ptr<T> fixture( new T(std::forward<ARGS>(args)...) );
            fixture->SetName(m_name + "(" + GetString(args...));
            fixture->AddCategory(category);

            PushFixture(std::move(fixture));
            return 0;
        }

        template<typename... ARGS> int operator()(std::initializer_list<Category> categories, ARGS&&... args)
        {
            std::unique_ptr<T> fixture( new T(std::forward<ARGS>(args)...) );
            fixture->SetName(m_name + "(" + GetString(args...));
            for(auto category : categories)
            	fixture->AddCategory(category);

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
