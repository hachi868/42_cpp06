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
		std::cout << "[test0]21\n" << std::endl;
		ScalarConverter::convert("21");
		std::cout << "[test0]2asdfg1\n" << std::endl;
		ScalarConverter::convert("2asdfg1");
		std::cout << "[test0]2147483647\n" << std::endl;
		ScalarConverter::convert("2147483647");
		std::cout << "[test0]2147483648\n" << std::endl;
		ScalarConverter::convert("2147483648");
		std::cout << "[test0]-2147483648\n" << std::endl;
		ScalarConverter::convert("-2147483648");
		std::cout << "[test0]-2147483649\n" << std::endl;
		ScalarConverter::convert("-2147483649");
	} else {
		ScalarConverter::convert(argv[1]);
	}
	return (0);
}
