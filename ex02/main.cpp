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
	struct timeval tv;
	gettimeofday(&tv, NULL);//マイクロ秒
	srand(static_cast<unsigned int>(tv.tv_usec));
	int i = rand() % 3;
	Base *ptrBase;
	switch (i) {
		case 0:
			try {
				ptrBase = new A;
			} catch (const std::bad_alloc& e) {
				std::cerr << ALERT << "Memory allocation failed." << RESET << std::endl;
			}
			break;
		case 1:
			try {
				ptrBase = new B;
			} catch (const std::bad_alloc& e) {
				std::cerr << ALERT << "Memory allocation failed." << RESET << std::endl;
			}
			break;
		case 2:
			try {
				ptrBase = new C;
			} catch (const std::bad_alloc& e) {
				std::cerr << ALERT << "Memory allocation failed." << RESET << std::endl;
			}
			break;
		default:
			ptrBase = nullptr;
			break;
	}
	return (ptrBase);
}

//dynamic_cast は、ランタイム型情報に基づいて、ポインタの型変換を行う演算子です。
//キャストしてみて、nullptrにならなければその型
void identify(Base *p) {
	if (dynamic_cast<A*>(p) != nullptr) {
		std::cout << "A" << std::endl;
		return ;
	}

	if (dynamic_cast<B*>(p) != nullptr) {
		std::cout << "B" << std::endl;
		return ;
	}

	if (dynamic_cast<C*>(p) != nullptr) {
		std::cout << "C" << std::endl;
		return ;
	}
	std::cerr << ALERT << "It is not an pointer to an object of A, B, or C." << RESET << std::endl;
}

//参照をnullptrにバインドできないのでA *と同様にはできない
void identify(Base &p) {
	if (dynamic_cast<A*>(&p) != nullptr) {
		std::cout << "A" << std::endl;
		return;
	}

	if (dynamic_cast<B*>(&p) != nullptr) {
		std::cout << "B" << std::endl;
		return;
	}

	if (dynamic_cast<C*>(&p) != nullptr) {
		std::cout << "C" << std::endl;
		return;
	}
	std::cerr << ALERT << "It is not an reference to an object of A, B, or C." << RESET << std::endl;
}

int main()
{
	Base *ptrBase = generate();
	if (ptrBase == nullptr) {
		std::cerr << ALERT << "Generate Base pointer is failed." << RESET << std::endl;
		return (1);
	}
	identify(ptrBase);
	identify(*ptrBase);
	delete ptrBase;
	return (0);
}
