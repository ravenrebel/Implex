using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;

namespace Implex.Models
{
    public class Method
    {
        public string Name { get; set; }

        public string Description { get; set; }
        
        public object Result { get; set; }

        public List<string> SourceCodePath { get; set; }
    }
}
