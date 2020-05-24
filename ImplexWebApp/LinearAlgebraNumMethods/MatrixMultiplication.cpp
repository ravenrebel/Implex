#include "pch.h"
#include "MatrixMultiplication.h"
#include "MethodHelper.h"
#pragma managed(push, off)
#include "ParallelNativeMatrixMult.h"
#include <string>
#pragma managed(pop)

typedef double TYPE;

namespace LinearAlgebraNumMethods {
	List<List<TYPE>^>^ MatrixMultiplication::multiply(List<List<TYPE>^>^ matrixA, List<List<TYPE>^>^ matrixB)
	{
		
		int K = matrixA[0]->Count;

		if (K != matrixB->Count) return nullptr;

		int N = matrixA->Count;
		int M = matrixB[0]->Count;

		TYPE* A = MethodHelper::sharpListToVector(matrixA);
		TYPE* B = MethodHelper::sharpListToVector(matrixB);
		
		int res_size = N * M;
		TYPE* res = new double[res_size];
		for (size_t i = 0; i < res_size; i++)
		{
			res[i] = 0;
		}
		matrix_mult_wiki(A, B, res, N, M, K);

		List<List<TYPE>^>^ matrixResult = MethodHelper::vectorToList(res, N, M);

		/*delete A;
		delete B;
		delete res;*/

		return matrixResult;
	}

	bool MatrixMultiplication::multiply(unsigned long fileId)
	{
		int N, M, K;
		string fileName = to_string(fileId);

		double* A = MethodHelper::readVector("wwwroot\\input_files\\" + fileName + "A" + ".txt", N, K);
		double* B = MethodHelper::readVector("wwwroot\\input_files\\" + fileName + "B" + ".txt", K, M);
		int res_size = N * M;
		TYPE* res = new double[res_size];
		for (size_t i = 0; i < res_size; i++)
		{
			res[i] = 0;
		}
		
		matrix_mult_wiki(A, B, res, N, M, K);

		MethodHelper::writeMatrix("wwwroot\\output_files\\" + fileName + ".txt", N, M, res); 

		delete[] A;
		delete[] B;
		delete[] res;

		return true;
	}
}

