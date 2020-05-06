#include "pch.h"
#include "MatrixMultiplicationASM.h"
#include "MethodHelper.h"
#include "Header.h"

namespace LinearAlgebraNumMethods {
	List<List<double>^>^ MatrixMultiplicationASM::multiplyASM(List<List<double>^>^ matrixA, List<List<double>^>^ matrixB)
	{
		int n = matrixA->Count;
		int m = matrixB->Count;
		int p = matrixA[0]->Count;

		double** a = MethodHelper::sharpListToMatrix(matrixA);
		double** b = MethodHelper::sharpListToMatrix(matrixB);
		double** res = new double* [m];

		for (int i = 0; i < m; i++)
		{
			res[i] = new double[m];
			for (int j = 0; j < m; j++)
			{
				res[i][j] = 0;
			}
		}

		ASM(a, b, res, n,  p, m);

		List<List<double>^>^ matrixResult = MethodHelper::matrixToList(res, m, m);
		return matrixResult;
	}

	
	
}

