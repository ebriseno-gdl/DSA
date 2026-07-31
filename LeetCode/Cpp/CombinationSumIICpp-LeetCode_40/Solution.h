#pragma once

#include <vector>

using namespace std;

class Solution {
public:
    // Backtracking implementation that finds unique combinations (each candidate used at most once).
    // - Sorts `candidates` and uses index-based recursion with duplicate skipping.
    // Time complexity: exponential in the worst case (depends on number of valid combinations).
    // Space complexity: O(output) + O(n) recursion/temporary storage.
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target);
};