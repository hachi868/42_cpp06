#ifndef __SCALAR_CONVERTER_H__
#define __SCALAR_CONVERTER_H__

#include <iostream>

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
	static void convertFromFloatToDouble(const float &literalFloat);
	//T_DOUBLE
	static void convertFromDouble(const std::string &literal);
	static void convertFromDoubleToChar(const double &literalDouble);
	static void convertFromDoubleToInt(const double &literalDouble);
	static void convertFromDoubleToFloat(const double &literalDouble);
	//helper
	static int countDot(const std::string &literal);
	static void fixedTo0(const float &literalFloat);
	static void fixedTo0(const double &literalDouble);

	//今回コンストラクタ、デストラクタは呼ばれない
	ScalarConverter();
	ScalarConverter(const ScalarConverter &obj);
	ScalarConverter &operator = (const ScalarConverter &obj);
	~ScalarConverter();
};

#endif //__SCALAR_CONVERTER_H__
