#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

__attribute__((destructor))
static void destructor() {
	system("leaks -q realtype");
}

int main()
{

	return (0);
}
