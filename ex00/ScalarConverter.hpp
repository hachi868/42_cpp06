#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <iomanip>//setprecision
#include <limits> // std::numeric_limits
#include <sstream>
#include <cmath> //floor

enum TypeLiteral {
	T_CHAR,
	T_INT,
	T_FLOAT,
	T_DOUBLE,
	INVALID
};

class ScalarConverter {
public:
	static void convert(const std::string &literal);

	const static std::string RESET;
	const static std::string DEBUG;
	const static std::string STATE;
	const static std::string ALERT;
	const static std::string MSG;

private:
	static TypeLiteral judgeTypes(const std::string &literal);
	//T_CHAR
	static void convertFromChar(const std::string &literal);
	static void convertFromCharToInt(const char &literalChar);
	static void convertFromCharToFloat(const char &literalChar);
	static void convertFromCharToDouble(const char &literalChar);
	//T_INT
	static void convertFromInt(const std::string &literal);
	static void convertFromIntToChar(const int &literalInt);
	static void convertFromIntToFloat(const int &literalInt);
	static void convertFromIntToDouble(const int &literalInt);
	//T_FLOAT
	static void convertFromFloat(const std::string &literal);
	static void convertFromFloatToChar(const float &literalFloat);
	static void convertFromFloatToInt(const float &literalFloat);
	static void convertFromFloatToDouble(const float &literalFloat, unsigned int n);
	//T_DOUBLE
	static void convertFromDouble(const std::string &literal);
	static void convertFromDoubleToChar(const double &literalDouble);
	static void convertFromDoubleToInt(const double &literalDouble);
	static void convertFromDoubleToFloat(const double &literalDouble, unsigned int n);
	//helper
	static void fixedToPrecision(const float &literalFloat, unsigned int n);
	static void fixedToPrecision(const double &literalDouble, unsigned int n);
	static unsigned int countDecimals(const std::string &literal);
	static bool ftIsInff(const float &literalFloat);
	static bool ftIsInf(const double &literalDouble);
	static bool ftIsNanf(const float &literalFloat);
	static bool ftIsNan(const double &literalDouble);
	static bool isSuffixFloat(const std::string &literal, unsigned int end);
	static bool isInfFloat(const std::string &literal);

	//今回コンストラクタ、デストラクタは呼ばれない
	ScalarConverter();
	ScalarConverter(const ScalarConverter &obj);
	ScalarConverter &operator = (const ScalarConverter &obj);
	~ScalarConverter();
};

#endif // SCALAR_CONVERTER_HPP
