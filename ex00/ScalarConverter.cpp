#include "ScalarConverter.hpp"
#include <iomanip>//setprecision
#include <limits> // std::numeric_limits
#include <sstream>

const std::string ScalarConverter::RESET = "\033[0m";
const std::string ScalarConverter::DEBUG = "\033[90m";
const std::string ScalarConverter::STATE = "\033[36m";
const std::string ScalarConverter::ALERT = "\033[31m";
const std::string ScalarConverter::MSG = "\033[34m";

void ScalarConverter::convert(const std::string &literal)
{
	TypeLiteral typeLiteral = judgeTypes(literal);
	switch (typeLiteral) {
		case T_CHAR:
			convertFromChar(literal);
			break;
		case T_INT:
			convertFromInt(literal);
			break;
		case T_FLOAT:
			convertFromFloat(literal);
			break;
		case T_DOUBLE:
			convertFromDouble(literal);
			break;
		case INVALID:
			std::cerr << ALERT << "Error: invalid literal" << RESET << std::endl;
			break;
	}
}

TypeLiteral ScalarConverter::judgeTypes(const std::string &literal)
{
	size_t i = 0, j = 0;
	//todo: nanf,inf判定甘い
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

//T_CHAR
void ScalarConverter::convertFromChar(const std::string &literal)
{
	char literalChar;
	literalChar = literal[0];
	//display
	std::cout << "char: ";
	std::cout << "'" << literalChar << "'" << std::endl;
	convertFromCharToInt(literalChar);
	convertFromCharToFloat(literalChar);
	convertFromCharToDouble(literalChar);
}
void ScalarConverter::convertFromCharToInt(const char &literalChar) {
	std::cout << "int: ";
	std::cout << static_cast<int>(literalChar) << std::endl;
}
void ScalarConverter::convertFromCharToFloat(const char &literalChar) {
	std::cout << "float: ";
	std::cout << std::fixed << std::setprecision(1) << static_cast<float>(literalChar) << "f" << std::endl;
}
void ScalarConverter::convertFromCharToDouble(const char &literalChar) {
	std::cout << "double: ";
	std::cout << std::fixed << std::setprecision(1) << static_cast<double>(literalChar) << std::endl;
}

//T_INT
void ScalarConverter::convertFromInt(const std::string &literal)
{
	int literalInt;
	try {
		literalInt = std::stoi(literal);
		convertFromIntToChar(literalInt);
		std::cout << "int: ";
		std::cout << literalInt << std::endl;
		convertFromIntToFloat(literalInt);
		convertFromIntToDouble(literalInt);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromIntToChar(const int &literalInt) {
	std::cout << "char: ";
	if(literalInt >= 32 && literalInt <= 126)
		std::cout << "'" << static_cast<char>(literalInt) << "'" << std::endl;
	else if(literalInt >= static_cast<int>(std::numeric_limits<char>::min()) \
					&& literalInt <= static_cast<int>(std::numeric_limits<char>::max()))
		std::cerr << MSG << "Non displayable" << RESET << std::endl;
	else
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
}
void ScalarConverter::convertFromIntToFloat(const int &literalInt) {
	std::cout << "float: ";
	try {
		std::cout << std::fixed << std::setprecision(1) << static_cast<float>(literalInt) << "f" << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromIntToDouble(const int &literalInt) {
	std::cout << "double: ";
	try {
		std::cout << std::fixed << std::setprecision(1) << static_cast<double>(literalInt) << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}

//T_FLOAT
void ScalarConverter::convertFromFloat(const std::string &literal) {
	float literalFloat;
	try {
		literalFloat = std::stof(literal);
		convertFromFloatToChar(literalFloat);
		convertFromFloatToInt(literalFloat);
		std::cout << "float: ";
		if (std::floor(literalFloat) == literalFloat)//infはここに入る
			fixedTo0(literalFloat);
		else//nanfはここに入る
			std::cout << literalFloat << "f" << std::endl;
		convertFromFloatToDouble(literalFloat);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromFloatToChar(const float &literalFloat) {
	//inf,nanfならimpossible表記
	if (isinf(literalFloat) || isnan(literalFloat)) {
		std::cout << "char: impossible" << std::endl;
		return ;
	}
	//intを経由してcharにcast（循環対策）
	try {
		int literalInt = static_cast<int>(literalFloat);
		convertFromIntToChar(literalInt);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromFloatToInt(const float &literalFloat) {
	//inf,nanfならimpossible表記
	if (isinf(literalFloat) || isnan(literalFloat)) {
		std::cout << "int: impossible" << std::endl;
		return ;
	}
	//intにcast
	try {
		int literalInt = static_cast<int>(literalFloat);
		std::cout << "int: " << literalInt << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromFloatToDouble(const float &literalFloat) {
	std::cout << "double: ";
	try {
		double literalFloatToDouble = static_cast<double>(literalFloat);
		if (std::floor(literalFloatToDouble) == literalFloatToDouble)//infはここに入る
			fixedTo0(literalFloatToDouble);
		else//nanはここに入る
			std::cout << literalFloatToDouble << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}

//T_FLOAT
void ScalarConverter::convertFromDouble(const std::string &literal) {
	double literalDouble;
	try {
		literalDouble = std::stod(literal);
		convertFromDoubleToChar(literalDouble);
		convertFromDoubleToInt(literalDouble);
		convertFromDoubleToFloat(literalDouble);
		std::cout << "double: ";

		int max_digits = std::numeric_limits<double>::digits10;
		if (std::floor(literalDouble) == literalDouble)//infはここに入る
			fixedTo0(literalDouble);
		else//nanfはここに入る
			std::cout << std::setprecision(max_digits) << literalDouble << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromDoubleToChar(const double &literalDouble) {
	//inf,nanfならimpossible表記
	if (isinf(literalDouble) || isnan(literalDouble)) {
		std::cout << "char: impossible" << std::endl;
		return ;
	}
	//intを経由してcharにcast（循環対策）
	try {
		int literalInt = static_cast<int>(literalDouble);
		convertFromIntToChar(literalInt);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromDoubleToInt(const double &literalDouble) {
	//inf,nanfならimpossible表記
	if (isinf(literalDouble) || isnan(literalDouble)) {
		std::cout << "int: impossible" << std::endl;
		return ;
	}
	//intにcast
	try {
		int literalInt = static_cast<int>(literalDouble);
		std::cout << "int: " << literalInt << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromDoubleToFloat(const double &literalDouble) {
	std::cout << "float: ";
	try {
		double literalDoubleToFloat = static_cast<float>(literalDouble);
		if (std::floor(literalDoubleToFloat) == literalDoubleToFloat)//infはここに入る
			fixedTo0(literalDoubleToFloat);
		else//nanはここに入る
			std::cout << literalDoubleToFloat << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}

//void ScalarConverter::convertFromFloat(const std::string &literal)
//{
//	//T_DOUBLE
//	if (literal == "-inf" || literal == "+inf" ||  literal == "nan") {
//		std::cerr << MSG << literal << "f" << RESET << std::endl;
//		return ;
//	}
//	try {
//		float c_literal = std::stof(literal);
//		std::cout << c_literal << "f" << std::endl;
//	} catch (const std::invalid_argument &e) {
//		std::cerr << MSG << "nanf" << RESET << std::endl;
//	} catch (const std::out_of_range &e) {
//		if (literal[0] == '-')
//			std::cerr << MSG << "-inff" << RESET << std::endl;
//		else
//			std::cerr << MSG << "+inff" << RESET << std::endl;
//	}
//}
//void ScalarConverter::convertFromDouble(const std::string &literal)
//{
//	//T_DOUBLE
//	if (literal == "-inf" || literal == "+inf" ||  literal == "nan") {
//		std::cerr << MSG << literal << RESET << std::endl;
//		return ;
//	}
//	try {
//		double c_literal = std::stod(literal);
//		double c_literal_floor = c_literal;
//		if (std::floor(c_literal_floor) == c_literal)
//			std::cout << std::fixed << std::setprecision(1) << c_literal << std::endl;
//		else
//			std::cout << std::fixed << std::setprecision(literal.size()) << c_literal << std::endl;
//	} catch (const std::invalid_argument &e) {
//		std::cerr << MSG << "nan" << RESET << std::endl;
//	} catch (const std::out_of_range &e) {
//		if (literal[0] == '-')
//			std::cerr << MSG << "-inf" << RESET << std::endl;
//		else
//			std::cerr << MSG << "+inf" << RESET << std::endl;
//	}
//}

//helper
int ScalarConverter::countDot(const std::string &literal)
{
	int	counter = 0;
	for (size_t i = 0; i < literal.size(); i++)
		if (literal[i] == '.') counter++;
	return (counter);
}

void ScalarConverter::fixedTo0(const float &literalFloat) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << literalFloat;
	std::string str = ss.str();
	std::cout << str << "f" << std::endl;
}
void ScalarConverter::fixedTo0(const double &literalDouble) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << literalDouble;
	std::string str = ss.str();
	std::cout << str << std::endl;
}
