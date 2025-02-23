#include "Identify.hpp"

// It randomly instanciates A, B or C and returns the instance as a Base pointer. Feel free
// to use anything you like for the random choice implementation.
Base *generate(void) {
	int random = rand() % 3;
	if (random == 0) {
		return new A();
	} else if (random == 1) {
		return new B();
	} else {
		return new C();
	}
}


// It prints the actual type of the object pointed to by p: "A", "B" or "C".
// dynamic cast will return nullptr if the cast is not possible (i.e. the object is not of the type)
void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "A" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B" << std::endl;
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "C" << std::endl;
	}
}


// It prints the actual type of the object pointed to by p: "A", "B" or "C". Using a pointer inside this function is forbidden.
void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	} catch (std::bad_cast&) {
		try {
			(void)dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
		} catch (std::bad_cast&) {
			try {
				(void)dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
			} catch (std::bad_cast&) {
				std::cout << "Error: unknown type" << std::endl;
			}
		}
	}
}