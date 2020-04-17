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
		static double** MethodHelper::readMatrix(string filename, int &n, int &m);
		static double* MethodHelper::readVector(string filename, int& n);
		static void MethodHelper::writeMatrix(string filename, int n, int m, double** A);
		static void MethodHelper::writeVector(string filename, int n, double* b);
	};
}

