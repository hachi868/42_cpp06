#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <iostream>

class Serializer {
public:
	static uintptr_t serialize(Data *ptr);
	static Data *deserialize(uintptr_t raw);

	const static std::string RESET;
	const static std::string DEBUG;
	const static std::string STATE;
	const static std::string ALERT;
	const static std::string MSG;

private:
	//今回コンストラクタ、デストラクタは呼ばれない
	Serializer();
	Serializer(const Serializer &obj);
	Serializer &operator = (const Serializer &obj);
	~Serializer();
};

#endif //SERIALIZER_HPP
