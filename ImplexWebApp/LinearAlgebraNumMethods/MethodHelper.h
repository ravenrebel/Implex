#pragma once
#include<iostream>

using namespace System;
using namespace System::Runtime::CompilerServices;
using namespace Collections::Generic;
using namespace std;

namespace LinearAlgebraNumMethods {
	static class MethodHelper {
	public:
		static double** sharpListToMatrix(List<List<double>^>^ matrixA, int n);
	};
}

