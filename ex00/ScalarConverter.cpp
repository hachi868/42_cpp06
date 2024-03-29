#include "ScalarConverter.hpp"

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
	//nan,inf判定されたらT_FLOAT or T_DOUBLE判定
	try {
		double tmpLiteralDouble = std::stod(literal);
		if (ftIsNan(tmpLiteralDouble)) {
			if (isSuffixFloat(literal, literal.size()-1))
				return (T_FLOAT);
			else
				return (T_DOUBLE);
		}
		if (ftIsInf(tmpLiteralDouble)) {
			if (isInfFloat(literal))
				return (T_FLOAT);
			else
				return (T_DOUBLE);
		}
	} catch (const std::invalid_argument &e) {} catch (const std::out_of_range &e) {
		return (T_DOUBLE);
	}
	//infなどの文字列ではなく、数字.数字f表記でfloatではinfの範囲にあるものを判定
	//doubleでは扱えるがfloatではinfになるものはstofからout_of_rangeがthrowされる
	try {
		(void)std::stof(literal);
	} catch (const std::invalid_argument &e) {} catch (const std::out_of_range &e) {
		if (isSuffixFloat(literal, literal.size()-1))
			return (T_FLOAT);
	}

	//.が含まれない => int or char / 1つ含まれる => 浮動小数 /2つ以上 => invalid
	int lenDot = countDots(literal);
	if (lenDot == 0) {
		if (isInteger(literal))
			return (T_INT);
		else if (literal.size() == 1 && literal[0] >= ' ' && literal[0] <= '~')
			return (T_CHAR);
		else
			return (INVALID);
	} else if (lenDot == 1) {
		if (isSuffixFloat(literal, literal.size() - 1) && isFloatingPoint(literal, literal.size() - 1))
			return (T_FLOAT);
		else if (isFloatingPoint(literal, literal.size()))
			return (T_DOUBLE);
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
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {//overflow
		std::cerr << "char: " << MSG << "impossible (out of range)" << RESET << std::endl;
		std::cerr << "int: " << MSG << "impossible (out of range)" << RESET << std::endl;
		std::cerr << "float: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
		std::cerr << "double: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
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
		//std::cout << "ftIsInff: " << ftIsInff(literalFloat) << " /ftIsNanf: " << ftIsNanf(literalFloat) << std::endl;
		unsigned int precision = countDecimals(literal);
		convertFromFloatToChar(literalFloat);
		convertFromFloatToInt(literalFloat);
		std::cout << "float: ";
		if (std::floor(literalFloat) == literalFloat)
			fixedToPrecision(literalFloat, 1);
		else {
			fixedToPrecision(literalFloat, precision);
		}
		convertFromFloatToDouble(literalFloat, precision);
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		std::cerr << "char: " << MSG << "impossible (out of range)" << RESET << std::endl;
		std::cerr << "int: " << MSG << "impossible (out of range)" << RESET << std::endl;
		if (literal[0] == '-') {
			std::cout << "float: -inff" << std::endl;
			std::cout << "double: -inf" << RESET << std::endl;
		} else {
			std::cout << "float: inff" << std::endl;
			std::cout << "double: inf" << RESET << std::endl;
		}
	}
}
void ScalarConverter::convertFromFloatToChar(const float &literalFloat) {
	if (ftIsNanf(literalFloat)) {
		std::cerr << "char: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
		return ;
	} else if (ftIsInff(literalFloat)) {
		std::cerr << "char: " << MSG << "impossible (out of range)" << RESET << std::endl;
		return ;
	}
	//intの範囲を超えないか確認
	if (literalFloat < std::numeric_limits<int>::min() || literalFloat > std::numeric_limits<int>::max()) {
		std::cerr << "char: " << MSG << "impossible (out of range)" << RESET << std::endl;
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
	if (ftIsNanf(literalFloat)) {
		std::cerr << "int: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
		return ;
	} else if (ftIsInff(literalFloat)) {
		std::cerr << "int: " << MSG << "impossible (out of range)" << RESET << std::endl;
		return ;
	}
	//intの範囲を超えないか確認
	if (literalFloat < std::numeric_limits<int>::min() || literalFloat > std::numeric_limits<int>::max()) {
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
		//std::cout << "ftIsInf: " << ftIsInf(literalDouble) << " /ftIsNan: " << ftIsNan(literalDouble) << std::endl;
		unsigned int precision = countDecimals(literal);
		convertFromDoubleToChar(literalDouble);
		convertFromDoubleToInt(literalDouble);
		convertFromDoubleToFloat(literalDouble, precision);
		std::cout << "double: ";
		if (std::floor(literalDouble) == literalDouble)
			fixedToPrecision(literalDouble, 1);
		else { //nanfはここに入る
			fixedToPrecision(literalDouble, precision);
		}
	} catch (const std::invalid_argument &e) {
		std::cerr << MSG << "impossible (cannot be converted)" << RESET << std::endl;
	} catch (const std::out_of_range &e) {
		//infがここに入らない
		std::cerr << MSG << "impossible (out of range)" << RESET << std::endl;
	}
}
void ScalarConverter::convertFromDoubleToChar(const double &literalDouble) {
	if (ftIsNanf(literalDouble)) {
		std::cerr << "char: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
		return ;
	} else if (ftIsInff(literalDouble)) {
		std::cerr << "char: " << MSG << "impossible (out of range)" << RESET << std::endl;
		return ;
	}
	//intの範囲を超えないか確認
	if (literalDouble < std::numeric_limits<int>::min() || literalDouble > std::numeric_limits<int>::max()) {
		std::cerr << "char: " << MSG << "impossible (out of range)" << RESET << std::endl;
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
	if (ftIsNanf(literalDouble)) {
		std::cerr << "int: " << MSG << "impossible (cannot be converted)" << RESET << std::endl;
		return ;
	} else if (ftIsInff(literalDouble)) {
		std::cerr << "int: " << MSG << "impossible (out of range)" << RESET << std::endl;
		return ;
	}
	//intの範囲を超えないか確認
	if (literalDouble < std::numeric_limits<int>::min() || literalDouble > std::numeric_limits<int>::max()) {
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
	//floatの範囲を超えないか確認
	if (literalDouble < -std::numeric_limits<float>::max() || literalDouble > std::numeric_limits<float>::max()) {
		std::cerr << "inff" << std::endl;
		return ;
	}
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
unsigned int ScalarConverter::countDecimals(const std::string &literal) {
	int	counter = 0;
	bool isCount = false;
	for (unsigned int i = 0; i < literal.size(); i++) {
		if (isCount && isdigit(literal[i])) counter++;
		if (literal[i] == '.') isCount = true;
	}
	return (counter);
}
unsigned int ScalarConverter::countDots(const std::string &literal) {
	int	counter = 0;
	for (unsigned int i = 0; i < literal.size(); i++)
		if (literal[i] == '.') counter++;
	return (counter);
}

//isnan,isinf https://www.jpcert.or.jp/sc-rules/c-flp04-c.html
bool ScalarConverter::ftIsInff(const float &literalFloat) {
	if (literalFloat - literalFloat != 0)
		return (true);
	return (false);
}
bool ScalarConverter::ftIsInf(const double &literalDouble) {
	if (literalDouble - literalDouble != 0)
		return (true);
	return (false);
}
//NaNは自分自身とも等しくない => x != x
bool ScalarConverter::ftIsNanf(const float &literalFloat) {
	return (literalFloat != literalFloat);
}
bool ScalarConverter::ftIsNan(const double &literalDouble) {
	return (literalDouble != literalDouble);
}

bool ScalarConverter::isSuffixFloat(const std::string &literal, unsigned int end) {
	return ((literal[end] == 'f' || literal[end] == 'F'));
}
bool ScalarConverter::isInfFloat(const std::string &literal) {
	unsigned int i=0;
	unsigned int sizeLiteral = literal.size();
	if (literal[i] == '+' || literal[i] == '-') i++;
	std::string strInf = literal.substr(i, 3);
	for (unsigned int j=0;j<3;j++)
		tolower(strInf[j]);
	return (strInf == "inf" && isSuffixFloat(literal, sizeLiteral-1) && sizeLiteral - i > 3);
}
bool ScalarConverter::isInteger(const std::string &literal) {
	unsigned int i = 0;
	unsigned int counterDigit = 0;
	if (literal[i] == '+' || literal[i] == '-') i++;
	while (i + counterDigit < literal.size()) {
		if (!isdigit(literal[i + counterDigit]))
			return (false);
		counterDigit++;
	}
	if (counterDigit > 0)
		return (true);
	return (false);
}
bool ScalarConverter::isFloatingPoint(const std::string &literal, unsigned int end) {
	unsigned int i = 0;
	unsigned int counterDigit = 0;
	if (literal[i] == '+' || literal[i] == '-') i++;
	while (i + counterDigit < end) {
		if (!isdigit(literal[i + counterDigit]) && literal[i + counterDigit] != '.')
			return (false);
		if (literal[i + counterDigit] == '.')
			i++;
		else
			counterDigit++;
	}
	if (counterDigit > 0)
		return (true);
	return (false);
}