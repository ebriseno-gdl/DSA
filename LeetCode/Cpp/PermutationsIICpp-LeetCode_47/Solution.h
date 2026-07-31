#pragma once

#include <vector>

using namespace std;

class Solution {
public:
    // Backtracking implementation that builds permutations in a separate `current` vector.
    // Time complexity: O(n * n!) (practical overhead from membership checks).
    // Space complexity: O(n * n!) output + O(n) recursion stack + O(n) temporary current vector.
    vector<vector<int>> permuteUnique(vector<int>& nums);
};