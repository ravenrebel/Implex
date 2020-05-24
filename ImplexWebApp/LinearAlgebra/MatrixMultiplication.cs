
using System.Diagnostics;
using System.Threading.Tasks;
using MathNet.Numerics.LinearAlgebra;


namespace LinearAlgebra
{
    public static class MatrixMultiplication
    {
        private static object _locker = new object();
        private static Stopwatch _watch = new Stopwatch();

        public static long Time { get; set; }

        public static int BlockSize { get; set; }

        public static double[,] NaiveMultiply(double[,] matrixA, double[,] matrixB)
        {
            if (CanMultiply(matrixA, matrixB))
            {
                _watch.Restart();
                long K = matrixB.GetLongLength(1);
                long N = matrixA.GetLongLength(0);
                long M = matrixB.GetLongLength(1);
                double[,] matrixC = new double[N, M];

                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < M; j++)
                    {
                        for (int k = 0; k < K; k++)
                        {
                            matrixC[i, j] += matrixA[i, k] * matrixB[k, j];
                        }
                    }
                }
                _watch.Stop();
                Time = _watch.ElapsedMilliseconds;
                return matrixC;
            }
            return null;
        }

        public static double[,] ParallelMultiply(double[,] matrixA, double[,] matrixB)
        {
            if (CanMultiply(matrixA, matrixB))
            {
                _watch.Restart();
                long K = matrixB.GetLongLength(1);
                long N = matrixA.GetLongLength(0);
                long M = matrixB.GetLongLength(1);
                double[,] matrixC = new double[N, M];

                Parallel.For(0, N,
                    (i) =>
                    {
                        for (int j = 0; j < M; j++)
                        {
                            for (int k = 0; k < K; k++)
                            {
                                matrixC[i, j] += matrixA[i, k] * matrixB[k, j];
                            }
                        }
                    });

                _watch.Stop();
                Time = _watch.ElapsedMilliseconds;
                return matrixC;
            }
            return null;
        }

        public static double[,] BlockMultiply(double[,] matrixA, double[,] matrixB)
        {
            if (CanMultiply(matrixA, matrixB))
            {
                _watch.Restart();
                long K = matrixB.GetLongLength(1);
                long N = matrixA.GetLongLength(0);
                long M = matrixB.GetLongLength(1);
                double[,] matrixC = new double[N, M];

                int bs = BlockSize;
                for (int jj = 0; jj < N; jj += bs)
                {
                    for (int kk = 0; kk < N; kk += bs)
                    {
                        for (int i = 0; i < N; i++)
                        {
                            for (int j = jj; j < ((jj + bs) > N ? N : (jj + bs)); j++)
                            {
                                for (int k = kk; k < ((kk + bs) > N ? N : (kk + bs)); k++)
                                {
                                    matrixC[i, j] += matrixA[i, k] * matrixB[k, j];
                                }
                            }
                        }
                    }
                }

                _watch.Stop();
                Time = _watch.ElapsedMilliseconds;
                return matrixC;
            }
            return null;
        }

        public static double[,] MathNetMultiply(double[,] matrixA, double[,] matrixB)
        {
            if (CanMultiply(matrixA, matrixB))
            {
                _watch.Restart();
                Matrix<double> A = Matrix<double>.Build.DenseOfArray(matrixA);
                Matrix<double> B = Matrix<double>.Build.DenseOfArray(matrixB);
                double[,] C = A.Multiply(B).ToArray();
                _watch.Stop();
                Time = _watch.ElapsedMilliseconds;
                return C;
            }
            return null;
        }

        private static bool CanMultiply(double[,] matrixA, double[,] matrixB)
        {
            if (matrixA == null || matrixB == null) return false;
            if (matrixA.GetLongLength(0) != matrixB.GetLongLength(1)) return false;
            return true;
        }

        public static bool Compare(double[,] matrixA, double[,] matrixB)
        {
            long K = matrixB.GetLongLength(1);

            for (int j = 0; j < K; j++)
            {
                for (int k = 0; k < K; k++)
                {
                    if (matrixA[j, k] != matrixB[j, k]) return false;
                }
            }
            return true;
        }
    }
}
