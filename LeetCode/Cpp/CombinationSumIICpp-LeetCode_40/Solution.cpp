#include "Solution.h"

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// combinationSum2:
// Backtracking implementation that finds unique combinations that sum to `target`.
// - Input `candidates` is sorted first to allow early pruning and easy duplicate skipping.
// - Uses index-based recursion (`idx`) so each element can be used at most once.
// - At each recursion level iterate from `idx`..end, skip duplicate values when `i > idx && candidates[i] == candidates[i-1]`
//   to avoid producing duplicate combinations at the same depth.
// - Build a `current` vector; when `remain == 0` push `current` into `output`.
// Time complexity: exponential in the worst case (depends on number of valid combinations and their lengths).
// Space complexity: O(output) for storing results + O(n) recursion stack + O(n) for the `current` vector.
// Note: Sorting is required for the duplicate-skip trick; if deterministic ordering of output is required, keep the sort.
vector<vector<int>> Solution::combinationSum2(vector<int>& candidates, int target)
{
    vector<vector<int>> output;
    if (candidates.empty()) return output; // handle empty input case

    vector<int> current;
    sort(candidates.begin(), candidates.end());

    function<void(int, int)> backtrack = [&](int idx, int remain)
        {
            // Base case
            if (remain == 0)
            {
                output.push_back(current);
                return;
            }
            else if (remain < 0)
            {
                return;
            }

            for (int i = idx; i < candidates.size() && remain >= candidates[i]; i++)
            {
                if (i > idx && candidates[i] == candidates[i - 1])
                    continue;

                current.push_back(candidates[i]); // choose
                backtrack(i + 1, remain - candidates[i]);  // explore
                current.pop_back(); // Un-choose (backtrack)
            }
        };

    backtrack(0, target);
    return output;
}