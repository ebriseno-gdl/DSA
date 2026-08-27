#include "Solution.h"

#include <vector>
#include <string>
#include <functional>
#include <unordered_set>

using namespace std;

vector<vector<string>> Solution::solveNQueens1(int n)
{
	vector<vector<string>> solutions;
        
    unordered_set<int> cols;
    unordered_set<int> diagonals;
    unordered_set<int> antiDiagonals;
        
    vector<vector<char>> intBoard(n, vector<char>(n, '.'));

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
        
    function<void(int)> backtrack = [&](int row)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if ( row == n)
        {
            solutions.push_back(createboard());
            return;
        }
            
        for (int col = 0; col < n; col++)
        {
            int currDiagonal = row - col;
            int currAntiDiagonal = row + col;
                
            // if the queen can be attacked
            if (cols.count(col) || diagonals.count(currDiagonal) || antiDiagonals.count(currAntiDiagonal))
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

vector<vector<string>> Solution::solveNQueens2(int n)
{
    // Solution where the board is managed directly as vector<string>
    // this is different to 1st solution where the board is managed as vector<vector<char>>
    // which needs of createOutBoard helper function to convert to a vector<string>,
    // so this solution saves both time and memory overhead

    vector<vector<string>> solutions;

    unordered_set<int> cols;
    unordered_set<int> diagonals;
    unordered_set<int> antiDiagonals;

    // initializa the board as a vector of strings    
    vector<string> board(n, string(n, '.'));

    function<void(int)> backtrack = [&](int row)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if (row == n)
        {
            solutions.push_back(board);  // Zero conversion cost: Direct push back
            return;
        }

        for (int col = 0; col < n; col++)
        {
            int currDiagonal = row - col;
            int currAntiDiagonal = row + col;

            // if the queen can be attacked
            if (cols.count(col) || diagonals.count(currDiagonal) || antiDiagonals.count(currAntiDiagonal))
            {
                continue;
            }

            // Add the Queen to the board - Choose
            cols.insert(col);
            diagonals.insert(currDiagonal);
            antiDiagonals.insert(currAntiDiagonal);
            board[row][col] = 'Q';

            // Move on the next row to placed the next queen con the updated board - Explore
            backtrack(row + 1);

            // remove the queen from board - Unchoose
            cols.erase(col);
            diagonals.erase(currDiagonal);
            antiDiagonals.erase(currAntiDiagonal);
            board[row][col] = '.';

        }
    };

    backtrack(0);
    return solutions;

};

vector<vector<string>> Solution::solveNQueens3(int n)
{
    // Solution that uses bitwise boolean vectors instead of std::unordered_set
    // eliminates the hash table overhead, reducing the diagonal and colummn
    // loockup times to a lightning-fast $O(1)$ constant time operations.

    vector<vector<string>> solutions;

    // Fixed-size boolean vectors act as director-lookup tables
    // Track columns (size n)
    vector<bool> cols(n, false);
    // Track main diagonals (range of row-col is -(n-1) to (n-1), Total 2n-1)
    vector<bool> diagonals(2 * n - 1, false);
    // Track anti-diagonals (range of row+col is 0 to 2*(n-1), Total 2n-1)
    vector<bool> antiDiagonals(2 * n - 1, false);

    // initializa the board as a vector of strings    
    vector<string> board(n, string(n, '.'));

    function<void(int)> backtrack = [&](int row)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if (row == n)
        {
            solutions.push_back(board);  // Zero conversion cost: Direct push back
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
            board[row][col] = 'Q';

            // Move on the next row to placed the next queen con the updated board - Explore
            backtrack(row + 1);

            // remove the queen from board - Unchoose
            // Flip booleans to false
            cols[col] = false;
            diagonals[currDiagIdx] = false;
            antiDiagonals[currAntiDiagIdx] = false;
            board[row][col] = '.';

        }
    };

    backtrack(0);
    return solutions;

};

vector<vector<string>> Solution::solveNQueens4(int n)
{
    // Solution that uses bitwise operations with standard integers (int).
    // It is the ultimate optimización for the N-Queensland problem.
    // Bécause standard integers have at least 32 bits, we can use individual
    // bits as binary flags (0 for open, 1 for blocked).
    // This complexity eliminates the vector<bool> arrays, reducting our 
    // tracking space complexity to a true $O(1)$ constant auxiliary space.

    vector<vector<string>> solutions;

    // initializa the board as a vector of strings    
    vector<string> board(n, string(n, '.'));

    // Using integers as bitmasks. Passed by value because ints fit entirely in CPU registers.
    function<void(int, int, int, int)> backtrack = [&](int row, int cols, int diags, int antiDiags)
    {
        // Base case - A Solution (N Quens has been placed in the board)
        if (row == n)
        {
            solutions.push_back(board);  // Zero conversion cost: Direct push back
            return;
        }

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
            board[row][col] = 'Q';

            // Move on the next row to placed the next queen con the updated board - Explore
            // Update bitmasks using the bitwise OR (|) operator.
            backtrack(row + 1,
                (cols | (1 << col)),
                (diags | (1 << (row - col + n - 1))),
                (antiDiags | (1 << (row + col))));

            // remove the queen from board - Unchoose.
            // Bitmasks revert automatically becuuse they were passed by value.
            board[row][col] = '.';

        }
    };

    // 0 means all calumns/diagonals/antidiagonals are completely free.
    backtrack(0, 0, 0, 0);
    return solutions;
};

vector<vector<string>> Solution::solveNQueens5(int n)
{
	// Solutionn that uses bitwise operations with standard integers (int) 
    // and a 1D primitive array to track the column index of the queen for each row.

    vector<vector<string>> solutions;

    // Tracks the column index of the queen for each row.
    // board[row] = col    
    vector<int> board(n);

    auto GenerateBoardStrings = [&]() -> vector<string>
    {
        vector<string> outBoard(n, string(n, '.'));

		// Fill the board with queens based on the column indices stored in the board vector.
		for (int row = 0; row < n; row++)
		{
			outBoard[row][board[row]] = 'Q';
		}
        return outBoard;
    };

    // Using integers as bitmasks. Passed by value because ints fit entirely in CPU registers.
    function<void(int, int, int, int)> backtrack = [&](int row, int cols, int diags, int antiDiags)
        {
            // Base case - A Solution (N Quens has been placed in the board)
            if (row == n)
            {
                solutions.push_back(GenerateBoardStrings());  // Zero conversion cost: Direct push back
                return;
            }

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
                board[row] = col;

                // Move on the next row to placed the next queen con the updated board - Explore
                // Update bitmasks using the bitwise OR (|) operator.
                backtrack(row + 1,
                    (cols | (1 << col)),
                    (diags | (1 << (row - col + n - 1))),
                    (antiDiags | (1 << (row + col))));

                // remove the queen from board - Unchoose
                // "Unchoose" step is implicit. 
                // The next loop iteration or higher stack frame will simply overwrite board[row].

            }
        };

    // 0 means all calumns/diagonals/antidiagonals are completely free.
    backtrack(0, 0, 0, 0);
    return solutions;
};
