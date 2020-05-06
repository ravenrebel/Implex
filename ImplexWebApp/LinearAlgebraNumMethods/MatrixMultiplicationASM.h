#pragma once
#include<iostream>

using namespace System;
using namespace System::Runtime::CompilerServices;
using namespace Collections::Generic;
using namespace std;


namespace LinearAlgebraNumMethods {
	public ref class MatrixMultiplicationASM
	{
	public:
		List<List<double>^>^ multiplyASM(List<List<double>^>^ matrixA, List<List<double>^>^ matrixB);
	private:
		//void ASM(double** a, double** b, double** res, int n, int p, int m);
	};
}
