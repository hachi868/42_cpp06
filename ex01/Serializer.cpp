#include "Serializer.hpp"

const std::string Serializer::RESET = "\033[0m";
const std::string Serializer::DEBUG = "\033[90m";
const std::string Serializer::STATE = "\033[36m";
const std::string Serializer::ALERT = "\033[31m";
const std::string Serializer::MSG = "\033[34m";

uintptr_t Serializer::serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}

//reinterpret_cast
//ポインタのアドレス値を整数型の変数に格納する場合などに使用