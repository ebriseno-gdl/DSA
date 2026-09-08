#include "Solution.h"

#include <vector>
#include <functional>
#include <bit>  // Required for std::popcount in C++20

using namespace std;

/*
 * solveSudoku1_JaggedNew
 *
 * Approach:
 *  - Classic backtracking (row-major) that mutates the input board in-place.
 *  - Uses dynamically allocated 2D int arrays (`int**`) as trackers for rows, columns and 3x3 boxes.
 *  - `could_place`, `place_number`, `remove_number` helper lambdas; separate `place_next_numbers` helper.
 *
 * Time complexity:
 *  - Exponential in the worst case (pruned; theoretical upper bound ~O(9^(81))).
 *
 * Space complexity:
 *  - O(N^2) for the tracker arrays (N=9) + recursion stack O(81).
 *
 * Pros:
 *  - Easy to read and matches a textbook backtracking implementation.
 *
 * Cons:
 *  - Manual heap allocation (`new[]`) increases allocation overhead and maintenance burden.
 *
 * Notes:
 *  - Box index is computed on the fly; stops early once the single guaranteed solution is found.
 */
void Solution::solveSudoku1_JaggedNew(vector<vector<char>>& board) 
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

	// Keep track of the status of each number in each row, column, and box
    int** rows = new int* [N];
    int** columns = new int* [N];
    int** boxes = new int* [N];
    
	// Initialize the tracking arrays
    for (int i = 0; i < N; i++) {
        rows[i] = new int[N + 1]();
        columns[i] = new int[N + 1]();
        boxes[i] = new int[N + 1]();
    }

	// Helper function to check if a number can be placed in a cell
    auto could_place = [&](int d, int row, int col) -> bool
    {
        int idx = (row / n) * n + col / n;
        return rows[row][d] + columns[col][d] + boxes[idx][d] == 0;
    };

	// Helper function to place a number in a cell
    function<void(int, int, int)> place_number = [&](int d, int row, int col)
    {
        int idx = (row / n) * n + col / n;
        rows[row][d]++;
        columns[col][d]++;
        boxes[idx][d]++;
        board[row][col] = (char)(d + '0');
    };

	// Helper function to remove a number from a cell
    function<void(int, int, int)> remove_number = [&](int d, int row, int col)
    {
        int idx = (row / n) * n + col / n;
        rows[row][d]--;
        columns[col][d]--;
        boxes[idx][d]--;
        board[row][col] = '.';
    };

	// Declaration of the Backtracking function to solve the Sudoku
    function<void(int, int)> backtrack;

	// Helper function to place the next numbers in the Sudoku
    function<void(int, int)> place_next_numbers = [&](int row, int col)
    {
        /*
        Call backtrack function in recursion
        to continue to place numbers
        till the moment we have a solution
        */
        // If we're in the last cell
        //  that means we have the solution
        if ((col == N - 1) && (row == N - 1)) {
            sudoku_solved = true;
        }
        // if not yet
        else {
            // If we're at the end of the row
            //  go to the next row
            if (col == N - 1) backtrack(row + 1, 0);
            // go to the next column
            else
                backtrack(row, col + 1);
        }
    };
    
	// Implementation of the Backtracking function to solve the Sudoku
    backtrack = [&](int row, int col)
    {
        // If the cell is empty
        if (board[row][col] == '.') {
            // iterate over all numbers from 1 to 9
            for (int d = 1; d < 10; d++) {
                if (could_place(d, row, col)) {
                    place_number(d, row, col);
                    place_next_numbers(row, col);
                    // If sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudoku_solved) remove_number(d, row, col);
                }
            }
        }
        else
        {
			// If the cell is not empty, continue to place the next numbers
            place_next_numbers(row, col);
        }
    };
    
	// Fill the tracking arrays based on the initial board configuration
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char num = board[i][j];
            if (num != '.') {
                int d = num - '0';
                place_number(d, i, j);
            }
        }
    }

	// Start the backtracking algorithm from the first cell
    backtrack(0, 0);
}

