/*
 * LeetCode Problem 3: Longest Substring Without Repeating Characters
 *
 * Given a string `s`, find the length of the longest substring without repeating characters.
 *
 * Example 1:
 * Input: "abcabcbb"
 * Output: 3  (one longest substring is "abc")
 *
 * Example 2:
 * Input: "bbbbb"
 * Output: 1  (one longest substring is "b")
 *
 * Example 3:
 * Input: "pwwkew"
 * Output: 3  (one longest substring is "wke")
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Brute-force (`LengthOfLongestSubstringBruteForce`)
    - What: Enumerate every substring [i, j] and check for duplicates using a `HashSet<char>`.
    - Time: O(n^3) (enumerate O(n^2) × check O(n)); Space: O(min(n, |charset|)) for the temporary set.
    - Pros: Simple and useful for correctness/testing.
    - Cons: Extremely inefficient for large inputs.

    2) Sliding-window with frequency counts (`LengthOfLongestSubstringSlidingWindow`)
    - What: Maintain a window [left, right] and a `Dictionary<char,int>` of counts; expand right and shrink left while duplicates exist.
    - Time: O(n); Space: O(min(n, |charset|)).
    - Pros: Linear time, works for arbitrary character sets.
    - Cons: Shrinking the window one-by-one can add overhead.

    3) Sliding-window optimized (jump `left`) (`LengthOfLongestSubstringSlidingWindowOptimized`)
    - What: Track the next index for each character and set `left = Math.Max(left, nextIndex)` on repeats so `left` can jump forward.
    - Time: O(n); Space: O(min(n, |charset|)).
    - Pros: Fewer pointer moves and typically faster in practice.

    4) Sliding-window optimized plus (fixed-size array for ASCII) (`LengthOfLongestSubstringSlidingWindowOptimizedPlus`)
    - What: Use a fixed `int[] lastIndex` (e.g., size 256) to store next indices for ASCII characters.
    - Time: O(n); Space: O(1) (fixed-size table) for ASCII.
    - Pros: Lowest overhead and fastest for ASCII inputs.
    - Cons: Needs modification/fallback for full Unicode support.

    Complexity summary:
    - Brute-force: Time O(n^3), Space O(min(n, |charset|))
    - Sliding-window variants: Time O(n), Space O(min(n, |charset|)) (optimized plus: O(1) for fixed alphabets)
*/
using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Enter a string to find the length of the longest substring without duplicate characters (or press Enter to use default examples): ");
        string? input = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(input))
        {
            int r = LengthOfLongestSubstringBruteForce(input);
            Console.WriteLine("Length of longest substring without duplicate characters (Brute Force): " + r);
            r = LengthOfLongestSubstringSlidingWindow(input);
            Console.WriteLine("Length of longest substring without duplicate characters (Sliding Window): " + r);
            r = LengthOfLongestSubstringSlidingWindowOptimized(input);
            Console.WriteLine("Length of longest substring without duplicate characters (Sliding Window Optimized): " + r);
            r = LengthOfLongestSubstringSlidingWindowOptimizedPlus(input);
            Console.WriteLine("Length of longest substring without duplicate characters (Sliding Window Optimized Plus): " + r);
        }
        else
        {
            // Default examples

            // Example 1
            string input1 = "abcabcbb";
            int r1 = LengthOfLongestSubstringBruteForce(input1);
            Console.WriteLine("Length of longest substring in \"" + input1 + "\" without duplicate characters (Brute Force): " + r1);
            r1 = LengthOfLongestSubstringSlidingWindow(input1);
            Console.WriteLine("Length of longest substring in \"" + input1 + "\" without duplicate characters (Sliding Window): " + r1);
            r1 = LengthOfLongestSubstringSlidingWindowOptimized(input1);
            Console.WriteLine("Length of longest substring in \"" + input1 + "\" without duplicate characters (Sliding Window Optimized): " + r1);
            r1 = LengthOfLongestSubstringSlidingWindowOptimizedPlus(input1);
            Console.WriteLine("Length of longest substring in \"" + input1 + "\" without duplicate characters (Sliding Window Optimized Plus): " + r1);
            Console.WriteLine();

            // Example 2
            string input2 = "bbbbb";
            int r2 = LengthOfLongestSubstringBruteForce(input2);
            Console.WriteLine("Length of longest substring in \"" + input2 + "\" without duplicate characters (Brute Force): " + r2);
            r2 = LengthOfLongestSubstringSlidingWindow(input2);
            Console.WriteLine("Length of longest substring in \"" + input2 + "\" without duplicate characters (Sliding Window): " + r2);
            r2 = LengthOfLongestSubstringSlidingWindowOptimized(input2);
            Console.WriteLine("Length of longest substring in \"" + input2 + "\" without duplicate characters (Sliding Window Optimized): " + r2);
            r2 = LengthOfLongestSubstringSlidingWindowOptimizedPlus(input2);
            Console.WriteLine("Length of longest substring in \"" + input2 + "\" without duplicate characters (Sliding Window Optimized Plus): " + r2);
            Console.WriteLine();

            // Example 3
            string input3 = "pwwkew";
            int r3 = LengthOfLongestSubstringBruteForce(input3);
            Console.WriteLine("Length of longest substring in \"" + input3 + "\" without duplicate characters (Brute Force): " + r3);
            r3 = LengthOfLongestSubstringSlidingWindow(input3);
            Console.WriteLine("Length of longest substring in \"" + input3 + "\" without duplicate characters (Sliding Window): " + r3);
            r3 = LengthOfLongestSubstringSlidingWindowOptimized(input3);
            Console.WriteLine("Length of longest substring in \"" + input3 + "\" without duplicate characters (Sliding Window Optimized): " + r3);
            r3 = LengthOfLongestSubstringSlidingWindowOptimizedPlus(input3);
            Console.WriteLine("Length of longest substring in \"" + input3 + "\" without duplicate characters (Sliding Window Optimized Plus): " + r3);
            Console.WriteLine();

            // Example 4
            string input4 = "abcdeafbdgcbb";
            int r4 = LengthOfLongestSubstringBruteForce(input4);
            Console.WriteLine("Length of longest substring in \"" + input4 + "\" without duplicate characters (Brute Force): " + r4);
            r4 = LengthOfLongestSubstringSlidingWindow(input4);
            Console.WriteLine("Length of longest substring in \"" + input4 + "\" without duplicate characters (Sliding Window): " + r4);
            r4 = LengthOfLongestSubstringSlidingWindowOptimized(input4);
            Console.WriteLine("Length of longest substring in \"" + input4 + "\" without duplicate characters (Sliding Window Optimized): " + r4);
            r4 = LengthOfLongestSubstringSlidingWindowOptimizedPlus(input4);
            Console.WriteLine("Length of longest substring in \"" + input4 + "\" without duplicate characters (Sliding Window Optimized Plus): " + r4);
            Console.WriteLine();
        }
    }

    // Brute-force approach (`LengthOfLongestSubstringBruteForce`)
    // Time complexity: O(n^3) — enumerate all substrings (O(n^2)) and check each for duplicates (O(n)).
    // Space complexity: O(min(n, |charset|)) for the temporary `HashSet<char>` used by `CheckRepetition`.
    // Explanation:
    // - Try every possible substring [i, j] and test whether it contains repeated characters.
    // - Uses a `HashSet<char>` to detect duplicates for each candidate substring.
    // Pros:
    // - Very simple and straightforward to implement.
    // - Easy to reason about and useful for correctness tests and tiny inputs.
    // Cons:
    // - Extremely inefficient for moderately large strings; not suitable for production on large inputs.
    // - Performs a lot of redundant work (re-checks overlapping substrings).
    public static int LengthOfLongestSubstringBruteForce(string s)
    {
        int n = s.Length;

        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                if (CheckRepetition(s, i, j))
                {
                    res = Math.Max(res, j - i + 1);
                }
            }
        }

        return res;
    }

    private static bool CheckRepetition(string s, int start, int end)
    {
        HashSet<char> chars = new HashSet<char>();

        for (int i = start; i <= end; i++)
        {
            char c = s[i];
            if (chars.TryGetValue(c, out char _))
            {
                return false;
            }
            //if (chars.Contains(c))
            //{
            //    return false;
            //}

            chars.Add(c);
        }

        return true;
    }

    // Sliding-window approach (frequency counts) (`LengthOfLongestSubstringSlidingWindow`)
    // Time complexity: O(n) — each character is added/removed from the window at most once.
    // Space complexity: O(min(n, |charset|)) for the `Dictionary<char,int>` tracking counts.
    // Explanation:
    // - Maintain a window [left, right] and a map of character counts.
    // - Expand `right`, increment count for `s[right]`.
    // - While a duplicate exists (count > 1), shrink window from `left` and decrement counts.
    // - Update max length after each expansion.
    // Pros:
    // - Linear time and easy to understand.
    // - Works for arbitrary character sets using a dynamic map.
    // Cons:
    // - Requires maintaining counts; slightly more overhead than index-jump optimized approaches.
    // - Shrinking the window one-by-one can cost extra operations when left must move far.
    public static int LengthOfLongestSubstringSlidingWindow(string s)
    {
        Dictionary<char, int> chars = new Dictionary<char, int>();

        int left = 0;
        int right = 0;

        int res = 0;
        while (right < s.Length)
        {
            char r = s[right];
            if (!chars.TryGetValue(r, out int _))
            {
                chars[r] = 0;
            }
            chars[r]++;

            while (chars[r] > 1)
            {
                char l = s[left];
                chars[l]--;
                left++;
            }

            res = Math.Max(res, right - left + 1);

            right++;
        }

        return res;
    }

    // Sliding-window optimized (store next index to jump left) (`LengthOfLongestSubstringSlidingWindowOptimized`)
    // Time complexity: O(n) — each character processed once; `left` can jump forward without repeated shrinking.
    // Space complexity: O(min(n, |charset|)) for the `Dictionary<char,int>` mapping a character to its next index.
    // Explanation:
    // - Map each character to the index immediately after its last occurrence (`right + 1`).
    // - On seeing a repeated character, move `left = Math.Max(left, nextIndex)` to skip past the previous occurrence.
    // - Avoids repeated element-by-element shrinking of the window.
    // Pros:
    // - Very efficient in practice; fewer pointer moves than the frequency-count sliding window.
    // - Simple and fast while remaining general for Unicode (when using `Dictionary<char,int>`).
    // Cons:
    // - Requires storing the "next index" mapping; slightly less intuitive than basic sliding window for beginners.
    // - Still uses a dictionary for large character sets (memory proportional to distinct chars).
    public static int LengthOfLongestSubstringSlidingWindowOptimized(string s)
    {
        Dictionary<char, int> charToNextIndex = new Dictionary<char, int>();
        int maxlen = 0;
        int left = 0;
        
        for (int right = 0; right < s.Length; right++)
        {
            if (charToNextIndex.TryGetValue(s[right], out int nextIndex))
            {
                left = Math.Max(left, nextIndex);
            }

            maxlen = Math.Max(maxlen, right - left + 1);
            charToNextIndex[s[right]] = right + 1;
        }
        return maxlen;
    }

    // Sliding-window optimized plus (fixed-size array for ASCII) (`LengthOfLongestSubstringSlidingWindowOptimizedPlus`)
    // Time complexity: O(n) — linear scan with constant-time index lookups.
    // Space complexity: O(1) — fixed-size array (256) for ASCII; treats array size as a constant.
    // Explanation:
    // - Use a fixed `int[] lastIndex` initialized to -1 (or store next index as `right + 1`).
    // - For ASCII characters, update `left = lastIndex[ci]` when `lastIndex[ci] >= left`, then set `lastIndex[ci] = right + 1`.
    // - Offers best performance for ASCII inputs; includes a comment/fallback for non-ASCII characters.
    // Pros:
    // - Fastest and lowest-overhead option for ASCII or small fixed alphabets.
    // - Constant-space (independent of input length) with very low per-character work.
    // Cons:
    // - Not suitable for arbitrary Unicode input without modification (would need a larger map or fallback).
    // - Uses a fixed-size table that may be wasteful for tiny alphabets or insufficient for large code points.
    public static int LengthOfLongestSubstringSlidingWindowOptimizedPlus(string s)
    {
        const int SIZE = 256; // use 128 for strict ASCII, 256 for extended ASCII
        int[] lastIndex = new int[SIZE];
        for (int i = 0; i < SIZE; i++) lastIndex[i] = -1;

        int maxlen = 0;
        int left = 0;

        for (int right = 0; right < s.Length; right++)
        {
            int ci = s[right];
            if (ci < SIZE)
            {
                if (lastIndex[ci] >= left)
                {
                    left = lastIndex[ci];
                }
            }
            else
            {
                // For non-ASCII characters you can either:
                // - expand to a larger array (not recommended for sparse Unicode),
                // - or use a Dictionary<char,int> fallback here.
                // Simple fallback: reset window (this is suboptimal for Unicode inputs)
                left = right + 1;
            }

            maxlen = Math.Max(maxlen, right - left + 1);
            lastIndex[ci] = right + 1;

        }

        return maxlen;
    }

}