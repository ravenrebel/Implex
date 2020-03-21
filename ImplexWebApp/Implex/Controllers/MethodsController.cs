using Implex.Models;
using Microsoft.AspNetCore.Mvc;
using LinearAlgebraNumMethods;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;

namespace Implex.Controllers
{
    public class MethodsController : Controller
    {
        // GET: Methods/JacobiMethod
        public IActionResult JacobiMethod()
        {
            return View(new JacobiMethod());
        }

        //Post: Methods/JacobiMethod
        [HttpPost]
        public IActionResult JacobiMethod(JacobiMethod jacobiMethod)
        {
            JacobiMethodCPlusPlus jacobiMethodCPlusPlus = new JacobiMethodCPlusPlus();
            if (jacobiMethodCPlusPlus.Method(jacobiMethod.MatrixA, jacobiMethod.VectorB, jacobiMethod.VectorX, jacobiMethod.Eps))
                jacobiMethod.Result =  jacobiMethodCPlusPlus.getVectorX();
            return View(jacobiMethod);
        }
    }
}