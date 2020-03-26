#pragma once


template<class T>

class Vector
{
public:
	//default constructor
	explicit Vector() = default;
	//constructor for creating vector row length and mem padding
	explicit Vector(size_t row, T mem) : data_(mem, row) {  }

	//constructor for zero vector row lenght
	explicit Vector(size_t row) : data_(row) {  }

	//constuctor for creating vector from valarray
	explicit Vector(std::valarray<T> Arr) : data_(Arr) {  }
	
	//destructor
	~Vector() {  }

	//copy constructor
	Vector(const Vector &) = default;

	//move constructor
	Vector(const Vector && pam) : data_(pam.data()) {  }

	//copy assignment operator
	Vector& operator=(const Vector& pam) { Vector copy(pam); copy.swap(*this); return *this; }

	//move assignment operator
	Vector& operator=(const Vector&& pam) { pam.swap(*this);  return *this; }

	//operator example(i)
	T & operator()(size_t Col) { return data_[Col]; }
	T operator()(size_t Col) const { return data_[Col]; };

	//operator example[i]
	T& operator[](const size_t index) { return data_[index]; }
	const T& operator[](const size_t index) const { return data_[index]; }


	//access to vector class values
	std::valarray<T> data() const { return data_; }
	size_t size() const { return data_.size(); }


	//slice for vector
	Vector slice(const size_t start, const size_t stop, const size_t step) { return data_[std::slice(start, stop, step)]; }


	//map for vector
	Vector map(T _Func(T)) const
	{
		Vector<T> other = *this;  
		for (T &i : other.data_)  //range-based for loop, since C++11
			i = _Func(i);
		return other;
	}
	Vector map(T _Func(const T&)) const
	{
		Vector<T> res = *this;
		for (T &i : res.data_)
			i = _Func(i);
		return res;
	}


	//apply for vector
	Vector apply(T _Func(T))
	{
		for (T &i : data_)
			i = _Func(i);
		return *this;
	}
	Vector apply(T _Func(const T&))
	{
		for (T &i : data_)
			i = _Func(i);
		return *this;
	}

	//static linespace
	static Vector linespace(T start, T end, size_t size)
	{
		T lenght = (end - start) / (size - 1);
		std::valarray <T> res(size);
		res[0] = start;
		for (size_t i{ 0 }; i < size ; ++i)
			res[i] = start + i * lenght;
		res[size-1] = end;
		return Vector(res);
	}


	//overload operators for scalars
	Vector& operator*=(const T scalar) { data_ *= scalar; return *this; }
	Vector& operator/=(const T scalar) { data_ /= scalar; return *this; }
	Vector& operator-=(const T scalar) { data_ -= scalar; return *this; }
	Vector& operator+=(const T scalar) { data_ += scalar; return *this; }

	Vector operator*(const T scalar) { Vector<T> pam(data_ * scalar); return pam; }
	Vector operator/(const T scalar) { Vector<T> pam(data_ / scalar); return pam; }
	Vector operator-(const T scalar) { Vector<T> pam(data_ - scalar); return pam; }
	Vector operator+(const T scalar) { Vector<T> pam(data_ + scalar); return pam; }


	//operators for vector&vector
	Vector& operator+=(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } *this += pam;  return *this; }
	Vector& operator-=(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } *this -= pam;  return *this; }
	Vector& operator/=(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } *this /= pam;  return *this; }
	Vector& operator*=(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } *this *= pam;  return *this; }

	Vector operator+(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } Vector<T> res(data_ + pam.data());  return res; }
	Vector operator-(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } Vector<T> res(data_ - pam.data());  return res; }
	Vector operator/(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } Vector<T> res(data_ / pam.data());  return res; }
	Vector operator*(const Vector& pam) { if (size() != pam.size()) { throw Vector_WrongSize{}; } Vector<T> res(data_ * pam.data());  return res; }

	bool operator==(const Vector& pam) { data_ == pam.data() ? true : false; }
	bool operator!=(const Vector& pam) { data_ != pam.data() ? true : false; }


private:
	std::valarray<T> data_;
};