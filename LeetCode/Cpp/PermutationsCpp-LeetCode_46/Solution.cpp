#include "Solution.h"

#include <iostream>
#include <vector>
//#include <sstream>
#include <functional>

using namespace std;

// permute:
// Backtracking implementation that builds permutations in a separate `current` vector.
// - Base case: when `current.size() == nums.size()` push a copy to output.
// - For each number in `nums`, if it's not already in `current`, choose it, recurse, then un-choose.
// Time complexity: O(n * n!) (practical overhead from membership checks).
// Space complexity: O(n * n!) output + O(n) recursion stack + O(n) temporary current vector.
vector<vector<int>> Solution::permute(vector<int>& nums)
{
	vector<vector<int>> output;
	if (nums.empty()) return output;// Handle empty input case

	vector<int> current;
	vector<bool> visited(nums.size(), false); // O(1) check for used elements

	// Lambda function for backtracking
	function<void()> backtrack = [&]() 
	{
		// Base case: if the current permutation is complete, add it to the output
		if (current.size() == nums.size()) 
		{
			output.push_back(current);
			return;
		}
		// Recursive case: try each number in nums
		for (size_t i = 0; i < nums.size(); ++i) 
		{
			if (!visited[i]) 
			{
				visited[i] = true;	// Mark the number as used
				current.push_back(nums[i]);	// Choose
				backtrack();            // Explore   
				current.pop_back();		// Un-choose (backtrack)
				visited[i] = false;	// Mark the number as unused
			}
		}
	};

	backtrack(); // Call the lambda function for backtracking
	return output;
}

// permute1:
// In-place swapping approach (recommended when performance and fewer allocations are desired).
// - Recursively fix one position at a time by swapping candidates into the current index.
// - When index == nums.size(), push a copy of nums to output.
// Benefits:
//  - Avoids O(n) membership checks per level.
//  - Reduces temporary allocations (no `current` vector).
// Tradeoffs:
//  - Modifies `nums` in-place during recursion but restores via swap-back.
//  - Equally correct and produces the same result set as `permute`.
vector<vector<int>> Solution::permute1(vector<int>& nums)
{
	vector<vector<int>> output;
	if (nums.empty()) return output;// Handle empty input case

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
		// Recursive case: try each number in nums
		for (auto num : nums) 
		{
			if (find(current.begin(), current.end(), num) == current.end())
			{
				current.push_back(num);	// Choose
				backtrack();            // Explore   
				current.pop_back();		// Un-choose (backtrack)
			}
		}
	};

	backtrack(); // Call the lambda function for backtracking
	return output;
}