#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

__attribute__((destructor))
static void destructor() {
	system("leaks -q serializer");
}

int main()
{
	Data *student;
	try {
		student = new Data;
	} catch (const std::bad_alloc& e) {
		std::cerr << Serializer::ALERT << "Memory allocation failed." << Serializer::RESET << std::endl;
	}
	student->number = 10;
	student->name = "user1";
	student->level = 3.1;

	std::cout << Serializer::STATE << "[student]" << Serializer::RESET << std::endl;
	std::cout << "student->number: " << student->number << std::endl;
	std::cout << "student->name: " << student->name << std::endl;
	std::cout << "student->level: " << student->level << std::endl;

	std::cout << std::endl << Serializer::STATE << "[serialize]" << Serializer::RESET << std::endl;
	uintptr_t	rawPtr = Serializer::serialize(student);
	std::cout << "rawPtr: " << rawPtr << std::endl;

	std::cout << std::endl << Serializer::STATE << "[deserialize]" << Serializer::RESET << std::endl;
	Data* studentDeserialize = Serializer::deserialize(rawPtr);
	std::cout << "studentDeserialize->number: " << studentDeserialize->number << std::endl;
	std::cout << "studentDeserialize->name: " << studentDeserialize->name << std::endl;
	std::cout << "studentDeserialize->level: " << studentDeserialize->level << std::endl << std::endl;
	delete student;
	return (0);
}
