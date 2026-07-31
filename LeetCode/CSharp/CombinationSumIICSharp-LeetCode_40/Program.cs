/*
 * LeetCode Problem 40: Combination Sum II
 *
 * Given a collection of candidate numbers (`candidates`) that may contain duplicates,
 * find all unique combinations in `candidates` where the candidate numbers sum to `target`.
 * Each number in `candidates` may be used at most once in the combination.
 *
 * Examples:
 *  - Input: candidates = [10,1,2,7,6,1,5], target = 8
 *    Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
 *  - Input: candidates = [2,5,2,1,2], target = 5
 *    Output: [[1,2,2],[5]]
 *  - Input: candidates = [0,0,0], target = 0
 *    Output: [[0,0,0]]
 *
 * Implementation overview:
 *  - Approach: Backtracking (DFS) with sorting + pruning + duplicate skipping.
 *    Sort `candidates` to allow early pruning (break when candidate > remaining)
 *    and to skip duplicates at the same recursion depth.
 *  - Choose a candidate, recurse with the next index (i + 1) because each element is used once,
 *    then remove the candidate (backtrack) to explore other combinations.
 *
 * Time complexity: exponential in general; effective pruning reduces the search space.
 * Space complexity: O(k * C) for output (k = avg combination length, C = number of combinations)
 *                   plus O(n) recursion stack and temporary buffers.
 *
 * Notes:
 *  - Duplicate candidates are handled by skipping equal elements at the same recursion depth.
 *  - Unit tests are located in the `CombinationSumIICSharp-LeetCode_40-TESTS` project.
 */

using System;
using System.Collections.Generic;

namespace Project
{
    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("--- Combination Sum II - LeetCode 40 - Backtracking (C#) ---");

            Console.Write("Enter a list of candidate numbers that might coontain duplicates (or press Enter to use default examples): ");
            string? input = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(input))
            {
                string[] tokens = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                int[] nums = Array.ConvertAll(tokens, int.Parse);

                /// A-2. Prompt for target and parse it
                Console.Write("Enter target integer: ");
                string? targetInput = Console.ReadLine();
                if (!int.TryParse(targetInput, out int target))
                {
                    Console.WriteLine("Invalid target. Please enter a valid integer.");
                    return;
                }

                var output = CombinationSum2(nums, target);

                Console.Write("[");
                foreach (var group in output)
                {
                    Console.Write($"[{string.Join(",", group)}]");
                }
                Console.Write("]");
            }
            else
            {
                // Default examples
                var testCases = new List<(int[] nums, int target)>
                {
                    (new int[] { 10, 1, 2, 7, 6, 1, 5 }, 8),
                    (new int[] { 2, 5, 2, 1, 2 }, 5),
                    (new int[] { 1, 1, 2, 2, 3 }, 4),
                    (new int[] { 1, 2, 3 }, 7),
                    (new int[] { 0, 0, 0 }, 0)
                };

                foreach (var (nums, target) in testCases)
                {
                    Console.WriteLine($"Input: [{string.Join(",", nums)}], Target: {target}");

                    var output = CombinationSum2(nums, target);

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

        // Generate all unique combinations that sum to `target` (LeetCode 40).
        // Time complexity: exponential; improved by sorting, pruning and duplicate skipping.
        // Space complexity: O(k * C) for result storage + O(n) recursion stack.
        // Approach:
        //  - Sort `candidates` to enable early pruning and duplicate detection.
        //  - Use backtracking: iterate candidates starting at `idx`, skip duplicates when
        //    `i > idx && candidates[i] == candidates[i - 1]`.
        //  - If a candidate exceeds the remaining target, break the loop (pruning).
        //  - Recurse with `i + 1` because each element may be used at most once.
        // Returns a list of unique combinations (each combination is a list of integers).
        public static IList<IList<int>> CombinationSum2(int[] candidates, int target)
        {
            var output = new List<List<int>>();
            Array.Sort(candidates);
            //Console.WriteLine($"Candidates Sorted: [{string.Join(",", candidates)}]");

            void Backtracking(int idx, List<int> curr, int remain)
            {
                if (remain == 0)
                {
                    output.Add(new List<int>(curr));
                    return;
                }
                else if (remain < 0)
                {
                    return;
                }

                for (int i = idx; i <= candidates.Length - 1; i++)
                {
                    // Prune: if current candidate exceeds remaining target, stop the loop
                    if (candidates[i] > remain) break;

                    // Skip duplicates at the same recursion depth
                    if (i > idx && candidates[i] == candidates[i - 1])
                    {
                        continue;
                    }

                    curr.Add(candidates[i]);        // choose the current candidate
                    Backtracking(i + 1, curr, remain - candidates[i]); // explore further with the next candidates
                    curr.RemoveAt(curr.Count - 1);  // unchoose the current candidate (backtrack)
                }
            }

            Backtracking(0, new List<int>(), target);
            return output.Cast<IList<int>>().ToList();
        }
    }
}