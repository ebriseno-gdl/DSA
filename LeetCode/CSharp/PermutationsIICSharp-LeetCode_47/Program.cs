/*
 * LeetCode Problem 47: Permutations II
 *
 * Given an array of integers `nums` that might contain duplicates, return all possible unique permutations.
 *
 * Examples:
 *  - Input: [1,1,2] -> Output: [[1,1,2],[1,2,1],[2,1,1]]
 *  - Input: [1,2,3] -> Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *  - Input: [0,0,0] -> Output: [[0,0,0]]
 *  - Input: []      -> Output: [] (empty input returns an empty list)
 *
 * *** PermuteUnique method generates all unique permutations of the input array, handling duplicates correctly.
 * Implementation overview:
 *  - Approach: Backtracking (DFS) with a frequency/count map to avoid generating duplicate permutations.
 *    Build a dictionary of value -> remaining count, choose a value when its count > 0, decrement the count,
 *    recurse, then restore the count on backtrack.
 *
 * Time complexity: O(n * n!) in the worst case (when all elements are distinct).
 * Space complexity: O(n * n!) for the output plus O(n) recursion stack and O(k) for the frequency map (k = distinct values).
 *
 * Notes:
 *  - This implementation returns only unique permutations even when `nums` contains duplicates.
 *  - Uses a frequency dictionary to track remaining occurrences of each value.
 * 
 * xxxx PermuteUniqueA, PermuteUniqueB, and PermuteUniqueC are incorrect implementations that fail to handle duplicates properly.
 *      they are included for educational purposes to illustrate common pitfalls in generating unique permutations.
 *      
 * Unit tests:
 *  - NUnit tests for `PermuteUnique` are in the `PermutationsIICSharp-LeetCode_47-TESTS` project.
 */
using System;
using System.Collections.Generic;

namespace Project
{

    public class Solution
    {

        static void Main(string[] args)
        {
            Console.WriteLine("--- Permutations II - LeetCode 47 - Backtracking (C#) ---");

            Console.Write("Enter a list of integers that might coontain duplicates (or press Enter to use default examples): ");
            string? input = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(input))
            {
                string[] tokens = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                int[] nums = Array.ConvertAll(tokens, int.Parse);

                var output = PermuteUnique(nums);
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
                var testCases = new List<int[]>
                {
                    new int[] { 1, 1, 2 },
                    new int[] { 1, 2, 3 },
                    new int[] { 0, 0, 0},
                    new int[] { 1, 2, 2 },
                    new int[] { 1, 1, 1, 2 }
                };
                foreach (var nums in testCases)
                {
                    Console.WriteLine($"Input: [{string.Join(",", nums)}]");

                    var outputs = new Dictionary<string, IList<IList<int>>>
                    {
                        { "PermuteUnique-Good-", PermuteUnique(nums) },
                        { "PermuteUniqueA-Bad-", PermuteUniqueA(nums) },
                        { "PermuteUniqueB-Bad-", PermuteUniqueB(nums) },
                        { "PermuteUniqueC-Bad-", PermuteUniqueC(nums) }
                    };

                    foreach(var kvp in outputs)
                    {
                        string methodName = kvp.Key;
                        var output = kvp.Value;
                        Console.Write($"Output from {methodName}: [");
                        foreach (var group in output)
                        {
                            Console.Write($"[{string.Join(",", group)}]");
                        }
                        Console.WriteLine("]");
                    }

                    Console.WriteLine();
                }
            }
        }

        // Generate all unique permutations for an array that may contain duplicates (LeetCode 47).
        // Time complexity: O(n * n!) worst-case (distinct values).
        // Space complexity: O(n * n!) output + O(n) recursion stack + O(k) frequency map.
        // Approach: Backtracking using a dictionary<int,int> of counts to ensure each value is used at most its remaining count,
        // producing unique permutations without post-filtering duplicate results.
        public static IList<IList<int>> PermuteUnique(int[] nums)
        {
            var output = new List<List<int>>();
            var countNums = new Dictionary<int, int>();

            foreach (var num in nums)
            {
                if (!countNums.ContainsKey(num))
                {
                    countNums.Add(num, 0);
                }
                countNums[num]++;
            }

            void Backtracking(List<int> curr)
            {
                if (curr.Count == nums.Length)
                {
                    output.Add(new List<int>(curr));
                    return;
                }

                foreach (var entry in countNums)
                {
                    int num = entry.Key;
                    int count = entry.Value;
                    if (count == 0)
                        continue;
                    curr.Add(num);
                    countNums[num]--;
                    Backtracking(curr);
                    curr.RemoveAt(curr.Count - 1);
                    countNums[num]++;
                }
            }

            Backtracking(new List<int>());
            return output.Cast<IList<int>>().ToList();
        }

