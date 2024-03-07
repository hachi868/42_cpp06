#include "ScalarConverter.hpp"
#include <iomanip>//setprecision

void ScalarConverter::convert(const std::string &literal)
{
	convertToChar(literal);
	convertToInt(literal);
	convertToFloat(literal);
	convertToDouble(literal);
}

void ScalarConverter::convertToChar(const std::string &literal)
{
//	std::cout << "char範囲"
//			  << (int)std::numeric_limits<char>::min() << " to "
//			  << (int)std::numeric_limits<char>::max() << std::endl;

	std::cout << "char: ";
	try {
		int c_literal = std::stoi(literal);
		if(c_literal >= 32 && c_literal <= 126)
			std::cout << "'" << static_cast<char>(c_literal) << "'" << std::endl;
		else if(c_literal >= 0 && c_literal <= 256)//todo: 校舎環境の範囲確認
			std::cout << "Non displayable" << std::endl;
		else
			std::cout << "impossible (out of range)" << std::endl;
	} catch (const std::invalid_argument& e) {
		std::cerr << "impossible (cannot be converted)" << std::endl;
	} catch (const std::out_of_range& e) {
		std::cerr << "impossible (out of range)" << std::endl;
	}
}
void ScalarConverter::convertToInt(const std::string &literal)
{
	std::cout << "int: ";
	try {
		int c_literal = std::stoi(literal);
		std::cout << c_literal << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << "impossible (cannot be converted)" << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << "impossible (out of range)" << std::endl;
	}
}
void ScalarConverter::convertToFloat(const std::string &literal)
{
	(void)literal;
	std::cout << "float: ";
	try {
		float c_literal = std::stof(literal);
		std::cout << c_literal << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << "nanf" << std::endl;
	} catch (const std::out_of_range &e) {
		if (literal[0] == '-')
			std::cerr << "-inff" << std::endl;
		else
			std::cerr << "+inff" << std::endl;
	}
}
void ScalarConverter::convertToDouble(const std::string &literal)
{
	std::cout << "double: ";
	try {
		double c_literal = std::stod(literal);
		if (std::floor(c_literal) == c_literal)
			std::cout << std::fixed << std::setprecision(1) << c_literal << std::endl;
		else
			std::cout << c_literal << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << "nan" << std::endl;
	} catch (const std::out_of_range &e) {
		if (literal[0] == '-')
			std::cerr << "-inf" << std::endl;
		else
			std::cerr << "+inf" << std::endl;
	}
}