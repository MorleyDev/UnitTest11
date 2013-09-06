#ifndef UT11_MOCKVERIFY_HPP_INCLUDED
#define UT11_MOCKVERIFY_HPP_INCLUDED

#include <string>

namespace ut11
{
	template<typename T> struct MockVerifyer
	{
	private:
		T& mockObj;
		std::size_t line;
		std::string file;

	public:
		MockVerifyer(T& mock, std::size_t line, std::string file)
			: mockObj(mock),
			  line(line),
			  file(file)
		{
		}

		template<typename... ARGS> void operator()(const ARGS&... args)
		{
			mockObj.Verify(line, file, args...);
		}
	};
}

#endif // UT11_MOCKVERIFY_HPP_INCLUDED