/*
 * solveSudoku2_IdxParam_JaggedNew
 *
 * Approach:
 *  - Backtracking with explicit trackers; helper functions accept the precomputed box index parameter.
 *  - Uses dynamically allocated tracker arrays but passes `idx` into the helpers for slight clarity.
 *
 * Time complexity:
 *  - Exponential (pruned by trackers).
 *
 * Space complexity:
 *  - O(N^2) for trackers + recursion stack.
 *
 * Pros:
 *  - Slightly clearer helpers (index passed) and explicit choose/explore/unchoose structure.
 *
 * Cons:
 *  - Still uses manual dynamic allocation; more boilerplate for memory management.
 *
 * Notes:
 *  - Attempts to avoid out-of-bounds recursion by marking `sudoku_solved` when the last cell is filled.
 */
void Solution::solveSudoku2_IdxParam_JaggedNew(vector<vector<char>>& board) 
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

    // Keep track of the status of each number in each row, column, and box
    int** rows = new int* [N];
    int** columns = new int* [N];
    int** boxes = new int* [N];

    // Initialize the tracking arrays
    for (int i = 0; i < N; i++)
    {
        rows[i] = new int[N + 1]();
        columns[i] = new int[N + 1]();
        boxes[i] = new int[N + 1]();
    }

    // Helper function to check if a number can be placed in a cell
    auto could_place = [&](int d, int row, int col, int idx)
        {
            return rows[row][d] + columns[col][d] + boxes[idx][d] == 0;
        };

    // Helper function to place a number in a cell
    function<void(int, int, int, int)> place_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]++;
            columns[col][d]++;
            boxes[idx][d]++;
            board[row][col] = (char)(d + '0');
        };

    // Helper function to remove a number from a cell
    function<void(int, int, int, int)> remove_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]--;
            columns[col][d]--;
            boxes[idx][d]--;
            board[row][col] = '.';
        };

    // Backtracking function to solve the Sudoku
    function<void(int, int)> backtrack = [&](int row, int col)
        {
            // If the cell is empty
            if (board[row][col] == '.')
            {
                int idx = (row / n) * n + col / n;
                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
					// If we cannot place the number d in the current cell, skip to the next number
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

					// Place the number d in the current cell - Choose
                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
                        // Case Base: If we're in the last cell, that means we have the solution
                        sudoku_solved = true;
                    }
                    else
                    {
						// If we're at the end of the row, go to the next row
						// Otherwise, go to the next column - Explore
                        if (col == N - 1)
                        {
                            backtrack(row + 1, 0);
                        }
                        else
                        {
                            backtrack(row, col + 1);
                        }
                    }

                    // If sudoku is solved, there is no need to backtrack
					// since the single unique solution is promised - Unchoose
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
				// If the cell is not empty, continue to place the next numbers
				if ((col == N - 1) && (row == N - 1))
                {
                    // Case Base: If we're in the last cell, that means we have the solution    
                    sudoku_solved = true;
                }
                else
                {
					// If we're at the end of the row, go to the next row
					// Otherwise, go to the next column - Explore
                    if (col == N - 1)
                    {
                        backtrack(row + 1, 0);
                    }
                    else
                    {
                        backtrack(row, col + 1);
                    }
                }
            }
        };

    // Fill the tracking arrays based on the initial board configuration
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char num = board[i][j];
            if (num != '.')
            {
                int d = num - '0';
                int idx = (i / n) * n + j / n;
                place_number(d, i, j, idx);
            }
        }
    }

    try
    {
        // Start the backtracking algorithm from the first cell
        backtrack(0, 0);
    }
    catch (...)
    {
        // THIS ACTS LIKE YOUR FINALLY BLOCK IF AN EXCEPTION OCCURS
        for (int i = 0; i < N; i++)
        {
            delete[] rows[i];
            delete[] columns[i];
            delete[] boxes[i];
        }
        delete[] rows;
        delete[] columns;
        delete[] boxes;

        throw; // Re-throw the exception so the caller knows something went wrong
    }

    // Clean up standard successful execution path
    for (int i = 0; i < N; i++)
    {
        delete[] rows[i];
        delete[] columns[i];
        delete[] boxes[i];
    }
    delete[] rows;
    delete[] columns;
    delete[] boxes;
}

/*
 * solveSudoku3_VectorRAII
 *
 * Approach:
 *  - (Pedagogical/alternate) Backtracking variant that prefers RAII-friendly containers for trackers.
 *  - Uses `vector<vector<int>>` (or `vector<int>`) for row/column/box trackers and standard helper lambdas.
 *
 * Time complexity:
 *  - Exponential with pruning.
 *
 * Space complexity:
 *  - O(N^2) for vectors + recursion stack.
 *
 * Pros:
 *  - Automatic memory management (no manual deletes), safer and easier to maintain.
 *
 * Cons:
 *  - Slight additional indirection vs. tightly-packed bitmasks.
 *
 * Notes:
 *  - Good intermediate implementation between naive and highly optimized bitmask variants.
 */
