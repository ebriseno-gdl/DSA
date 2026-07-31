#include "Solution.h"

#include <vector>
#include <functional>
#include <unordered_map>


using namespace std;

// permuteUnique:
// Backtracking implementation that generates unique permutations using a frequency map.
// - Uses `countNums` (value -> remaining count) and a `current` vector to build permutations.
// - At each recursion level try each distinct value with count > 0: decrement count, push value, recurse, pop and restore count.
// - By tracking counts we avoid generating duplicate permutations (no post-filtering required).
// Time complexity: O(n * n!) in the worst case when all values are distinct; duplicates reduce branching and total work.
// Space complexity: O(n * n!) output + O(n) recursion stack + O(k) extra for the frequency map (k = distinct values).
// Note: iteration order of `unordered_map` is unspecified; use a sorted container if deterministic ordering of output is required.
vector<vector<int>> Solution::permuteUnique(vector<int>& nums)
{
	vector<vector<int>> output;
	if (nums.empty()) return output; // Handle empty input case

	// Count the occurrences of each number in nums
	unordered_map<int, int> countNums;
    for (auto num : nums)
    {
        countNums[num]++;
    }

    vector<int> current;

	// Lambda function for backtracking
    function<void()> backtrack = [&]()
    {
		// Base case: if the current permutation is complete, add it to the output
        if (current.size() == nums.size())
        {
            output.push_back(current);
            return;
        }

		// Recursive case: try each unique number in countNums
        for (auto entry : countNums)
        {
            int num = entry.first;
            int count = entry.second;
            if (count == 0)
                continue;
            countNums[num]--;
			current.push_back(num); // Choose
			backtrack();            // Explore
			current.pop_back();     // Un-choose (backtrack)
            countNums[num]++;
        }
    };

    backtrack();
    return output;
}
