using System;
using System.Collections.Generic;

namespace Project
{
    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("--- N-Queens - LeetCode 51 - Backtracking (C#) ---");

            Console.Write("Enter the size of the chessboard (N): ");
            string input = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(input))
            {
                if (!int.TryParse(input, out int n))
                {
                    Console.WriteLine("Invalid input. Please enter a valid integer.");
                    return;
                }

                var output1 = SolveNQueens1(n);
                PrintSolutions("1", output1);

                var output2 = SolveNQueens2(n);
                PrintSolutions("2", output2);

                Console.WriteLine();

            }
            else
            {
                // Default examples
                var testCases = new List<int> { 4, 5, 6 };
                foreach (int testCase in testCases)
                {
                    Console.WriteLine($"Size of the chessboard (N) = {testCase}:");
                                        
                    var output1 = SolveNQueens1(testCase);
                    PrintSolutions("1", output1);

                    var output2 = SolveNQueens2(testCase);
                    PrintSolutions("2", output2);

                    Console.WriteLine();
                }

                Console.WriteLine();
            }
        }

        private static void PrintSolutions(string prompt, IList<IList<string>> solutions)
        {
            Console.WriteLine($"Solutions({prompt}):");
            foreach (var solution in solutions)
            {
                Console.WriteLine($"   [{string.Join(",", solution)}]");
            }
        }

        public static IList<IList<string>> SolveNQueens1(int n)
        {
            List<IList<string>> solutions = new List<IList<string>>();

            char[][] intBoard = new char[n][];
            for (int row = 0; row < n; row++)
            {
                intBoard[row] = new char[n];
                for (int col = 0; col < n; col++)
                {
                    intBoard[row][col] = '.';
                }
            }

            HashSet<int> cols = new HashSet<int>();
            HashSet<int> diags = new HashSet<int>();
            HashSet<int> antiDiags = new HashSet<int>();

            void Backtrack(int row)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(createOutBoard(intBoard));
                    return;
                }

                for (int col = 0; col < n; col++)
                {
                    int diag = row - col;
                    int antiDiag = row + col;

                    // if the queen can be attacked
                    if (cols.Contains(col) ||
                         diags.Contains(diag) ||
                         antiDiags.Contains(antiDiag))
                    {
                        continue;
                    }

                    // Add the Queen to the board - Choose
                    cols.Add(col);
                    diags.Add(diag);
                    antiDiags.Add(antiDiag);
                    intBoard[row][col] = 'Q';

                    // Move on the next row to placed the next queen - Explore
                    Backtrack(row + 1);

                    // remove the queen from board - Unchoose
                    cols.Remove(col);
                    diags.Remove(diag);
                    antiDiags.Remove(antiDiag);
                    intBoard[row][col] = '.';

                }
            };

            List<string> createOutBoard(char[][] intBoard)
            {
                List<string> outBoard = new List<string>();
                for (int row = 0; row < n; row++)
                {
                    string curr_row = new string(intBoard[row]);
                    outBoard.Add(curr_row);
                }
                return outBoard;
            };

            Backtrack(0);

            return solutions.Cast<IList<string>>().ToList();
        }

        public static IList<IList<string>> SolveNQueens2(int n)
        {
            // Solution where there is an internal board, same than previous one,
            // but now it is a 2D array, continue needing of createOutBoard helper function
            // to convert from the 2D char array (internal board) into the requested List<string> format (out board)


            List<IList<string>> solutions = new List<IList<string>>();

            // initialize 2D intern board with '.' (empty board)
            char[,] intBoard = new char[n, n];
            for (int row = 0; row < n; row++)
            {
                for (int col = 0; col < n; col++)
                {
                    intBoard[row, col] = '.';
                }
            }

            HashSet<int> cols = new HashSet<int>();
            HashSet<int> diags = new HashSet<int>();
            HashSet<int> antiDiags = new HashSet<int>();

            void Backtrack(int row)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(createOutBoard(intBoard));
                    return;
                }

                for (int col = 0; col < n; col++)
                {
                    int diag = row - col;
                    int antiDiag = row + col;

                    // if the queen can be attacked
                    if (cols.Contains(col) ||
                         diags.Contains(diag) ||
                         antiDiags.Contains(antiDiag))
                    {
                        continue;
                    }

                    // Add the Queen to the board - Choose
                    cols.Add(col);
                    diags.Add(diag);
                    antiDiags.Add(antiDiag);
                    intBoard[row, col] = 'Q';

                    // Move on the next row to placed the next queen - Explore
                    Backtrack(row + 1);

                    // remove the queen from board - Unchoose
                    cols.Remove(col);
                    diags.Remove(diag);
                    antiDiags.Remove(antiDiag);
                    intBoard[row, col] = '.';

                }
            }
            ;

            // Helper to convert the 2D char array (internal board) into the requested List<string> format (out board)
            List<string> createOutBoard(char[,] intBoard)
            {
                List<string> outBoard = new List<string>();
                for (int row = 0; row < n; row++)
                {
                    char[] rowChars = new char[n];
                    for (int col = 0; col < n; col++)
                    {
                        rowChars[col] = intBoard[row, col];
                    }
                    outBoard.Add(new string(rowChars));
                }
                return outBoard;
            }
            ;

            Backtrack(0);

            return solutions.Cast<IList<string>>().ToList();

        }
    }
}