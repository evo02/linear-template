#pragma once
#include <iostream>
#include <vector>
#include <valarray>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <tuple>
#include <ostream>
#include <fstream>
#include "Vector.hpp"


template<typename T>

class Matrix {
public:
	explicit Matrix() = default;                  //конструктор по умолчанию
	
	explicit Matrix(size_t rows, std::valarray<T> data) : rows_(rows), cols_(data.size() / rows), data_(data) {  }

	explicit Matrix(size_t rows, std::size_t columns) : rows_(rows), cols_(columns), data_(rows * columns) {  }

	template<typename U> explicit Matrix(size_t rows, std::size_t columns, const U auth) : rows_(rows), cols_(columns), data_(auth, rows * columns) {  }	

	explicit Matrix(size_t rows, std::size_t columns, std::valarray<T> data) : rows_(rows), cols_(columns), data_(data) {}

	~Matrix() {  } //деструктор

	Matrix(const Matrix &) = default;         //конструктор копирования

	Matrix(const Matrix &&pam) : rows_(pam.Rows()), cols_(pam.Cols()), data_(pam.Array()) //конструктор перемещения
	{
		rows_ = pam.Rows();
		cols_ = pam.Cols();
		data_ = pam.Array();
	}          

	Matrix& operator=(const Matrix& pam) = default;
	Matrix& operator=(const Matrix&& pam) { rows_ = pam.Rows(); cols_ = pam.Cols(); data_ = pam.Array();  return *this; }


	//Доступ к значениям класса для считывания
	size_t Rows() const { return rows_; }
	size_t Cols() const { return cols_; }         
	std::valarray<T> Array() const { return data_; }

	//slices для задания и в помощь 
	std::valarray<T> row(size_t r) const { return data_[std::slice(r * Cols(), Cols(), 1)]; }
	std::valarray<T> col(size_t c) const { return data_[std::slice(c, Rows(), Cols())]; }

	std::slice_array<T> row(size_t r) { return data_[std::slice(r * Cols(), Cols(), 1)]; }
	std::slice_array<T> col(size_t c) { return data_[std::slice(c, Rows(), Cols())]; }



	T & operator()(size_t Row, size_t Col) { return data_[Row * cols_ + Col]; }
	T operator()(size_t Row, size_t Col) const { return data_[Row * cols_ + Col]; };
	T& operator[](const size_t index) { return data_[index]; }
	T& operator[](const size_t index) const { return data_[index]; }

	Matrix transpose() //транспонирование
	{
		Matrix<T> result(cols_, rows_);
		for (std::size_t i = 0; i < rows_; ++i)
			result.col(i) = static_cast<std::valarray<T>> (row(i));
		return result;
	}

	template<typename U> Matrix& operator*=(const U scalar) { data_ *= scalar; return *this; }
	Matrix& operator*=(const Matrix& pam) { *this = std::move(*this * pam); return *this; }
	template<typename U>Matrix& operator*=(const Vector<T>& pam) { *this = std::move(*this * pam); return *this; }



	Matrix& operator+=(const Matrix& pam) { data_ += pam;  return *this;  }
	Matrix& operator-=(const Matrix& pam) { data_ -= pam;  return *this;  }
	Matrix& operator/=(const Matrix& pam) { data_ /= pam;  return *this; }

	//итераторы
	auto begin() { return data_.begin(); } 
	auto begin() const { return data_.begin(); }
	auto end() { return data_.end(); }            
	auto end() const { return data_.end(); }

	//для удобства индексирования
	const size_t index(const size_t row, const size_t column) const { return row * cols_ + column; }  



protected:
	std::size_t rows_; //строки
	std::size_t cols_; //столбцы
	std::valarray<T> data_;
};


#include "Matrix.inl"
