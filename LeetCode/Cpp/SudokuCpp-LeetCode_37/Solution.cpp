#include "Solution.h"

#include <vector>
#include <functional>
#include <bit>  // Required for std::popcount in C++20

using namespace std;

void Solution::solveSudoku1(vector<vector<char>>& board) 
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

void Solution::solveSudoku2(vector<vector<char>>& board) 
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
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
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

                    // If sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
                if ((col == N - 1) && (row == N - 1))
                {
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

void Solution::solveSudoku3(vector<vector<char>>& board)
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
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
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

                    // If sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
                if ((col == N - 1) && (row == N - 1))
                {
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

void Solution::solveSudoku4(vector<vector<char>>& board)
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
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
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

                    // If sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
                if ((col == N - 1) && (row == N - 1))
                {
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

void Solution::solveSudoku5(vector<vector<char>>& board)
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
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup

                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
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

                    // If sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
                if ((col == N - 1) && (row == N - 1))
                {
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

void Solution::solveSudoku6(vector<vector<char>>& board)
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
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup

                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
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

                    // If sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
                if ((col == N - 1) && (row == N - 1))
                {
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

void Solution::solveSudoku7(vector<vector<char>>& board)
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
                int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup

                // iterate over all numbers from 1 to 9
                for (int d = 1; d < 10; d++)
                {
                    if (!could_place(d, row, col, idx))
                    {
                        continue;
                    }

                    place_number(d, row, col, idx);

                    // If we just filled the last cell, mark solution found instead of recursing out-of-bounds
                    if ((row == N - 1) && (col == N - 1))
                    {
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

                    // If sudoku is solved, there is no need to backtrack
                    // since the single unique solution is promised
                    if (!sudoku_solved)
                    {
                        remove_number(d, row, col, idx);
                    }
                }
            }
            else
            {
                if ((col == N - 1) && (row == N - 1))
                {
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

void Solution::solveSudoku8(vector<vector<char>>& board)
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
                        int idx = BOX_INDEX[row][col]; // Optimized: Direct array lookup 

                        int choices_mask = get_valid_choices(row, col, idx);

                        // Built-in function to count set bits (number of valid choices)
                        //int count = __builtin_popcount(choices_mask);
						//int count = __popcnt(choices_mask); // For MSVC, use __popcnt instead of __builtin_popcount
						int count = popcount(static_cast<unsigned int>(choices_mask)); // For C++20 and later, use std::popcount

                        // If a cell has 0 valid choices, this branch is invalid. Backtrack immediately!
                        if (count == 0) return;

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
                if (best_choices_mask & (1 << d))
                {
                    int idx = BOX_INDEX[best_row][best_col]; // Optimized: Direct 

                    place_number(d, best_row, best_col, idx);

                    backtrack();

                    if (sudoku_solved) return;

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