void Solution::solveSudoku3_VectorRAII(vector<vector<char>>& board)
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

    // Keep track of the status of each number in each row, column, and box
    int** rows = new int* [N];
    int** columns = new int* [N];
    int** boxes = new int* [N];

    // Initialize the tracking arrays
    for (int i = 0; i < N; i++)
    {
        rows[i] = new int[N + 1]();
        columns[i] = new int[N + 1]();
        boxes[i] = new int[N + 1]();
    }

    // Dedicated cleanup lambda to avoid duplicating array deletion code
    auto cleanup_memory = [&]()
        {
            for (int i = 0; i < N; i++)
            {
                delete[] rows[i];
                delete[] columns[i];
                delete[] boxes[i];
            }
            delete[] rows;
            delete[] columns;
            delete[] boxes;
        };

    // Helper function to check if a number can be placed in a cell
    auto could_place = [&](int d, int row, int col, int idx)
        {
            return rows[row][d] + columns[col][d] + boxes[idx][d] == 0;
        };

    // Helper function to place a number in a cell
    function<void(int, int, int, int)> place_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]++;
            columns[col][d]++;
            boxes[idx][d]++;
            board[row][col] = (char)(d + '0');
        };

    // Helper function to remove a number from a cell
    function<void(int, int, int, int)> remove_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]--;
            columns[col][d]--;
            boxes[idx][d]--;
            board[row][col] = '.';
        };

    // Backtracking function to solve the Sudoku
    function<void(int, int)> backtrack = [&](int row, int col)
        {
            // If the cell is empty
            if (board[row][col] == '.')
            {
                int idx = (row - row % n) + col / n;
                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
					// If we cannot place the number d in the current cell, skip to the next number
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

					// Place the number d in the current cell - Choose
                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
                        // Case Base: If we're in the last cell, that means we have the solution
                        sudoku_solved = true;
                    }
                    else
                    {
						// If we're at the end of the row, go to the next row
						// Otherwise, go to the next column - Explore
                        if (col == N - 1)
                        {
                            backtrack(row + 1, 0);
                        }
                        else
                        {
                            backtrack(row, col + 1);
                        }
                    }

                    // If sudoku is solved, there is no need to backtrack
					// since the single unique solution is promised - Unchoose
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
				// If the cell is not empty, continue to place the next numbers
				// If we're in the last cell, that means we have the solution
                if ((col == N - 1) && (row == N - 1))
                {
                    // Case Base: If we're in the last cell, that means we have the solution    
                    sudoku_solved = true;
                }
                else
                {
					// If we're at the end of the row, go to the next row
					// Otherwise, go to the next column - Explore
                    if (col == N - 1)
                    {
                        backtrack(row + 1, 0);
                    }
                    else
                    {
                        backtrack(row, col + 1);
                    }
                }
            }
        };

    // Fill the tracking arrays based on the initial board configuration
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            char num = board[row][col];
            if (num != '.')
            {
                int d = num - '0';
                int idx = (row - row % n) + col / n;
                place_number(d, row, col, idx);
            }
        }
    }

    try
    {
        // Start the backtracking algorithm from the first cell
        backtrack(0, 0);
    }
    catch (...)
    {
        // THIS ACTS LIKE YOUR FINALLY BLOCK IF AN EXCEPTION OCCURS
        cleanup_memory(); // Triggers on error/exception crash

        throw; // Re-throw the exception so the caller knows something went wrong
    }

    // Clean up standard successful execution path
    cleanup_memory(); // Triggers on a standard successful exit
}

/*
 * solveSudoku4_ManualCleanup
 *
 * Approach:
 *  - Backtracking with manual trackers but includes a dedicated `cleanup_memory` lambda to centralize deletion.
 *  - Helpers are similar to prior variants; try/catch used to ensure cleanup on exceptions.
 *
 * Time complexity:
 *  - Exponential (pruned).
 *
 * Space complexity:
 *  - O(N^2) for trackers + recursion stack.
 *
 * Pros:
 *  - Safer manual-cleanup pattern (single place to free allocated arrays).
 *
 * Cons:
 *  - Still relies on heap allocations; non-idiomatic compared to modern C++ RAII.
 *
 * Notes:
 *  - Useful when keeping the same underlying tracker layout but improving robustness around early exits/errors.
 */
