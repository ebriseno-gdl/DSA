using System;
using System.Collections.Generic;

public class UnionFind
{
    private List<int> parent;
    private List<int> rank;
    private int count; // number of connected components

    public UnionFind(char[][] grid)
    {
        int m = grid.Length;
        int n = grid[0].Length;
        parent = new List<int>(m * n);
        rank = new List<int>(m * n);
        count = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    parent.Add(i * n + j);
                    count++;
                }
                else
                {
                    parent.Add(-1);
                }
                rank.Add(0);
            }
        }
    }

    public int Find(int i) // path compression
    {
        if (parent[i] != i)
        {
            parent[i] = Find(parent[i]);
        }
        return parent[i];
    }

    public void Union(int x, int y) // union with rank
    {
        int rootx = Find(x);
        int rooty = Find(y);
        if (rootx != rooty)
        {
            if (rank[rootx] > rank[rooty])
            {
                parent[rooty] = rootx;
            }
            else if (rank[rootx] < rank[rooty])
            {
                parent[rootx] = rooty;
            }
            else
            {
                parent[rooty] = rootx;
                rank[rootx] += 1;
            }
            count--;
        }
    }

    public int GetCount()
    {
        return count;
    }
}

public class Program
{

    static void Main(string[] args)
    {
        Console.Write("Enter the array of intervals (or press Enter to use default examples) (example of input: \'(2,5) (1,4) (9,10) (6,9)\' ): ");
        string? line = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(line))
        {
            // Split the input string into tokens based on spaces, removing any empty entries
            string[] tokens = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            //// Create a list to hold the parsed intervals
            //var intervals = new List<int[]>();
            //// Process each token to extract the start and end values of the intervals
            //foreach (string token in tokens)
            //{
            //    string trimmed = token.Trim('(', ')');
            //    string[] parts = trimmed.Split(',');
            //    if (parts.Length == 2 && int.TryParse(parts[0], out int start) && int.TryParse(parts[1], out int end))
            //    {
            //        intervals.Add(new int[] { start, end });
            //    }
            //    else
            //    {
            //        Console.WriteLine($"Invalid interval format: {token}");
            //        return;
            //    }
            //}
            //// Convert the list of intervals to a 2D array for easier processing
            //int[][] input = intervals.ToArray();

            //var output = MergeBrutForceWithSort(input);

            //PrintGrid("Output", output);

        }
        else
        {
            // Default example

            // Example 1:
            //char[][] input1 = new char[][]
            //{
            //    new char[] { "1","1","1","1","0" },
            //    new char[] { "1","1","0","1","0" },
            //    new char[] { "1","1","0","0","0" },
            //    new char[] { "0", "0", "0", "0", "0" }
            //};
            char[][] input1 = new char[][]
            {
                new char[] { '1','1','0','0' },
                new char[] { '1','0','0','1' },
                new char[] { '0','0','1','1' }
            };
            PrintGrid("Input 1", input1);
            var output1A = NumIslands(input1);
            Console.WriteLine("Number of Islands: " + output1A);
            
        }
    }
    public static int NumIslands(char[][] grid)
    {
        int nr = grid.Length;
        if (nr == 0) return 0;
        int nc = grid[0].Length;

        UnionFind uf = new UnionFind(grid);

        for (int r = 0; r < nr; ++r)
        {
            for (int c = 0; c < nc; ++c)
            {
                if (grid[r][c] == '1')
                {
                    grid[r][c] = '0';
                    if (r - 1 >= 0 && grid[r - 1][c] == '1') uf.Union(r * nc + c, (r - 1) * nc + c);
                    if (r + 1 < nr && grid[r + 1][c] == '1') uf.Union(r * nc + c, (r + 1) * nc + c);
                    if (c - 1 >= 0 && grid[r][c - 1] == '1') uf.Union(r * nc + c, r * nc + c - 1);
                    if (c + 1 < nc && grid[r][c + 1] == '1') uf.Union(r * nc + c, r * nc + c + 1);
                }
            }
        }

        return uf.GetCount();
    }

    private static void PrintGrid(string prompt, char[][] intervals)
    {
        Console.WriteLine(prompt + ": {");
        foreach (var interval in intervals)
        {
            Console.WriteLine($"( {string.Join(", ",interval)} )");
        }
        Console.WriteLine("}");
    }
}
