using Implex.Models;
using Microsoft.AspNetCore.Mvc;
using LinearAlgebraNumMethods;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Hosting;
using System.IO;
using System.Threading;

namespace Implex.Controllers
{
    public class MethodsController : Controller
    {
        private IHostingEnvironment _hostingEnvironment;
        private readonly Options _options;
        private JacobiMethod _jacobiMethodCPP;
        private MatrixMultiplication _multiplicationASM;

        public MethodsController(IHostingEnvironment environment, Options options)
        {
            _hostingEnvironment = environment;
            _options = options;

            _jacobiMethodCPP = new JacobiMethod();
            _jacobiMethodCPP.Implementation = "C++ is a high-level, general-purpose programming language created by Bjarne Stroustrup as an extension of the C programming language.";

            _multiplicationASM = new MatrixMultiplication();
            _multiplicationASM.Implementation = "In computer programming, assembly language(or assembler language), often abbreviated asm, is any low - level programming language in which there is a very strong correspondence between the instructions in the language and the architecture's machine code instructions.";
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
                JacobiMethodCPlusPlus jacobiMethodCPP = new JacobiMethodCPlusPlus();

                if (jacobiMethodCPP.method(jacobiMethod.MatrixA, jacobiMethod.VectorB, jacobiMethod.VectorX, jacobiMethod.Eps))
                    jacobiMethod.Result = jacobiMethodCPP.getVectorX();
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

            foreach (var file in inputFiles)
            {
                if (file != null)
                {
                    string files = Path.Combine(_hostingEnvironment.WebRootPath, "input_files");
                    string filePath = Path.Combine(files, id.ToString() + markers[i] + ".txt");

                    await using FileStream stream = System.IO.File.Create(filePath);
                    await file.CopyToAsync(stream);
                    stream.Close();
                }

                i++;
            }

            JacobiMethodCPlusPlus jacobiMethodCPlusPlus = new JacobiMethodCPlusPlus();
            if (jacobiMethodCPlusPlus.method(id, jacobiMethod.Eps))
            {
                fileResult += id.ToString() + ".txt";
            }
            else fileResult += "empty.txt";

            Stream newStream = new FileStream(fileResult, FileMode.Open);

            return File(newStream, "text/plain");
        }

        [HttpGet]
        public IActionResult FormMatrixMultiplicationAssembly()
        {
            return View(_multiplicationASM);
        }

        [HttpPost]
        public IActionResult FormMatrixMultiplicationAssembly(MatrixMultiplication matrixMultiplication)
        {
            return View(_multiplicationASM);
        }
    }
}