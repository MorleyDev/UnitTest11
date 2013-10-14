#ifndef UT11_DECLAREFIXTURE_HPP_INCLUDED
#define UT11_DECLAREFIXTURE_HPP_INCLUDED

#include "Category.hpp"
#include "TestFixtureAbstract.hpp"
#include "utility/ToString.hpp"
#include <memory>

namespace ut11
{
	namespace detail
	{
		extern void PushFixture(std::shared_ptr<TestFixtureAbstract>);

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

			template<typename... ARGS> int operator()(ARGS && ... args)
			{
				std::unique_ptr<T> fixture(new T(std::forward<ARGS>(args)...));
				fixture->SetName(m_name + "(" + GetString(args...));
				PushFixture(std::move(fixture));

				return 0;
			}

			template<typename... ARGS> int operator()(Category category, ARGS && ... args)
			{
				std::unique_ptr<T> fixture(new T(std::forward<ARGS>(args)...));
				fixture->SetName(m_name + "(" + GetString(args...));
				fixture->AddCategory(category);

				PushFixture(std::move(fixture));
				return 0;
			}

			template<typename... ARGS> int operator()(std::initializer_list<Category> categories, ARGS && ... args)
			{
				std::unique_ptr<T> fixture(new T(std::forward<ARGS>(args)...));
				fixture->SetName(m_name + "(" + GetString(args...));
				for (auto category : categories)
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
				return utility::ToString(value) + ", " + GetString(args...);
			}
		};
	}
}

#endif // !UT11_DECLAREFIXTURE_HPP_INCLUDED
