#include "ScalarConverter.hpp"

static void ScalarConverter::convert(const std::string &literal)
{
	convertToChar(literal);
	convertToInt(literal);
	convertToFloat(literal);
	convertToDouble(literal);
}

static void ScalarConverter::convertToChar(const std::string &literal)
{
	int c_literal;

	std::cout << "char: " << endl;
	if (literal.size() != 1) {
		std::cout << "impossible" << endl;
		return ;
	}
	c_literal = std::stoi(literal);
	if(c_literal >= 32 || c_literal <= 126)
		std::cout << "'" << (char)c_literal << "'" << endl;
	else
		std::cout << "Non displayable" << endl;
}
static void ScalarConverter::convertToInt(const std::string &literal)
{
	std::cout << "int: " << endl;
}
static void ScalarConverter::convertToFloat(const std::string &literal)
{
	std::cout << "float: " << endl;
}
static void ScalarConverter::convertToDouble(const std::string &literal)
{
	std::cout << "double: " << endl;
}