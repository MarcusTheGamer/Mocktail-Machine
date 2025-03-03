using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace Mocktail_Arduino_WPF_Prototype
{
    public class Mocktail
    {
        public string Name { get; set; }
        public string? ImagePath { get; set; }
        public List<Outputs> Ingredients { get; set; } = new List<Outputs>();
        public List<int> Amounts { get; set; } = new List<int>();
    }
}