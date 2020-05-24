#include "pch.h"
#include "MethodHelper.h"
#include <fstream>

namespace LinearAlgebraNumMethods {
	double** MethodHelper::sharpListToMatrix(List<List<double>^>^ matrixA) {

		int n = matrixA[0]->Count;

		double** newA = new double* [n];
		int i = 0;
		for each (List<double>^ row in matrixA)
		{
			newA[i] = new double[n];
			for (int j = 0; j < n; j++)
			{
				newA[i][j] = row[j];
			}
			i++;
		}
		return newA;
	}

	double* MethodHelper::sharpListToVector(List<List<double>^>^ matrixA) {

		int n = matrixA[0]->Count;

		double* newA = new double[n];
		int i = 0;
		for each (List<double> ^ row in matrixA)
		{
			for (int j = 0; j < n; j++)
			{
				newA[j + i * n] = row[j];
			}
			i++;
		}
		return newA;
	}

	List<List<double>^>^ MethodHelper::matrixToList(double** matrix, int n, int m)
	{
		List<List<double>^>^ list = gcnew List<List<double>^>();

		for (int i = 0; i < n; i++)
		{
			List<double>^ row = gcnew List<double>();
			for (int j = 0; j < m; j++)
				row->Add(matrix[i][j]);
			list->Add(row);
		}

		return list;
	}

	List<List<double>^>^ MethodHelper::vectorToList(double* matrix, int n, int m)
	{
		List<List<double>^>^ list = gcnew List<List<double>^>();

		for (int i = 0; i < n; i++)
		{
			List<double>^ row = gcnew List<double>();
			for (int j = 0; j < m; j++)
				row->Add(matrix[j + i * n]);
			list->Add(row);
		}

		return list;
	}

	double** MethodHelper::readMatrix(string filename, int &n, int &m) {
		ifstream file;
		file.open(filename);
		file >> n >> m;
		double** A = new double* [n];

		for (int i = 0; i < n; i++) A[i] = new double[m];

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				file >> A[i][j];
		}
		file.close();
		return A;
	}

	double* MethodHelper::readVector(string filename, int& n)
	{
		ifstream file;
		file.open(filename);
		file >> n;
		double* b = new double [n];

		for (int i = 0; i < n; i++)
		{
			file >> b[i];
		}
		file.close();
		return b;
	}

	double* MethodHelper::readVector(string filename, int& n, int& m)
	{
		ifstream file;
		file.open(filename);
		file >> n >> m;

		double* A = new double [n*m];

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				file >> A[j + i * m];
		}
		file.close();
		return A;
	}

	void MethodHelper::writeVector(string filename, int n, double* b)
	{
		ofstream file;
		file.open(filename);
		file << n << "\n";

		for (int i = 0; i < n; i++)
		{
			file << b[i] << " ";
		}
		file.close();
	}

	void MethodHelper::writeMatrix(string filename, int n, int m, double** A) {
		ofstream file;
		file.open(filename);
		file << n << " "<< m << "\n";

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				file << A[i][j] << " ";
			file << "\n";
		}
		file.close();
	}

	void MethodHelper::writeMatrix(string filename, int n, int m, double* A)
	{
		ofstream file;
		file.open(filename);
		file << n << " " << m << "\n";

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				file << A[j + i * m] << " ";
			file << "\n";
		}
		file.close();
	}
}