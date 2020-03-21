using System.Collections.Generic;

namespace Implex.Models
{
    public class JacobiMethod:Method
    {
        public List<List<double>> MatrixA { get; set; }
        
        public List<double> VectorX { get; set; }
        
        public List<double> VectorB { get; set; }

        public double Eps { get; set; }

        public JacobiMethod()
        {
            Name = "Jacobi Method";
            Description = "In numerical linear algebra, the Jacobi method is an iterative algorithm for determining the solutions of a strictly diagonally dominant system of linear equations. Each diagonal element is solved for, and an approximate value is plugged in. The process is then iterated until it converges. This algorithm is a stripped-down version of the Jacobi transformation method of matrix diagonalization. The method is named after Carl Gustav Jacob Jacobi.";
            SourceCodePath = new List<string>();
        }
    }
}