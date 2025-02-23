#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>

struct Data {
	int value;
	char *str;
};

class Serializer {
	private:
		// Canonical form
		Serializer();
		Serializer(const Serializer &other);
		Serializer &operator=(const Serializer &other);
		~Serializer();

	public:
		// Member functions
		static uintptr_t serialize(Data* ptr); // It takes a pointer and converts it to the unsigned integer type uintptr_t.
		static Data* deserialize(uintptr_t raw); // It takes an unsigned integer parameter and converts it to a pointer to Data.
};

#endif