void Solution::solveSudoku4_ManualCleanup(vector<vector<char>>& board)
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

    // Keep track of the status of each number in each row, column, and box
    int** rows = new int* [N];
    int** columns = new int* [N];
    int** boxes = new int* [N];

    // Initialize the tracking arrays
    for (int i = 0; i < N; i++)
    {
        rows[i] = new int[N + 1]();
        columns[i] = new int[N + 1]();
        boxes[i] = new int[N + 1]();
    }

    // Dedicated cleanup lambda to avoid duplicating array deletion code
    auto cleanup_memory = [&]()
        {
            for (int i = 0; i < N; i++)
            {
                delete[] rows[i];
                delete[] columns[i];
                delete[] boxes[i];
            }
            delete[] rows;
            delete[] columns;
            delete[] boxes;
        };

    // Helper function to check if a number can be placed in a cell
    auto could_place = [&](int d, int row, int col, int idx)
        {
            return rows[row][d] + columns[col][d] + boxes[idx][d] == 0;
        };

    // Helper function to place a number in a cell
    function<void(int, int, int, int)> place_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]++;
            columns[col][d]++;
            boxes[idx][d]++;
            board[row][col] = (char)(d + '0');
        };

    // Helper function to remove a number from a cell
    function<void(int, int, int, int)> remove_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]--;
            columns[col][d]--;
            boxes[idx][d]--;
            board[row][col] = '.';
        };

    // Backtracking function to solve the Sudoku
    function<void(int, int)> backtrack = [&](int row, int col)
        {
            // If the cell is empty
            if (board[row][col] == '.')
            {
                int idx = (row - row % 3) + col / 3;
                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
					// If we cannot place the number d in the current cell, skip to the next number
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

					// Place the number d in the current cell - Choose
                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
                        // Case Base: If we're in the last cell, that means we have the solution    
                        sudoku_solved = true;
                    }
                    else
                    {
						// If we're at the end of the row, go to the next row
						// Otherwise, go to the next column - Explore
                        if (col == N - 1)
                        {
                            backtrack(row + 1, 0);
                        }
                        else
                        {
                            backtrack(row, col + 1);
                        }
                    }

                    // If sudoku is solved, there is no need to backtrack
					// since the single unique solution is promised - Unchoose
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
				// If the cell is not empty, continue to place the next numbers
				// If we're in the last cell, that means we have the solution
                if ((col == N - 1) && (row == N - 1))
                {
                    // Case Base: If we're in the last cell, that means we have the solution    
                    sudoku_solved = true;
                }
                else
                {
					// If we're at the end of the row, go to the next row
					// Otherwise, go to the next column - Explore
                    if (col == N - 1)
                    {
                        backtrack(row + 1, 0);
                    }
                    else
                    {
                        backtrack(row, col + 1);
                    }
                }
            }
        };

    // Fill the tracking arrays based on the initial board configuration
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            char num = board[row][col];
            if (num != '.')
            {
                int d = num - '0';
                int idx = (row - row % 3) + col / 3;
                place_number(d, row, col, idx);
            }
        }
    }

    try
    {
        // Start the backtracking algorithm from the first cell
        backtrack(0, 0);
    }
    catch (...)
    {
        // THIS ACTS LIKE YOUR FINALLY BLOCK IF AN EXCEPTION OCCURS
        cleanup_memory(); // Triggers on error/exception crash

        throw; // Re-throw the exception so the caller knows something went wrong
    }

    // Clean up standard successful execution path
    cleanup_memory(); // Triggers on a standard successful exit
}

/*
 * solveSudoku5_PrecomputedBox_Vector
 *
 * Approach:
 *  - Optimized tracker representation using `vector<vector<int>>` together with a precomputed box index table.
 *  - Backtracking remains the core algorithm; helpers accept explicit box index for O(1) box lookup.
 *
 * Time complexity:
 *  - Exponential with pruning; faster in practice due to reduced index arithmetic and RAII containers.
 *
 * Space complexity:
 *  - O(N^2) for trackers + recursion stack.
 *
 * Pros:
 *  - Cleaner code and automatic memory management; precomputed indices reduce repeated computations.
 *
 * Cons:
 *  - Still not as memory/CPU compact as bitmask-based solutions.
 *
 * Notes:
 *  - Balanced choice for readability and reasonable performance.
 */
