/*
 * LeetCode Problem 1: Two Sum
 * 
 * Given an array of integers nums and an integer target, 
 * return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution,
 * and you may not use the same element twice.
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
    Implementations overview (what each does, differences, pros/cons)

    1) Single-pass hash map (`TwoSum`)
    - What: Iterate once; for each element compute complement = target - nums[i],
        check dictionary for complement, otherwise store current value->index.
    - Pros: Average O(n) time, returns as soon as a match is found (early exit),
        low constant factors in practice.
    - Cons: O(n) extra space; dictionary operations have rare worst-case O(n)
        (pathological hash collisions) so theoretical worst-case O(n^2).

    2) Two-pass hash map (`TwoSum_TwoPass`)
    - What: First build a value->index map for all elements, then iterate again
        to check for complements (ensuring indices differ).
    - Pros: Average O(n) time; straightforward; similar memory use to single-pass.
    - Cons: No early return during the map-build phase (so may do more work before
        checking); still uses O(n) space and shares same hash-collision worst case.

    3) Sort-based two-pointer (`TwoSum_Sort`)
    - What: Create (value,index) pairs, sort by value, then use two pointers
        from both ends to find the pair that sums to target.
    - Pros: Deterministic worst-case time O(n log n) (no hash-collision concerns);
        useful when predictable behavior under adversarial inputs is required.
    - Cons: Slower than hash on average due to sorting; uses O(n) extra space to
        keep pairs (or modifies input if sorted in-place, which loses original order).

    When to choose:
    - Use single-pass hash map (`TwoSum`) for typical cases and interviews (fastest avg).
    - Use two-pass if you prefer a clearer separation of build/lookup phases (no major perf gain).
    - Use sort-based (`TwoSum_Sort`) when worst-case time guarantees or avoiding hash-based
    attacks is important, or when you can tolerate the O(n log n) cost.

    Complexity summary:
    - Single-pass / two-pass (hash): average O(n) time, O(n) space; worst-case O(n^2) under
    pathological hash behavior.
    - Sort-based: O(n log n) time, O(n) space (or O(1) extra if sorting destructively and index loss allowed).
*/

using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("--- Day 1: Hash Mapp Debugging(C#) ---");

        // CASE A: Standard Input/Output with Custom Parsing

        // A-1. Prompt for list of integers and parse them into a vector
        Console.Write("Enter space-separated integers for the array: ");
        string? input = Console.ReadLine();
        if (string.IsNullOrEmpty(input)) return;

        // Splitting an input line of space-separated integers into an array
        string[] tokens = input.Split(' ');
        int[] nums = Array.ConvertAll(tokens, int.Parse);

        /// A-2. Prompt for target and parse it
        Console.Write("Enter target integer: ");
        string? targetInput = Console.ReadLine();
        if (!int.TryParse(targetInput, out int target))
        {
            Console.WriteLine("Invalid target. Please enter a valid integer.");
            return;
        }

        // A-3. Call the twoSum function
        int[] result = TwoSum(nums, target);
        //int[] result = TwoSum_TwoPass(nums, target);
        //int[] result = TwoSum_Sort(nums, target);

        // CASE B: Predefined Test Cases (Uncomment to use)
        // You can comment out the above input section and uncomment the following test cases to run predefined inputs.
        /*
        // B-1. Predefined Test Cases
        int[] testNums1 = { 2, 7, 11, 15 };
        int target1 = 9;

        int[] testNums2 = { 3, 2, 4 };
        int target2 = 6;

        int[] testNums3 = { 3, 5, 1, 4, -8 };
        int target3 = 5;

        int[] testNums4 = { 3, 4, 9, 6, 4 };
        int target4 = 8;

        int[] testNums5 = { 4, -2, 5, 0, 6, 3, 2, 7 };
        int target5 = 1;

        // B-2. Call the twoSum function with a predefined test case
        int[] result = TwoSum(testNums5, target5);
        //int[] result = TwoSum_TwoPass(testNums5, target5);
        //int[] result = TwoSum_Sort(testNums5, target5);
        */

        // Output the result
        if (result.Length == 2)
            Console.WriteLine($"Result Indices: [{result[0]}, {result[1]}]");
        else
            Console.WriteLine("No two-sum solution found for the provided input.");

        // Keep the console window open
        Console.Write("Press Enter to exit:");
        Console.ReadLine();
    }

    /*
     TwoSum - single-pass hash map approach (Dictionary<int,int>)

     Complexity guarantees:
     - Time (average / expected): O(n)
       * Each of the n elements performs at most one dictionary lookup and one insert.
       * Dictionary operations are O(1) on average for integer keys -> total O(n).
     - Time (best): O(1)
       * If the matching pair is found immediately, the method returns early.
     - Time (worst): O(n^2)
       * In rare/adversarial cases with pathological hash collisions, individual
         lookups/inserts can be O(n), which yields O(n^2) overall.
     - Space: O(n) auxiliary
       * The dictionary may store up to one entry per input element.
    */
    public static int[] TwoSum(int[] nums, int target)
    {
        Dictionary<int, int> seenNumbers = new Dictionary<int, int>();

        for (int i = 0; i < nums.Length; i++)
        {
            int complement = target - nums[i];

            // If we found the matchiing pair, return their indexes instantly
            if (seenNumbers.TryGetValue(complement, out int index))
            {
                return new int[] { index, i };
            }

            // save the current number and its index in our map
            seenNumbers[nums[i]] = i;
        }

        return new int[] { };  // Return an empty array if no solution is found

    }

    // Two-pass hash map: build map then search
    // Avg time: O(n), Space: O(n)
    public static int[] TwoSum_TwoPass(int[] nums, int target)
    {
        var map = new System.Collections.Generic.Dictionary<int, int>(nums.Length);
        for (int i = 0; i < nums.Length; i++)
            map[nums[i]] = i;

        for (int i = 0; i < nums.Length; i++)
        {
            int complement = target - nums[i];
            if (map.TryGetValue(complement, out int j) && j != i)
                return new int[] { i, j };
        }

        return Array.Empty<int>();
    }

    // Sort-based two pointers: sort value/index pairs then move pointers
    // Time: O(n log n), Space: O(n)
    public static int[] TwoSum_Sort(int[] nums, int target)
    {
        var pairs = new (int value, int index)[nums.Length];
        for (int i = 0; i < nums.Length; i++)
            pairs[i] = (nums[i], i);

        Array.Sort(pairs, (a, b) => a.value.CompareTo(b.value));

        int l = 0, r = pairs.Length - 1;
        while (l < r)
        {
            int sum = pairs[l].value + pairs[r].value;
            if (sum == target) return new int[] { pairs[l].index, pairs[r].index };
            if (sum < target) l++; else r--;
        }

        return Array.Empty<int>();
    }

}