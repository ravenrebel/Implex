#pragma once
#pragma once
#include<iostream>

using namespace System;
using namespace System::Runtime::CompilerServices;
using namespace Collections::Generic;
using namespace std;
typedef double TYPE;


namespace LinearAlgebraNumMethods {
	public ref class MatrixMultiplication
	{
	public:
		List<List<TYPE>^>^ multiply(List<List<TYPE>^>^ matrixA, List<List<TYPE>^>^ matrixB);
		bool multiply(unsigned long fileId);
	};
}
