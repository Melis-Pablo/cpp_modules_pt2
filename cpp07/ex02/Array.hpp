#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template<typename T>
class Array {
	private:
		T * _array;
		unsigned int _size;
	public:
		// Canonical form
		Array();	// Constructor
		Array(unsigned int n);	// Parametric constructor
		Array(Array const & src);	// Copy constructor
		Array & operator=(Array const & src);	// Assignation operator
		~Array();	// Destructor

		// Member functions
		T & operator[](unsigned int i);
		T const & operator[](unsigned int i) const;
		unsigned int size() const;

		// Exceptions
		class OutOfBoundsException : public std::exception {
			public:
				virtual const char * what() const throw() {
					return "Error: out of bounds";
				}
		};
};

#include "Array.tpp" // Include the template implementation file

#endif