        /*
         * NOTE: `PermuteUniqueA` — INCORRECT for LeetCode 47 (Permutations II)
         *
         * What it does:
         *  - Uses value-based containment (`curr.Contains(num)`) when choosing elements.
         *
         * Distinct characteristic / why it fails:
         *  - Prevents using the same value more than once regardless of how many occurrences exist in `nums`.
         *  - As a result, it cannot place duplicate values multiple times in a single permutation and
         *    therefore produces incomplete / wrong permutations for inputs with repeated elements
         *    (e.g., [1,1,2] will not produce permutations that contain two `1`s).
         *
         * Recommendation:
         *  - Do NOT use this for Problem 47. Use the canonical `PermuteUnique` method which tracks counts.
         */
        public static IList<IList<int>> PermuteUniqueA(int[] nums)
        {
            var output = new List<List<int>>();

            void Backtracking(List<int> curr)
            {
                if (curr.Count == nums.Length)
                {
                    output.Add(new List<int>(curr));
                    return;
                }

                foreach (var num in nums)
                {
                    if (!curr.Contains(num)) 
                    {
                        curr.Add(num);
                        Backtracking(curr);
                        curr.RemoveAt(curr.Count - 1);
                    }
                }
            }

            Backtracking(new List<int>());
            return output.Cast<IList<int>>().ToList();
        }

        /*
         * NOTE: `PermuteUniqueB` — INCORRECT for LeetCode 47 (Permutations II)
         *
         * What it does:
         *  - Attempts an index-driven backtracking loop with a `idx` parameter and uses `curr.Contains` to avoid reuse.
         *
         * Distinct characteristic / why it fails:
         *  - Advances the recursion with `Backtracking(idx + 1, ...)` regardless of which loop index `i` was chosen.
         *  - Mixes index progression with element selection, causing incorrect branching: some permutations are missed
         *    and duplicate-avoidance logic still relies on value containment (which is wrong for duplicates).
         *
         * Recommendation:
         *  - This variant is flawed conceptually for generating unique permutations from arrays with duplicates.
         *  - Use `PermuteUnique` which uses a frequency map and correct recursion control.
         */
        public static IList<IList<int>> PermuteUniqueB(int[] nums)
        {
            var output = new List<List<int>>();

            void Backtracking(int idx, List<int> curr)
            {
                if (curr.Count == nums.Length)
                {
                    output.Add(new List<int>(curr));
                    return;
                }

                for (int i = idx; i <= nums.Length-1; i++)
                {
                    if (!curr.Contains(nums[i])) 
                    {
                        curr.Add(nums[i]);
                        Backtracking(idx + 1, curr);
                        curr.RemoveAt(curr.Count - 1);
                    }
                }
            }

            Backtracking(0, new List<int>());
            return output.Cast<IList<int>>().ToList();
        }

        /*
         * NOTE: `PermuteUniqueC` — INCORRECT for LeetCode 47 (Permutations II)
         *
         * What it does:
         *  - Uses an index-based loop and recurses with `Backtracking(i + 1, curr)`.
         *
         * Distinct characteristic / why it fails:
         *  - The `i + 1` recursion pattern produces combination-like behavior (preserves increasing indices)
         *    rather than generating all orderings (permutations). It therefore omits permutations that reorder
         *    previously chosen elements.
         *  - It also uses `curr.Contains` to avoid reuse, so duplicates are not handled properly.
         *
         * Recommendation:
         *  - This method behaves like a combinations generator and is not suitable for Problem 47.
         *  - Use `PermuteUnique` which correctly tracks counts and generates unique permutations.
         */
        public static IList<IList<int>> PermuteUniqueC(int[] nums)
        {
            var output = new List<List<int>>();

            void Backtracking(int idx, List<int> curr)
            {
                if (curr.Count == nums.Length)
                {
                    output.Add(new List<int>(curr));
                    return;
                }

                for (int i = idx; i <= nums.Length - 1; i++)
                {
                    if (!curr.Contains(nums[i])) 
                    {
                        curr.Add(nums[i]);
                        Backtracking(i + 1, curr);
                        curr.RemoveAt(curr.Count - 1);
                    }
                }
            }

            Backtracking(0, new List<int>());
            return output.Cast<IList<int>>().ToList();
        }
    }
}
