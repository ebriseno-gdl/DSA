#pragma once

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    // Generate all possible letter combinations for a digit string (LeetCode 17)
    // Time complexity: O(4^N * N), where N = digits.length()
    // Space complexity: O(4^N * N) for the output plus O(N) recursion stack and temporary string.
    vector<string> letterCombinations(string digits);
};