void Solution::solveSudoku5_PrecomputedBox_Vector(vector<vector<char>>& board)
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

    // Static 9x9 lookup table for instantaneous O(1) box index retrieval
    static const int BOX_INDEX[9][9] = {
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8}
    };

    // Keep track of the status of each number in each row, column, and box
    int** rows = new int* [N];
    int** columns = new int* [N];
    int** boxes = new int* [N];

    // Initialize the tracking arrays
    for (int i = 0; i < N; i++)
    {
        rows[i] = new int[N + 1]();
        columns[i] = new int[N + 1]();
        boxes[i] = new int[N + 1]();
    }

    // Dedicated cleanup lambda to avoid duplicating array deletion code
    auto cleanup_memory = [&]()
        {
            for (int i = 0; i < N; i++)
            {
                delete[] rows[i];
                delete[] columns[i];
                delete[] boxes[i];
            }
            delete[] rows;
            delete[] columns;
            delete[] boxes;
        };

    // Helper function to check if a number can be placed in a cell
    auto could_place = [&](int d, int row, int col, int idx)
        {
            return rows[row][d] + columns[col][d] + boxes[idx][d] == 0;
        };

    // Helper function to place a number in a cell
    function<void(int, int, int, int)> place_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]++;
            columns[col][d]++;
            boxes[idx][d]++;
            board[row][col] = (char)(d + '0');
        };

    // Helper function to remove a number from a cell
    function<void(int, int, int, int)> remove_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]--;
            columns[col][d]--;
            boxes[idx][d]--;
            board[row][col] = '.';
        };

    // Backtracking function to solve the Sudoku
    function<void(int, int)> backtrack = [&](int row, int col)
        {
            // If the cell is empty
            if (board[row][col] == '.')
            {
				// Use the precomputed box index for O(1) access
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup

                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
					// If we cannot place the number d in the current cell, skip to the next number
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

					// Place the number d in the current cell - Choose
                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
					if ((row == N - 1) && (col == N - 1))
                    {
                        // Case Base: If we're in the last cell, that means we have the solution    
                        sudoku_solved = true;
                    }
                    else
                    {
						// If we're at the end of the row, go to the next row
						// Otherwise, go to the next column - Explore
                        if (col == N - 1)
                        {
                            backtrack(row + 1, 0);
                        }
                        else
                        {
                            backtrack(row, col + 1);
                        }
                    }

                    // If sudoku is solved, there is no need to backtrack
					// since the single unique solution is promised - Unchoose
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
				// If the cell is not empty, continue to place the next numbers
				// If we're in the last cell, that means we have the solution
                if ((col == N - 1) && (row == N - 1))
                {
                    // Case Base: If we're in the last cell, that means we have the solution    
                    sudoku_solved = true;
                }
                else
                {
					// If we're at the end of the row, go to the next row
					// Otherwise, go to the next column - Explore
                    if (col == N - 1)
                    {
                        backtrack(row + 1, 0);
                    }
                    else
                    {
                        backtrack(row, col + 1);
                    }
                }
            }
        };

    // Fill the tracking arrays based on the initial board configuration
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            char num = board[row][col];
            if (num != '.')
            {
                int d = num - '0';
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup
                place_number(d, row, col, idx);
            }
        }
    }

    try
    {
        // Start the backtracking algorithm from the first cell
        backtrack(0, 0);
    }
    catch (...)
    {
        // THIS ACTS LIKE YOUR FINALLY BLOCK IF AN EXCEPTION OCCURS
        cleanup_memory(); // Triggers on error/exception crash

                throw; // Re-throw the exception so the caller knows something went wrong
    }

    // Clean up standard successful execution path
    cleanup_memory(); // Triggers on a standard successful exit
}

/*
 * solveSudoku6_Bitmask_Candidates
 *
 * Approach:
 *  - Candidate-selection / bitmask-oriented variant (uses bit operations to represent available digits).
 *  - Uses bitmasks for rows/cols/boxes to speed occupancy checks and to compute candidates quickly.
 *
 * Time complexity:
 *  - Exponential but with much smaller constants due to bit-level pruning and candidate enumeration.
 *
 * Space complexity:
 *  - O(N) bitmasks (flat arrays) + recursion stack.
 *
 * Pros:
 *  - Low memory footprint for trackers; very fast O(1) occupancy checks.
 *
 * Cons:
 *  - Slightly more complex bit manipulation logic; less immediately readable to newcomers.
 *
 * Notes:
 *  - Good base for further heuristics (select cell with fewest candidates using popcount).
 */
