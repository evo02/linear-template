
template<class T, class U>
Matrix<T> operator*(const Matrix<T>& leftMatrix, const Matrix<U>& rightMatrix)  //умножение матриц друг на друга
{
	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols());
	for (size_t wlv(0); wlv < res.Rows(); ++wlv)
	{
		for (size_t column(0); column < res.Rows(); ++column)
		{
			for (size_t i(0); i < leftMatrix.Cols(); ++i)
			{
				res(wlv, column) += leftMatrix(wlv, i) * rightMatrix(i, column);
			}
		}
	}

	return res;
}

template<class T, class U>
Matrix<T> operator*(const  Matrix<T>& leftMatrix, const Vector<U>& RightPam)
{
	//check that matrix cols_ == vector.height
	Matrix<T> res(1, RightPam.Height());
	for (size_t column(0); column < res.Rows(); ++column)
	{
		for (size_t i(0); i < leftMatrix.Cols(); ++i)
		{
			res(1, column) += leftMatrix(1, i) * RightPam(i, column);
		}////?!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	return res;
}

template<class T, class U>
Matrix<T> operator+(const Matrix<T>& leftMatrix, const Matrix<U>& rightMatrix)
{
	/*if (leftMatrix.GetRowCount() != rightMatrix.GetRowCount())
	{
		throw Matrix_DifferentRowCount{};
	}
	else if (leftMatrix.GetColumnCount() != rightMatrix.GetColumnCount())
	{
		throw Matrix_DifferentColumnCount{};
	}*/

	Matrix<T> res(leftMatrix.Rows(), rightMatrix.Cols());
	auto resIt{ res.begin() };
	auto it1{ leftMatrix.begin() };
	auto it2{ rightMatrix.begin() };

	while (resIt != res.end())
	{
		*resIt++ = *it1++ + *it2++;
	}

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