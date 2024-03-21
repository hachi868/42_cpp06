#include <iostream>
#include "ScalarConverter.hpp"

__attribute__((destructor))
static void destructor() {
	system("leaks -q convert");
}

int main(int argc, char **argv)
{
	if (argc > 2) {
		std::cerr << "Error: invalid argc\n" << std::endl;
		return (1);
	}
	//コマンドライン引数なしならテスト実行
	if (argc == 1) {
		// T_CHAR
//		std::cout << ScalarConverter::STATE << "[test char 1]c" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("c");
//		std::cout << std::endl << ScalarConverter::STATE << "[test char 0]0" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("0");
//		std::cout << std::endl << ScalarConverter::STATE << "[test char 0]A" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("A");
//		std::cout << std::endl << ScalarConverter::STATE << "[test char 0]*" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("*");

		std::cout << std::endl << "*-*-*-*-*-*-*" << std::endl << std::endl;
		// T_INT
//		std::cout << ScalarConverter::STATE << "[test int 1]42" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("42");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 2]+42" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("+42");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 3]-42" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-42");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 4]+-42" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("+-42");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 5]126" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("126");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 6]127" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("127");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 7]128" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("128");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 8]42qwerty24" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("42qwerty24");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 9]2147483647" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("2147483647");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 10]-2147483648" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-2147483648");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 11]2147483648" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("2147483648");
//		std::cout << std::endl << ScalarConverter::STATE << "[test int 12]-2147483649" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-2147483649");

		std::cout << std::endl << "*-*-*-*-*-*-*" << std::endl;
		// T_FLOAT
//		std::cout << ScalarConverter::STATE << "[test float 1]inff" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("inff");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 2]-inff" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-inff");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 3]+inff" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("+inff");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 4]nanf" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("nanf");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 5]42.0f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("42.0f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 6]-42.0f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-42.0f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 7]42.042f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("42.042f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 8]-42.042f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-42.042f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 9]4242.04242f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("4242.04242f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 10]-4242.04242f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-4242.04242f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 11]2147483647.04242f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("2147483647.04242f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 12]-2147483648.04242f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("-2147483648.04242f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 13]0.012345f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("0.012345f");
//		std::cout << std::endl << ScalarConverter::STATE << "[test float 14]0.0123456789f" << ScalarConverter::RESET << std::endl;
//		ScalarConverter::convert("0.0123456789f");

//		std::cout << std::endl << "*-*-*-*-*-*-*" << std::endl << std::endl;
		// T_DOUBLE
		std::cout << ScalarConverter::STATE << "[test double 1]inf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("inf");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 2]-inf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-inf");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 3]+inf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+inf");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 4]nan" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("nan");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 5]42.0" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.0");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 6]-42.0" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-42.0");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 7]42.042" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.042");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 8]-42.042" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-42.042");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 9]4242.04242" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("4242.04242");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 10]-4242.04242" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-4242.04242");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 11]2147483647.04242" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483647.04242");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 12]-2147483648.04242" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483648.04242");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 13]0.012345" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("0.012345");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 14]0.0123456789" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("0.0123456789");
	} else {
		ScalarConverter::convert(argv[1]);
	}
	return (0);
}
