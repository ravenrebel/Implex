#include "pch.h"
#include "MethodHelper.h"
#include "LinearAlgebraNumMethods.h"
#include<string>


namespace LinearAlgebraNumMethods {
	bool JacobiMethodCPlusPlus::checkMatrix(double** matrix, int n) {
		int check = 0;
		for (int i = 0; i < n; i++) {

			double sum = 0;
			for (int j = 0; j < n; j++)
			{
				sum += fabs(matrix[i][j]);
			}

			if (2 * fabs(matrix[i][i]) > sum)
			{
				check++;
			}
		}
		if (check == n)
		{
			return true;
		}
		else return false;
	}

	void JacobiMethodCPlusPlus::jacobi(int n, double** A, double* B, double* X, double eps) {
		double norm, * TempX = new double[n], start, end;

		do {
			for (int i = 0; i < n; i++)
			{
				TempX[i] = B[i];
				for (int j = 0; j < n; j++)
				{
					if (i != j)
						TempX[i] -= A[i][j] * X[j];
				}

				TempX[i] /= A[i][i];
			}

			norm = abs(X[0] - TempX[0]);

			for (int h = 0; h < n; h++)
			{
				if (abs(X[h] - TempX[h]) > norm)
					norm = abs(X[h] - TempX[h]);

				X[h] = TempX[h];
			}
		} while (norm > eps);

		delete[] TempX;
	}

	List<double>^ JacobiMethodCPlusPlus::getVectorX() {
		return vectorX;
	}

	bool JacobiMethodCPlusPlus::method(List<List<double>^>^ matrixA, List<double>^ vectorB, List<double>^ initialX, double eps) {
		int n = matrixA->Count;
		double** A = LinearAlgebraNumMethods::MethodHelper::sharpListToMatrix(matrixA);

		if (checkMatrix(A, n))
		{
			double* x = new double[n];
			double* b = new double[n];

			for (int j = 0; j < n; j++)
			{
				x[j] = initialX[j];
				b[j] = vectorB[j];
			}

			jacobi(n, A, b, x, eps);

			for (int j = 0; j < n; j++)
			{
				vectorX->Add(x[j]);
			}

			for (int j = 0; j < n; j++)
			{
				delete[] A[j];
			}
			delete[] A;
			delete[] x;
			delete[] b;

			return true;
		}
		return false;
	}

	bool JacobiMethodCPlusPlus::method(unsigned long fileId, double eps) {
		int n;
		string fileName = to_string(fileId);

		double** A = MethodHelper::readMatrix("wwwroot\\input_files\\" + fileName + "A" + ".txt", n, n);
		if (checkMatrix(A, n))
		{
			double* b = MethodHelper::readVector("wwwroot\\input_files\\" + fileName + "b" + ".txt", n);
			double* x = MethodHelper::readVector("wwwroot\\input_files\\" + fileName + "x" + ".txt", n);

			jacobi(n, A, b, x, eps);

			MethodHelper::writeVector("wwwroot\\output_files\\" + fileName + ".txt", n, x);

			for (int j = 0; j < n; j++)
			{
				delete[] A[j];
			}
			delete[] A;
			delete[] x;
			delete[] b;

			return true;
		}
		return false;
	}
}