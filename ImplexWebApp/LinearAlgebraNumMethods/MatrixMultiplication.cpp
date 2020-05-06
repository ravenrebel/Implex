#include "pch.h"
#include "MatrixMaltiplication.h"

namespace LinearAlgebraNumMethods {
	double** MatrixMultiplication::multiplyASM(List<List<double>^>^ matrixA, int n) {
		double** newA = new double* [n];
		int i = 0;
		for each (List<double> ^ row in matrixA)
		{
			newA[i] = new double[n];
			for (int j = 0; j < n; j++)
			{
				newA[i][j] = row[j];
			}
			i++;
		}
		return newA;
	}
}