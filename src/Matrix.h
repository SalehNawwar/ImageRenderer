#pragma once
#include <vector>

#define EPSILON 0.00001f

class Matrix
{
public:
	Matrix() = delete;

	Matrix(int rows, int columns);
	Matrix(const std::vector<std::vector<float>>& arr);
	
	Matrix T() const;
	Matrix Inv() const;
	Matrix Sub(int st_row=0,int end_row = -1,int st_column=0, int end_column=-1) const;
	float At(int row, int column) const;
	void Set(int row, int column, float val);
	int Columns() const;
	int Rows() const;
	float Id() const;

	void Assign(const Matrix& other,int st_row,int st_column);

	void CheckIndex(int row, int column) const;
	void CheckRowRange(int st, int end) const;
	void CheckColumnsRange(int st, int end) const;

	Matrix ConcatH(const Matrix& other) const;
	Matrix ConcatV(const Matrix& other) const;

	Matrix operator+(const Matrix& ) const;
	Matrix operator-(const Matrix& ) const;
	Matrix operator*(const Matrix& ) const;
	Matrix operator/(const Matrix& ) const;

	Matrix operator+(float val) const;
	Matrix operator-(float val) const;
	Matrix operator-() const;
	Matrix operator*(float val) const;
	Matrix operator/(float val) const;

	static Matrix Identity(int rows);

protected:
	std::vector<std::vector<float>> _arr;
};

