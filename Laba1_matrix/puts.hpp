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


/*template<typename T>
void wCSV(std::ofstream& f, Vector<T> m)
{
	for (size_t i{ 0 }; i < m.size(); ++i)
			f << ";" << m[i];
}

/*template<typename T>
std::ofstream& PutToFile(std::ofstream& out, Matrix<T>&a)
{
	for (int i = 0; i < a.Rows(); i++)
	{
		for (int j = 0; j < a.Cols(); j++)
		{
			out << a[i*a.Rows()+j] << ";";
		}
		out << std::endl;
	}
	return out;
}

/*template<typename T>
Matrix<T> rCSV(std::ifstream& file)
{
	size_t rows = 0, columns = 0;
	std::string line, value;
	double temp = 0.0;
	while (getline(file, line))
		rows++;
	std::istringstream strm(line);
	while (getline(strm, value, ','))
		columns++;
	file.clear();
	file.seekg(0);
	Matrix<T> m(rows, columns);
	for (size_t i = 0; i < rows; i++)
	{
		getline(file, line);
		std::istringstream strm(line);
		for (size_t j = 0; j < columns; j++)
		{
			getline(strm, value, ',');
			std::stringstream ss(value);
			ss >> temp;
			m[i*m.Rows()+j] = temp;
		}
	}
	return m;
}*/



/*template<class T>
Matrix<T> toFile(std::string file, size_t w) 
{

	std::filebuf fb;
	std::istream is(&fb);

	fb.open(file.c_str(), std::ios::in);
	Matrix<T> m = textToM2d(is, w);
	fb.close();

	return m;
}




template<class T>
void printValarray(std::ostream & os,
	const std::valarray<int> & va) {

	copy(&va[0], &va[va.size() - 1], std::ostream_iterator<T >(os, " "));
	os << va[va.size() - 1] << "\n";
}*/