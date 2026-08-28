/*
 * LeetCode Problem 51: N-Queens
 *
 * Place N queens on an N×N chessboard so that no two queens attack each other.
 * Return all distinct board configurations (each configuration is a list of N strings).
 *
 * Examples
 *
 * Example 1
 *  - Input: N = 4
 *  - Output:
 *    [
 *      [ ".Q..",
 *        "...Q",
 *        "Q...",
 *        "..Q." ],
 *
 *      [ "..Q.",
 *        "Q...",
 *        "...Q",
 *        ".Q.." ]
 *    ]
 *    (Two distinct solutions for 4×4.)
 *
 * Example 2
 *  - Input: N = 1
 *  - Output:
 *    [
 *      [ "Q" ]
 *    ]
 * Overview explanation for all implementations:
 *  - All implementations solve N-Queens by exploring row-by-row placements with backtracking: choose a column for the current row,
 *    test for conflicts, recurse to the next row, and undo the placement on return. Pruning via conflict trackers (sets, arrays, or masks)
 *    dramatically reduces the search space compared to naive enumeration.
 *    
 * Implementations overview (what each does, differences, pros/cons)
 *
 * 1) SolveNQueens1_JaggedHash
 *    - What: Backtracking using a jagged `char[][]` board and three `HashSet<int>` trackers
 *      for columns, main-diagonals (row-col) and anti-diagonals (row+col).
 *    - Pros: Very readable; explicit board makes debugging and result construction trivial.
 *    - Cons: `HashSet` lookups are heavier than array/bit checks; internal board storage O(N^2).
 *
 * 2) SolveNQueens2_Array2D
 *    - What: Same backtracking strategy but using a `char[,]` 2D array for the board and `HashSet` trackers.
 *    - Pros: Slightly better memory locality than jagged arrays; still easy to follow.
 *    - Cons: Same `HashSet` overhead and O(N^2) board storage.
 *
 * 3) SolveNQueens3_BoolArr
 *    - What: Backtracking with `bool[]` arrays for columns and diagonals (index-mapped) instead of `HashSet`.
 *    - Pros: O(1) checks with very low overhead (array access); simpler than bitmasks while avoiding `HashSet` cost.
 *    - Cons: Needs diagonal index mapping; board storage may remain O(N^2) if kept.
 *
 * 4) SolveNQueens4_BitMask
 *    - What: Backtracking using integer bitmasks for columns, main-diagonals and anti-diagonals;
 *      board stored in `char[,]` for output.
 *    - Pros: Fastest conflict checks (bitwise ops), low per-check overhead, masks passed in recursion avoid separate unchoose steps.
 *    - Cons: Limited by integer width; for N near/exceeding the bit width switch to `long` or another representation.
 *
 * 5) SolveNQueens5_JaggedBM
 *    - What: Hybrid: jagged `char[][]` internal board + integer bitmasks for trackers.
 *    - Pros: Readable board plus fast mask checks.
 *    - Cons: Same bit-width caveat; jagged layout overhead vs compact arrays.
 *
 * 6) SolveNQueens6_Compact
 *    - What: Compact, mask-first implementation that minimizes allocations and builds solution rows on the fly.
 *    - Pros: Lowest memory overhead and typically fastest in practice for moderate-to-large N; minimal allocations.
 *    - Cons: More compact bit-index logic can be harder to debug; still bounded by integer/long width.
 *
 * Recommendation (which is best)
 *  - Best performance & memory: `SolveNQueens6_Compact` (compact bitmask variant). Use this for production or benchmarking.
 *  - Best clarity + good performance: `SolveNQueens4_BitMask` / `SolveNQueens5_JaggedBM`.
 *  - Best for teaching / readability: `SolveNQueens1_JaggedHash` or `SolveNQueens2_Array2D`.
 *
 * Practical notes
 *  - All methods perform exponential backtracking; pruning (via trackers) reduces the search space significantly.
 *  - Bitmask implementations assume enough bits in the chosen integer type. For N >= 32 use `long` (64-bit) or adapt the approach.
 *  - Several helper variants are included so individual `SolveNQueens*` methods can be copied into LeetCode submissions without external dependencies.
 *
 */

using System;
using System.Buffers;
using System.Collections.Generic;

