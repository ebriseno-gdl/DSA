/*
 * LeetCode Problem 47: Permutations II
 *
 * Given an array of integers `nums` that may contain duplicates, return all
 * possible unique permutations (no duplicate permutations in the result).
 *
 * Examples:
 *  - Input: [1,1,2] -> Output: [[1,1,2],[1,2,1],[2,1,1]]
 *  - Input: [1,2,3] -> Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *  - Input: [0,0,0] -> Output: [[0,0,0]]
 *  - Input: []      -> Output: [] (empty input returns an empty list)
 *
 * Implementation overview:
 *  - `permuteUnique` : Backtracking (DFS) using a frequency map (`countNums`)
 *                      that tracks remaining counts for each distinct value.
 *                      At each recursion level try every value with remaining count > 0:
 *                      decrement count, push value to `current`, recurse, then restore count.
 *                      This ensures duplicate values are handled without post-filtering.
 *
 * Differences vs. Permutations I (Problem 46):
 *  - Problem 46 assumes all elements are distinct; typical approaches either use
 *    a visited array or in-place swapping.
 *  - Problem 47 must avoid producing duplicate permutations. Using a frequency map
 *    (or sorting + skip-equals strategies) reduces redundant branches.
 *
 * Notes:
 *  - Time complexity: O(n * n!) in the worst case when all values are distinct;
 *    the presence of duplicates reduces branching and total work.
 *  - Space complexity: O(n * n!) for the output + O(n) recursion stack + O(k)
 *    extra for the frequency map (k = number of distinct values).
 *  - Iteration order of `unordered_map` is unspecified; if deterministic output
 *    ordering is required, use a sorted container or collect and sort distinct values.
 *
 * Unit tests:
 *  - GoogleTest unit tests for `permuteUnique` live in the
 *    `PermutationsIICpp-LeetCode_47-TESTS` project.
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
	cout << "]" << "\n";
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
	cout << "]" << "\n";
}

int main()
{
	cout << "--- Permutations II - LeetCode 47 - Backtracking (C++) ---\n";

	// CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Prompt for list of integers
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
		
		// Call the permuteUnique function and print the output
		vector<vector<int>> result = solver.permuteUnique(nums);
		cout << "Output: ";
		printOutput(result);
	}
	else
	{
		// CASE B: Default Examples
		vector<vector<int>> testCases = {
			{1, 1, 2},
			{1, 2, 3},
			{0, 0, 0},
			{1, 2, 2},
			{1, 1, 1, 2}
		};
		for (vector<int> testCase : testCases)
		{
			cout << "Input: ";
			printInput(testCase);
			vector<vector<int>> result = solver.permuteUnique(testCase);
			cout << "Output: ";
			printOutput(result);
			cout << "\n";
		}
	}
	return 0;
}