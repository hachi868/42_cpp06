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
	std::cout << "char: " << endl;
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