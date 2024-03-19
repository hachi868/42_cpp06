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
	static void convertToChar(const std::string &literal, const TypeLiteral &type);
	static void convertToInt(const std::string &literal, const TypeLiteral &type);
	static void convertToFloat(const std::string &literal, const TypeLiteral &type);
	static void convertToDouble(const std::string &literal, const TypeLiteral &type);
	static int countDot(const std::string &literal);
	static bool checkIntOverFlow(const std::string &literal, size_t i);
	static const std::string intMaxAbs;
	static const std::string intMinAbs;

	//今回コンストラクタ、デストラクタは呼ばれない
	ScalarConverter();
	ScalarConverter(const ScalarConverter &obj);
	ScalarConverter &operator = (const ScalarConverter &obj);
	~ScalarConverter();
};

#endif //__SCALAR_CONVERTER_H__
