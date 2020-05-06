#pragma once
#include<iostream>

using namespace System;
using namespace System::Runtime::CompilerServices;
using namespace Collections::Generic;
using namespace std;

namespace LinearAlgebraNumMethods {

	class MatrixMultiplicaton {
	public:
		static double** myltiplyASM(List<List<double>^>^ matrixA, List<List<double>^>^ matrixB);
		
	};
}