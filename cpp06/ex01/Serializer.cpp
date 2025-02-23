#include "Serializer.hpp"

// Canonical form
Serializer::Serializer() {}
Serializer::Serializer(const Serializer &other) {*this = other;}
Serializer &Serializer::operator=(const Serializer &other) {
	if (this != &other)
		*this = other;
	return *this;
}
Serializer::~Serializer() {}

// Member functions
uintptr_t Serializer::serialize(Data* ptr) { // It takes a pointer and converts it to the unsigned integer type uintptr_t.
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) { // It takes an unsigned integer parameter and converts it to a pointer to Data.
	return reinterpret_cast<Data*>(raw);
}