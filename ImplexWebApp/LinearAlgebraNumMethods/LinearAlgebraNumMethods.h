#include<iostream>
#include "MethodHelper.h"

using namespace System;
using namespace System::Runtime::CompilerServices;
using namespace Collections::Generic;
using namespace std;

namespace LinearAlgebraNumMethods {

	public ref class JacobiMethodCPlusPlus {
	private:
		List<double>^ vectorX = gcnew List<double>();
		bool checkMatrix(double** matrix, int n);
		void jacobi(int n, double** A, double* B, double* X, double eps);

	public:
		List<double>^ getVectorX();
		bool method(List<List<double>^>^ matrixA, List<double>^ vectorB, List<double>^ initialX, double eps);
		bool method(unsigned long fileId, double eps);
	};
}
