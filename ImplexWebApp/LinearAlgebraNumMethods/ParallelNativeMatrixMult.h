#pragma once
#include "pch.h"
#include "ParallelNativeMatrixMult.h"
#include<iostream>
#include <chrono>
#include <ctime>
#include <random>
#include <omp.h>

using namespace std;

typedef double TYPE;
#define MAX_VAL 10
#define MIN_VAL 1
#define BLOCK_SIZE 512

chrono::time_point<chrono::system_clock> _start, _end;

TYPE** random_square_matrix(int dimension) {

	TYPE** matrix = new TYPE * [dimension];

	for (int i = 0; i < dimension; i++) {
		matrix[i] = new TYPE[dimension];
	}

	srand(time(0));

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			matrix[i][j] = rand() % (MAX_VAL + MIN_VAL);
		}
	}

	return matrix;
}

TYPE** zero_square_matrix(int dimension) {

	TYPE** matrix = new TYPE * [dimension];

	for (int i = 0; i < dimension; i++) {
		matrix[i] = new TYPE[dimension];
	}

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			matrix[i][j] = 0.0;
		}
	}

	return matrix;
}

int matrix_mult(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension) {

	_start = std::chrono::system_clock::now();

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			for (int k = 0; k < dimension; k++) {
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	_end = chrono::system_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
}

int matrix_block_mult(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension) {

	_start = std::chrono::system_clock::now();

	int bs = BLOCK_SIZE;
	for (int jj = 0; jj < dimension; jj += bs) {
		for (int kk = 0; kk < dimension; kk += bs) {
			for (int i = 0; i < dimension; i++) {
				for (int k = kk; k < ((kk + bs) > dimension ? dimension : (kk + bs)); k++) {
					TYPE r = matrixA[i][k];
					for (int j = jj; j < ((jj + bs) > dimension ? dimension : (jj + bs)); j++) {
						matrixC[i][j] += r * matrixB[k][j];
					}
				}
			}
		}
	}

	_end = chrono::system_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
}

int matrix_mult_parallel(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension) {

	_start = std::chrono::system_clock::now();

#pragma omp parallel for
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			for (int k = 0; k < dimension; k++) {
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	_end = chrono::system_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
}

void convert(TYPE** matrixA, TYPE** matrixB, int dimension, TYPE* flatA, TYPE* flatB) {

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			flatA[j + i * dimension] = matrixA[i][j];
			flatB[j + i * dimension] = matrixB[i][j];
		}
	}
}

bool compare(TYPE** matrixA, TYPE** matrixB, int dimension) {
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			if (matrixA[i][j] != matrixB[i][j]) return false;
		}
	}
	return true;
}

bool compare(TYPE* matrixA, TYPE* matrixB, int dimension) {
	for (int i = 0; i < dimension; i++)
	{
		if (matrixA[i] != matrixB[i]) return false;
	}
	return true;
}

void print_matrix(TYPE** matrix, int length) {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void print_vector(TYPE* vector, int length) {
	for (int i = 0; i < length; i++)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}

int matrix_mult_naive(const TYPE* A, const TYPE* B, TYPE* C, const int N, const int M, const int K) {

	_start = std::chrono::system_clock::now();

#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			TYPE sum = 0;
			for (int l = 0; l < M; l++) {
				sum += A[M * i + l] * B[K * l + j];
			}
			C[K * i + j] = sum;
		}
	}

	_end = chrono::system_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
}

int matrix_mult_wiki(const TYPE* A, const TYPE* B, TYPE* C, const int N, const int M, const int K) {

	_start = std::chrono::system_clock::now();

#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		for (int l = 0; l < M; l++) {
			TYPE a = A[M * i + l];
			for (int j = 0; j < K; j++) {
				C[K * i + j] += a * B[K * l + j];
			}
		}
	}

	_end = chrono::system_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
}

int matrix_mult_wiki_block(const TYPE* A, const TYPE* B, TYPE* C, const int N, const int M, const int K) {

	_start = std::chrono::system_clock::now();
	const int bs = BLOCK_SIZE;

	for (int l2 = 0; l2 < M; l2 += bs) {
		for (int j2 = 0; j2 < K; j2 += bs) {
#pragma omp parallel for
			for (int i = 0; i < N; i++) {
				for (int l = l2; l < min(M, l2 + bs); l++) {
					TYPE r = A[M * i + l];
					for (int j = j2; j < min(K, j2 + bs); j++) {
						C[K * i + j] += r * B[K * l + j];
					}
				}
			}
		}
	}

	_end = chrono::system_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(_end - _start).count();
}

