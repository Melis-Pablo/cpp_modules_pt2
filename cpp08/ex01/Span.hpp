#ifndef SPAN_HPP
#define SPAN_HPP

#include <exception>
#include <iostream>
#include <vector>
#include <algorithm>

class Span {
	private:
		unsigned int _N;
		std::vector<int> _v;
	public:
		// Canonical form
		Span();
		Span(unsigned int N);
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();
		// Member functions
		void addNumber(int n);

		template <typename T>
		void addNumber(T begin, T end) {
			if (std::distance(begin, end) > _N)
				throw spanFull();
			while (begin != end) {
				addNumber(*begin);
				begin++;
			}
		}
		int shortestSpan();
		long longestSpan();
		int shortestSpan() const;
		long longestSpan() const;
		// Exceptions
		class spanFull : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class noSpan : public std::exception {
			public:
				virtual const char *what() const throw();
		};
};


#endif