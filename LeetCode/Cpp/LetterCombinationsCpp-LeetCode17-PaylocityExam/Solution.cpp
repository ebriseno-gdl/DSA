#include "Solution.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

// Generate all possible letter combinations for a digit string (LeetCode 17)
// Time complexity: O(4^N * N), where N = digits.length()
//   - Each digit maps to at most 4 letters, so there are up to 4^N combinations.
//   - Constructing each combination takes O(N) time to append/copy the characters.
// Space complexity: O(4^N * N) for the output plus O(N) recursion stack and temporary string.
// Explanation: Use a fixed mapping from digits '2'..'9' to their letters and a backtracking (DFS)
// approach to build combinations. At each position choose a letter, recurse to the next digit,
// and then undo the choice (backtrack). Edge cases: return an empty vector for empty input and
// assume input contains only digits '2'..'9' (no validation performed here).
vector<string> Solution::letterCombinations(string digits)
{
	if (digits.empty()) return {}; // Handle empty input case

	vector<string> output;
	string current;
	current.reserve(digits.size()); // Reserve space to avoid reallocations

	unordered_map<char, string> mapDigitToLetters = {
		{'2', "abc"},
		{'3', "def"}, 
		{'4', "ghi"}, 
		{'5', "jkl"},
		{'6', "mno"}, 
		{'7', "pqrs"}, 
		{'8', "tuv"}, 
		{'9', "wxyz"}
	};

	// Lambda function for backtracking
	function<void(size_t)> backtrack = [&](size_t idx)
	{
		// Base case: if the current permutation is complete, add it to the output
		if (idx == digits.size())
		{
			output.push_back(current);
			return;
		}
		// Recursive case: try each number in nums
		const string& letters = mapDigitToLetters[digits[idx]];
		for (char letter : letters)
		{
			current.push_back(letter);	// Choose
			backtrack(idx + 1);          // Explore   
			current.pop_back();			// Un-choose (backtrack)
		}
	};

	backtrack(0); // Call the lambda function for backtracking
	return output;
}
