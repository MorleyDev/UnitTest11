/*
 * Category.hpp
 *
 *  Created on: 10 Jun 2013
 *      Author: Jason
 */

#ifndef UT11_CATEGORY_HPP_INCLUDED
#define UT11_CATEGORY_HPP_INCLUDED

#include <string>

namespace ut11
{
	struct Category
	{
	public:
		Category(std::string category)
			: m_category(category)
		{
		}

		const std::string& GetName() const
		{
			return m_category;
		}

		bool operator==(const Category& other) const
		{
			return m_category == other.m_category;
		}

		bool operator<(const Category& other) const
		{
			return m_category < other.m_category;
		}

	private:
		std::string m_category;
	};
}

#endif /* UT11_CATEGORY_HPP_INCLUDED */
