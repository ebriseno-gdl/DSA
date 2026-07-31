#include "Solution.h"

#include <vector>
#include <functional>

using namespace std;

// combinationSum3:
// Backtracking implementation that finds all unique combinations of `k` distinct numbers
// from 1..9 that add up to `n`.
// - Uses an index-based recursion (`idx`) that iterates the fixed domain 1..9 and increases
//   the start index on recursive calls so each number is used at most once.
// - Maintains a `current` vector; when `remain == 0` and `current.size() == k` the combination
//   is added to `output`.
// - Prunes branches when `remain < 0` or when `current.size() == k` but `remain != 0`.
// Time complexity: exponential in general (depends on branching and number of valid combinations),
//                  but the small fixed domain (1..9) limits the search space.
// Space complexity: O(output) for results + O(k) recursion stack and temporary storage.
// Notes: Because the domain is 1..9 and we iterate in increasing order, no additional duplicate
//        checks are required and generated combinations are in ascending order.
vector<vector<int>> Solution::combinationSum3(int k, int n)
{
	vector<vector<int>> output;
	vector<int> current;

	// Backtracking function to find combinations
	function<void(int, int)> backtrack = [&](int idx, int remain)
	{
		if (remain == 0 && current.size() == k)
		{
			output.push_back(current);
			return;
		}
		else if (remain < 0 || current.size() == k)
		{
			return;
		}

		// Iterate from idx to 9 (inclusive) since we can only use numbers 1-9
		for (int i = idx; i <= 9 && remain >= i; i++)
		{
			current.push_back(i); // choose
			backtrack(i + 1, remain - i); // explore
			current.pop_back(); // Un-choose (backtrack)
		}
	};

	backtrack(1, n);
	return output;
}