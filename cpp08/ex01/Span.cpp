#include "Span.hpp"

Span::Span() : _N(0) {}

Span::Span(unsigned int N) : _N(N) {}

Span::Span(const Span &other) : _N(other._N), _v(other._v) {}

Span &Span::operator=(const Span &other) {
	if (this != &other) {
		_N = other._N;
		_v = other._v;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int n) {
	if (_v.size() == _N)
		throw spanFull();
	_v.push_back(n);
}

int Span::shortestSpan() {
	if (_v.size() < 2)
		throw noSpan();
	std::vector<int> v = _v;
	std::sort(v.begin(), v.end());
	int min = v[1] - v[0];
	for (size_t i = 2; i < v.size(); i++) {
		if (v[i] - v[i - 1] < min)
			min = v[i] - v[i - 1];
	}
	return min;
}

long Span::longestSpan() {
    if (_v.size() < 2)
        throw noSpan();
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> bounds =
        std::minmax_element(_v.begin(), _v.end());
    return static_cast<long>(*bounds.second) - *bounds.first;
}

long Span::longestSpan() const {
	if (_v.size() < 2)
		throw noSpan();
	std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> bounds =
		std::minmax_element(_v.begin(), _v.end());
	return static_cast<long>(*bounds.second) - *bounds.first;
}

int Span::shortestSpan() const {
	if (_v.size() < 2)
		throw noSpan();
	std::vector<int> v = _v;
	std::sort(v.begin(), v.end());
	int min = v[1] - v[0];
	for (size_t i = 2; i < v.size(); i++) {
		if (v[i] - v[i - 1] < min)
			min = v[i] - v[i - 1];
	}
	return min;
}

const char *Span::spanFull::what() const throw() {
	return "Span is full";
}

const char *Span::noSpan::what() const throw() {
	return "No span to find";
}