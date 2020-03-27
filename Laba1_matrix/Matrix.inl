#pragma once

template<class T>
Matrix<T> operator*(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)  //matrix multiplication
{
	if (leftMatrix.Cols() != rightMatrix.Rows()) { throw Matrix_RowColumnMismatch{}; }
	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols());
	for (size_t r{ 0 }; r < res.Rows(); ++r)
		for (size_t c(0); c < res.Cols(); ++c)
			for (size_t i{ 0 }; i < leftMatrix.Cols(); ++i)
				res(r, c) += leftMatrix(r, i) * rightMatrix(i, c);

	return res;
}

template<class T>
Matrix<T> operator*(const  Matrix<T>& leftMatrix, const Vector<T>& RightVec) //it is work !!!!!
{
	Matrix<T> rightMatrix(RightVec); //
	return leftMatrix * rightMatrix;
}

template<class T>
Matrix<T> operator*(const Vector<T>& leftVec, const  Matrix<T>& rightMatrix) //it is work !!!!!
{
	Matrix<T> leftMatrix(leftVec); //
	return leftMatrix * rightMatrix;
}

template<class T>
Matrix<T> operator*(const Matrix<T>& leftMatrix, const  T& scalar) //it is work !!!!!
{
	Matrix<T> res(leftMatrix.Rows(), leftMatrix.Cols(), leftMatrix.Array()*scalar);
	return res;
}

template<class T>
Matrix<T> operator*(const  T& scalar, const  Matrix<T>& rightMatrix) //it is work !!!!!
{
	Matrix<T> res(rightMatrix.Rows(), rightMatrix.Cols(), rightMatrix.Array()*scalar);
	return res;
}


template<class T>
Matrix<T> operator+(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	if (leftMatrix.Rows() != rightMatrix.Rows()) { throw Matrix_DifferentRowCount{}; }
	else if (leftMatrix.Cols() != rightMatrix.Cols()) { throw Matrix_DifferentColumnCount{}; }
	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols(), leftMatrix.Array()+rightMatrix.Array());
	return res;
}


template<class T>
Matrix<T> operator-(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	if (leftMatrix.Rows() != rightMatrix.Rows()) { throw Matrix_DifferentRowCount{}; }
	else if (leftMatrix.Cols() != rightMatrix.Cols()){ throw Matrix_DifferentColumnCount{}; }
	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols(), leftMatrix.Array() - rightMatrix.Array());
	return res;
}

template<class T>
Matrix<T> operator/(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	if (leftMatrix.Rows() != rightMatrix.Rows()){ throw Matrix_DifferentRowCount{}; }
	else if (leftMatrix.Cols() != rightMatrix.Cols()){ throw Matrix_DifferentColumnCount{}; }
	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols(), leftMatrix.Array() / rightMatrix.Array());
	return res;
}


template<class T>
bool operator==(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	if (&leftMatrix == &rightMatrix)
		return true;

	if (leftMatrix.Rows() != rightMatrix.Rows() || leftMatrix.Cols() != rightMatrix.Cols())
		return false;

	auto leftIt{ leftMatrix.begin() };
	auto rightIt{ rightMatrix.begin() };

	while (leftIt != leftMatrix.end())
	{
		if (*leftIt++ != *rightIt++)
		{
			return false;
		}
	}

	return true;
}

template<class T>
bool operator!=(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	return !(leftMatrix == rightMatrix);
}

template<class T>
Vector<T> operator+(const T& scalar, const Vector<T>& rightVector)
{
	Vector<T> res(rightVector);
	res += scalar;
	return res;
}

template<class T>
Vector<T> operator+(const Vector<T>& rightVector,  const T& scalar)
{
	Vector<T> res(rightVector);
	res += scalar;
	return res;
}

template<class T>
Vector<T> operator+(const Vector<T>& leftVector, const Vector<T>& rightVector)
{
	if (leftVector.size() != rightVector.size()) { throw Vector_WrongSize{}; }
	Vector<T> res(leftVector);
	res += rightVector;
	return res;
}

template<class T>
Vector<T> operator*(const Vector<T>& leftVector, const Vector<T>& rightVector)
{
	if (leftVector.size() != rightVector.size()) { throw Vector_WrongSize{}; }
	Vector<T> res(leftVector);
	res *= rightVector;
	return res;
}

template<class T>
Vector<T> operator*(const T& scalar, const Vector<T>& rightVector)
{
	Vector<T> res(rightVector);
	res *= scalar;
	return res;
}

template<class T>
Vector<T> operator*(const Vector<T>& rightVector, const T& scalar)
{
	Vector<T> res(rightVector);
	res *= scalar;
	return res;
}
