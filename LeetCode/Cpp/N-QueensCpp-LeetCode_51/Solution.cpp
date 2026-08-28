#include "Solution.h"

#include <vector>
#include <string>
#include <functional>
#include <unordered_set>

using namespace std;

/*
 * solveNQueens1
 *
 * Approach: Row-by-row backtracking using an explicit `vector<vector<char>>` internal board
 * and three `unordered_set<int>` trackers for columns, main-diagonals (row-col) and anti-diagonals (row+col).
 *
 * Time complexity: Exponential (upper bound comparable to O(N!)); pruning via trackers reduces the explored space.
 * Space complexity: O(N^2) for the internal board + O(N) recursion depth + O(N) average set storage.
 *
 * Pros:
 *  - Very readable; explicit board makes debugging and result construction trivial.
 * Cons:
 *  - `unordered_set` lookups and management have higher constant overhead than arrays/bitmasks.
 *
 * Notes:
 *  - Uses an internal `createboard()` helper to convert `vector<vector<char>>` into `vector<string>` for output.
 *  - Good as a pedagogy / reference implementation.
 */
vector<vector<string>> Solution::SolveNQueens1_JaggedHash(int n)
{
	vector<vector<string>> solutions;
        
    unordered_set<int> cols;
    unordered_set<int> diagonals;
    unordered_set<int> antiDiagonals;
    
	// Initialize the intern board as a 2D vector of chars, filled with '.'
    vector<vector<char>> intBoard(n, vector<char>(n, '.'));

	// Helper function to convert the internal board representation into a vector of strings for output
	auto createboard = [&]() -> vector<string>
	{
		vector<string> outBoard;
		for (int row = 0; row < n; row++)
		{
			string curr_row(intBoard[row].begin(), intBoard[row].end());
			outBoard.push_back(curr_row);
		}
		return outBoard;
	};
    
	// Backtracking function to place queens row by row
    function<void(int)> backtrack = [&](int row)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if ( row == n)
        {
            solutions.push_back(createboard());
            return;
        }
        
		// Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++)
        {
            int currDiagonal = row - col;
            int currAntiDiagonal = row + col;
                
            // if the queen can be attacked
            if (cols.count(col) || 
                diagonals.count(currDiagonal) || 
                antiDiagonals.count(currAntiDiagonal))
            {
                continue;
            }
                
            // Add the Queen to the board - Choose
            cols.insert(col);
            diagonals.insert(currDiagonal);
            antiDiagonals.insert(currAntiDiagonal);
            intBoard[row][col] = 'Q';
                
            // Move on the next row to placed the next queen con the updated board - Explore
            backtrack(row+1);
                
            // remove the queen from board - Unchoose
            cols.erase(col);
            diagonals.erase(currDiagonal);
            antiDiagonals.erase(currAntiDiagonal);
            intBoard[row][col] = '.';
                           
        }
    };
        
    backtrack(0);
    return solutions;
};

/*
 * solveNQueens2
 *
 * Approach: Backtracking while maintaining the board directly as `vector<string>` and using
 * `unordered_set<int>` trackers for columns and diagonals.
 *
 * Time complexity: Exponential (pruned by trackers).
 * Space complexity: O(N^2) for board strings + O(N) recursion depth + O(N) set storage.
 *
 * Pros:
 *  - Avoids conversion/clone overhead by storing rows as `string` directly; simpler result push.
 * Cons:
 *  - `unordered_set` overhead remains; board still uses O(N^2) memory.
 *
 * Notes:
 *  - Preferred over the jagged-char variant when clarity and slightly lower allocation cost are desired.
 */
vector<vector<string>> Solution::solveNQueens2_StringBoard_Hash(int n)
{
    vector<vector<string>> solutions;

    unordered_set<int> cols;
    unordered_set<int> diagonals;
    unordered_set<int> antiDiagonals;

	// Initialize the internal Board as a vector of strings, each string representing a row filled with '.' 
    vector<string> intBoard(n, string(n, '.'));

	// Backtracking function to place queens row by row
    function<void(int)> backtrack = [&](int row)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if (row == n)
        {
            solutions.push_back(intBoard);  // Zero conversion cost: Direct push back
            return;
        }

		// Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++)
        {
            int currDiagonal = row - col;
            int currAntiDiagonal = row + col;

            // if the queen can be attacked
            if (cols.count(col) || 
                diagonals.count(currDiagonal) || 
                antiDiagonals.count(currAntiDiagonal))
            {
                continue;
            }

            // Add the Queen to the board - Choose
            cols.insert(col);
            diagonals.insert(currDiagonal);
            antiDiagonals.insert(currAntiDiagonal);
            intBoard[row][col] = 'Q';

            // Move on the next row to placed the next queen con the updated board - Explore
            backtrack(row + 1);

            // remove the queen from board - Unchoose
            cols.erase(col);
            diagonals.erase(currDiagonal);
            antiDiagonals.erase(currAntiDiagonal);
            intBoard[row][col] = '.';

        }
    };

    backtrack(0);
    return solutions;

};

