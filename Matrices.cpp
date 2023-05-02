#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		//assign member variables
		rows = _rows;
		cols = _cols;

		//resize vector		
		a.resize(rows);
		for (size_t i = 0; i < rows; i++)
		{
			a[i].resize(cols);

			//initialize all cells to 0
			for (size_t j = 0; j < cols; j++)
			{
				a[i][j] = 0;
			}
		}

		/*
		Alternate way to resize vector
		a.resize(rows, vector<double>(cols, 0));

		*/
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(15) << a(i, j) << " ";
			}
			os << endl; // don't use cout, use os
		}
		return os; //allows stuff like=> cout << a << endl;
	}

	//Returns a matrix that is the sum of a & b
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			//this will return to the caller
			throw runtime_error("Error: dimensions don't match");
		}

		//add stuff
		Matrix c(a.getRows(), a.getCols());
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}
}