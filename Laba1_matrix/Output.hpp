#pragma once
#include <vector>
#include <iostream>
#include <istream>
#include <iterator>
#include "Matrix.hpp"
#include "Vector.hpp"


template<class T>
class matrix2dio {
public:

	Matrix<T> textToM2d(std::istream & is, size_t w);
	Matrix<T> fileToM2d(std::string file, size_t w);
	void m2dToText(std::ostream & os, const Matrix<T> & m);
	void printValarray(std::ostream & os, const std::valarray<int> & va);
};

typedef std::istream_iterator<int> int_istrm_iter;

template<class T>
Matrix<T> matrix2dio<T>::textToM2d(std::istream & is, size_t w) {

	std::vector<T> v;
	std::valarray<T> a;

	if (!is.good() || is.eof())
		return;

	copy(int_istrm_iter(is), int_istrm_iter(), back_inserter(v));
	a.resize(v.size(), sizeof(int));
	copy(v.begin(), v.end(), &a[0]);

	return new Matrix<T >(w, a);
}

template<class T>
Matrix<T> matrix2dio<T>::fileToM2d(std::string file, size_t w) {

	std::filebuf fb;
	std::istream is(&fb);

	fb.open(file.c_str(), std::ios::in);
	Matrix<T> m = textToM2d(is, w);
	fb.close();

	return m;
}

template<class T>
void matrix2dio<T>::m2dToText(std::ostream & os, const Matrix<T> & m) {

	size_t i = 0, j = 0;

	for (i = 0; i < m.Rows(); i++) {

		std::valarray<T> r = m.row(i);
		os << r[0];

		for (j = 1; j < m.Cols(); j++)
			std::cout << ' ' << r[j];

		os << '\n';
	}

	os << std::flush;
}

template<class T>
void matrix2dio<T>::printValarray(std::ostream & os,
	const std::valarray<int> & va) {

	copy(&va[0], &va[va.size() - 1], std::ostream_iterator<T >(os, " "));
	os << va[va.size() - 1] << "\n";
}