#include "Output.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
void testConstructors() {

	std::cout << "\n\n\nRunning Constructor Tests\n\n";

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	std::valarray<int> v(a, 12);
	std::size_t x = 3, y = 4;
	matrix2dio<int> i;
	std::cout <<
		"\nTesting: Matrix(std::size_t rows, std::size_t columns, "
		"std::valarray<T> data);\n";
	Matrix<int> m1(x, y, v);
	Matrix<int> gsg(m1);
	std::cout << m1(1, 0) << " " << gsg[11] << std::endl;
	i.m2dToText(std::cout, m1);
	std::cout << "number of rows: " << m1.Rows() << '\n'
		<< "number of cols: " << m1.Cols() << '\n'
		<< "matrix content:\n";
	i.m2dToText(std::cout, m1);

	std::cout << "\nTesting: Matrix(std::size_t rows, std::size_t columns);\n";
	Matrix<int> m2(x, y);

	std::cout << "number of rows: " << m2.Rows() << '\n'
		<< "number of cols: " << m2.Cols() << '\n'
		<< "matrix content:\n";
	i.m2dToText(std::cout, m2);

	std::cout <<
		"\nTesting: Matrix(std::size_t rows, std::valarray<T> data);\n";
	Matrix<int> m3(x, v);

	std::cout << "number of rows: " << m3.Rows() << '\n'
		<< "number of cols: " << m3.Cols() << '\n'
		<< "matrix content:\n";
	i.m2dToText(std::cout, m3);
}

void testRowsAndCols() {

	std::cout << "\n\n\nRunning Row/Col Accessor Tests\n\n";

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	std::valarray<int> v(a, 12);
	std::size_t x = 3, y = 4;
	matrix2dio<int> i;

	Matrix<int> m1(x, y, v);

	std::cout << "\nTesting: std::valarray<T> row(std::size_t r) const;\n";

	std::valarray<int> r1 = m1.row(0);
	std::valarray<int> r2 = m1.row(1);
	std::valarray<int> r3 = m1.row(2);

	std::cout << "row 1:\n";
	i.printValarray(std::cout, r1);
	std::cout << "row 2:\n";
	i.printValarray(std::cout, r2);
	std::cout << "row 3:\n";
	i.printValarray(std::cout, r3);

	std::cout << "\nTesting: std::valarray<T> col(std::size_t r) const;\n";

	std::valarray<int> c1 = m1.col(0);
	std::valarray<int> c2 = m1.col(1);
	std::valarray<int> c3 = m1.col(2);
	std::valarray<int> c4 = m1.col(3);

	std::cout << "col 1:\n";
	i.printValarray(std::cout, c1);
	std::cout << "col 2:\n";
	i.printValarray(std::cout, c2);
	std::cout << "col 3:\n";
	i.printValarray(std::cout, c3);
	std::cout << "col 4:\n";
	i.printValarray(std::cout, c4);

	std::cout << "\nTesting: std::slice_array<T> row(std::size_t r);\n";

	std::slice_array<int> rs1 = m1.row(0);
	std::slice_array<int> rs2 = m1.row(1);
	std::slice_array<int> rs3 = m1.row(2);

	std::cout << "row 1:\n";
	i.printValarray(std::cout, rs1);
	std::cout << "row 2:\n";
	i.printValarray(std::cout, rs2);
	std::cout << "row 3:\n";
	i.printValarray(std::cout, rs3);

	std::cout << "\nTesting: std::slice_array<T> col(std::size_t r);\n";

	std::slice_array<int> cs1 = m1.col(0);
	std::slice_array<int> cs2 = m1.col(1);
	std::slice_array<int> cs3 = m1.col(2);
	std::slice_array<int> cs4 = m1.col(3);

	std::cout << "col 1:\n";
	i.printValarray(std::cout, cs1);
	std::cout << "col 2:\n";
	i.printValarray(std::cout, cs2);
	std::cout << "col 3:\n";
	i.printValarray(std::cout, cs3);
	std::cout << "col 4:\n";
	i.printValarray(std::cout, cs4);
}

void testGenerators() {

	std::cout << "\n\n\nRunning Generator Tests\n\n";

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	int b[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120 };
	std::valarray<int> v1(a, 12);
	std::valarray<int> v2(b, 12);
	std::size_t x = 3, y = 4;
	matrix2dio<int> i;

	Matrix<int> m1(x, y, v1);
	Matrix<int> m2(x, y, v2);

	std::cout << "\nTesting: Matrix<T> transpose();\noriginal:\n";

	Matrix<int> m3 = m1.transpose();
	i.m2dToText(std::cout, m1);
	std::cout << "transposed:\n";
	i.m2dToText(std::cout, m3);
	std::valarray<int> ax = { 2, -3, 1, 5, 4, -2 };
	std::valarray<int> bx = { -7, 5, 2, -1, 4, 3 };
	Matrix<int> A(2, 3, ax);
	Matrix<int> B(3, 2, bx);
	i.m2dToText(std::cout, A);
	i.m2dToText(std::cout, B);
	A *= B;
	i.m2dToText(std::cout, A);

}

void testMatrix2d() {

	testConstructors();
	testRowsAndCols();
	testGenerators();
}


int main(int argc, char** argv) {

	testMatrix2d();
	return (EXIT_SUCCESS);
}