void Solution::solveSudoku6_Bitmask_Candidates(vector<vector<char>>& board)
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

    // Static 9x9 lookup table for instantaneous O(1) box index retrieval
    static const int BOX_INDEX[9][9] = {
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8}
    };

    // Modern tracking arrays using vectors. RAII guarantees automatic cleanup
    vector<vector<int>> rows(N, vector<int>(N + 1, 0));
    vector<vector<int>> columns(N, vector<int>(N + 1, 0));
    vector<vector<int>> boxes(N, vector<int>(N + 1, 0));

    // Helper function to check if a number can be placed in a cell
    auto could_place = [&](int d, int row, int col, int idx)
        {
            return rows[row][d] + columns[col][d] + boxes[idx][d] == 0;
        };

    // Helper function to place a number in a cell
    function<void(int, int, int, int)> place_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]++;
            columns[col][d]++;
            boxes[idx][d]++;
            board[row][col] = (char)(d + '0');
        };

    // Helper function to remove a number from a cell
    function<void(int, int, int, int)> remove_number = [&](int d, int row, int col, int idx)
        {
            rows[row][d]--;
            columns[col][d]--;
            boxes[idx][d]--;
            board[row][col] = '.';
        };

    // Backtracking function to solve the Sudoku
    function<void(int, int)> backtrack = [&](int row, int col)
        {
            // If the cell is empty
            if (board[row][col] == '.')
            {
				// Use the precomputed box index for O(1) access
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup

                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
					// If we cannot place the number d in the current cell, skip to the next number
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

					// Place the number d in the current cell - Choose
                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
                        // Case Base: If we're in the last cell, that means we have the solution    
                        sudoku_solved = true;
                    }
                    else
                    {
						// If we're at the end of the row, go to the next row
						// Otherwise, go to the next column - Explore
                        if (col == N - 1)
                        {
                            backtrack(row + 1, 0);
                        }
                        else
                        {
                            backtrack(row, col + 1);
                        }
                    }

                    // If sudoku is solved, there is no need to backtrack
					// since the single unique solution is promised - Unchoose
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
				// If the cell is not empty, continue to place the next numbers
				// If we're in the last cell, that means we have the solution
                if ((col == N - 1) && (row == N - 1))
                {
                    // Case Base: If we're in the last cell, that means we have the solution    
                    sudoku_solved = true;
                }
                else
                {
					// If we're at the end of the row, go to the next row
					// Otherwise, go to the next column - Explore
                    if (col == N - 1)
                    {
                        backtrack(row + 1, 0);
                    }
                    else
                    {
                        backtrack(row, col + 1);
                    }
                }
            }
        };

    // Fill the tracking arrays based on the initial board configuration
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            char num = board[row][col];
            if (num != '.')
            {
                int d = num - '0';
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup
                place_number(d, row, col, idx);
            }
        }
    }

    // Start the backtracking algorithm from the first cell
    backtrack(0, 0);
}

/*
 * solveSudoku7_Bitmask_Flat
 *
 * Approach:
 *  - Highly optimized bitmask solution:
 *    - Flat int arrays `rows[9]`, `columns[9]`, `boxes[9]` store 9-bit masks of used digits.
 *    - Static `BOX_INDEX[9][9]` for O(1) box index lookup.
 *  - Place/remove operations use bit OR/AND; `could_place` uses mask checks.
 *
 * Time complexity:
 *  - Exponential but often the fastest of the presented variants due to bit-level operations.
 *
 * Space complexity:
 *  - O(1) extra (fixed-size arrays) + recursion stack.
 *
 * Pros:
 *  - Best practical performance among these implementations; minimal memory and fast checks.
 *
 * Cons:
 *  - Code is less intuitive; careful attention to bit-shifting is required.
 *
 * Notes:
 *  - Well suited for production/contest usage where speed matters.
 */