/*
 * solveNQueens3
 *
 * Approach: Backtracking using `vector<bool>` arrays for `cols`, `diagonals`, and `antiDiagonals`
 * to achieve O(1) occupancy checks, with the board stored as `vector<string>`.
 *
 * Time complexity: Exponential with much-reduced constant factors thanks to O(1) boolean checks.
 * Space complexity: O(N^2) for the board + O(N) recursion stack + O(N) boolean arrays (2n-1 for diagonals).
 *
 * Pros:
 *  - Very fast constant-time checks without hash overhead; straightforward index mapping.
 * Cons:
 *  - Needs diagonal index shifting (row-col + offset).
 *
 * Notes:
 *  - Use this variant when hash-table overhead is a bottleneck but bitmasking is undesired.
 */
vector<vector<string>> Solution::solveNQueens3_BoolArr(int n)
{
    vector<vector<string>> solutions;

    // Fixed-size boolean vectors act as director-lookup tables
    // Track columns (size n)
    vector<bool> cols(n, false);
    // Track main diagonals (range of row-col is -(n-1) to (n-1), Total 2n-1)
    vector<bool> diagonals(2 * n - 1, false);
    // Track anti-diagonals (range of row+col is 0 to 2*(n-1), Total 2n-1)
    vector<bool> antiDiagonals(2 * n - 1, false);

    // Initialize the internal Board as a vector of strings, each string representing a row filled with '.' 
    vector<string> intBoard(n, string(n, '.'));

    //  
    function<void(int)> backtrack = [&](int row)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if (row == n)
        {
            solutions.push_back(intBoard);  // Zero conversion cost: Direct push back
            return;
        }

        for (int col = 0; col < n; col++)
        {
            // Sniff negative diagonal indices by (n - 1) to keep array indices positive
            int currDiagIdx = row - col + (n - 1);
            int currAntiDiagIdx = row + col;

            // if the queen can be attacked
            // Instant O(1) checks without casting math overhead
            if (cols[col] ||
                diagonals[currDiagIdx] ||
                antiDiagonals[currAntiDiagIdx])
            {
                continue;
            }

            // Add the Queen to the board - Choose
            // Flip booleans to true
            cols[col] = true;
            diagonals[currDiagIdx] = true;
            antiDiagonals[currAntiDiagIdx] = true;
            intBoard[row][col] = 'Q';

            // Move on the next row to placed the next queen con the updated board - Explore
            backtrack(row + 1);

            // remove the queen from board - Unchoose
            // Flip booleans to false
            cols[col] = false;
            diagonals[currDiagIdx] = false;
            antiDiagonals[currAntiDiagIdx] = false;
            intBoard[row][col] = '.';

        }
    };

    backtrack(0);
    return solutions;

};

/*
 * solveNQueens4
 *
 * Approach: Backtracking using integer bitmasks for `cols`, main-diagonals and anti-diagonals;
 * board stored as `vector<string>` for result generation. Masks are passed by value in recursion.
 *
 * Time complexity: Exponential; bitmask checks use low-overhead bitwise operations giving excellent performance.
 * Space complexity: O(N^2) for board (output) + O(N) recursion depth; bitmasks use O(1) auxiliary space.
 *
 * Pros:
 *  - Fastest conflict checks (bitwise ops), minimal per-check overhead. Masks passed by value avoid separate unchoose.
 * Cons:
 *  - Limited by integer width (use wider types for N near/above bit width).
 *
 * Notes:
 *  - For N >= 32 (or platform-dependent bit width) switch to `long long` or another representation.
 */
