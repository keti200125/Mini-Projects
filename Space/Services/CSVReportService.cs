using Space.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space.Services
{
    public class CSVReportService
    {
        public void GenerateCSVReport(CosmicMap map, List<Position> path, string filePath= "shortest_path.csv")
        {
            string[,] shortestPathMap = map.GetShortestPathMap(path);

            using (var writer = new StreamWriter(filePath))
            {
                for (int i = 0; i < map.Rows; i++)
                {
                    for (int j = 0; j < map.Cols; j++)
                    {
                        writer.Write(shortestPathMap[i, j].PadRight(4));
                        if (j < map.Cols - 1)
                            writer.Write(' ');
                    }
                    writer.WriteLine();
                }
            }
            Console.WriteLine("CSV report generated successfully.");
        }
    }
}
