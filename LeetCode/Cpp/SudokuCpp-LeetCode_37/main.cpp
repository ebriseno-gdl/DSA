/*
 * LeetCode Problem 37: Sudoku Solver (C++)
 *
 * Fill a 9x9 Sudoku board so that each row, column and 3x3 box contains digits 1-9 exactly once.
 * Input/Output: `vector<vector<char>>` with '.' for empty cells; solver mutates the board in-place.
 *
 * Overview:
 *  - Core technique: backtracking (choose a digit for an empty cell, recurse, undo on return).
 *  - Variants trade off readability, memory management, and runtime constant factors:
 *      - jagged dynamic arrays, RAII `vector` trackers, flat bitmasks and candidate heuristics (MRV).
 *
 * Implementations (brief differences / pros-cons):
 *  1) `solveSudoku1_JaggedNew`  - Classic row-major backtracking using manually `new[]`ed `int**` trackers.
 *       Pros: straightforward; Cons: manual heap management, higher allocation overhead.
 *
 *  2) `solveSudoku2_IdxParam_JaggedNew`  - Similar to (1) but passes precomputed box index to helpers for clarity.
 *       Pros: clearer helper signatures; Cons: still manual allocation.
 *
 *  3) `solveSudoku3_VectorRAII`  - RAII-friendly variant using `vector` trackers instead of raw `new[]`.
 *       Pros: safer memory management; Cons: slightly more indirection vs. bitmasks.
 *
 *  4) `solveSudoku4_ManualCleanup`  - Manual trackers with centralized `cleanup_memory` and try/catch for safety.
 *       Pros: safer manual cleanup; Cons: non-idiomatic vs. RAII.
 *
 *  5) `solveSudoku5_PrecomputedBox_Vector`  - Vector-based trackers + precomputed box-index table for O(1) box lookup.
 *       Pros: balanced readability and speed.
 *
 *  6) `solveSudoku6_Bitmask_Candidates`  - Bitmask + candidate bitsets using popcount for pruning / candidate enumeration.
 *       Pros: low overhead, fast candidate computation; Cons: more complex bit logic.
 *
 *  7) `solveSudoku7_Bitmask_Flat`  - Flat bitmask arrays + static `BOX_INDEX` for minimal footprint and fast checks.
 *       Pros: best practical speed among straightforward variants; Cons: less intuitive.
 *
 *  8) `solveSudoku8_Bitmask_MRV_Popcount`  - Bitmask + MRV (minimum-remaining-values) heuristic using `std::popcount`.
 *       Pros: best at solving hardest boards; Cons: most complex to read/maintain.
 *
 *  9) `solveSudoku9_Bitmask_MRV_PrivateHelpers` - Bitmask + MRV (minimum-remaining-values) heuristic using `std::popcount` +
 *     - Same algorithm as `solveSudoku8` (bitmask + MRV + popcount), but previously inline lambdas
 *       have been refactored into private member helper methods.
 *     - Pros: this has the best perfomance, improved testability and modularity; clearer class-level behavior and easier to unit-test helpers.
 *     - Cons: slightly more class coupling and longer interface surface.
 * 
 * Recommendation:
 *  - For speed: `solveSudoku7_Bitmask_Flat` or `solveSudoku8_Bitmask_MRV_Popcount`  / `solveSudoku9_Bitmask_MRV_PrivateHelpers` (bitmask + heuristics).
 *  - For clarity / teaching: `solveSudoku3_VectorRAII` or `solveSudoku5_PrecomputedBox_Vector` (vector-based, RAII).
 *
 * Practical notes:
 *  - Sudoku solving is exponential in worst case; heuristics and fast occupancy checks greatly reduce search.
 *  - Use `std::popcount` (C++20) for fast candidate counts where available.
 *  - Keep conversion/IO helpers local or priavte so implementations can be copied to online judges easily.
 */
#include "Solution.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Helper function to print the board
static void printBoard(string prompt, const vector<vector<char>>& board)
{
    cout << prompt << " (" << board.size() << " rows) : \n";
    for (const auto& r : board) {
        for (char ch : r) cout << ch << ' ';
        cout << '\n';
    }
}

