#pragma once

#include <vector>

using namespace std;

class Solution
{
public:
	// Backtracking implementation for LeetCode 216 (`combinationSum3`).
	// - Returns all combinations of `k` distinct numbers from 1..9 that sum to `n`.
	// - Uses increasing `idx` and recursion so each number is used at most once.
	// - Time complexity: exponential (limited by small domain 1..9).
	// - Space complexity: O(output) + O(k) recursion/temporary storage.
	vector<vector<int>> combinationSum3(int k, int n);
};
