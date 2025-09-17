using Space.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space.Services
{
    public class MapGeneratorService
    {
        private static Random random = new Random();

        public CosmicMap Generate(int rows, int cols, int numberOfAsteroids)
        {
            if (numberOfAsteroids >= rows * cols -1)
                throw new ArgumentException("Too many asteroids.");

            char[,] map = new char[rows, cols];

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    map[i, j] = 'O';

            Position start = RandomEmptyPosition(map, rows, cols);
            map[start.Row, start.Col] = 'S';

            Position finish;
            do
            {
                finish = RandomEmptyPosition(map, rows, cols);
            } while (finish.Row == start.Row && finish.Col == start.Col);
            map[finish.Row, finish.Col] = 'F';

            int placedAsteroids = 0;
            while (placedAsteroids < numberOfAsteroids)
            {
                Position pos = RandomEmptyPosition(map, rows, cols);
                if (map[pos.Row, pos.Col] == 'O')
                {
                    map[pos.Row, pos.Col] = 'X';
                    placedAsteroids++;
                }
            }

            string[] lines = new string[rows];
            for (int i = 0; i < rows; i++)
            {
                string line = "";
                for (int j = 0; j < cols; j++)
                {
                    line += map[i, j] + " ";
                }
                lines[i] = line.Trim();
            }
            return new CosmicMap(rows, cols, lines);
        }

        private Position RandomEmptyPosition(char[,] map, int rows, int cols)
        {
            int r, c;
            do
            {
                r = random.Next(rows);
                c = random.Next(cols);
            } while (map[r, c] != 'O');
            return new Position(r, c);
        }

    }
}
