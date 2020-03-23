using System;
using System.Collections.Generic;

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
