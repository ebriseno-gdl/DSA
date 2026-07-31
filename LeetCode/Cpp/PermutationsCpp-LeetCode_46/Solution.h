#pragma once

#include <vector>

using namespace std;

class Solution {
public:
    // Backtracking implementation that builds permutations in a separate `current` vector.
    // Time complexity: O(n * n!) (with additional membership-check overhead).
    // Space complexity: O(n * n!) for output + O(n) recursion stack + O(n) for current buffer.
    vector<vector<int>> permute(vector<int>& nums);

    // Alternative in-place swapping implementation (recommended for performance).
    // Approach: swap `nums[i]` with `nums[index]`, recurse with index+1, swap back (restore).
    // Time complexity: O(n * n!) with smaller constants than `permute`.
    // Space complexity: O(n * n!) for output + O(n) recursion stack; minimal extra buffers.
    vector<vector<int>> permute1(vector<int>& nums);
};
