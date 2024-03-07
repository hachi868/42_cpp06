#ifndef __SCALAR_CONVERTER_H__
#define __SCALAR_CONVERTER_H__

#include <iostream>

class ScalarConverter {
public:
	static void convert(const std::string &literal);

private:
	static void convertToChar(const std::string &literal);
	static void convertToInt(const std::string &literal);
	static void convertToFloat(const std::string &literal);
	static void convertToDouble(const std::string &literal);

	//今回コンストラクタ、デストラクタは呼ばれない
	ScalarConverter();
	ScalarConverter(const ScalarConverter &obj);
	ScalarConverter &operator = (const ScalarConverter &obj);
	~ScalarConverter();
};


#endif //__SCALAR_CONVERTER_H__
