/*
 * Minesweeper.cpp
 *
 *  Created on: 7 Apr 2013
 *	  Author: Jason
 */

// A solution to the Kata: http://codingdojo.org/cgi-bin/wiki.pl?KataMinesweeper

#include <cstdint>
#include <string>

namespace minesweeper
{
	class InvalidInputException : public std::exception
	{
	public:
		virtual ~InvalidInputException() throw() { }

		virtual const char* what() const throw()
		{
			return "An invalid input was specified";
		}
	};

	class MinefieldGenerator
	{
	private:
		std::uint8_t m_width, m_height;

	public:
		MinefieldGenerator(std::uint8_t width, std::uint8_t height)
			: m_width(width), m_height(height)
		{
		}

		std::string GenerateMinefield(std::string data) const
		{
			if ( data.length() != m_width * m_height )
				throw InvalidInputException();

			CreateEmptyGridPopulatedWithMines(data);

			for (auto j = 0; j < m_height; ++j)
				for (auto i = 0; i < m_width; ++i)
					UpdateCell(i,j,data);

			return data;
		}

	private:
		static void CreateEmptyGridPopulatedWithMines(std::string& data)
		{
			for (auto& c : data)
				if (c != '*')
					c = '0';
		}

		void UpdateCell(std::uint16_t i, std::uint16_t j, std::string& data) const
		{
			if ( data[i + j * m_width] == '*' )
				for (auto b = j - 1; b <= j + 1; ++b)
					for (auto a = i - 1; a <= i + 1; ++a)
						TryIncrement(a, b, data);
		}

		void TryIncrement(std::int8_t i, std::int8_t j, std::string& data) const
		{
			if ( i >= 0 && i < m_width && j < m_height && j >= 0 )
			{
				auto position = static_cast<std::uint8_t>(i) + static_cast<std::uint8_t>(j) * m_width;
				if ( data[position] != '*' )
					data[position] += 1;
			}
		}
	};
}

#include <UnitTest11.hpp>

class MinefieldGeneratorTests : public ut11::TestFixture
{
private:
	std::string m_expectedGrid;
	std::string m_returnedGrid;

	void TestExpectedGridIsProduced(uint8_t w, uint8_t h, std::string input, std::string expected)
	{
		m_expectedGrid = expected;

		std::stringstream whenDescription;
		whenDescription << "generating a field with width " << (int)w << " and height " << (int)h << " and input of " << input;
		When(whenDescription.str(), [&, w, h, input, expected]() {
			m_expectedGrid = expected;

			minesweeper::MinefieldGenerator generator(w,h);
			m_returnedGrid = generator.GenerateMinefield(input);
		});

		Then("the expected result was returned", [&](){
			AssertThat(m_returnedGrid, ut11::Is::EqualTo(m_expectedGrid));
		});
	}

public:
	virtual void Run()
	{
		TestExpectedGridIsProduced(4,4, "*........*......", "*10022101*101110");
		TestExpectedGridIsProduced(5,3, "**.........*...", "**100332001*100");

		TestExpectedGridIsProduced(1,1, ".", "0");
		TestExpectedGridIsProduced(1,1, "*", "*");
		TestExpectedGridIsProduced(2,1, "*.", "*1");
		TestExpectedGridIsProduced(3,1, "*..", "*10");
		TestExpectedGridIsProduced(3,1, ".*.", "1*1");
		TestExpectedGridIsProduced(3,1, "***", "***");
		TestExpectedGridIsProduced(3,2, ".*....", "1*1111");

		Then("when the size of the supplied grid is less than the expected size the expected exception is thrown", [&]() {

			AssertThat([]() {
				minesweeper::MinefieldGenerator generator(5, 9);
				generator.GenerateMinefield("..");
			}, ut11::Will::Throw<minesweeper::InvalidInputException>());
		});
	}
};
DeclareFixture(MinefieldGeneratorTests)(ut11::Category("example"));
