/*
 * Empty.hpp
 *
 *  Created on: 27 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_IS_EMPTY_HPP_INCLUDED
#define UT11_IS_EMPTY_HPP_INCLUDED

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"

#include <string>
#include <sstream>

namespace ut11
{
    namespace Operands
    {
        struct IsEmpty : public ut11::Utility::BaseOperand
        {
        	inline bool operator()(const char* actual) const { return std::string(actual).length() == 0; }

            template<typename T> inline bool operator()(const T& actual) const
            {
            	for(const auto& i : actual)
            		return false;
                return true;
            }

            template<typename U> inline std::string GetErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected empty but was " << Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

	namespace Is
	{
		extern Operands::IsEmpty Empty;

		namespace Not
		{
			extern Utility::NotOperand<Operands::IsEmpty> Empty;
		}
	}
}


#endif /* UT11_IS_EMPTY_HPP_INCLUDED */
