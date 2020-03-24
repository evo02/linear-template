#pragma once
#include "Matrix.hpp"

template<class T>

class Vector
{
public:
	explicit Vector() = default;
	explicit Vector(size_t row, T mem) : data_(mem, row) {  }
	explicit Vector(size_t row) : data_(row) {  }
	explicit Vector(std::valarray<T> Arr) : data_(Arr) {  }

	~Vector() {  } //деструктор

	Vector(const Vector &) = default;
	Vector(const Vector && pam) : data_(pam.Data) {  }

	T & operator()(size_t Col) { return data_[Col]; }
	T operator()(size_t Col) const { return data_[Col]; };
	T& operator[](const size_t index) { return data_[index]; }
	T& operator[](const size_t index) const { return data_[index]; }

	Vector& operator=(const Vector& pam) { Vector copy(pam); copy.swap(*this); return *this; }
	Vector& operator=(const Vector&& pam) { pam.swap(*this);  return *this; }

	Vector slice(const size_t start, const size_t stop, const size_t step) //Slice for vector, нужен тест
	{
		return data_[std::slice(start, stop, step)];
	}

	Vector map(T _Func(T))
	{
		Vector res = *this;
		return _Func(res.data_);
	}
	
	Vector apply(T _Func(T)) const
	{
		*this->data_ = *this->data_.apply(_Func(T));
		return *this;
	}

	static Vector linespace(T start, T end, size_t size)
	{
		size_t lenght = (end - start) / (size - 1);
		std::valarray <T> res;
		for (size_t i(0); i < size - 1; ++i)
			res[i] = start + i * lenght;
		return Vector(res);
	}
	


	/*_NODISCARD valarray apply(_Ty _Func(_Ty)) const
	{	// return valarray transformed by _Func, value argument
		valarray<_Ty> _Ans(size()); ;
		for (size_t _Idx = 0; _Idx < _Ans.size(); ++_Idx)
			_Ans[_Idx] = _Func(_Myptr[_Idx]);
			return (_Ans);
	}

	_NODISCARD valarray apply(_Ty _Func(const _Ty&)) const
	{	// return valarray transformed by _Func, nonmutable argument
		_VALOP(_Ty, size(), _Func(_Myptr[_Idx]));
	}*/






	//Доступ к значениям класса для считывания
	std::valarray<T> data() const { return data_; }
	size_t size() const { return data_.size; }




private:
	std::valarray<T> data_;
};