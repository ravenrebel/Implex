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
		bool CheckMatrix(double** matrix, int n);
		void Jacobi(int n, double** A, double* B, double* X, double eps);

	public:
		List<double>^ getVectorX();
		bool Method(List<List<double>^>^ matrixA, List<double>^ vectorB, List<double>^ initialX, double eps);
	};
}
