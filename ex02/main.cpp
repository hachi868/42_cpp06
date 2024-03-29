#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib> // for rand(), srand()
#include <sys/time.h>

__attribute__((destructor))
static void destructor() {
	system("leaks -q realtype");
}

const std::string RESET = "\033[0m";
const std::string DEBUG = "\033[90m";
const std::string STATE = "\033[36m";
const std::string ALERT = "\033[31m";
const std::string MSG = "\033[34m";

Base *generate(void) {
	int i = rand() % 3;
	Base *ptrBase;
	switch (i) {
	case 0:
		ptrBase = new A;
		break;
	case 1:
		ptrBase = new B;
		break;
	case 2:
		ptrBase = new C;
		break;
	}
	return (ptrBase);
}

//dynamic_cast は、ランタイム型情報に基づいて、ポインタの型変換を行う演算子です。
//キャストしてみて、NULLにならなければその型
void identify(Base *p) {
	if (dynamic_cast<A*>(p) != NULL) {
		std::cout << "A";
		return ;
	}

	if (dynamic_cast<B*>(p) != NULL) {
		std::cout << "B";
		return ;
	}

	if (dynamic_cast<C*>(p) != NULL) {
		std::cout << "C";
		return ;
	}
	std::cerr << ALERT << "It is not an pointer to an object of A, B, or C." << RESET << std::endl;
}

//参照をNULLにバインドできないのでA *と同様にはできない
void identify(Base &p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return ;
	} catch (const std::bad_cast &e) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return ;
	} catch (const std::bad_cast &e) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	} catch (const std::bad_cast &e) {
		std::cerr << ALERT << "It is not an reference to an object of A, B, or C." << RESET << std::endl;
	}
}

int doGenerate() {
	Base *ptrBase = generate();
	if (ptrBase == NULL) {
		std::cerr << ALERT << "Generate Base pointer is failed." << RESET << std::endl;
		return (1);
	}
	std::cout << "------" << std::endl;
	identify(ptrBase);
	std::cout << " : ";
	identify(*ptrBase);
	std::cout << std::endl;
	delete ptrBase;
	return (0);
}

int main() {
	struct timeval tv;
	gettimeofday(&tv, NULL); // マイクロ秒
	srand(static_cast<unsigned int>(tv.tv_usec));

	int i = 0;
	while (i < 10)
	{
		doGenerate();
		i++;
	}
	return (0);
}