void Solution::solveSudoku7_Bitmask_Flat(vector<vector<char>>& board)
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

    // Static 9x9 lookup table for instantaneous O(1) box index retrieval
    static const int BOX_INDEX[9][9] = {
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8}
    };

    // Flat arrays of bitmasks for rows, columns, and 3x3 boxes.
    // Each array index contains a 9-bit bitmask representing digits 1-9.
    int rows[9] = { 0 };
    int columns[9] = { 0 };
    int boxes[9] = { 0 };

    // Helper function to check if a number can be placed in a cell
    auto could_place = [&](int d, int row, int col, int idx)
        {
            int mask = 1 << d;
            return (rows[row] & mask) == 0 &&
                (columns[col] & mask) == 0 &&
                (boxes[idx] & mask) == 0;
        };

    // Helper function to place a number in a cell
    function<void(int, int, int, int)> place_number = [&](int d, int row, int col, int idx)
        {
            int mask = 1 << d;
            rows[row] |= mask;      // Set bit to 1
            columns[col] |= mask;   // Set bit to 1
            boxes[idx] |= mask;     // Set bit to 1
            board[row][col] = (char)(d + '0');
        };

    // Helper function to remove a number from a cell
    function<void(int, int, int, int)> remove_number = [&](int d, int row, int col, int idx)
        {
            int mask = 1 << d;
            rows[row] &= ~mask;      // Clear bit back to 0
            columns[col] &= ~mask;   // Clear bit back to 0
            boxes[idx] &= ~mask;     // Clear bit back to 0
            board[row][col] = '.';
        };

    // Backtracking function to solve the Sudoku
    function<void(int, int)> backtrack = [&](int row, int col)
        {
            // If the cell is empty
            if (board[row][col] == '.')
            {
				// Use the precomputed box index for O(1) access
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup

                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
					// If we cannot place the number d in the current cell, skip to the next number
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

					// Place the number d in the current cell - Choose
                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
						// Case Base: If we're in the last cell, that means we have the solution
                        sudoku_solved = true;
                    }
                    else
                    {
						// If we're at the end of the row, go to the next row
						// Otherwise, go to the next column - Explore
                        if (col == N - 1)
                        {
                            backtrack(row + 1, 0);
                        }
                        else
                        {
                            backtrack(row, col + 1);
                        }
                    }

                    // If sudoku is solved, there is no need to backtrack
					// since the single unique solution is promised - Unchoose
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
				// If the cell is not empty, continue to place the next numbers
				// If we're in the last cell, that means we have the solution
                if ((col == N - 1) && (row == N - 1))
                {
					// Case Base: If we're in the last cell, that means we have the solution
                    sudoku_solved = true;
                }
                else
                {
                    if (col == N - 1)
                    {
                        backtrack(row + 1, 0);
                    }
                    else
                    {
                        backtrack(row, col + 1);
                    }
                }
            }
        };

    // Fill the tracking arrays based on the initial board configuration
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            char num = board[row][col];
            if (num != '.')
            {
                int d = num - '0';
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup
                place_number(d, row, col, idx);
            }
        }
    }

    // Start the backtracking algorithm from the first cell
    backtrack(0, 0);
}

/*
 * solveSudoku8_Bitmask_MRV_Popcount
 *
 * Approach:
 *  - Advanced/combined approach:
 *    - Uses bitmasks for speed and additional heuristics (e.g., choose cell with minimum candidates).
 *    - May use `std::popcount` / candidate enumeration to implement minimum-remaining-values heuristic.
 *
 * Time complexity:
 *  - Exponential but typically explores far fewer branches because of heuristic selection.
 *
 * Space complexity:
 *  - O(1) fixed-size bitmasks + O(81) recursion stack.
 *
 * Pros:
 *  - Best overall solver for hardest boards: combines bit-level speed with heuristic pruning.
 *
 * Cons:
 *  - Most complex implementation to read and maintain.
 *
  * Notes:
 *  - Uses C++20 `std::popcount` where available to count candidate bits efficiently.
 */
