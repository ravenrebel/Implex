#include "pch.h"
#include "MethodHelper.h"
#include <fstream>

namespace LinearAlgebraNumMethods {
	double** MethodHelper::sharpListToMatrix(List<List<double>^>^ matrixA, int n) {
		double** newA = new double* [n];
		int i = 0;
		for each (List<double>^ row in matrixA)
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

	double** MethodHelper::readMatrix(string filename, int &n, int &m) {
		ifstream file;
		file.open(filename);
		file >> n >> m;
		double** A = new double* [n];

		for (int i = 0; i < n; i++) A[i] = new double[m];

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				file >> A[i][j];
		}
		file.close();
		return A;
	}
}