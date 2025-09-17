using Space.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Space.Services
{
    public class PathService
    {
        public List<Position> BFS(CosmicMap map)
        {
            Queue<Position> q = new Queue<Position>();
            bool[,] visited = new bool[map.Rows, map.Cols];
            Position[,] prev = new Position[map.Rows, map.Cols];

            q.Enqueue(map.Start);
            visited[map.Start.Row, map.Start.Col] = true;

            while(q.Count > 0)
            {
                var curr = q.Dequeue();
                if (curr.Row == map.Finish.Row && curr.Col == map.Finish.Col)
                    break;

                foreach (var neighbor in map.Neighbours(curr))
                {
                    if (!visited[neighbor.Row, neighbor.Col])
                    {
                        visited[neighbor.Row, neighbor.Col] = true;
                        prev[neighbor.Row, neighbor.Col] = curr;
                        q.Enqueue(neighbor);
                    }
                }
            }

            if (!visited[map.Finish.Row, map.Finish.Col])
                return new List<Position>();

            List<Position> path = new List<Position>();
            Position step = map.Finish;

            while (step != null && step != map.Start)
            {
                path.Add(step);
                step = prev[step.Row, step.Col];
            }
            path.Add(map.Start);
            path.Reverse();
            return path;
        }

        public int CountAllPaths(CosmicMap map)
        {
            bool[,] visited = new bool[map.Rows,map.Cols];
            int count = DFS(map, visited, map.Start);

            return count;
        }

        private int DFS(CosmicMap map, bool[,] visited, Position curr)
        {
            if (curr.Col == map.Finish.Col && curr.Row == map.Finish.Row)
                return 1;

            visited[curr.Row, curr.Col] = true;
            int count = 0;

            foreach (var neighbor in map.Neighbours(curr))
            {
                if (!visited[neighbor.Row, neighbor.Col])
                    count += DFS(map,visited, neighbor);
            }
            visited[curr.Row, curr.Col] = false;

            return count;
        }
    }
}

