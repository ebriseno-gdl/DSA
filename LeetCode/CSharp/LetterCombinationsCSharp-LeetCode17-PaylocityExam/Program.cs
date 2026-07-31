/*
 * LeetCode Problem 17: Letter Combinations of a Phone Number
 *
 * Given a string containing digits from 2-9 inclusive, return all possible letter
 * combinations that the number could represent. The order of the output does not matter.
 *
 * Examples:
 *  - Input: "23" -> Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *  - Input: ""   -> Output: []  (empty input returns an empty list)
 *  - Input: "7"  -> Output: ["p","q","r","s"]
 *
 * Implementation overview:
 *  - Approach: Backtracking (DFS) using a fixed mapping from digits '2'..'9' to letters.
 *  - Time complexity: O(4^N * N) where N = digits.Length.
 *  - Space complexity: O(4^N * N) for the output plus O(N) recursion stack and temporary buffers.
 *
 * Notes:
 *  - This implementation assumes input contains only digits '2'..'9' (no additional validation).
 *
 * Unit tests:
 *  - Unit tests for `LetterCombinations` are located in the
 *    `LetterCombinationsCSharp-LeetCode17-PaylocityExam-TESTS` project.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace Project
{
    public class MainClass
    {
        static void Main(string[] args)
        {
            Console.WriteLine("--- Letter Combinations of a Phone Number - LeetCode 17 - Backtracking (C#) ---");

            Console.Write("Enter a string containing digits from 2-9 inclusiv (or press Enter to use default examples): ");
            string? input = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(input))
            {
                var output = LetterCombinations(input);
                Console.WriteLine($"Output: {string.Join(", ", output)}");
            }
            else 
            {
                // Default examples                 
                List<string> testcases = new List<string> { "23", "32", "662", "", "5" };
                foreach (var digits in testcases)
                {
                    Console.WriteLine("Input: " + digits);
                    var output = LetterCombinations(digits);
                    Console.WriteLine($"Output: {string.Join(", ", output)}");
                }
            }
        }

        // Method to generate all possible letter combinations for a digit string (LeetCode 17)
        // Time complexity: O(4^N * N), where N = digits.Length.
        //   - Each digit maps to at most 4 letters, so there are up to 4^N combinations.
        //   - Constructing each combination takes O(N) time to append/copy the characters.
        // Space complexity: O(4^N * N) for the output plus O(N) recursion stack and temporary StringBuilder.
        // Explanation: Use a fixed mapping from digits '2'..'9' to their letters and a backtracking (DFS)
        // approach to build combinations. At each position choose a letter, recurse to the next digit,
        // and then undo the choice (backtrack). Edge cases: return an empty list for empty input and
        // assume input contains only digits '2'..'9' (no validation performed here).
        public static IList<string> LetterCombinations(string digits)
        {
            if (string.IsNullOrEmpty(digits)) return new List<string>();

            var output = new List<string>();

            Dictionary<char, string> mapDigitToLetters = new Dictionary<char, string>()
            {
                { '2', "abc" },
                { '3', "def" },
                { '4', "ghi" },
                { '5', "jkl" },
                { '6', "mno" },
                { '7', "pqrs" },
                { '8', "tuv" },
                { '9', "wxyz" }
            };


            void Backtracking(int idx, StringBuilder current)
            {
                // Base case
                if (idx == digits.Length)
                {
                    output.Add(current.ToString());
                    return;
                }

                string letters = mapDigitToLetters[digits[idx]];
                foreach (char letter in letters)
                {
                    current.Append(letter);     // Choose
                    Backtracking(idx + 1, current); // Explore
                    current.Length--;           // Backtrack - remove last character, because it was completed a branch
                }
            }

            Backtracking(0, new StringBuilder());
            return output;
        }
    }
}
