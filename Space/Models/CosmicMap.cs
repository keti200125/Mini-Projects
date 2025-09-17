using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace Space.Models
{
    public class CosmicMap
    {
        public int Rows { get; }
        public int Cols { get; }
        public char[,] Map { get; }

        public Position Start { get; private set; }
        public Position Finish { get; private set; }

        public CosmicMap(int rows, int cols, string[] lines)
        {
            Rows = rows;
            Cols = cols;
            Map = new char[rows, cols];

            for (int i = 0; i < rows; i++)
            {
                var symbols = lines[i].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                if (symbols.Length != cols)
                    throw new FormatException($"Row must contain {cols} elements.");

                for (int j = 0; j < cols; j++)
                {
                    char symbol = symbols[j][0];

                    if (symbol != 'S' && symbol != 'F' && symbol != 'O' && symbol != 'X')
                        throw new FormatException($"Invalid symbol '{symbol}'. " +
                            "Allowed symbols: S, F, O, X.");

                    Map[i, j] = symbol;

                    if (symbol == 'S')
                    {
                        if (Start != null)
                            throw new InvalidOperationException("Multiple starting positions.");
                        Start = new Position(i, j);
                    }
                    else if (symbol == 'F')
                    {
                        if (Finish != null)
                            throw new InvalidOperationException("Multiple finish positions.");
                        Finish = new Position(i, j);
                    }
                }
            }
            if (Start == null || Finish == null)
                throw new InvalidOperationException("Map must contain start and finish symbols.");
        }

        public void PrintMap()
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    Console.Write(Map[i, j] + " ");
                }
                Console.WriteLine();
            }
        }

        public List<Position> Neighbours(Position pos)
        {
            List<Position> neighbours = new List<Position>();

            if (pos.Row > 0 && Map[pos.Row - 1, pos.Col] != 'X')
                neighbours.Add(new Position(pos.Row - 1, pos.Col));

            if (pos.Row < Rows - 1 && Map[pos.Row + 1, pos.Col] != 'X')
                neighbours.Add(new Position(pos.Row + 1, pos.Col));

            if (pos.Col > 0 && Map[pos.Row, pos.Col - 1] != 'X')
                neighbours.Add(new Position(pos.Row, pos.Col - 1));

            if (pos.Col < Cols - 1 && Map[pos.Row, pos.Col + 1] != 'X')
                neighbours.Add(new Position(pos.Row, pos.Col + 1));

            return neighbours;
        }

        public string[,] GetShortestPathMap(List<Position> path)
        {
            string[,] displayMap = new string[Rows, Cols];

            for (int i = 0; i < Rows; i++)
                for (int j = 0; j < Cols; j++)
                    displayMap[i, j] = Map[i, j].ToString();

            for (int i = 0; i < path.Count; i++)
            {
                var pos = path[i];

                if (Map[pos.Row, pos.Col] == 'S')
                    continue;

                displayMap[pos.Row, pos.Col] = i.ToString();
            }
            return displayMap;
        }
    }
}

