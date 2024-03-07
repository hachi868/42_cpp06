#include <iostream>
#include "ScalarConverter.hpp"

__attribute__((destructor))
static void destructor() {
	system("leaks -q convert");
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: invalid argc\n" << std::endl;
		return (1);
	}
	ScalarConverter.convert(argv[i]);
	return (0);
}
