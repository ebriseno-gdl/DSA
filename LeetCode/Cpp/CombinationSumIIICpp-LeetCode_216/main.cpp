/*
 * LeetCode Problem 216: Combination Sum III
 *
 * Given two integers `k` and `n`, return all possible combinations of `k` distinct numbers
 * chosen from 1..9 that add up to `n`. Each number may be used at most once.
 *
 * Examples:
 *  - Input: k = 3, n = 7  -> Output: [[1,2,4]]
 *  - Input: k = 3, n = 9  -> Output: [[1,2,6],[1,3,5],[2,3,4]]
 *  - Input: k = 4, n = 1  -> Output: [] (no valid combinations)
 *
 * Implementation overview:
 *  - `combinationSum3`: Backtracking (DFS) over the fixed domain 1..9 using an increasing start index.
 *    This ensures each number is used at most once and combinations are generated in ascending order.
 *  - Maintain a `current` vector and a remaining sum `remain`. When `current.size() == k && remain == 0`
 *    add a copy of `current` to the results.
 *  - Prune branches when `current.size() == k && remain != 0`, or when `remain < 0`.
 *  - Iterate `i` from `idx` to 9 and recurse with `i + 1` to avoid reusing numbers.
 *
 * Notes:
 *  - Time complexity: exponential in general (depends on branching and number of valid combinations);
 *    pruning and the small fixed domain (1..9) reduce the search space.
 *  - Space complexity: O(output) for results + O(k) recursion/temporary storage.
 *  - Because the domain is 1..9 and iteration is increasing, no explicit duplicate-skipping is required.
 *
 * Unit tests:
 *  - GoogleTest unit tests for `combinationSum3` live in the
 *    `CombinationSumIIICpp-LeetCode_216-TESTS` project.
 */

#include "Solution.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

static void printOutput(const vector<vector<int>>& groups)
{
	cout << "[";
	for (size_t i = 0; i < groups.size(); ++i) {
		cout << "[";
		for (size_t j = 0; j < groups[i].size(); ++j) {
			cout << groups[i][j];
			if (j + 1 < groups[i].size()) cout << ",";
		}
		cout << "]";
	}
	cout << "]" << endl;
}

int main()
{
	cout << "--- Combination Sum III - LeetCode 216 - Backtracking (C++) ---\n";

	// CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	// Prompt for list of integers, if empty, use default examples
	cout << "Enter two integers k and n (space-separated or press Enter to use default examples): ";
	string inputLine;
	if (!getline(cin, inputLine)) return 0;
	
	Solution solver;
	
	if (!inputLine.empty() && inputLine.find_first_not_of(" \t\r\n") != string::npos)
	{
		// CASE A: Standard Input/Output with Custom Parsing
		// Custom Input Parsing: Converting string stream into two integers
		stringstream ss(inputLine);
		int k, n;
		ss >> k >> n;

		// Call the combinationSum2 function and print the output
		vector<vector<int>> result = solver.combinationSum3(k, n);
		cout << "Output: ";
		printOutput(result);
	}
	else
	{
		// CASE B: Default Examples
		vector<pair<int, int>> defaultExamples = { {3, 7}, {3, 9}, {4, 1} };

		for (const auto& example : defaultExamples) {
			int k = example.first;
			int n = example.second;
			cout << "Input: k = " << k << ", n = " << n << endl;

			vector<vector<int>> result = solver.combinationSum3(k, n);

			cout << "Output: ";
			printOutput(result);
			cout << endl;
		}
	}
	return 0;
}