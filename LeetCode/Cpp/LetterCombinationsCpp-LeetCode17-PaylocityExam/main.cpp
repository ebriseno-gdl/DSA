/*
 * LeetCode Problem 17: Letter Combinations of a Phone Number
 *
 * Given a string containing digits from 2-9 inclusive, return all possible letter
 * combinations that the number could represent. The order of the output does not matter.
 *
 * Examples:
 *  - Input: "23" -> Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *  - Input: ""   -> Output: []  (empty input returns an empty list)
 *  - Input: "7"  -> Output: ["p","q","r","s"]
 *
 * Implementation overview:
 *  - Approach: Backtracking (DFS) using a fixed mapping from digits '2'..'9' to letters.
 *  - Time complexity: O(4^N * N) where N = digits.length().
 *  - Space complexity: O(4^N * N) for the output plus O(N) recursion stack and temporary buffers.
 *
 * Notes:
 *  - This implementation assumes input contains only digits '2'..'9' (no additional validation).
 *
 * Unit tests:
 *  - Unit tests for `Solution::letterCombinations` are located in the
 *    `LetterCombinationsCpp-LeetCode17-PaylocityExam-TESTS` project.
 */
#include "Solution.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cout << "--- Letter Combinations of a Phone Number - LeetCode 17 - Backtracking (C++) ---\n";
	
	// CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	// Prompt for input digits
	cout << "Enter a string of digits (2-9) (or press Enter to use default examples): ";
	string inputLine;
	if (!getline(cin, inputLine)) return 0;

	Solution solver;
	
	if (!inputLine.empty() && inputLine.find_first_not_of(" \t\r\n") != string::npos)
	{
		// CASE A: Standard Input/Output with Custom Parsing
		vector<string> combinations = solver.letterCombinations(inputLine);
		cout << "Letter combinations for \"" << inputLine << "\":\n";
		for (const auto& combination : combinations) {
			cout << combination << " ";
		}
		cout << endl;
	}
	else
	{
		// CASE B: Default Examples
		vector<string> testCases = { "23", "32", "662", "", "5"};
		for (const auto& digits : testCases) {
			vector<string> combinations = solver.letterCombinations(digits);
			cout << "Letter combinations for \"" << digits << "\":\n";
			for (const auto& combination : combinations) {
				cout << combination << " ";
			}
			cout << endl;
		}
	}
	return 0;
}