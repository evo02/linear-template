#pragma once



template<typename T>

class Matrix {
public:
	//default constructor
	explicit Matrix() = default;                  
	
	//
	explicit Matrix(size_t rows, std::valarray<T> data) : rows_(rows), cols_(data.size() / rows), data_(data) { if (data.size() % rows != 0) throw Matrix_WrongSize{}; }

	//constructor for zero matrix
	explicit Matrix(size_t rows, size_t columns) : rows_(rows), cols_(columns), data_(rows * columns) {  }

	//constructor to fill the matrix with the same elements "auth"
	explicit Matrix(size_t rows, size_t columns, const T auth) : rows_(rows), cols_(columns), data_(auth, rows * columns) {  }

	//constructor for creating a matrix with the number of rows, columns and valarray
	explicit Matrix(size_t rows, size_t columns, std::valarray<T> data) : rows_(rows), cols_(columns), data_(data) {  }

	// vector to matrix for overload operators(vector-column)
	explicit Matrix(Vector<T> vect) : rows_(vect.size()), cols_(1), data_(vect.data()) {  }

	//construct with initializer_list<initializer_list<T>>
	Matrix(size_t rows, size_t columns, const std::initializer_list<T>& pam) : rows_(rows), cols_(columns), data_(pam.size()) { std::copy(pam.begin(), pam.end(), &data_[0]); }

	//construct with Vector<Vector<T>>
	//Matrix(Vector<Vector<T>> pam) : rows_(pam.size()->size()), cols_(pam.begin()),

	//destructor
	~Matrix() {  } 

	//copy constructor
	Matrix(const Matrix &) = default;         

	//move constructor
	Matrix(const Matrix &&pam) : rows_(pam.Rows()), cols_(pam.Cols()), data_(pam.Array()) 
	{
		rows_ = pam.Rows();
		cols_ = pam.Cols();
		data_ = pam.Array();
	}          

	//copy assignment operator
	Matrix& operator=(const Matrix& pam) = default;  

	//move assignment operator
	Matrix& operator=(const Matrix&& pam) { rows_ = pam.Rows(); cols_ = pam.Cols(); data_ = pam.Array();  return *this; } 

	//Matrix& operator=(, const Vector<T>) { }

	//access to matrix class values
	size_t Rows() const { return rows_; }
	size_t Cols() const { return cols_; }         
	std::valarray<T> Array() const { return data_; }


	//operator(m, n)
	T & operator()(size_t Row, size_t Col) { return data_[Row * cols_ + Col]; }
	const T & operator()(size_t Row, size_t Col) const { return data_[Row * cols_ + Col]; };

	//operator[m x n], 
	//for example in matrix
	//1 2 3
	//4 5 6
	//7 8 9
	//example[7] = 8, numbering as in valarray
	T & operator[](const size_t index) { return data_[index]; }
	const T & operator[](const size_t index) const { return data_[index]; }



	//matrix transpose mode
	Matrix transpose()
	{
		Matrix<T> result(cols_, rows_);
		for (std::size_t i = 0; i < rows_; ++i)
			result.col(i) = static_cast<std::valarray<T>> (row(i));
		return result;
	}


	//operation apply for apply any function elementwise
	Matrix apply(T _Func(T))
	{
		for (T &i : data_)//range-based for loop, since C++11
			i = _Func(i);
		return *this;
	}
	Matrix apply(T _Func(const T&))
	{
		for (T &i : data_)
			i = _Func(i);
		return *this;
	}


	//operation map with which you can apply element-wise any function to a copy of the matrix
	Matrix map(T _Func(T)) const
	{
		Matrix<T> res = *this;  
		for (T &i : res.data_) 
			i = _Func(i);
		return res;
	}
	Matrix map(T _Func(const T&)) const
	{
		Matrix<T> res = *this;
		for (T &i : res.data_)
			i = _Func(i);
		return res;
	}

	


	//numpy slice analog for matrix
	Matrix slice(const size_t row_begin, const size_t row_end, const size_t row_step,
		const size_t column_begin, const size_t column_end, const size_t column_step) const
	{
		size_t r = (size_t)ceil((row_end - row_begin) / row_step);
		size_t c = (size_t)ceil((column_end - column_begin) / column_step);
		Matrix<T> res(r, c);
		for (size_t i{ row_begin }, m{ 0 }; i < row_end; i += row_step, ++m)
			for (size_t j{ column_begin }, n{ 0 }; j < column_end; j += column_step, ++n)

				res[m*c + n] = data_[i*c + j];
		return res;
	}


	//slices
	//Vector<T> row(size_t r) { return Vector<T>(data_[std::slice(r * Cols(), Cols(), 1)]); };
	//Vector<T> col(size_t c) { return Vector<T>(data_[std::slice(c, Rows(), Cols())] ); }

	Matrix<T> setRow(size_t r, Vector<T> row) {
		for (size_t j{ 0 }; j < row.size(); j++)
			data_[r*cols_ + j] = row[j];
		return *this;
		}

	std::slice_array<T> row(size_t r) { return data_[std::slice(r * Cols(), Cols(), 1)]; }
	std::slice_array<T> col(size_t c) { return data_[std::slice(c, Rows(), Cols())]; }

	std::valarray<T> row(size_t r) const { return data_[std::slice(r * Cols(), Cols(), 1)]; }
	std::valarray<T> col(size_t c) const { return data_[std::slice(c, Rows(), Cols())]; }
	
	//overload operators for scalars
	Matrix& operator*=(const T scalar) { data_ *= scalar; return *this; }
	Matrix& operator/=(const T scalar) { data_ /= scalar; return *this; }
	Matrix& operator-=(const T scalar) { data_ -= scalar; return *this; }
	Matrix& operator+=(const T scalar) { data_ += scalar; return *this; }



	//overload operator for matrix to vector multilpication
	Matrix& operator*=(const Vector<T>& pam) { *this = std::move(*this * pam); return *this; }


	//overload operators for matrix x matrix
	Matrix& operator+=(const Matrix& pam) { data_ += pam;  return *this;  }
	Matrix& operator-=(const Matrix& pam) { data_ -= pam;  return *this;  }
	Matrix& operator/=(const Matrix& pam) { data_ /= pam;  return *this; }
	Matrix& operator*=(const Matrix& pam) { *this = std::move(*this * pam); return *this; }
	

	//stream operators
	//friend std::ostream& operator<<(std::ostream &, const Matrix<T> &);

private:
	std::size_t rows_; //rows
	std::size_t cols_; //columns
	std::valarray<T> data_; //array
};




