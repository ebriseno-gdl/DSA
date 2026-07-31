/*
 * LeetCode Problem 1: Two Sum
 *
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 * Input: nums = [3,5,1,4,-8], target = 5
 * Output: [0,3]
 * Explanation: Because nums[0] + nums[3] == 5, we return [0, 3].
 *
 * Example 4:
 * Input: nums = [3,4,9,6,4], target = 8
 * Output: [0,1]
 *
 * Example 5:
 * Input: nums = [4,-2,5,0,6,3,2,7], target = 1
 * Output: [0,6]
 *
 */

 /*
   Implementations overview (three common Two Sum approaches), differences, pros/cons

   1) Single-pass hash map (current `twoSum`):
      - What: Iterate once. For each element compute complement = target - nums[i],
        check unordered_map for complement, otherwise store current value->index.
      - Complexity:
          Average time: O(n), Best: O(1) if found early, Worst: O(n^2) in pathological hash-collision cases.
          Space: O(n).
      - Pros: Fast in practice, early exit when pair found, simple.
      - Cons: Uses extra memory; theoretical worst-case due to hash collisions.

   2) Two-pass hash map:
      - What: First build a value->index map for all elements, then iterate again to check complements.
      - Complexity:
          Average time: O(n) (two linear passes), Space: O(n). Worst-case same hash-collision caveat.
      - Pros: Clear separation of build and lookup phases; still O(n) on average.
      - Cons: No early return during the map-build phase (may do more work before checks);
              same memory use and hash-collision worst-case.

   3) Sort-based two-pointer:
      - What: Build (value,index) pairs, sort by value, then use two pointers from both ends to find the sum.
      - Complexity:
          Time: O(n log n) (deterministic), Space: O(n) for pairs (or O(1) extra if sorting in-place and losing indices).
      - Pros: Predictable worst-case runtime (no hash-collision attacks), simple two-pointer scan.
      - Cons: Slower than hash on average because of sorting; must track original indices (extra space)
              or lose original ordering if sorting in-place.

   When to choose:
    - Use single-pass hash map for typical workloads and interviews (fastest average).
    - Use two-pass only for clarity or when code structure prefers it; performance similar to single-pass.
    - Use sort-based when deterministic worst-case guarantees are required or when avoiding hash tables.

   Summary:
    - Single-pass / two-pass hash: average O(n) time, O(n) space; worst-case O(n^2) with pathological hashes.
    - Sort-based: O(n log n) time, O(n) space; deterministic worst-case behavior.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

/*
 twoSum - single-pass hash map approach

 Complexity guarantees:
 - Time (average / expected): O(n)
   * Each of the n elements causes at most one hash lookup and one hash insert.
   * For typical inputs unordered_map lookup/insert are O(1) on average -> total O(n).
 - Time (best): O(1)
   * If the matching pair is found immediately, the function returns early.
 - Time (worst): O(n^2)
   * In adversarial or pathological cases (extreme hash collisions), individual
     lookups/inserts can degrade to O(n) -> n operations × O(n) = O(n^2).
     This worst-case is rare in practice.
 - Space: O(n) auxiliary
   * The unordered_map may store up to one entry per input element.

 Notes:
 - This single-pass approach is typically faster than a two-pass map build because
   it can return as soon as a match is found.
 - If worst-case adversarial behavior is a concern, consider alternative strategies
   (e.g., sorting + two pointers: O(n log n) time, O(1) extra space if reordering is allowed).
*/
vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int> seenNumbers; // Map to store the index of each number seen so far
	for (int i = 0; i < nums.size(); ++i) {
		int complement = target - nums[i]; // Calculate the complement
		if (seenNumbers.find(complement) != seenNumbers.end()) { // Check if the complement exists in the map
			return { seenNumbers[complement], i }; // Return the indices of the two numbers
		}
		seenNumbers[nums[i]] = i; // Store the index of the current number
	}
	return {}; // Return an empty vector if no solution is found
}

// Two-pass unordered_map: build map then search
// Avg time: O(n), Space: O(n)
vector<int> twoSumTwoPass(vector<int>& nums, int target) {
    unordered_map<int, int> mp;
    mp.reserve(nums.size());
    for (int i = 0; i < (int)nums.size(); ++i) mp[nums[i]] = i;
    for (int i = 0; i < (int)nums.size(); ++i) {
        int c = target - nums[i];
        auto it = mp.find(c);
        if (it != mp.end() && it->second != i) return { i, it->second };
    }
    return {};
}

// Sort-based two pointers: build (value,index) pairs and sort
// Time: O(n log n), Space: O(n)
vector<int> twoSumSort(vector<int>& nums, int target) {
    vector<pair<int, int>> pairs;
    pairs.reserve(nums.size());
    for (int i = 0; i < (int)nums.size(); ++i) pairs.emplace_back(nums[i], i);
    sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) { return a.first < b.first; });

    int l = 0, r = (int)pairs.size() - 1;
    while (l < r) {
        int sum = pairs[l].first + pairs[r].first;
        if (sum == target) return { pairs[l].second, pairs[r].second };
        if (sum < target) ++l; else --r;
    }
    return {};
}

int main() {

    cout << "--- Day 1: Hash Map Debugging (C++) ---\n";

	// CASE A: Standard Input/Output with Custom Parsing
    
    // A-1. CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	// A-2. Prompt for list of integers and parse them into a vector
	cout << "Enter a list of integers (space-separated): ";
    string inputLine;
    if (!getline(cin, inputLine)) return 0;
    if (inputLine.empty() || inputLine.find_first_not_of(" \t\r\n") == string::npos) {
        cout << "No list of integers provided\n";
        return 0;
    }
    // Custom Input Parsing: Converting string stream into a vector
    vector<int> nums;
    stringstream ss(inputLine);
    int number;
    while (ss >> number) {
        nums.push_back(number);
    }

    // A-3. Prompt for target and parse it
    cout << "Enter target value: ";
    string targetLine;
    if (!getline(cin, targetLine)) return 0;
    if (targetLine.empty() || targetLine.find_first_not_of(" \t\r\n") == string::npos) {
        cout << "No target provided\n";
        return 0;
    }
    stringstream ts(targetLine);
    int target;
    if (!(ts >> target)) {
        cout << "Invalid target\n";
        return 0;
    }

	// A-4. Call the twoSum function
    auto result = twoSum(nums, target);

	// CASE B: Predefined Test Cases (Uncomment to use)
	// You can comment out the above input section and uncomment the following test cases to run predefined inputs.
    /*
	// B-1. Predefined Test Cases
    vector<int> testNums1 = { 2, 7, 11, 15 };
    int target1 = 9;

    vector<int> testNums2 = { 3, 2, 4 };
    int target2 = 6;

    vector<int> testNums3 = { 3, 5, 1, 4, -8 };
    int target3 = 5;

    vector<int> testNums4 = { 3, 4, 9, 6, 4 };
    int target4 = 8;

    vector<int> testNums5 = { 4, -2, 5, 0, 6, 3, 2, 7 };
    int target5 = 1;

	// B-2. Call the twoSum function with a predefined test case
    auto result = twoSum(testNums5, target5);
    */

	// Output the result
    if (result.size() == 2) {
        cout << "Result Indices: [" << result[0] << ", " << result[1] << "]\n";
    }
    else {
        cout << "No solution found\n";
    }

    // Pause the console (Windows)
	cout << "Press Enter to exit:";
    cin.get();
    return 0;
}
