#include "ScalarConverter.hpp"
#include <iomanip>//setprecision
#include <limits> // std::numeric_limits
//#include <cstdlib>// atof
//#include <stdlib.h>
#include <sstream>

const std::string ScalarConverter::RESET = "\033[0m";
const std::string ScalarConverter::DEBUG = "\033[90m";
const std::string ScalarConverter::STATE = "\033[36m";
const std::string ScalarConverter::ALERT = "\033[31m";
const std::string ScalarConverter::MSG = "\033[34m";

const std::string ScalarConverter::intMaxAbs = "2147483647";
const std::string ScalarConverter::intMinAbs = "2147483648";

void ScalarConverter::convert(const std::string &literal)
{
	TypeLiteral typeLiteral = judgeTypes(literal);
	if (typeLiteral == INVALID)
	{
		std::cerr << ScalarConverter::ALERT << "Error: invalid literal" << ScalarConverter::RESET << std::endl;
		return ;
	}
	convertToChar(literal, typeLiteral);
	convertToInt(literal, typeLiteral);
	convertToFloat(literal, typeLiteral);
	convertToDouble(literal, typeLiteral);
}

int ScalarConverter::countDot(const std::string &literal)
{
	int	counter = 0;
	for (size_t i = 0; i < literal.size(); i++)
		if (literal[i] == '.') counter++;
	return (counter);
}

bool ScalarConverter::checkIntOverFlow(const std::string &literal, size_t i)
{
	const std::string &intM = (literal[0] == '-') ? ScalarConverter::intMinAbs : ScalarConverter::intMaxAbs;
	for (size_t k = 0; k < 10; k++)
		if (literal[i + k] > intM[k]) return (true);
	return (false);
}

TypeLiteral ScalarConverter::judgeTypes(const std::string &literal)
{
	size_t i = 0, j = 0;
	if (literal == "-inff" || literal == "+inff" ||  literal == "nanf") return (T_FLOAT);
	if (literal == "-inf" || literal == "+inf" ||  literal == "nan") return (T_DOUBLE);
	//「.」0=> T_CHAR or T_INT / 1つ=>T_FLOAT or T_DOUBLE / 2以上=>INVALID
	int lenDot = countDot(literal);
	if (lenDot == 0) {
		if (literal.size() == 1 && literal[0] >= ' ' && literal[0] <= '~') return (T_CHAR);
		//頭の符号はOK
		if (literal[0] == '-' || literal[0] == '+') i++;
		//jで数字の桁数を数える。数字の後の文字は無視
		while (literal[i + j] && isdigit(literal[i + j])) j++;
		if (j == 0 || j > 10) return (INVALID);
		if (j == 10 && checkIntOverFlow(literal, i))
			return (INVALID);
		return (T_INT);
	} else if (lenDot == 1) {
		if (literal.size() == 1) return (T_CHAR);
		//頭の符号はOK
		if (literal[i] == '-' || literal[i] == '+') i++;
		//必ず1桁以上の数字
		if (isdigit(literal[i])) i++;
		else return (INVALID);
		//数字連続してOK
		while (isdigit(literal[i])) i++;
		//数字の後に「.」
		if (literal[i] == '.') i++;
		else return (INVALID);
		//必ず1桁以上の数字
		if (literal[i] && isdigit(literal[i])) i++;
		else return (INVALID);
		//数字連続してOK
		while (literal[i] && isdigit(literal[i])) i++;
		//末尾ならreturn (T_DOUBLE);
		if (literal[i] == '\0') return (T_DOUBLE);
		else if (literal[i] == 'f') return (T_FLOAT);
		else return (INVALID);
	}
	return (INVALID);
}

