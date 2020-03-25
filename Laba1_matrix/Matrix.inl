#pragma once

template<class T>
Matrix<T> operator*(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)  //matrix multiplication
{
	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols());
	for (size_t wlv(0); wlv < res.Rows(); ++wlv)
	{
		for (size_t column(0); column < res.Cols(); ++column)
		{
			for (size_t i(0); i < leftMatrix.Cols(); ++i)
			{
				res(wlv, column) += leftMatrix(wlv, i) * rightMatrix(i, column);
			}
		}
	}

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
	if (leftMatrix.Rows() != rightMatrix.Rows())
	{
		throw Matrix_DifferentRowCount{};
	}
	else if (leftMatrix.Cols() != rightMatrix.Cols())
	{
		throw Matrix_DifferentColumnCount{};
	}

	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols(), leftMatrix.Array()+rightMatrix.Array());
	return res;
}

template<class T>
Matrix<T> operator-(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	if (leftMatrix.Rows() != rightMatrix.Rows())
	{
		throw Matrix_DifferentRowCount{};
	}
	else if (leftMatrix.Cols() != rightMatrix.Cols())
	{
		throw Matrix_DifferentColumnCount{};
	}

	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols(), leftMatrix.Array() - rightMatrix.Array());
	return res;
}

template<class T>
Matrix<T> operator/(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	if (leftMatrix.Rows() != rightMatrix.Rows())
	{
		throw Matrix_DifferentRowCount{};
	}
	else if (leftMatrix.Cols() != rightMatrix.Cols())
	{
		throw Matrix_DifferentColumnCount{};
	}

	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols(), leftMatrix.Array() / rightMatrix.Array());
	return res;
}


template<class T>
bool operator==(const Matrix<T>& leftMatrix, const Matrix<T>& rightMatrix)
{
	if (&leftMatrix == &rightMatrix)
	{
		return true;
	}

	if (leftMatrix.Rows() != rightMatrix.Rows() ||
		leftMatrix.Cols() != rightMatrix.Cols())
	{
		return false;
	}

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

