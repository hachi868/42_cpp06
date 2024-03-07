#ifndef __SCALARCONVERTER_H__
#define __SCALARCONVERTER_H__


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


#endif //__SCALARCONVERTER_H__
