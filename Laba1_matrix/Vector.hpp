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

	//construct with initializer_list
	Vector(const std::initializer_list<T>& pam) : data_(pam.size()) { std::copy(pam.begin(), pam.end(), &data_[0]); }
	
	//destructor
	~Vector() {  }

	//copy constructor
	Vector(const Vector &) = default;

	//move constructor
	Vector(const Vector && pam) : data_(pam.data()) {  }

	//copy assignment operator
	Vector& operator=(const Vector& pam) { data_ = pam.data_; return *this; }

	//move assignment operator
	Vector& operator=(Vector&& pam) noexcept { data_ = pam.data_;  return *this; }

	//valarray operator=
	Vector& operator=(std::valarray<T>& pam) { data_(pam); return *this; }

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

	//operators for vector&vector
	Vector& operator+=(const Vector& pam) { if (data_.size() != pam.size()) { throw Vector_WrongSize{}; } data_ += pam.data();  return *this; }
	Vector& operator-=(const Vector& pam) { if (data_.size() != pam.size()) { throw Vector_WrongSize{}; } data_ -= pam.data();  return *this; }
	Vector& operator/=(const Vector& pam) { if (data_.size() != pam.size()) { throw Vector_WrongSize{}; } data_ /= pam.data();  return *this; }
	Vector& operator*=(const Vector& pam) { if (data_.size() != pam.size()) { throw Vector_WrongSize{}; } data_ *= pam.data();  return *this; }

	bool operator==(const Vector& pam) { data_ == pam.data() ? true : false; }
	bool operator!=(const Vector& pam) { data_ != pam.data() ? true : false; }


private:
	std::valarray<T> data_;
};