/*
 * LeetCode Problem 51: N-Queens (C++)
 *
 * Place N queens on an N×N chessboard so that no two queens attack each other.
 * Return all distinct board configurations (each configuration is a vector<string> of length N).
 *
 * Examples:
 *  - N = 4
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
 *
 * Overview:
 *  - All implementations perform row-by-row backtracking: choose a column for the current row,
 *    test for conflicts, recurse to the next row, and undo the placement on return.
 *  - Pruning via trackers (sets, arrays or bitmasks) drastically reduces the search space.
 *
 * Implementations (what each does, differences, pros/cons):
 *  1) SolveNQueens1_JaggedHash
 *     - Backtracking with an explicit `vector<vector<char>>` internal board and `unordered_set<int>` trackers
 *     - Pros: Very readable; easy to debug and construct output
 *     - Cons: Hash set overhead and O(N^2) board storage
 *
 *  2) SolveNQueens2_StringBoard_Hash
 *     - Backtracking with `vector<string>` board and `unordered_set<int>` trackers
 *     - Pros: Avoids board conversion; direct push of `vector<string>`
 *     - Cons: Hash overhead remains
 *
 *  3) SolveNQueens3_BoolArr
 *     - Backtracking using `vector<bool>` arrays for columns and diagonals (index-mapped)
 *     - Pros: O(1) checks with low overhead; simple and fast
 *     - Cons: Needs diagonal index shifting (row - col + offset)
 *
 *  4) SolveNQueens4_BitMask
 *     - Backtracking using integer bitmasks for columns and diagonals; board as `vector<string>` for output
 *     - Pros: Fastest conflict checks via bitwise ops; minimal per-check overhead
 *     - Cons: Limited by integer width (use wider integer types for large N)
 *
 *  5) SolveNQueens5_IndexBoard_BitMask
 *     - Compact approach: 1D `vector<int>` storing queen column per row + bitmasks for trackers
 *     - Pros: Minimal working memory; build output from compact representation
 *     - Cons: Same bit-width caveat as mask-based approaches
 *
 * Recommendation:
 *  - For best raw performance: `SolveNQueens4_BitMask` or `SolveNQueens5_IndexBoard_BitMask`.
 *  - For clarity / teaching: `SolveNQueens1_JaggedHash` or `SolveNQueens2_StringBoard_Hash`.
 *
 * Practical notes:
 *  - All methods are exponential by nature; pruning and efficient conflict checks matter.
 *  - For N near/exceeding the native integer bit width, switch to `long long` or another representation.
 *  - Helpers that convert internal boards to `vector<string>` are kept local so implementations can be
 *    copied to online judges without external dependencies.
 */
#include "Solution.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Helper function to print the solutions in a readable format
static void printSolutions(string prompt, const vector<vector<string>>& solutions)
{
	cout << "  Solutions(" << prompt << "):" << "\n";
	for (const auto& solution : solutions) {
		cout << "    [";
		for (const auto& row : solution) {
			cout << row;
			if (&row != &solution.back()) cout << ",";
		}
		cout << "]" << "\n";
	}
}

int main()
{
	cout << "--- N-Queens Problem - LeetCode 51 - Backtracking (C++) ---\n";

	// CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Prompt for input n
	cout << "Enter the size of the chessboard (n) (or press Enter to use default examples): ";
	string inputLine;
	if (!getline(cin, inputLine)) return 0;

	Solution solver;

	if (!inputLine.empty() && inputLine.find_first_not_of(" \t\r\n") != string::npos)
	{
		// CASE A: Standard Input/Output with Custom Parsing

		// Custom Input Parsing: Converting string to integer
		stringstream ss(inputLine);
		int n;
		if (!(ss >> n)) {
			cout << "Invalid input. Please enter a valid integer for n." << "\n";
			return 1;
		}

		// Solve the N-Queens problem for the given n and print the solutions
		vector<vector<string>> solutions1 = solver.SolveNQueens1_JaggedHash(n);
		printSolutions("1", solutions1);

		vector<vector<string>> solutions2 = solver.solveNQueens2_StringBoard_Hash(n);
		printSolutions("2", solutions2);

		vector<vector<string>> solutions3 = solver.solveNQueens3_BoolArr(n);
		printSolutions("3", solutions3);

		vector<vector<string>> solutions4 = solver.solveNQueens4_BitMask(n);
		printSolutions("4", solutions4);

		vector<vector<string>> solutions5 = solver.solveNQueens5_IndexBoard_BitMask(n);
		printSolutions("5", solutions5);
	}
	else
	{
		// CASE B: Default Examples
		vector<int> testCases = { 1, 2, 3, 4, 5, 6 };
		for (int n : testCases)
		{
			cout << "Test Case n = " << n << "\n";

			vector<vector<string>> solutions1 = solver.SolveNQueens1_JaggedHash(n);
			printSolutions("1", solutions1);

			vector<vector<string>> solutions2 = solver.solveNQueens2_StringBoard_Hash(n);
			printSolutions("2", solutions2);

			vector<vector<string>> solutions3 = solver.solveNQueens3_BoolArr(n);
			printSolutions("3", solutions3);

			vector<vector<string>> solutions4 = solver.solveNQueens4_BitMask(n);
			printSolutions("4", solutions4);
			
			vector<vector<string>> solutions5 = solver.solveNQueens5_IndexBoard_BitMask(n);
			printSolutions("5", solutions5);
		}
	}
	return 0;

}
