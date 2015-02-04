#ifndef UT11_DETAIL_MOCKTIMESVERIFY_HPP_INCLUDED
#define UT11_DETAIL_MOCKTIMESVERIFY_HPP_INCLUDED

#include <string>

namespace ut11
{
	namespace detail
	{
		template<typename Op, typename T> struct MockTimesVerifyer
		{
		private:
			T& mockObj;
			const Op& times;
			std::size_t line;
			std::string file;

		public:
			MockTimesVerifyer(T& mock, const Op& times, std::size_t line, std::string file)
				: mockObj(mock),
				times(times),
				line(line),
				file(file)
			{
			}

			template<typename... ARGS> void operator()(const ARGS&... args)
			{
				mockObj.VerifyTimes(line, file, times, args...);
			}
		};
	}
}

#endif // UT11_DETAIL_MOCKTIMESVERIFY_HPP_INCLUDED
