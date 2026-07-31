/*
 * LeetCode Problem 40: Combination Sum II
 *
 * Given a collection of candidate numbers (`candidates`) and a target number `target`,
 * return all unique combinations in which the candidate numbers sum to `target`.
 * Each candidate may only be used once in the combination.
 *
 * Examples:
 *  - Input: candidates = [10,1,2,7,6,1,5], target = 8
 *    -> Output: [[1,1,6],[1,2,5],[1,7],[2,6]] (order may vary)
 *  - Input: candidates = [2,5,2,1,2], target = 5
 *    -> Output: [[1,2,2],[5]]
 *  - Input: candidates = [1,2,3], target = 7
 *    -> Output: [] (no valid combinations)
 *
 * Implementation overview:
 *  - `combinationSum2`: Backtracking (DFS) with sorting + duplicate skipping.
 *    Sort `candidates` to allow early pruning (stop when remaining < candidate)
 *    and to skip equal values at the same recursion depth (avoid duplicate combos).
 *  - Use index-based recursion so each element is considered at most once.
 *  - Build a `current` vector; when remaining target reaches 0, add `current` to output.
 *
 * Differences vs. Combination Sum (Problem 39):
 *  - Problem 39 allows unlimited reuse of each candidate (repeat choices).
 *  - Problem 40 restricts each candidate to be used at most once and requires
 *    careful duplicate-skipping after sorting.
 *
 * Notes:
 *  - Time complexity: exponential in general (depends on branching and number of valid combos).
 *  - Space complexity: O(output) for results + O(n) recursion/temporary storage.
 *  - Sorting is required for the skip-equals trick; keep sort if deterministic behavior is needed.
 *
 * Unit tests:
 *  - GoogleTest unit tests for `combinationSum2` live in the
 *    `CombinationSumIICpp-LeetCode_40-TESTS` project.
 */

#include "Solution.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

static void printInput(const vector<int>& group)
{
	cout << "[";
	for (size_t i = 0; i < group.size(); ++i) {
		cout << group[i];
		if (i + 1 < group.size()) cout << ",";
	}
	cout << "]" << endl;
}

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
	cout << "--- Combination Sum II - LeetCode 40 - Backtracking (C++) ---\n";

	// CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Prompt for list of integers, if empty, use default examples
	cout << "Enter a list of integers (space-separated or press Enter to use default examples): ";
	string inputLine;
	if (!getline(cin, inputLine)) return 0;

	Solution solver;

	if (!inputLine.empty() && inputLine.find_first_not_of(" \t\r\n") != string::npos)
	{
		// CASE A: Standard Input/Output with Custom Parsing

		// Custom Input Parsing: Converting string stream into a vector
		stringstream ss(inputLine);
		vector<int> nums;
		int num;
		while (ss >> num) {
			nums.push_back(num);
		}

		// Prompt for target and parse it
		cout << "Enter target value: ";
		string targetLine;
		if (!getline(cin, targetLine)) return 0;
		if (targetLine.empty() || targetLine.find_first_not_of(" \t\r\n") == string::npos) {
			cout << "No target provided\n";
			return 0;
		}
		stringstream ts(targetLine);
		int target;
		if (!(ts >> target)) {
			cout << "Invalid target\n";
			return 0;
		}

		// Call the combinationSum2 function and print the output
		vector<vector<int>> result = solver.combinationSum2(nums, target);
		cout << "Output: ";
		printOutput(result);

	}
	else
	{
		// CASE B: Default Examples
		vector<pair<vector<int>, int>> testCases = {
			{{10, 1, 2, 7, 6, 1, 5}, 8},
			{{2, 5, 2, 1, 2}, 5},
			{{1, 1, 2, 2, 3}, 4},
			{{1, 2, 3}, 7},
			{{0, 0, 0}, 0}
		};
		for (const auto& testCase : testCases)
		{
			const auto& nums = testCase.first;
			int target = testCase.second;

			cout << "Input: ";
			printInput(nums);
			cout << "Target: " << target << endl;
			vector<vector<int>> result = solver.combinationSum2(const_cast<vector<int>&>(nums), target);
			cout << "Output: ";
			printOutput(result);
			cout << endl;
		}
	}
	return 0;
}