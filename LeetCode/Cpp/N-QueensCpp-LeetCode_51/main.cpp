#include "Solution.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

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
		vector<vector<string>> solutions1 = solver.solveNQueens1(n);
		printSolutions("1", solutions1);

		vector<vector<string>> solutions2 = solver.solveNQueens2(n);
		printSolutions("2", solutions2);

		vector<vector<string>> solutions3 = solver.solveNQueens3(n);
		printSolutions("3", solutions3);

		vector<vector<string>> solutions4 = solver.solveNQueens4(n);
		printSolutions("4", solutions4);

		vector<vector<string>> solutions5 = solver.solveNQueens5(n);
		printSolutions("5", solutions5);
	}
	else
	{
		// CASE B: Default Examples
		vector<int> testCases = { 1, 2, 3, 4, 5, 6 };
		for (int n : testCases)
		{
			cout << "Test Case n = " << n << "\n";

			vector<vector<string>> solutions1 = solver.solveNQueens1(n);
			printSolutions("1", solutions1);

			vector<vector<string>> solutions2 = solver.solveNQueens2(n);
			printSolutions("2", solutions2);

			vector<vector<string>> solutions3 = solver.solveNQueens3(n);
			printSolutions("3", solutions3);

			vector<vector<string>> solutions4 = solver.solveNQueens4(n);
			printSolutions("4", solutions4);
			
			vector<vector<string>> solutions5 = solver.solveNQueens5(n);
			printSolutions("5", solutions5);
		}
	}
	return 0;

}
