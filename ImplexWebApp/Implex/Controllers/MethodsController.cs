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
                if (jacobiMethodCPlusPlus.Method(jacobiMethod.MatrixA, jacobiMethod.VectorB, jacobiMethod.VectorX, jacobiMethod.Eps))
                    jacobiMethod.Result = jacobiMethodCPlusPlus.getVectorX();
            }
            return View(jacobiMethod);
        }

        [HttpPost]
        public async Task<IActionResult> FileJacobiMethod(JacobiMethod jacobiMethod, [FromForm(Name = "matrix")]IFormFile matrix)
        {
            if (matrix != null)
            {
                int id = _options.FileId;
                lock(_options) _options.FileId++;

                string files = Path.Combine(_hostingEnvironment.WebRootPath, "files");
                string filePath = Path.Combine(files, id.ToString() + ".txt");

                await using FileStream stream = System.IO.File.Create(filePath);
                await matrix.CopyToAsync(stream);

                JacobiMethodCPlusPlus jacobiMethodCPlusPlus = new JacobiMethodCPlusPlus();
                if (jacobiMethodCPlusPlus.Method(id)) { }
                   // jacobiMethod.Result = jacobiMethodCPlusPlus.getVectorX();
                
            }
            return View(new JacobiMethod());
        }
    }
}