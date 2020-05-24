using Implex.Models;
using Microsoft.AspNetCore.Mvc;
using LinearAlgebraNumMethods;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Hosting;
using System.IO;
using System;

namespace Implex.Controllers
{
    public class MethodsController : Controller
    {
        private IHostingEnvironment _hostingEnvironment;
        private readonly Options _options;
        private JacobiMethod _jacobiMethodCPP;
        private Models.MatrixMultiplication _multiplicationCPP;

        public MethodsController(IHostingEnvironment environment, Options options)
        {
            _hostingEnvironment = environment;
            _options = options;

            _jacobiMethodCPP = new JacobiMethod();
            _jacobiMethodCPP.Implementation = "C++ is a high-level, general-purpose programming language created by Bjarne Stroustrup as an extension of the C programming language.";

            _multiplicationCPP = new Models.MatrixMultiplication();
            _multiplicationCPP.Implementation = "This method was written on C++ which is a high - level, general - purpose programming language. The first optimization is to re-order the loops to enforce local access in all of the matrices. The standard mapping was then used from a two-dimensional array onto a one-dimensional space. This makes explicit the fact that subscripting in a two-dimensional array requires integer multiplication as well as addition. Replacing subscripting with explicit pointer access allows the elimination of these multiplications.";
        }

        [HttpGet]
        public IActionResult FormJacobiMethod()
        {
            return View(_jacobiMethodCPP);
        }

        [HttpGet]
        public IActionResult FileJacobiMethod()
        {
            return View(_jacobiMethodCPP);
        }

        [HttpPost]
        public IActionResult FormJacobiMethod(JacobiMethod jacobiMethod)
        {
            if (jacobiMethod.VectorB != null && jacobiMethod.MatrixA != null && jacobiMethod.VectorX != null)
            {
                try
                {
                    JacobiMethodCPlusPlus jacobiMethodCPP = new JacobiMethodCPlusPlus();

                    if (jacobiMethodCPP.method(jacobiMethod.MatrixA, jacobiMethod.VectorB, jacobiMethod.VectorX, jacobiMethod.Eps))
                        _jacobiMethodCPP.Result = jacobiMethodCPP.getVectorX();
                    else _jacobiMethodCPP.Result = "It is not strictly diagonally dominant system of linear equations.";
                }
                catch (Exception) { }
            }
            return View(_jacobiMethodCPP);
        }

        [HttpPost]
        public async Task<IActionResult> FileJacobiDownload(JacobiMethod jacobiMethod, IFormFileCollection inputFiles)
        {
            uint id = _options.FileId;
            lock (_options) _options.FileId++;

            List<string> markers = new List<string> { "A", "b", "x"};
            int i = 0;

            string fileResult = _hostingEnvironment.WebRootPath + "\\output_files\\";
            string files = Path.Combine(_hostingEnvironment.WebRootPath, "input_files");

            foreach (var file in inputFiles)
            {
                if (file != null)
                {
                    string filePath = Path.Combine(files, id.ToString() + markers[i] + ".txt");

                    await using FileStream stream = System.IO.File.Create(filePath);
                    await file.CopyToAsync(stream);
                    stream.Close();
                }

                i++;
            }

            try
            {
                JacobiMethodCPlusPlus jacobiMethodCPlusPlus = new JacobiMethodCPlusPlus();
                if (jacobiMethodCPlusPlus.method(id, jacobiMethod.Eps))
                {
                    fileResult += id.ToString() + ".txt";
                }
                else fileResult += "empty.txt";
            }
            catch (Exception) { }

            Stream newStream = new FileStream(fileResult, FileMode.Open);

            return File(newStream, "text/plain");
        }

        [HttpGet]
        public IActionResult FormMatrixMultiplication()
        {
            return View(_multiplicationCPP);
        }

        [HttpPost]
        public IActionResult FormMatrixMultiplication(Models.MatrixMultiplication matrixMultiplication)
        {
            if (matrixMultiplication.MatrixA != null && matrixMultiplication.MatrixB != null)
            {
                try
                {
                    LinearAlgebraNumMethods.MatrixMultiplication multiplication = new LinearAlgebraNumMethods.MatrixMultiplication();
                    _multiplicationCPP.Result = multiplication.multiply(matrixMultiplication.MatrixA, matrixMultiplication.MatrixB);
                }
                catch (Exception) { }
            }
            return View(_multiplicationCPP);
        }

        [HttpGet]
        public IActionResult FileMatrixMultiplication()
        {
            return View(_multiplicationCPP);
        }

        [HttpPost]
        public async Task<IActionResult> FileMatrixMultiplicationDownload(Models.MatrixMultiplication matrixMultiplication, IFormFileCollection inputFiles)
        {
            uint id = _options.FileId;
            lock (_options) _options.FileId++;

            List<string> markers = new List<string> { "A", "B"};
            int i = 0;

            string fileResult = _hostingEnvironment.WebRootPath + "\\output_files\\";
            string files = Path.Combine(_hostingEnvironment.WebRootPath, "input_files");

            foreach (var file in inputFiles) // refactor pls
            {
                if (file != null)
                {
                    string filePath = Path.Combine(files, id.ToString() + markers[i] + ".txt");

                    await using FileStream stream = System.IO.File.Create(filePath);
                    await file.CopyToAsync(stream);
                    stream.Close();
                }

                i++;
            }

            try
            {
                LinearAlgebraNumMethods.MatrixMultiplication multiplication = new LinearAlgebraNumMethods.MatrixMultiplication();
                if (multiplication.multiply(id))
                {
                    fileResult += id.ToString() + ".txt";
                }
                else fileResult += "empty.txt";
            }
            catch(Exception) { }

            Stream newStream = new FileStream(fileResult, FileMode.Open);

            return File(newStream, "text/plain");
        }
    }
}