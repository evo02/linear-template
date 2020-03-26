
#pragma once


class Vector_Exception : std::exception
{
public:
	Vector_Exception(const char* msg) : std::exception(msg) {};
};

class Vector_WrongSize : Vector_Exception
{
public:
	Vector_WrongSize() : Vector_Exception("Size of Vector must be value must be the same") {  }
};

class Matrix_Exception : std::exception
{
public:
	Matrix_Exception(const char* msg) : std::exception(msg) {};
};

class Matrix_WrongRowCount : Matrix_Exception
{
public:
	Matrix_WrongRowCount() : Matrix_Exception("Row count should be at least 1") {}
};

class Matrix_WrongColumnCount : Matrix_Exception
{
public:
	Matrix_WrongColumnCount() : Matrix_Exception("Column count should be at least 1") {}
};

class Matrix_WrongSize : Matrix_Exception
{
public:
	Matrix_WrongSize() : Matrix_Exception("Size of array must be split into an equal number of columns and rows") {}
};

class Matrix_ArrayIsEmpty : Matrix_Exception
{
public:
	Matrix_ArrayIsEmpty() : Matrix_Exception("Array argument is empty") {}
};

class Matrix_ArrayIsJagged : Matrix_Exception
{
public:
	Matrix_ArrayIsJagged() : Matrix_Exception("Array argument is jagged") {}
};

class Matrix_DifferentRowCount : Matrix_Exception
{
public:
	Matrix_DifferentRowCount() : Matrix_Exception("Matrices have different row count") {}
};

class Matrix_DifferentColumnCount : Matrix_Exception
{
public:
	Matrix_DifferentColumnCount() : Matrix_Exception("Matrices have different column count") {}
};

class Matrix_RowColumnMismatch : Matrix_Exception
{
public:
	Matrix_RowColumnMismatch() : Matrix_Exception("Left column count is different than right row count") {}
};
