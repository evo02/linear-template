#include "connect.hpp"



//csv reader to matrix
Matrix<double> rCSV(std::istream & is)
{
	size_t rows{ 0 }, cols{ 0 };
	std::string nline;
	std::vector<double> v;
	std::valarray<double> a;
	while (getline(is, nline))
	{
		std::replace(nline.begin(), nline.end(), ';', ' ');
		std::istringstream is(nline);
		std::string word;
		while (is >> word)
		{
			cols++;
			v.push_back(stod(word));
		};
		rows++;
	}
	a.resize(v.size(), sizeof(double));
	copy(v.begin(), v.end(), &a[0]);
	return Matrix<double>(rows, a);
}

using std::cout;
using std::cin;
using std::valarray;
using std::slice_array;
using std::endl;

void testConstructors() {

	std::cout << "\n\n\nRunning Constructor Tests\n\n";

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	std::valarray<int> v(a, 12);
	std::size_t x = 3, y = 4;
	Matrix<int> m1(x, y, v);
	Matrix<int> gsg(m1);
	Matrix<int> m2(x, y);
	std::cout <<
		"\nTesting: Matrix(std::size_t rows, std::valarray<T> data);\n";
	Matrix<int> m3(x, v);
	std::cout << "number of rows: " << m3.Rows() << '\n'
		<< "number of cols: " << m3.Cols() << '\n'
		<< "matrix content:\n" << m3 << endl <<endl;
}
int peace(int a) { return a * 9; }


void testOperators()
{
	std::cout << "\n\n\nTest operator* for matrix*matrix:\n\n";
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	int b[] = { 12, 11, 10, 9 };
	int c[] = { 1,2,3,4 };
	int e[] = { 1,1,1,1,1,1,1,1,1 };
	std::valarray<int> one(e, 9);
	std::valarray<int> v(a, 12);
	std::valarray<int> v1(b, 4);
	std::valarray<int> v2(c, 4);
	Matrix<int> threexfour(3, 4, v);
	Matrix<int> fourxfive(4, 3, v);
	Matrix<int> threexfour2(threexfour);
	Matrix<int> edin(3, 3, one);
	Vector<int> pam(v1);
	Matrix<int> bam(1, 4, v2);
	cout << "Multiplication two matrix:\n";
	cout << "first\n" << threexfour << endl;
	cout << "second\n" << fourxfive << endl;
	cout << "Result:\n" << threexfour*fourxfive << endl << endl;
	cout << "Multiplication matrix and vector:\n";
	cout << "matrix:\n" << threexfour << endl;
	cout << "vector:\n" << pam;
	cout << "Result:\n" << threexfour * pam << endl << endl;
	cout << "Multiplication matrix and scalar(10):\n";
	cout << "matrix:\n" << threexfour << endl;
	cout << "Result:\n" << threexfour * 10 << endl << endl;
	cout << "Multiplication vector and scalar(10):\n";
	cout << "vector:\n" << pam << endl;
	cout << "Result:\n" << pam * 10 << endl << endl;
	cout << "Addition, subtraction and division work similarly.\n\n";
	cout << "map for matrix: \n " << threexfour.map(peace) << endl << endl;
	cout << "check: \n" << threexfour << endl << endl;
	cout << "Apply for matrix: \n " << threexfour.apply(peace) << endl << endl;
	cout << "check: \n" << threexfour << endl << endl;
	cout << "transpoce matrix: \n" << "before: \n" << fourxfive << endl << "after: \n" << fourxfive.transpose() << endl << endl;
	cout << "slice for matrix: \n" << fourxfive.slice(0, 3, 1, 1, 3, 1) << endl << "for vectors works easier based 'slice' in <valarray>" << endl << endl;
	Vector <double> lin = Vector<double>::linespace(1.00, 15.00, 10);
	cout << "linspace for vector: \n" << lin;

}



void testRowsAndCols() {

	std::cout << "\n\n\nRunning Row/Col Accessor Tests\n\n";

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	valarray<int> v(a, 12);
	size_t x = 3, y = 4;
	Matrix<int> m1(x, y, v);
	cout << "\nTesting: std::valarray<T> row(std::size_t r) const;\n";

	valarray<int> r1 = m1.row(0);
	valarray<int> r2 = m1.row(1);
	valarray<int> r3 = m1.row(2);

	cout << "row 1:\n";
	cout << r1;
	cout << "row 2:\n";
	cout << r2;
	cout << "row 3:\n";
	cout << r3;

	cout << "\nTesting: std::valarray<T> col(std::size_t r) const;\n";

	std::valarray<int> c1 = m1.col(0);
	std::valarray<int> c2 = m1.col(1);
	std::valarray<int> c3 = m1.col(2);
	std::valarray<int> c4 = m1.col(3);

	cout << "col 1:\n";
	cout << c1;
	cout << "col 2:\n";
	cout << c2;
	cout << "col 3:\n";
	cout << c3;
	cout << "col 4:\n";
	cout << c4;

	cout << "\nTesting: std::slice_array<T> row(std::size_t r);\n";

	std::slice_array<int> rs1 = m1.row(0);
	std::slice_array<int> rs2 = m1.row(1);
	std::slice_array<int> rs3 = m1.row(2);

	cout << "row 1:\n";
	cout << rs1;
	cout << "row 2:\n";
	cout << rs2;
	cout << "row 3:\n";
	cout << rs3;

	cout << "\nTesting: std::slice_array<T> col(std::size_t r);\n";

	slice_array<int> cs1 = m1.col(0);
	slice_array<int> cs2 = m1.col(1);
	slice_array<int> cs3 = m1.col(2);
	slice_array<int> cs4 = m1.col(3);

	cout << "col 1:\n";
	cout << cs1;
	cout << "col 2:\n";
	cout << cs2;
	cout << "col 3:\n";
	cout << cs3;
	cout << "col 4:\n";
	cout << cs4;
}


void testCSV()
{
	cout << "Testing CSV writing and reading\n";
	std::ofstream out("out.csv");
	int b[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120 };
	std::valarray<int> v2(b, 12);
	Matrix<int> m2(3, 4, v2);
	std::cout << "This matrix will be in CSV \n"<< m2;
	wCSV(out, m2);
	std::cout << "Worked, can check";
	std::ifstream input("in.csv");
	Matrix<double> a;
	cout << "Now we count from the file\n";
	a = rCSV(input);
	std::cout << "\n" << a;
	std::cout << "Worked, can check\n\n\n";
}

void testMatrix2d() {
	testCSV();
	testConstructors();
	testOperators();
}


int main(int argc, char** argv) {

	testMatrix2d();
 	return (EXIT_SUCCESS);
}