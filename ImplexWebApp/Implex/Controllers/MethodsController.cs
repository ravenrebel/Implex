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

        public MethodsController(IHostingEnvironment environment, Options options)
        {
            _hostingEnvironment = environment;
            _options = options;
        }

        [HttpGet]
        public IActionResult FormJacobiMethod()
        {
            return View(new JacobiMethod());
        }

        [HttpGet]
        public IActionResult FileJacobiMethod()
        {
            return View(new JacobiMethod());
        }

        [HttpPost]
        public IActionResult FormJacobiMethod(JacobiMethod jacobiMethod)
        {
            if (jacobiMethod.VectorB != null && jacobiMethod.MatrixA != null && jacobiMethod.VectorX != null)
            {
                JacobiMethodCPlusPlus jacobiMethodCPlusPlus = new JacobiMethodCPlusPlus();
                if (jacobiMethodCPlusPlus.method(jacobiMethod.MatrixA, jacobiMethod.VectorB, jacobiMethod.VectorX, jacobiMethod.Eps))
                    jacobiMethod.Result = jacobiMethodCPlusPlus.getVectorX();
            }
            return View(jacobiMethod);
        }

        [HttpPost]
        [Route("result")]
        public async Task<FileResult> FileJacobiDownload(JacobiMethod jacobiMethod, IFormFileCollection inputFiles)
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

            return File(new FileStream(fileResult, FileMode.Open), "text/plain");
        }
    }
}