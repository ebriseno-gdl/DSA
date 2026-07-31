/*
 * LeetCode Problem 216: Combination Sum III
 *
 * Given two integers `k` and `n`, return all possible combinations of `k` distinct numbers
 * (chosen from 1..9) that add up to `n`. Each number may be used at most once.
 *
 * Examples:
 *  - Input: k = 3, n = 7  -> Output: [[1,2,4]]
 *  - Input: k = 3, n = 9  -> Output: [[1,2,6],[1,3,5],[2,3,4]]
 *  - Input: k = 4, n = 1  -> Output: [] (no valid combinations)
 *
 * Implementation overview:
 *  - Approach: Backtracking (DFS) over the fixed domain 1..9 using an increasing start index.
 *    This ensures each value is used at most once and combinations are generated in ascending order.
 *  - Maintain a `curr` list and remaining sum `remain`. When `curr.Count == k && remain == 0`
 *    add a copy of `curr` to the result set.
 *  - Prune branches when `curr.Count == k` and `remain != 0`, or when `remain < 0`.
 *  - Iterate `i` from `idx` to `9` and recurse with `i + 1` to avoid reusing numbers.
 *
 * Time complexity: Exponential in general (depends on branching and number of valid combinations);
 *                  pruning and the small fixed domain (1..9) limit the search space.
 * Space complexity: O(k * C) for result storage (k = combination length, C = number of combinations)
 *                   plus O(k) recursion stack and temporary buffers.
 *
 * Notes:
 *  - The small domain (1..9) makes iteration efficient and eliminates the need for duplicate checks.
 *  - Unit tests are located in the `CombinationSumIIICSharp-LeetCode_216-TESTS` project.
 */
using System;
using System.Collections.Generic;

namespace Project
{

    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("--- Combination Sum III - LeetCode 216 - Backtracking (C#) ---");
        
            Console.Write("Enter the number of integers to combine (k) (or press Enter to use default examples): ");
            string? kInput = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(kInput))
            {
                if (!int.TryParse(kInput, out int k))
                {
                    Console.WriteLine("Invalid k. Please enter a valid integer.");
                    return;
                }

                Console.Write("Enter the target sum (n): ");
                string? nInput = Console.ReadLine();
                if (!int.TryParse(nInput, out int n))
                {
                    Console.WriteLine("Invalid n. Please enter a valid integer.");
                    return;
                }

                var output = CombinationSum3(k, n);

                Console.Write("Output: [");
                foreach (var group in output)
                {
                    Console.Write($"[{string.Join(",", group)}]");
                }
                Console.WriteLine("]");

            }
            else
            {
                // Default examples
                var testCases = new List<(int n, int k)>
                    {
                        (3, 7),
                        (3, 9),
                        (4, 1)
                    };

                foreach (var (k, n) in testCases)
                {
                    Console.WriteLine($"Input: k: {k}, n: {n}");

                    var output = CombinationSum3(k, n);

                    Console.Write($"Output: [");
                    foreach (var group in output)
                    {
                        Console.Write($"[{string.Join(",", group)}]");
                    }
                    Console.WriteLine("]");

                    Console.WriteLine();
                }
            }
        }

        // Generate all unique combinations of `k` distinct numbers (1..9) that sum to `n` (LeetCode 216).
        // Time complexity: exponential in general (depends on branching and number of valid combinations);
        //                  effective pruning (remaining < next candidate or reached k elements) reduces work.
        // Space complexity: O(k * C) for result storage (k = combination length, C = number of combinations)
        //                   plus O(k) recursion stack and temporary buffers.
        //
        // Approach:
        //  - Use backtracking (DFS) over the fixed domain 1..9. Track the current combination `curr`, the
        //    next starting value `idx` and the remaining sum `remain`.
        //  - Stop exploring a branch when `curr.Count == k` and `remain != 0`, or when `remain < 0`.
        //  - When `curr.Count == k && remain == 0` add a copy of `curr` to `output`.
        //  - Use increasing `idx` and call `BackTracking(i + 1, ...)` so each number is used at most once and
        //    combinations are generated in ascending order (no duplicate combinations).
        //
        // Notes:
        //  - Domain is small (1..9), so iterating from `idx` to 9 is efficient and simple.
        //  - This implementation builds combinations in ascending order; no additional duplicate checks are required.
        public static IList<IList<int>> CombinationSum3(int k, int n)
        {
            var output = new List<IList<int>>();
        
            void BackTracking(int idx, List<int> curr, int remain)
            {
                //Base case
                if (curr.Count == k && remain == 0)
                {
                    output.Add(new List<int>(curr));
                    return;
                }
                else if (curr.Count == k || remain < 0)
                {
                    return;
                }

                // Loop
                for (int i = idx; i <= 9 && remain >= i; i++)
                {
                    curr.Add(i);                         // Choose
                    BackTracking(i+1, curr, remain - i);    // Explore
                    curr.RemoveAt(curr.Count - 1);          // Backtrack
                }
            }
            BackTracking(1, new List<int>(), n);
            return output;
        }

    }
}