#include <iostream>
#include "ScalarConverter.hpp"

//__attribute__((destructor))
//static void destructor() {
//	system("leaks -q convert");
//}

int main(int argc, char **argv)
{
	if (argc > 2) {
		std::cerr << "Error: invalid argc\n" << std::endl;
		return (1);
	}
	//コマンドライン引数なしならテスト実行
	if (argc == 1) {
		// T_CHAR
		std::cout << ScalarConverter::STATE << "[test char 1]c" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("c");
		std::cout << std::endl << ScalarConverter::STATE << "[test char 2]0" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("0");
		std::cout << std::endl << ScalarConverter::STATE << "[test char 3]A" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("A");
		std::cout << std::endl << ScalarConverter::STATE << "[test char 4]*" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("*");
		std::cout << std::endl << ScalarConverter::STATE << "[test char 5]+" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+");
		std::cout << std::endl << ScalarConverter::STATE << "[test char 6]-" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-");

		std::cout << std::endl << "*-*-*-*-*-*-*" << std::endl << std::endl;
		// T_INT
		std::cout << ScalarConverter::STATE << "[test int 1]42" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 2]+42" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+42");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 3]-42" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-42");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 4]126" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("126");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 5]127" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("127");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 6]128" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("128");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 7]42qwerty24" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42qwerty24");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 8]42f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42f");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 9]2147483647" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483647");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 10]-2147483648" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483648");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 11]2147483648" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483648");
		std::cout << std::endl << ScalarConverter::STATE << "[test int 12]-2147483649" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483649");

		std::cout << std::endl << "*-*-*-*-*-*-*" << std::endl;
		// T_FLOAT
		std::cout << ScalarConverter::STATE << "[test float 1]inff" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("inff");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 2]-inff" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-inff");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 3]+inff" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+inff");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 3]infinityf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+infinityf");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 3]inffinityf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+inffinityf");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 3]infifnity" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+infifnity");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 4]nanf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("nanf");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 4]NaNf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("NaNf");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 4]+nanf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+nanf");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 4]-nanf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-nanf");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 5]42.0f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.0f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 6]-42.0f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-42.0f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 7]42.042f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.042f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 8]-42.042f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-42.042f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 9]4242.04242f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("4242.04242f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 10]-4242.04242f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-4242.04242f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 11]2147483647.04242f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483647.04242f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 12]-2147483648.04242f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483648.04242f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 13]2147483648.04242f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483648.04242f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 14]-2147483649.04242f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483649.04242f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 15]2147483648.1f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483648.1f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 16]-2147483649.1f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483649.1f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 17]0.012345f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("0.012345f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 18]0.0123456789f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("0.0123456789f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 19]42.f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.f");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 20]42.12fg" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.12fg");
		std::cout << std::endl << ScalarConverter::STATE << "[test float 21]42f" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42f");

		std::cout << std::endl << "*-*-*-*-*-*-*" << std::endl << std::endl;
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
		std::cout << std::endl << ScalarConverter::STATE << "[test double 13]2147483648.04242" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483648.04242");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 14]-2147483649.04242" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483649.04242");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 15]2147483648.1" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("2147483648.1");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 16]-2147483649.1" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-2147483649.1");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 17]0.012345" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("0.012345");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 18]0.0123456789" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("0.0123456789");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 19].012" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert(".012");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 20]42." << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.");
		std::cout << std::endl << ScalarConverter::STATE << "[test double 21]42.12dfg" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("42.12dfg");

		std::cout << std::endl << "*-*-*-*-*-*-*" << std::endl << std::endl;
		// INVALID
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 1]aa" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("aa");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 2]f.42" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("f.42");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 3]..42" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("..42");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 5]a." << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("a.");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 6]intf" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("intf");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 7]na" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("na");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 8]+-42" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+-42");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 9]+." << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("+.");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 10]-." << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("-.");
		std::cout << std::endl << ScalarConverter::STATE << "[test invalid 11]" << ScalarConverter::RESET << std::endl;
		ScalarConverter::convert("");
	} else {
		ScalarConverter::convert(argv[1]);
	}
	return (0);
}
