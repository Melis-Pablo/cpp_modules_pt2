#ifndef ARRAY_IMPL_HPP
#define ARRAY_IMPL_HPP

template<typename T>
Array<T>::Array() : _array(NULL), _size(0) {	// Constructor
}

template<typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]), _size(n) {	// Parametric constructor
}

template<typename T>
Array<T>::Array(Array const & src) {	// Copy constructor
	_array =  new T[src.size()];
	_size = src.size();
	for (unsigned int i = 0; i < src.size(); i++) {
		_array[i] = src[i];
	}
}

template<typename T>
Array<T> & Array<T>::operator=(Array<T> const & src) {	// Assignation operator
	if (this != &src) {
		delete [] _array;
		_array = new T[src.size()];
		_size = src.size();
		for (unsigned int i = 0; i < src.size(); i++) {
			_array[i] = src[i];
		}
	}
	return *this;
}

template<typename T>
Array<T>::~Array() {	// Destructor
	delete [] _array;
}

// Member functions
template<typename T>
T & Array<T>::operator[](unsigned int i) {
	if (i >= _size) {
		throw OutOfBoundsException();
	}
	return _array[i];
}

template<typename T>
T const & Array<T>::operator[](unsigned int i) const {
	if (i >= _size) {
		throw OutOfBoundsException();
	}
	return _array[i];
}

template<typename T>
unsigned int Array<T>::size() const {
	return _size;
}

#endif