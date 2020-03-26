#pragma once


template<typename T>
std::ostream& operator<<(std::ostream & os, const Matrix<T> & m)
{
	for (size_t i{ 0 }; i < m.Rows(); ++i) 
	{
		for (size_t j{ 0 }; j < m.Cols(); ++j)
			os << ' ' << m(i, j);
		os << '\n';
	}
	os << std::flush;
	return os;
}

template<typename T>
std::istream& operator>>(std::istream &is, const Matrix<T> &m)
{
	for (size_t i{ 0 }; i < m.Rows(); ++i)
		for (size_t j{ 0 }; j < m.Cols(); j++)
			is >> m[i*m.Rows() + j];
	return is;
}

template<typename T>
std::ostream& operator<<(std::ostream & os, const Vector<T> & m)
{
	for (size_t i{ 0 }; i < m.size(); ++i)
		os << m[i] << '\n';
	os << '\n';// << std::flush;
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream & os, const std::slice_array<T> & m)
{
	std::valarray<T> z(m);
	for (size_t i{ 0 }; i < z.size(); ++i)
		os << z[i] << ' ';
	os << '\n';// << std::flush;
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream & os, const std::valarray<T> & m)
{
	for (size_t i{ 0 }; i < m.size(); ++i)
		os << m[i] << ' ';
	os << '\n';// << std::flush;
	return os;
}


template<typename T>
std::istream& operator>>(std::istream &is, const Vector<T> &m)
{
	for (size_t i{ 0 }; i < m.size(); ++i)
			is >> m[i];
	return is;
}



//function that writes matrix in csv file
template<typename T>
void wCSV(std::ofstream& f, Matrix<T> m) 
{
	for (size_t i{ 0 }; i < m.Rows(); ++i)
	{
		for (size_t j{ 0 }; j < m.Cols(); ++j)
			f << m[i*m.Rows() + j] << ";";
		f << std::endl;
	}
}

