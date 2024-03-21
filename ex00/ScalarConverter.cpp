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
	//std::cout << "typeLiteral " << typeLiteral << std::endl;
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
	//nan,inf判定されたらT_FLOAT or T_DOUBLE判定
	//inf, nanの連なる文字列で始まる。頭に符号が着くのはOK
	//fが見つかって、(nan or inf判定できる文字列) + f の構成ではじまっていればT_FLOAT、なければT_DOUBLE
	try {
		double tmpLiteralDouble = std::stod(literal);
		if (isnan(tmpLiteralDouble))
			return (T_DOUBLE);
		if (isinf(tmpLiteralDouble)) {
			return (T_DOUBLE);
		} else if (isinf(static_cast<float>(tmpLiteralDouble))) {
			return (T_FLOAT);
		}
	} catch (const std::invalid_argument &e) {}
	int lenDot = 0;
	if (literal.size() == 1 && literal[0] >= ' ' && literal[0] <= '~') return (T_CHAR);
	//頭の符号はOK
	if (literal[0] == '-' || literal[0] == '+') i++;
	//jで数字の桁数を数える。数字の後の文字は無視
	while (literal[i + j + lenDot]) {
		//「.」
		if (literal[i + j + lenDot] == '.') {
			//1.23.4 => doubleの1.23
			if (lenDot > 0) {
				if (j > 0)
					return (T_DOUBLE);
				else
					return (INVALID);
			}
			lenDot++;
			//..と2つ続くならINVALID
			if (i + j + lenDot < literal.size() && literal[i + j + lenDot] == '.')
				return (INVALID);
		}
		//数字連続してOK
		while (literal[i + j + lenDot] && isdigit(literal[i + j + lenDot])) j++;
		//.の後、数字の直後にfがつけばT_FLOAT
		if (literal[i + j + lenDot] == 'f') {
			if (lenDot > 0) return (T_FLOAT);
			else if (j == 0) return (INVALID);
			else return (T_INT);
		}
		else if (literal[i + j + lenDot] != '.') {//fでも数字でも.でもない。
			if (lenDot > 0 && j > 0) {
				return (T_DOUBLE);
			}
			else if (j == 0) return (INVALID);
			return (T_INT);
		}
	}
	if (j > 0) return (T_DOUBLE);
	else return (INVALID);
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
	fixedToPrecision(static_cast<float>(literalChar), 1);
}
void ScalarConverter::convertFromCharToDouble(const char &literalChar) {
	std::cout << "double: ";
	fixedToPrecision(static_cast<double>(literalChar), 1);
}

//T_INT
void ScalarConverter::convertFromInt(const std::string &literal)
{
	//形から判定して整数型はintと類推するが、オーバーフローはここで判定
	int literalInt;
	try {
		literalInt = std::stoi(literal);
		convertFromIntToChar(literalInt);
		std::cout << "int: ";
		std::cout << literalInt << std::endl;
		convertFromIntToFloat(literalInt);
		convertFromIntToDouble(literalInt);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "int: impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "int: impossible (out of range)" << RESET << std::endl;
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
		fixedToPrecision(static_cast<float>(literalInt), 1);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromIntToDouble(const int &literalInt) {
	std::cout << "double: ";
	try {
		fixedToPrecision(static_cast<double>(literalInt), 1);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}

//T_FLOAT
void ScalarConverter::convertFromFloat(const std::string &literal) {
	try {
		float literalFloat = std::stof(literal);
		unsigned int precision = numDecimals(literal);
		convertFromFloatToChar(literalFloat);
		convertFromFloatToInt(literalFloat);
		std::cout << "float: ";
		if (std::floor(literalFloat) == literalFloat)//infはここに入る
			fixedToPrecision(literalFloat, 1);
		else {//nanfはここに入る
			fixedToPrecision(literalFloat, precision);
		}
		convertFromFloatToDouble(literalFloat, precision);
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
		std::cerr << MSG << "int: impossible (cannot be converted)" << RESET << std::endl;
		return ;
	}
	//overflow判定のため一旦longにキャスト
	long literalLong = static_cast<long>(literalFloat);
	if (literalLong > INT_MAX || literalLong < INT_MIN) {
		std::cerr << "int: " << MSG << "impossible (out of range)" << RESET << std::endl;
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
void ScalarConverter::convertFromFloatToDouble(const float &literalFloat, unsigned int n) {
	std::cout << "double: ";
	try {
		double literalFloatToDouble = static_cast<double>(literalFloat);
		if (std::floor(literalFloatToDouble) == literalFloatToDouble)//infはここに入る
			fixedToPrecision(literalFloatToDouble, 1);
		else//nanはここに入る
			fixedToPrecision(literalFloatToDouble, n);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}

//T_Double
void ScalarConverter::convertFromDouble(const std::string &literal) {
	try {
		double literalDouble = std::stod(literal);
		unsigned int precision = numDecimals(literal);
		convertFromDoubleToChar(literalDouble);
		convertFromDoubleToInt(literalDouble);
		convertFromDoubleToFloat(literalDouble, precision);
		std::cout << "double: ";
		if (std::floor(literalDouble) == literalDouble)//infはここに入る
			fixedToPrecision(literalDouble, 1);
		else { //nanfはここに入る
			fixedToPrecision(literalDouble, precision);
		}
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromDoubleToChar(const double &literalDouble) {
	//inf,nanfならimpossible表記
	if (isinf(literalDouble) || isnan(literalDouble)) {
		std::cerr << "char: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
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
		std::cerr << "int: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
		return ;
	}
	//overflow判定のため一旦longにキャスト
	long literalLong = static_cast<long>(literalDouble);
	if (literalLong > INT_MAX || literalLong < INT_MIN) {
		std::cerr << "int: " << MSG << "impossible (out of range)" << RESET << std::endl;
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
void ScalarConverter::convertFromDoubleToFloat(const double &literalDouble, unsigned int n) {
	std::cout << "float: ";
	try {
		float literalDoubleToFloat = static_cast<float>(literalDouble);
		if (std::floor(literalDoubleToFloat) == literalDoubleToFloat)//infはここに入る
			fixedToPrecision(literalDoubleToFloat, 1);
		else//nanはここに入る
			fixedToPrecision(literalDoubleToFloat, n);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}

//helper
void ScalarConverter::fixedToPrecision(const float &literalFloat, unsigned int n) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(n) << literalFloat;
	std::string str = ss.str();
	std::cout << str << "f" << std::endl;
}
void ScalarConverter::fixedToPrecision(const double &literalDouble, unsigned int n) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(n) << literalDouble;
	std::string str = ss.str();
	std::cout << str << std::endl;
}
unsigned int ScalarConverter::numDecimals(const std::string &literal) {
	int	counter = 0;
	bool isCount = false;
	for (size_t i = 0; i < literal.size(); i++) {
		if (isCount && isdigit(literal[i])) counter++;
		if (literal[i] == '.') isCount = true;
	}
	return (counter);
};