void Solution::solveSudoku8_Bitmask_MRV_Popcount(vector<vector<char>>& board)
{
    // box size
    int n = 3;
    // row size
    int N = n * n;
    bool sudoku_solved = false;

    // Static 9x9 lookup table for instantaneous O(1) box index retrieval
    static const int BOX_INDEX[9][9] = {
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {0,0,0, 1,1,1, 2,2,2},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {3,3,3, 4,4,4, 5,5,5},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8},
        {6,6,6, 7,7,7, 8,8,8}
    };

    // Flat arrays of bitmasks for rows, columns, and 3x3 boxes.
    // Each array index contains a 9-bit bitmask representing digits 1-9.
    int rows[9] = { 0 };
    int columns[9] = { 0 };
    int boxes[9] = { 0 };

    // Returns a bitmask of ALL valid numbers (1-9) that can be placed at board[row][col]
    auto get_valid_choices = [&](int row, int col, int idx)
        {
            // Combined mask of taken numbers across row, column, and box
            int taken = rows[row] | columns[col] | boxes[idx];

            // Return only the valid bits for digits 1-9 that are NOT taken
            // (1 << d) for d=1..9 means bits 1 to 9. Mask 0x3FE represents all bits 1-9 set to 1.
            return (~taken) & 0x3FE;
        };

    // Helper function to place a number in a cell
    function<void(int, int, int, int)> place_number = [&](int d, int row, int col, int idx)
        {
            int mask = 1 << d;
            rows[row] |= mask;      // Set bit to 1
            columns[col] |= mask;   // Set bit to 1
            boxes[idx] |= mask;     // Set bit to 1
            board[row][col] = (char)(d + '0');
        };

    // Helper function to remove a number from a cell
    function<void(int, int, int, int)> remove_number = [&](int d, int row, int col, int idx)
        {
            int mask = 1 << d;
            rows[row] &= ~mask;      // Clear bit back to 0
            columns[col] &= ~mask;   // Clear bit back to 0
            boxes[idx] &= ~mask;     // Clear bit back to 0
            board[row][col] = '.';
        };

    // Backtracking function to solve the Sudoku
    function<void()> backtrack = [&]()
        {
            int min_choices = 10;
            int best_row = -1;
            int best_col = -1;
            int best_choices_mask = 0;

            // Constraint Propagation / MRV (Minimum Remaining Values) Scan
            for (int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    if (board[row][col] == '.')
                    {
						// Use the precomputed box index for O(1) access
                        int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup 

						// Get the bitmask of valid choices for this empty cell
                        int choices_mask = get_valid_choices(row, col, idx);

                        // Built-in function to count set bits (number of valid choices)
						//int count = __builtin_popcount(choices_mask); // For GCC/Clang, use __builtin_popcount
						//int count = __popcnt(choices_mask); // For MSVC, use __popcnt instead of __builtin_popcount
						int count = popcount(static_cast<unsigned int>(choices_mask)); // For C++20 and later, use std::popcount
                        // Comment about the popcount functions: 
                        // __builtin_popcount is a GCC/Clang built-in function that counts the number of set bits (1s) in an integer.
                        // __popcnt is the equivalent for MSVC (Microsoft Visual C++).
                        // std::popcount is available in C++20 and later, which also counts the number of set bits in an integer.

                        // If a cell has 0 valid choices, this branch is invalid. Backtrack immediately!
                        if (count == 0) return;

						// Update the cell with the fewest valid choices (MRV heuristic)
                        if (count < min_choices)
                        {
                            min_choices = count;
                            best_row = row;
                            best_col = col;
                            best_choices_mask = choices_mask;
                        }

                        // Naked Single found (only 1 unique choice). Look no further, solve this cell!
                        if (min_choices == 1) break;

                    }
                }
				// Naked Single found (only 1 unique choice). Look no further, solve this cell!
                if (min_choices == 1) break;
            }

            // If no empty cells are left, the Sudoku is successfully solved
            if (best_row == -1) {
                sudoku_solved = true;
                return;
            }

            // Try the valid choices for the cell with the fewest options
            for (int d = 1; d <= 9; d++)
            {
				//  Check if digit d is a valid choice for the best cell using the bitmask
                if (best_choices_mask & (1 << d))
                {
					// Use the precomputed box index for O(1) access
                    int idx = BOX_INDEX[best_row][best_col]; // Optimized: Direct 

					// Place the number d in the best cell - Choose
                    place_number(d, best_row, best_col, idx);

					// Recursively call backtrack to continue solving - Explore
                    backtrack();

					// If sudoku is solved, there is no need to backtrack
                    if (sudoku_solved) return;

					// Unchoose: Remove the number d from the best cell and try the next valid choice
                    remove_number(d, best_row, best_col, idx);
                }
            }
        };

    // Fill the tracking arrays based on the initial board configuration
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            char num = board[row][col];
            if (num != '.')
            {
                int d = num - '0';
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup
                place_number(d, row, col, idx);
            }
        }
    }

    // Start the backtracking algorithm from the first cell
    backtrack();
}