// Main function to run the Sudoku solver
int main()
{
	cout << "--- Sudoku Solver Problem - LeetCode 37 - Backtracking (C++) ---\n";

	// CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    // Prompt for input n
    cout << "Enter the board (single line or multiple lines) and then send EOF (or press Enter to use default examples): \n";
    cout << "Note: On Windows console: press Ctrl+Z then Enter to send EOF \n";
    string inputLine;

	Solution solver;

    if (!getline(cin, inputLine)) return 0;

    if (!inputLine.empty() && inputLine.find_first_not_of(" \t\r\n") != string::npos)
    {
        // Paste the board (single line or multiple lines) and then send EOF.
        // On Windows console: press Ctrl+Z then Enter to send EOF.
        string input;
        input += inputLine;
        while (getline(cin, inputLine)) {
            if (!input.empty()) input.push_back('\n');
            input += inputLine;
        }

        vector<vector<char>> board;
        vector<char> row;
        int depth = 0;

        for (size_t i = 0; i < input.size(); ++i) {
            char c = input[i];
            if (c == '[') {
                ++depth;
            }
            else if (c == ']') {
                --depth;
                // when we close an inner array (depth goes from 2 -> 1), push collected row
                if (depth == 1 && !row.empty()) {
                    board.push_back(row);
                    row.clear();
                }
            }
            else if (c == '"') {
                size_t j = input.find('"', i + 1);
                if (j == string::npos) break;
                string token = input.substr(i + 1, j - (i + 1));
                // token for Sudoku input should be single char like "5" or "."
                if (!token.empty()) row.push_back(token[0]);
                else row.push_back(' ');
                i = j;
            }
        }

        if (board.empty()) {
            cerr << "Failed to parse board. Make sure the pasted text matches the format.\n";
            return 1;
        }

        // Print Input board
		printBoard("Input board", board);

		auto board1 = board; // copy board (separate instance)
		solver.solveSudoku1_JaggedNew(board1);
        printBoard("Solved 1 (JaggedNew) board", board1);

		auto board2 = board; // copy board (separate instance)
        solver.solveSudoku2_IdxParam_JaggedNew(board2);
        printBoard("Solved 2 (IdxParam_JaggedNew) board", board2);

        auto board3 = board; // copy board (separate instance)
        solver.solveSudoku3_VectorRAII(board3);
        printBoard("Solved 3 (VectorRAII) board", board3);

        auto board4 = board; // copy board (separate instance)
        solver.solveSudoku4_ManualCleanup(board4);
        printBoard("Solved 4 (ManualCleanup) board", board4);
        
        auto board5 = board; // copy board (separate instance)
        solver.solveSudoku5_PrecomputedBox_Vector(board5);
        printBoard("Solved 5 (PrecomputedBox_Vector) board", board5);

        auto board6 = board; // copy board (separate instance)
        solver.solveSudoku6_Bitmask_Candidates(board6);
        printBoard("Solved 6 (Bitmask_Candidates) board", board6);

        auto board7 = board; // copy board (separate instance)
        solver.solveSudoku7_Bitmask_Flat(board7);
        printBoard("Solved 7 (Bitmask_Flat) board", board7);

        auto board8 = board; // copy board (separate instance)
        solver.solveSudoku8_Bitmask_MRV_Popcount(board8);
        printBoard("Solved 8 (Bitmask_MRV_Popcount) board", board8);

        auto board9 = board; // copy board (separate instance)
        solver.solveSudoku9_Bitmask_MRV_PrivateHelpers(board9);
        printBoard("Solved 9 (Bitmask_MRV_PrivateHelpers) board", board9);
    }
    else
    {
		// Default Examples
        
		// Example 1
		vector<vector<char>> boardA = {
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
        };
		printBoard("Input board A", boardA);

		auto boardA1 = boardA; // copy board (separate instance)
		solver.solveSudoku1_JaggedNew(boardA1);
		printBoard("Solved 1 (JaggedNew) board A", boardA1);

		auto boardA2 = boardA; // copy board (separate instance)
        solver.solveSudoku2_IdxParam_JaggedNew(boardA2);
        printBoard("Solved 2 (IdxParam_JaggedNew) board A", boardA2);

		auto boardA3 = boardA; // copy board (separate instance)
		solver.solveSudoku3_VectorRAII(boardA3);
		printBoard("Solved 3 (VectorRAII) board A", boardA3);

        auto boardA4 = boardA; // copy board (separate instance)
        solver.solveSudoku4_ManualCleanup(boardA4);
        printBoard("Solved 4 (ManualCleanup) board A", boardA4);

        auto boardA5 = boardA; // copy board (separate instance)
        solver.solveSudoku5_PrecomputedBox_Vector(boardA5);
        printBoard("Solved 5 (PrecomputedBox_Vector) board A", boardA5);

        auto boardA6 = boardA; // copy board (separate instance)
        solver.solveSudoku6_Bitmask_Candidates(boardA6);
        printBoard("Solved 6 (Bitmask_Candidates) board A", boardA6);

        auto boardA7 = boardA; // copy board (separate instance)
        solver.solveSudoku7_Bitmask_Flat(boardA7);
        printBoard("Solved 7 (Bitmask_Flat) board A", boardA7);

        auto boardA8 = boardA; // copy board (separate instance)
        solver.solveSudoku8_Bitmask_MRV_Popcount(boardA8);
        printBoard("Solved 8 (Bitmask_MRV_Popcount) board A", boardA8);

        auto boardA9 = boardA; // copy board (separate instance)
        solver.solveSudoku9_Bitmask_MRV_PrivateHelpers(boardA9);
        printBoard("Solved 9 (Bitmask_MRV_PrivateHelpers) board A", boardA9);
    }
    return 0;
}