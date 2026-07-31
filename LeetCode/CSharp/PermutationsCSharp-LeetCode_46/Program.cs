/*
 * LeetCode Problem 46: Permutations
 *
 * Given an array of distinct integers `nums`, return all possible permutations.
 *
 * Examples:
 *  - Input: [1,2,3] -> Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *  - Input: [0,1]   -> Output: [[0,1],[1,0]]
 *  - Input: [1]     -> Output: [[1]]
 *  - Input: []      -> Output: [] (empty input returns an empty list)
 *
 * Implementation overview:
 *  - Approach: Backtracking (DFS). Iterate over `nums`, skip values already present in the
 *    current permutation, append a value, recurse to the next position, then remove the value
 *    (backtrack) to explore other branches.
 *
 * Time complexity: O(n * n!) where n = nums.Length.
 * Space complexity: O(n * n!) for the output plus O(n) recursion stack and temporary buffers.
 *
 * Notes:
 *  - This implementation assumes `nums` contains distinct integers (no duplicate handling).
 *
 * Unit tests:
 *  - NUnit tests for `Permute` are in the `PermutationsCSharp-LeetCode_46-TESTS` project.
 */

using System;
using System.Collections.Generic;

namespace Project
{ 
    public class Program
    {
        static void Main(string[] args)
        {
            Console.Write("--- Permutations - LeetCode 46 - Backtraking (C#) ---");

            Console.Write("Enter a list of distinct integers (or press Enter to use default examples): ");
            string? input = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(input))
            {
                string[] tokens = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                int[] nums = Array.ConvertAll(tokens, int.Parse);

                var output = Permute(nums);
                Console.Write("[");
                foreach (var group in output)
                {
                    Console.Write($"[{string.Join(",", group)}]");
                }
                Console.Write("]");
            }
            else
            {
                Console.WriteLine("");
                var input1 = new int[] { 1, 2, 3 };
                var output1 = Permute(input1);
                Console.WriteLine($"Example 1: [{string.Join(",", input1)}]");
                Console.Write("Output: [");
                foreach (var group in output1)
                {
                    Console.Write($"[{string.Join(",", group)}]");
                }
                Console.WriteLine("]");

                Console.WriteLine("");
                var input2 = new int[] { 0, 1 };
                var output2 = Permute(input2);
                Console.WriteLine($"Example 2: [{string.Join(",", input2)}]");
                Console.Write("Output: [");
                foreach (var group in output2)
                {
                    Console.Write($"[{string.Join(",", group)}]");
                }
                Console.WriteLine("]");

                Console.WriteLine("");
                var input3 = new int[] { 1 };
                var output3 = Permute(input3);
                Console.WriteLine($"Example 3: [{string.Join(",", input3)}]");
                Console.Write("Output: [");
                foreach (var group in output3)
                {
                    Console.Write($"[{string.Join(",", group)}]");
                }
                Console.WriteLine("]");

            }
        }

        // Method to generate all permutations for an array of distinct integers (LeetCode 46)
        // Time complexity: O(n * n!) where n = nums.Length.
        // Space complexity: O(n * n!) for output + O(n) recursion stack.
        // Approach: Backtracking (choose -> explore -> un-choose). Returns an empty list for empty input.
        public static IList<IList<int>> Permute(int[] nums)
        {
            var output = new List<IList<int>>();
            if (nums.Length == 0) return output;

            void BackTracking(List<int> current)
            {
                //Base case
                if (current.Count == nums.Length)
                {
                    output.Add(new List<int>(current));
                    return;
                }

                // Loop
                foreach (var num in nums)
                {
                    if (!current.Contains(num))
                    {
                        current.Add(num);           // Choose
                        BackTracking(current);    // Explore
                        current.RemoveAt(current.Count - 1); // Un-choose (backtrack)
                    }
                }
            }

            BackTracking(new List<int>());
            return output;
        }

    }
}