namespace Project
{
    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("--- N-Queens - LeetCode 51 - Backtracking (C#) ---");

            Console.Write("Enter the size of the chessboard (N) (or press Enter to use default examples): ");
            string? input = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(input))
            {
                if (!int.TryParse(input, out int n))
                {
                    Console.WriteLine("Invalid input. Please enter a valid integer.");
                    return;
                }

                var output1 = SolveNQueens1_JaggedHash(n);
                PrintSolutions("1-JaggedHash", output1);

                var output2 = SolveNQueens2_Array2D(n);
                PrintSolutions("2-Array2D", output2);

                var output3 = SolveNQueens3_BoolArr(n);
                PrintSolutions("3-BoolArr", output3);

                var output4 = SolveNQueens4_BitMask(n);
                PrintSolutions("4-BitMask", output4);

                var output5 =  SolveNQueens5_JaggedBM(n);
                PrintSolutions("5-JaggedBM", output5);

                var output6 =  SolveNQueens6_Compact(n);
                PrintSolutions("6-Compact", output6);

                Console.WriteLine();

            }
            else
            {
                // Default examples
                var testCases = new List<int> { 1, 2, 3, 4, 5, 6 };
                foreach (int testCase in testCases)
                {
                    Console.WriteLine($"Size of the chessboard (N) = {testCase}:");

                    var output1 = SolveNQueens1_JaggedHash(testCase);
                    PrintSolutions("1-JaggedHash", output1);

                    var output2 = SolveNQueens2_Array2D (testCase);
                    PrintSolutions("2-Array2D", output2);

                    var output3 = SolveNQueens3_BoolArr(testCase);
                    PrintSolutions("3-BoolArr", output3);

                    var output4 = SolveNQueens4_BitMask(testCase);
                    PrintSolutions("4-BitMask", output4);

                    var output5 =  SolveNQueens5_JaggedBM(testCase);
                    PrintSolutions("5-JaggedBM", output5);

                    var output6 =  SolveNQueens6_Compact(testCase);
                    PrintSolutions("6-Compact", output6);

                    Console.WriteLine();
                }

                Console.WriteLine();
            }
        }

        // Helper method to print the solutions in a readable format
        private static void PrintSolutions(string prompt, IList<IList<string>> solutions)
        {
            Console.WriteLine($"  Solutions({prompt}):");
            foreach (var solution in solutions)
            {
                Console.WriteLine($"     [{string.Join(",", solution)}]");
            }
        }

        /*
         * SolveNQueens1_JaggedHash
         *
         * Approach: Backtracking (DFS) using an internal jagged char[][] board and three HashSet<int>
         *           trackers for columns, main-diagonals (row-col) and anti-diagonals (row+col).
         *
         * Time complexity: Exponential. Upper bound is approximated by O(N!) (searching permutations of
         *                  queen placements) but pruning via the trackers reduces the explored space.
         *
         * Space complexity: O(N^2) for the internal board + O(N) recursion stack. Output requires O(S * N)
         *                   where S is the number of solutions.
         *
         * Explanation: Place queens row-by-row. For each column check the three HashSets for conflicts.
         *              If safe, mark the trackers and the board, recurse to the next row, then undo.
         *
         * Edge cases / notes:
         *  - Returns an empty list for non-positive N.
         *  - Works for moderate N; performance degrades exponentially as N grows.
         *  
         * Helper: uses `createOutBoard(char[][])` to convert the jagged internal board into List<string>
         *         This helper fuuction is same as the one inside and used by SolveNQueens5_JaggedBM, 
         *         this is done because if the body of a SolveNQueens* methods is copied to be tested in the LeetCode platform, 
         *         all the functionality needed will be contained inside the SolveNQueen method in LeetCode. 
         */
        public static IList<IList<string>> SolveNQueens1_JaggedHash(int n)
        {
            List<IList<string>> solutions = new List<IList<string>>();

            // initialize jagged intern board with '.' (empty board)
            char[][] intBoard = new char[n][];
            for (int row = 0; row < n; row++)
            {
                intBoard[row] = new char[n];
                for (int col = 0; col < n; col++)
                {
                    intBoard[row][col] = '.';
                }
            }

            // HashSets to track columns, main-diagonals and anti-diagonals
            HashSet<int> cols = new HashSet<int>();
            HashSet<int> diags = new HashSet<int>();
            HashSet<int> antiDiags = new HashSet<int>();

            // Backtracking function to place queens row by row 
            void Backtrack(int row)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(createOutBoard(intBoard));
                    return;
                }

                // Try placing a queen in each column of the current row
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
            }
            ;

            // Helper to convert the jagged char array (internal board) into the requested List<string> format (out board)
            // This is a simple conversion from char[][] to List<string>
            List<string> createOutBoard(char[][] intBoard)
            {
                List<string> outBoard = new List<string>();
                for (int row = 0; row < n; row++)
                {
                    string curr_row = new string(intBoard[row]);
                    outBoard.Add(curr_row);
                }
                return outBoard;
            }
            ;

            Backtrack(0);

            return solutions.Cast<IList<string>>().ToList();
        }

        /*
         * SolveNQueens2_Array2D
         *
         * Approach: Backtracking using a 2D char[,] internal board with three HashSet<int> trackers
         *           for columns, main-diagonals and anti-diagonals. Uses a helper to convert the
         *           2D internal board into the requested List<string> output format.
         *
         * Time complexity: Exponential (upper bound similar to O(N!)); pruning reduces actual work.
         *
         * Space complexity: O(N^2) for the internal 2D board + O(N) recursion stack. Output is O(S * N).
         *
         * Explanation: Identical backtracking logic to other implementations but using a rectangular
         *              2D array for the internal board representation. Choose/Explore/Unchoose pattern
         *              with HashSet conflict checks.
         *
         * Edge cases / notes:
         *  - Behaves the same as the jagged-array variant (SolveNQueens1_JaggedHash) but uses contiguous 2D storage.
         *
         * Helper: uses `createOutBoard(char[,])` to convert the 2D internal board into List<string>.
         *         This helper fuuction is same as the one inside and used by SolveNQueens3_BoolArr and SolveNQueens4_BitMask, 
         *         this is done because if the body of a SolveNQueens* methods is copied to be tested in the LeetCode in the LeetCode platform, 
         *         all the functionality needed will be contained inside the SolveNQueen method in LeetCode. 
         */
        public static IList<IList<string>> SolveNQueens2_Array2D (int n)
        {
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

            // HashSets to track columns, main-diagonals and anti-diagonals
            HashSet<int> cols = new HashSet<int>();
            HashSet<int> diags = new HashSet<int>();
            HashSet<int> antiDiags = new HashSet<int>();

            // Backtracking function to place queens row by row
            void Backtrack(int row)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(createOutBoard(intBoard));
                    return;
                }

                // Try placing a queen in each column of the current row
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
            // This is a simple conversion from char[,] to List<string>
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

        /*
         * SolveNQueens3_BoolArr
         *
         * Approach: Backtracking using a 2D char[,] internal board and fixed-size boolean arrays
         *           for columns, main-diagonals and anti-diagonals (index-shifted to keep indices >= 0).
         *           This eliminates hash-table overhead in favor of O(1) boolean lookups.
         *
         * Time complexity: Exponential (upper bound similar to O(N!)), but faster in practice due to
         *                  lower constant factors on conflict checks.
         *
         * Space complexity: O(N^2) for the internal board + O(N) recursion stack + O(N) for the boolean trackers.
         *                   Output is O(S * N).
         *
         * Explanation: Use boolean arrays indexed by column and shifted-diagonal indices to check safety
         *              in O(1). Flip booleans on choose and reset them on backtrack.
         *
         * Edge cases / notes:
         *  - Diagonal arrays are sized 2*n-1 to cover the full index range for row-col and row+col.
         *
         * Helper: uses `createOutBoard(char[,])` to convert the 2D internal board into List<string>.
         *         This helper fuuction is same as the one inside and used by SolveNQueens3_BoolArr and SolveNQueens4_BitMask, 
         *         this is done because if the body of a SolveNQueens* methods is copied to be tested in the LeetCode in the LeetCode platform, 
         *         all the functionality needed will be contained inside the SolveNQueen method in LeetCode.
         */
        public static IList<IList<string>> SolveNQueens3_BoolArr(int n)
        {
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

            // Fixed-size boolean arrays act as director-lookup tables:
            // Track columns (size n)
            bool[] cols = new bool[n];
            // Track main diagonals (range of row-col is -(n-1) to (n-1), Total 2n-1)
            bool[] diags = new bool[2 * n - 1];
            // Track anti-diagonals (range row+com is 0 to 2*(n-1), Total 2n-1)
            bool[] antiDiags = new bool[2 * n - 1];

            // Backtracking function to place queens row by row
            void Backtrack(int row)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(createOutBoard(intBoard));
                    return;
                }

                // Try placing a queen in each column of the current row
                for (int col = 0; col < n; col++)
                {
                    // Shift negative diagonals indices by (n-1) to keep array indices positive
                    int diag = row - col + (n - 1);
                    int antiDiag = row + col;

                    // if the queen can be attacked
                    // Instant O(1) checks without causing math overhead
                    if (cols[col] ||
                        diags[diag] ||
                        antiDiags[antiDiag])
                    {
                        continue;
                    }

                    // Add the Queen to the board - Choose
                    // Flip booleans to true
                    cols[col] = true;
                    diags[diag] = true;
                    antiDiags[antiDiag] = true;
                    intBoard[row, col] = 'Q';

                    // Move on the next row to placed the next queen - Explore
                    Backtrack(row + 1);

                    // remove the queen from board - Unchoose
                    // Flip booleans to false
                    cols[col] = false;
                    diags[diag] = false;
                    antiDiags[antiDiag] = false;
                    intBoard[row, col] = '.';

                }
            }
            ;

            // Helper to convert the 2D char array (internal board) into the requested List<string> format (out board)
            // This is a simple conversion from char[,] to List<string>
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

        /*
         * SolveNQueens4_BitMask
         *
         * Approach: Backtracking with a 2D char[,] internal board and integer bitmasks for columns,
         *           main-diagonals and anti-diagonals. Uses bitwise operations to test and set conflicts
         *           in O(1) with minimal overhead.
         *
         * Time complexity: Exponential (upper bound comparable to O(N!)). Bitmasking reduces constant factors
         *                  and can significantly speed up conflict checks.
         *
         * Space complexity: O(N^2) for the internal board + O(N) recursion stack. Bitmask trackers use O(1)
         *                   auxiliary integer storage. Output is O(S * N).
         *
         * Explanation: Represent each column/diagonal occupancy as bits in an integer. Check conflicts via
         *              bitwise AND, and set/unset bits via OR (pass-by-value masks in recursion) to avoid
         *              separate unchoose steps for the masks.
         *
         * Edge cases / notes:
         *  - This implementation uses 32-bit integers for bitmasks; for large N (close to or exceeding
         *    the number of available bits) switch to wider integer types (e.g., long) or another approach.
         *
         * Helper: uses `createOutBoard(char[,])` to convert the 2D internal board into List<string>.
         *         This helper fuuction is same as the one inside and used by SolveNQueens3_BoolArr and SolveNQueens4_BitMask, 
         *         this is done because if the body of a SolveNQueens* methods is copied to be tested in the LeetCode in the LeetCode platform, 
         *         all the functionality needed will be contained inside the SolveNQueen method in LeetCode.
         */
        public static IList<IList<string>> SolveNQueens4_BitMask(int n)
        {
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

            // Backtracking function to place queens row by row
            void Backtrack(int row, int cols, int diags, int antiDiags)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(createOutBoard(intBoard));
                    return;
                }

                // Try placing a queen in each column of the current row
                for (int col = 0; col < n; col++)
                {

                    // if the queen can be attacked
                    // Instant O(1) checks without causing math overhead
                    if ((cols & (1 << col)) != 0 ||
                        (diags & (1 << (row - col + (n - 1)))) != 0 ||
                        (antiDiags & (1 << (row + col))) != 0)
                    {
                        continue;
                    }

                    // Add the Queen to the board - Choose
                    intBoard[row, col] = 'Q';

                    // Move on the next row to placed the next queen - Explore
                    Backtrack(row + 1,
                              (cols | (1 << col)),
                              (diags | (1 << (row - col + (n - 1)))),
                              (antiDiags | (1 << (row + col))));

                    // remove the queen from board - Unchoose
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

            Backtrack(0, 0, 0, 0);

            return solutions.Cast<IList<string>>().ToList();
        }

        /*
         * SolveNQueens5_JaggedBM
         * 
         * Approach: Backtracking using a jagged char[][] internal board and integer bitmasks for
         *           columns, main-diagonals and anti-diagonals (bitwise conflict tracking).
         *
         * Time complexity: Exponential, upper bound similar to O(N!), with bitmask pruning reducing constants.
         *
         * Space complexity: O(N^2) for the jagged internal board + O(N) recursion stack. Bitmask trackers
         *                   are constant-size integers. Output requires O(S * N).
         *
         * Explanation: Same bitmask strategy as other bitwise variants but stores the board as a jagged
         *              array. Use (cols | (1 << col)) style expressions to pass updated masks into recursion.
         *
         * Edge cases / notes:
         *  - Bitmask variants assume enough integer bits for the problem size; consider using wider types
         *    if N approaches the bit width limit.
         * - This solution is a hybrid of the jagged board and bitmasking, combining the best of both worlds.
         *   It is the same as SolveNQueens4_BitMask, but using a jagged board instead of a 2D array.
         *
         * Helper: uses `createOutBoard(char[][])` to convert the jagged internal board into List<string>
         *         This helper fuuction is same as the one inside and used by SolveNQueens1_JaggedBM, 
         *         this is done because if the body of a SolveNQueens* methods is copied to be tested in the LeetCode platform, 
         *         all the functionality needed will be contained inside the SolveNQueen method in LeetCode. 
         */
        public static IList<IList<string>>  SolveNQueens5_JaggedBM(int n)
        {
            List<IList<string>> solutions = new List<IList<string>>();

            // initialize jagged intern board with '.' (empty board)
            char[][] intBoard = new char[n][];
            for (int row = 0; row < n; row++)
            {
                intBoard[row] = new string('.', n).ToCharArray();
            }

            // Backtracking function to place queens row by row
            void Backtrack(int row, int cols, int diags, int antiDiags)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(createOutBoard(intBoard));
                    return;
                }

                // Try placing a queen in each column of the current row
                for (int col = 0; col < n; col++)
                {

                    // if the queen can be attacked
                    // Instant O(1) checks without causing math overhead
                    if ((cols & (1 << col)) != 0 ||
                        (diags & (1 << (row - col + (n - 1)))) != 0 ||
                        (antiDiags & (1 << (row + col))) != 0)
                    {
                        continue;
                    }

                    // Add the Queen to the board - Choose
                    intBoard[row][col] = 'Q';

                    // Move on the next row to placed the next queen - Explore
                    Backtrack(row + 1,
                              (cols | (1 << col)),
                              (diags | (1 << (row - col + (n - 1)))),
                              (antiDiags | (1 << (row + col))));

                    // remove the queen from board - Unchoose
                    intBoard[row][col] = '.';

                }
            }
            ;

            // Helper to convert the jagged char array (internal board) into the requested List<string> format (out board)
            // This is a simple conversion from char[][] to List<string>
            List<string> createOutBoard(char[][] intBoard)
            {
                List<string> outBoard = new List<string>();
                for (int row = 0; row < n; row++)
                {
                    outBoard.Add(new string(intBoard[row]));
                }
                return outBoard;
            }
            ;

            Backtrack(0, 0, 0, 0);

            return solutions.Cast<IList<string>>().ToList();
        }

        /*
         * SolveNQueens6_Compact
         *
         * Approach: High-performance backtracking using integer bitmasks for conflict tracking and a
         *           compact 1D integer `intBoard` that stores the queen column for each row.
         *           Memory overhead during backtracking is completely reduced to O(N) primitive integers.
         *           Uses allocation-friendly string construction (`String.Create`) when generating final rows.
         *
         * Time complexity: Exponential (upper bound comparable to O(N!)), with the smallest practical
         *                  constant factors among the provided variants due to compact state and bit ops.
         *
         * Space complexity: O(N) for the 1D `intBoard` + O(N) recursion stack. Bitmask trackers are O(1).
         *                   Output is O(S * N).
         *
         * Explanation: Store queen positions as integers in a 1D array (board[row]=col) to minimize
         *              memory churn. Use bitmasks to test/set conflicts and construct output strings
         *              efficiently once a full placement is found.
         *
         * Edge cases / notes:
         *  - As with other bitmask implementations, watch bit-width limits for large N and switch to
         *    larger integer types if required.
         *
         * Helper: uses `GenerateBoardStrings(int[])` to produce the List<string> solution representation.
         */
        public static IList<IList<string>>  SolveNQueens6_Compact(int n)
        {
            List<IList<string>> solutions = new List<IList<string>>();

            // Tracks the column index of the queen for each row.
            // board[row] = col
            int[] intBoard = new int[n];

            // Backtracking function to place queens row by row
            void Backtrack(int row, int cols, int diags, int antiDiags)
            {
                // Base case - A Solution (N Quens has been placed in the board)
                if (row == n)
                {
                    solutions.Add(GenerateBoardStrings(intBoard));
                    return;
                }

                // Try placing a queen in each column of the current row
                for (int col = 0; col < n; col++)
                {

                    // if the queen can be attacked
                    // Instant O(1) checks without causing math overhead
                    if ((cols & (1 << col)) != 0 ||
                        (diags & (1 << (row - col + (n - 1)))) != 0 ||
                        (antiDiags & (1 << (row + col))) != 0)
                    {
                        continue;
                    }

                    // Add the Queen to the board - Choose
                    // Record choice in the 1D primitive array (O(1) memory write)
                    intBoard[row] = col;

                    // Move on the next row to placed the next queen - Explore
                    Backtrack(row + 1,
                              (cols | (1 << col)),
                              (diags | (1 << (row - col + (n - 1)))),
                              (antiDiags | (1 << (row + col))));

                    // remove the queen from board - Unchoose
                    // "Unchoose" step is implicit. 
                    // The next loop iteration or higher stack frame will simply overwrite board[row].

                }
            }
            ;

            // Helper method optimized to construct strings cleanly using modern C# features
            // 
            // NOTE: Explanation of the snippet
            //        string rowString = string.Create(n, queenCol, (span, colIdx) => 
            //        {
            //           span.Fill('.');
            //           span[colIdx] = 'Q';
            //         });
            // 
            //   - `String.Create(int length, TState state, SpanAction<char, TState> action)`:
            //        - Allocates the resulting `string` of length `n`.
            //        - Calls the provided `action` exactly once with a `Span<char>` pointing into
            //          the newly allocated string's characters and the `state` (`queenCol` here).
            //        - Lets you initialize the characters in-place, avoiding a temporary `char[]`
            //          allocation and a separate copy into a string.
            //
            //   - In the lambda `(span, colIdx) => { ... }`:
            //        - `span` is a `Span<char>` representing the string's character buffer you can write to.
            //        - `colIdx` is the `queenCol` value passed as `state`.
            //        - `span.Fill('.')` sets every character to `'.'`.
            //        - `span[colIdx] = 'Q'` places the queen at column `colIdx`.
            //
            //   - Result: `rowString` is a string like `"....Q..."` (length `n`) with `'.'` everywhere except a `'Q'` at `queenCol`.
            //
            //   - Why "allocation-friendly": this builds the string's contents directly in the target memory,
            //     eliminating the intermediate `char[]` and extra copy that `new string(char[])` or
            //     `string.Concat` would cause. Suitable for high-performance scenarios.
            //
            //   Equivalent(but less allocation - efficient) code:
            //        char[] rowChars = new char[n];
            //        Array.Fill(rowChars, '.');
            //        rowChars[queenCol] = 'Q';
            //        string rowString = new string(rowChars);
            //     This approache allocates a temporary `char[]` and copy it into a string.
            //     The `String.Create` approach avoids that extra allocation and copy.
            IList<string> GenerateBoardStrings(int[] board)
            {
                var solution = new List<string>(n);
                for (int row = 0; row < n; row++)
                {
                    int queenCol = board[row];

                    // Allocation-friendly string generation using String.Create
                    string rowString = string.Create(n, queenCol, (span, colIdx) =>
                    {
                        span.Fill('.');
                        span[colIdx] = 'Q';
                    });

                    solution.Add(rowString);
                }
                return solution;
            }
            ;

            Backtrack(0, 0, 0, 0);

            return solutions;
        }

    }
    
}