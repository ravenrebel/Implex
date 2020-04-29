using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Implex.Models
{
    public class MatrixMultiplication:Method
    {
        public List<List<double>> MatrixA { get; set; }

        public List<List<double>> MatrixB { get; set; }

        public MatrixMultiplication()
        {
            Name = "Multiplication";
            Description = "In mathematics, matrix multiplication is a binary operation that produces a matrix from two matrices. For matrix multiplication, the number of columns in the first matrix must be equal to the number of rows in the second matrix. The result matrix, known as the matrix product, has the number of rows of the first and the number of columns of the second matrix.";
        }
    }
}
