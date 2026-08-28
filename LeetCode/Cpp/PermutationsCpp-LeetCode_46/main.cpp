/*
 * LeetCode Problem 46: Permutations
 *
 * Given an array of distinct integers `nums`, return all possible permutations.
 *
 * Examples:
 *  - Input: [1,2,3] -> Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *  - Input: [0,1]   -> Output: [[0,1],[1,0]]
 *  - Input: [1]     -> Output: [[1]]
 *  - Input: []      -> Output: [] (empty input returns an empty list)
 *
 * Implementation overview:
 *  - `permute`    : Backtracking (DFS) using a `current` vector and membership checks
 *                   (search using `find`) to avoid re-using elements already in the
 *                   current permutation. Simple to read and follows the choose/explore/un-choose pattern.
 *
 *  - `permute1`   : (Suggested alternative) In-place swapping approach. Recursively swap the current index
 *                   with each candidate index and recurse on the next position. This avoids explicit membership
 *                   checks and many temporary allocations.
 *
 * Differences between `permute` and `permute1`:
 *  - `permute` uses an auxiliary `current` vector and membership checks (O(n) check per visit).
 *    This is straightforward but has higher constant overhead due to repeated `find`/contains checks
 *    and more push/pop operations.
 *  - `permute1` (swapping approach) operates in-place on `nums`, generating permutations by swapping.
 *    It avoids membership checks and reduces temporary allocations and copying, so it is faster in practice
 *    and uses slightly less working memory (aside from output).
 *
 * Which is better:
 *  - Both generate the same set of permutations and have the same asymptotic complexity of O(n * n!) time
 *    and O(n * n!) output size. However, `permute1` (swapping) is generally better in practice due to
 *    lower constant factors and fewer allocations. `permute` is more explicit and sometimes easier to reason about.
 *
 * Notes:
 *  - Both implementations assume `nums` contains distinct integers (no duplicate handling).
 *  - Time complexity: O(n * n!) (practical constants differ between the two approaches).
 *  - Space complexity: O(n * n!) for the output plus O(n) recursion stack; swapping uses fewer temporary buffers.
 *
 * Unit tests:
 *  - Google Unit tests for `Permute` and `Permute1` in the `PermutationsCpp-LeetCode_46-TESTS` project.
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
	cout << "--- Permutations - LeetCode 46 - Backtraking (C++) ---\n";

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

		// Call the permute function and print the output
		auto outputA = solver.permute(nums);
		cout << "Output (Permute-Auxiliary Backtracking): ";
		printOutput(outputA);
		auto outputB = solver.permute1(nums);
		cout << "Output (Permute-In-place Backtracking - Best): ";
		printOutput(outputB);
		cout << "\n";
	}
	else
	{
		// CASE B: Predefined Test Cases
		vector<vector<int>> testCases = { 
			{1, 2, 3}, 
			{0, 1}, 
			{1} 
		};
		for (vector<int> testCase : testCases)
		{
			cout << "Input: ";
			printInput(testCase);
			auto outputA = solver.permute(testCase);
			cout << "Output (Permute-Auxiliary Backtracking): ";
			printOutput(outputA);
			auto outputB = solver.permute1(testCase);
			cout << "Output (Permute-In-place Backtracking - Best): ";
			printOutput(outputB);
			cout << "\n";
		}

		//// Example 1
		//vector<int> input1 = { 1, 2, 3 };
		//cout << "Input 1: ";
		//printInput(input1);
		//auto output1A = solver.permute(input1);
		//cout << "Output 1 (Permute-Auxiliary Backtracking): ";
		//printOutput(output1A);
		//auto output1B = solver.permute1(input1);
		//cout << "Output 1 (Permute-In-place Backtracking - Best): ";
		//printOutput(output1B);
		//cout << "\n";

		//// Example 2
		//vector<int> input2 = { 0, 1 };
		//cout << "Input 2: ";
		//printInput(input2);
		//auto output2A = solver.permute(input2);
		//cout << "Output 2 (Permute-Auxiliary Backtracking): ";
		//printOutput(output2A);
		//auto output2B = solver.permute1(input2);
		//cout << "Output 2 (Permute-In-place Backtracking - Best): ";
		//printOutput(output2B);
		//cout << "\n";

		//// Example 3
		//vector<int> input3 = { 1 };
		//cout << "Input 3: ";
		//printInput(input3);
		//auto output3A = solver.permute(input3);
		//cout << "Output 3 (Permute-Auxiliary Backtracking): ";
		//printOutput(output3A);
		//auto output3B = solver.permute1(input3);
		//cout << "Output 3 (Permute-In-place Backtracking - Best): ";
		//printOutput(output3B);
		//cout << "\n";
	}

	return 0;
}