vector<vector<string>> Solution::solveNQueens4_BitMask(int n)
{
    vector<vector<string>> solutions;

    // Initialize the internal Board as a vector of strings, each string representing a row filled with '.' 
    vector<string> intBoard(n, string(n, '.'));

    // Using integers as bitmasks. Passed by value because ints fit entirely in CPU registers.
    function<void(int, int, int, int)> backtrack = [&](int row, int cols, int diags, int antiDiags)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if (row == n)
        {
            solutions.push_back(intBoard);  // Zero conversion cost: Direct push back
            return;
        }

		// Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++)
        {

            // if the queen can be attacked
            // Instant O(1) checks without casting math overhead
            // Check if the col~th bit is set im any of our masks
            // (1 << col) create a mask with a 1 at the specific colummn position.
            if ((cols & (1 << col)) ||
                (diags & (1 << (row - col + n - 1))) ||
                (antiDiags & (1 << (row + col))))
            {
                continue;
            }

            // Add the Queen to the board - Choose
            intBoard[row][col] = 'Q';

            // Move on the next row to placed the next queen con the updated board - Explore
            // Update bitmasks using the bitwise OR (|) operator.
            backtrack(row + 1,
                (cols | (1 << col)),
                (diags | (1 << (row - col + n - 1))),
                (antiDiags | (1 << (row + col))));

            // remove the queen from board - Unchoose.
            // Bitmasks revert automatically becuuse they were passed by value.
            intBoard[row][col] = '.';

        }
    };

    // 0 means all calumns/diagonals/antidiagonals are completely free.
    backtrack(0, 0, 0, 0);
    return solutions;
};

/*
 * solveNQueens5
 *
 * Approach: Hybrid: integer bitmasks for occupancy tracking and a 1D `vector<int>` board where
 * `board[row] = col` stores queen column indices; `GenerateBoardStrings()` builds the output.
 *
 * Time complexity: Exponential; low constant factors due to bitmasks.
 * Space complexity: O(N^2) for generated output + O(N) for the 1D board + O(1) bitmask storage.
 *
 * Pros:
 *  - Minimal runtime memory for intermediate board state; fast mask checks and cheap final board generation.
 * Cons:
 *  - Same bit-width caveat as other mask-based solutions; slightly less direct board visualization during debugging.
 *
 * Notes:
 *  - Good compromise between minimal working memory and speed; `GenerateBoardStrings()` converts the compact
 *    representation into `vector<string>` for the caller.
 */
vector<vector<string>> Solution::solveNQueens5_IndexBoard_BitMask(int n)
{
    vector<vector<string>> solutions;

    // Tracks the column index of the queen for each row.
    // intBoard[row] = col    
    vector<int> intBoard(n);

	// Helper function to convert the 1D board representation into a vector of strings for output
    auto GenerateBoardStrings = [&]() -> vector<string>
    {
        vector<string> outBoard(n, string(n, '.'));

		// Fill the out board with queens based on the column indices stored in the int board vector.
		for (int row = 0; row < n; row++)
		{
			outBoard[row][intBoard[row]] = 'Q';
		}
        return outBoard;
    };

	// Backtracking function to place queens row by row
    function<void(int, int, int, int)> backtrack = [&](int row, int cols, int diags, int antiDiags)
        {
            // Base case - A Solution (N Quens has been placed in the board)
            if (row == n)
            {
                solutions.push_back(GenerateBoardStrings());  // Zero conversion cost: Direct push back
                return;
            }

			// Try placing a queen in each column of the current row
            for (int col = 0; col < n; col++)
            {

                // if the queen can be attacked
                // Instant O(1) checks without casting math overhead
                // Check if the col~th bit is set im any of our masks
                // (1 << col) create a mask with a 1 at the specific colummn position.
                if ((cols & (1 << col)) ||
                    (diags & (1 << (row - col + n - 1))) ||
                    (antiDiags & (1 << (row + col))))
                {
                    continue;
                }

                // Add the Queen to the board - Choose
                // Record choice in the 1D primitive array (O(1) memory write)
                intBoard[row] = col;

                // Move on the next row to placed the next queen con the updated board - Explore
                // Update bitmasks using the bitwise OR (|) operator.
                backtrack(row + 1,
                    (cols | (1 << col)),
                    (diags | (1 << (row - col + n - 1))),
                    (antiDiags | (1 << (row + col))));

                // remove the queen from internal board - Unchoose
                // "Unchoose" step is implicit. 
                // The next loop iteration or higher stack frame will simply overwrite board[row].

            }
        };

    // 0 means all calumns/diagonals/antidiagonals are completely free.
    backtrack(0, 0, 0, 0);
    return solutions;
};