void ScalarConverter::convertToChar(const std::string &literal, const TypeLiteral &type)
{
	std::cout << "char: ";
	switch (type) {
		case T_CHAR:
			std::cout << "'" << literal << "'" << std::endl;
			break;
		case T_INT:
			try {
				int i_literal = std::atoi(literal.c_str());
				if(i_literal >= 32 && i_literal <= 126)
					std::cout << "'" << static_cast<char>(i_literal) << "'" << std::endl;
				else if(i_literal >= static_cast<int>(std::numeric_limits<char>::min()) \
						&& i_literal <= static_cast<int>(std::numeric_limits<char>::max()))//todo: 校舎環境の範囲確認
					std::cerr << ScalarConverter::MSG << "Non displayable" << ScalarConverter::RESET << std::endl;
				else
					std::cerr << ScalarConverter::MSG << "impossible (out of range)" << ScalarConverter::RESET << std::endl;
			} catch (const std::invalid_argument& e) {
				std::cerr << ScalarConverter::MSG << "impossible (cannot be converted)" << ScalarConverter::RESET << std::endl;
			} catch (const std::out_of_range& e) {
				std::cerr << ScalarConverter::MSG << "impossible (out of range)" << ScalarConverter::RESET << std::endl;
			}
			break;
		case T_FLOAT:
			if (literal == "-inff" || literal == "+inff" ||  literal == "nanf") {
				std::cerr << ScalarConverter::MSG << "impossible (cannot be converted)" << ScalarConverter::RESET << std::endl;
				return ;
			}
			try {
				//todo: stofとatof
				float c_literal = std::stof(literal);
				float c_literal_floor = c_literal;
				if (std::floor(c_literal_floor) == c_literal)
					std::cout << std::fixed << std::setprecision(1) << c_literal << std::endl;
				else
					std::cerr << ScalarConverter::MSG << "impossible (cannot be converted)" << ScalarConverter::RESET << std::endl;
				//
				//float f_literal = static_cast<float>(std::atof(literal.c_str()));
				//std::cout << f_literal << std::endl;
			} catch (const std::invalid_argument& e) {
				std::cerr << ScalarConverter::MSG << "impossible (cannot be converted)" << ScalarConverter::RESET << std::endl;
			} catch (const std::out_of_range& e) {
				std::cerr << ScalarConverter::MSG << "impossible (out of range)" << ScalarConverter::RESET << std::endl;
			}
			break;
		case T_DOUBLE:
			if (literal == "-inf" || literal == "+inf" ||  literal == "nan") {
				std::cerr << ScalarConverter::MSG << "impossible (cannot be converted)" << ScalarConverter::RESET << std::endl;
				return ;
			}
			try {
				std::istringstream iss(literal);
				double d_literal;
				iss >> d_literal;
				std::cout << d_literal << std::endl;
			} catch (const std::invalid_argument& e) {
				std::cerr << ScalarConverter::MSG << "impossible (cannot be converted)" << ScalarConverter::RESET << std::endl;
			} catch (const std::out_of_range& e) {
				std::cerr << ScalarConverter::MSG << "impossible (out of range)" << ScalarConverter::RESET << std::endl;
			}
			break;
		case INVALID://todo: 例外
			break;
	}
}
void ScalarConverter::convertToInt(const std::string &literal, const TypeLiteral &type)
{
	std::cout << "int: ";
	if (type == T_CHAR){
		std::cout << (int)literal[0] << std::endl;
		return ;
	}
	try {
		int c_literal = std::stoi(literal);
		std::cout << c_literal << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << ScalarConverter::MSG << "impossible (cannot be converted)" << ScalarConverter::RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << ScalarConverter::MSG << "impossible (out of range)" << ScalarConverter::RESET << std::endl;
	}
}
void ScalarConverter::convertToFloat(const std::string &literal, const TypeLiteral &type)
{
	std::cout << "float: ";
	if (type == T_CHAR){
		std::cout << std::fixed << std::setprecision(1) << static_cast<float>(literal[0]) << "f" << std::endl;
		return ;
	}
	//T_FLOAT
	if (literal == "-inff" || literal == "+inff" ||  literal == "nanf") {
		std::cerr << ScalarConverter::MSG << literal << ScalarConverter::RESET << std::endl;
		return ;
	}
	//T_DOUBLE
	if (literal == "-inf" || literal == "+inf" ||  literal == "nan") {
		std::cerr << ScalarConverter::MSG << literal << "f" << ScalarConverter::RESET << std::endl;
		return ;
	}
	try {
		float c_literal = std::stof(literal);
		std::cout << c_literal << "f" << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << ScalarConverter::MSG << "nanf" << ScalarConverter::RESET << std::endl;
	} catch (const std::out_of_range &e) {
		if (literal[0] == '-')
			std::cerr << ScalarConverter::MSG << "-inff" << ScalarConverter::RESET << std::endl;
		else
			std::cerr << ScalarConverter::MSG << "+inff" << ScalarConverter::RESET << std::endl;
	}
}
void ScalarConverter::convertToDouble(const std::string &literal, const TypeLiteral &type)
{
	(void)type;
	std::cout << "double: ";
	if (type == T_CHAR){
		std::cout << std::fixed << std::setprecision(1) << static_cast<double>(literal[0]) << std::endl;
		return ;
	}
	//T_FLOAT
	if (literal == "-inff" || literal == "+inff" ||  literal == "nanf") {
		std::cerr << ScalarConverter::MSG;
		for (int i=0;i<(int)literal.size()-1;i++)
			std::cerr << literal[i];
		std::cerr << ScalarConverter::RESET << std::endl;
		return ;
	}
	//T_DOUBLE
	if (literal == "-inf" || literal == "+inf" ||  literal == "nan") {
		std::cerr << ScalarConverter::MSG << literal << ScalarConverter::RESET << std::endl;
		return ;
	}
	try {
		double c_literal = std::stod(literal);
		double c_literal_floor = c_literal;
		if (std::floor(c_literal_floor) == c_literal)
			std::cout << std::fixed << std::setprecision(1) << c_literal << std::endl;
		else
			std::cout << std::fixed << std::setprecision(literal.size()) << c_literal << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << ScalarConverter::MSG << "nan" << ScalarConverter::RESET << std::endl;
	} catch (const std::out_of_range &e) {
		if (literal[0] == '-')
			std::cerr << ScalarConverter::MSG << "-inf" << ScalarConverter::RESET << std::endl;
		else
			std::cerr << ScalarConverter::MSG << "+inf" << ScalarConverter::RESET << std::endl;
	}
}
