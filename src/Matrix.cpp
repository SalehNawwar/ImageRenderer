#include "Matrix.h"

Matrix::Matrix(int rows, int columns) {
	_arr.assign(rows, std::vector<float>(columns));
}

Matrix::Matrix(const std::vector<std::vector<float>>& arr):_arr(arr) {}

float Matrix::At(int row, int column) const {
	if (row < 0 || column < 0) {
		throw -1;
	}

	return _arr.at(row).at(column);
}

int Matrix::Columns() const {
	return _arr.at(0).size();
}

int Matrix::Rows() const {
	return _arr.size();
}

void Matrix::CheckIndex(int row, int column) const {
	if (row < 0 || column < 0 || row >= Rows() || column >= Columns()) {
		throw - 1;
	}
}

void Matrix::CheckRowRange(int st, int end) const {
	if (st >= end || st<0 || end>Rows()) {
		throw -1;
	}
}

void Matrix::CheckColumnsRange(int st, int end) const {
	if (st >= end || st<0 || end>Columns()) {
		throw -1;
	}
}

void Matrix::Set(int row, int column, float val) {
	CheckIndex(row, column);

	_arr.at(row).at(column) = val;
}

Matrix Matrix::T() const {
	int n = Rows();
	int m = Columns();
	
	Matrix ret(m, n);
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			ret.Set(j, i, At(i, j));
		}
	}
	
	return ret;
}

Matrix Matrix::Inv() const {
	if (Rows() != Columns()) {
		throw -1;
	}

	Matrix curr(this->ConcatH(Matrix::Identity(Rows())));

	for (int column = 0; column < Columns(); ++column) {
		curr.Assign(curr.Sub(column, column + 1) / curr.At(column, column), column, 0);
		for (int row = 0; row < Rows(); ++row) {
			if (row == column) {
				continue;
			}
			curr.Assign(curr.Sub(row, row + 1) - curr.Sub(column, column + 1) * curr.At(row, column), row, 0);
		}
	}

	return curr.Sub(0,-1,Columns(),-1);
}

float Matrix::Id() const {
	throw -1;
}

Matrix Matrix::Sub(int st_row, int end_row, int st_column, int end_column) const {
	if (end_row == -1) {
		end_row = Rows();
	}
	if (end_column == -1) {
		end_column = Columns();
	}

	CheckRowRange(st_row, end_row);
	CheckColumnsRange(st_column, end_column);

	Matrix ret(end_row - st_row, end_column - st_column);
	for (int i = st_row; i < end_row; ++i) {
		for (int j = st_column; j < end_column; ++j) {
			ret.Set(i-st_row, j-st_column, At(i, j));
		}
	}

	return ret;
}

void Matrix::Assign(const Matrix& other, int st_row, int st_column) {
	if (st_row + other.Rows() > Rows() || st_column + other.Columns() > Columns()) {
		throw -1;
	}

	for (int i = st_row; i < st_row + other.Rows(); ++i) {
		for (int j = st_column; j < st_column + other.Columns(); ++j) {
			Set(i, j, other.At(i - st_row, j - st_column));
		}
	}

}

Matrix Matrix::ConcatH(const Matrix& other) const {
	int n = Rows();
	int m = other.Columns() + Columns();
	Matrix ret(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < Columns(); ++j) {
			ret.Set(i, j, At(i, j));
		}
		for (int j = 0; j < other.Columns(); ++j) {
			ret.Set(i, j + Columns(), other.At(i, j));
		}
	}
	return ret;
}

Matrix Matrix::ConcatV(const Matrix& other) const {
	int n = other.Rows() + Rows();
	int m = Columns();
	Matrix ret(n, m);
	for (int i = 0; i < Rows(); ++i) {
		for (int j = 0; j < m; ++j) {
			ret.Set(i, j, At(i, j));
		}
	}
	for (int i = 0; i < other.Rows(); ++i) {
		for (int j = 0; j < m; ++j) {
			ret.Set(i + Rows(), j, ret.At(i, j));
		}
	}
	return ret;
}

Matrix Matrix::operator+(float val) const {
	Matrix ret(Rows(),Columns());
	for (int i = 0; i < Rows(); ++i) {
		for (int j = 0; j < Columns(); ++j) {
			ret.Set(i, j, At(i, j) + val);
		}
	}
	return ret;
}

Matrix Matrix::operator-(float val) const {
	Matrix ret(Rows(), Columns());
	for (int i = 0; i < Rows(); ++i) {
		for (int j = 0; j < Columns(); ++j) {
			ret.Set(i, j, At(i, j) - val);
		}
	}
	return ret;
}

Matrix Matrix::operator-() const {
	return (*this) * -1;
}

Matrix Matrix::operator*(float val) const {
	Matrix ret(Rows(), Columns());
	for (int i = 0; i < Rows(); ++i) {
		for (int j = 0; j < Columns(); ++j) {
			ret.Set(i, j, At(i, j) * val);
		}
	}
	return ret;
}

Matrix Matrix::operator/(float val) const {
	Matrix ret(Rows(), Columns());
	for (int i = 0; i < Rows(); ++i) {
		for (int j = 0; j < Columns(); ++j) {
			ret.Set(i, j, At(i, j) / val);
		}
	}
	return ret;
}

Matrix Matrix::operator+(const Matrix& other) const {
	
	if (Rows() != other.Rows() || Columns() != other.Columns()) {
		throw -1;
	}
	
	Matrix ret(Rows(), Columns());

	for (int i = 0; i < Rows(); ++i) {
		for (int j = 0; j < Columns(); ++j) {
			ret.Set(i, j, At(i, j) + other.At(i, j));
		}
	}

	return ret;
}

Matrix Matrix::operator-(const Matrix& other) const {

	if (Rows() != other.Rows() || Columns() != other.Columns()) {
		throw - 1;
	}
	
	Matrix ret(Rows(), Columns());

	for (int i = 0; i < Rows(); ++i) {
		for (int j = 0; j < Columns(); ++j) {
			ret.Set(i, j, At(i, j) - other.At(i, j));
		}
	}

	return ret;
}

Matrix Matrix::operator*(const Matrix& other) const {

	if (Columns() != other.Rows()) {
		throw -1;
	}
	int n = Rows();
	int m = other.Columns();
	int common = Columns();
	Matrix ret(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			float sum = 0;
			for (int k = 0; k < common; ++k) {
				sum += At(i, k) * other.At(k, j);
				//sum += _arr[i][k] * other._arr[k][j];
			}
			ret.Set(i, j, sum);
			//ret._arr[i][j] = sum;
		}
	}

	return ret;
}

Matrix Matrix::operator/(const Matrix& other) const {
	return (*this) * other.Inv();
}

Matrix Matrix::Identity(int rows) {
	Matrix ret(rows,rows);
	for (int i = 0; i < rows; ++i) {
		ret.Set(i, i, 1);
	}
	return ret;
}
