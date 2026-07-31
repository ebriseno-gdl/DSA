/*
 * LeetCode Problem 20: Valid Parentheses
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 *
 * An input string is valid if:
 *  1) Open brackets are closed by the same type of brackets.
 *  2) Open brackets are closed in the correct order.
 *
 * Example 1:
 * Input: "()"
 * Output: true
 *
 * Example 2:
 * Input: "([)]"
 * Output: false
 *
 * Example 3:
 * Input: "{[[]{}]}()()"
 * Output: true
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Stack-based approach (`IsValid`)
    - What: Scan the string left-to-right, push opening brackets onto a `Stack<char>`, and when encountering
      a closing bracket pop and compare against the expected opening bracket using a lookup `Dictionary<char,char>`.
    - Pros: Runs in O(n) time and uses O(n) additional space in the worst case (all opening brackets).
    - Cons: Requires an explicit stack allocation; however this is standard and efficient for this problem.

    Complexity summary:
    - Time: O(n), where n is the length of the input string.
    - Space: O(n) worst-case for the stack.
*/
using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Enter a string containing just the characters '(', ')', '{', '}', '[' and ']' to determine if it is valid: ");
        string? input = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(input))
        {
            // Validate allowed characters
            string allowed = "(){}[]";
            foreach (char c in input)
            {
                if (!allowed.Contains(c))
                {
                    Console.WriteLine("Input contains invalid characters. Only the characters '(', ')', '{', '}', '[' and ']' are allowed.");
                    return;
                }
            }

            bool isValid = IsValid(input);
            Console.WriteLine($"Is the string \"{input}\" valid? {isValid}");
        }
        else
        {
            // Default examples

            // Example 1
            string s1 = "({[]})";
            bool isValid1 = IsValid(s1);
            Console.WriteLine($"Is the string \"{s1}\" valid? {isValid1}");

            // Example 2
            string s2 = "([)]";
            bool isValid2 = IsValid(s2);
            Console.WriteLine($"Is the string \"{s2}\" valid? {isValid2}");

            // Example 3
            string s3 = "{[[]{}]}()()";
            bool isValid3 = IsValid(s3);
            Console.WriteLine($"Is the string \"{s3}\" valid? {isValid3}");

        }

    }

    // Stack-based validation (LeetCode 20: Valid Parentheses)
    // Time complexity: O(n), where n is the length of the input string (single pass).
    // Space complexity: O(n) additional space in the worst case for the stack (all opening brackets).
    // Explanation:
    // - Use a `Stack<char>` to track opening brackets as we scan the string left-to-right.
    // - Use a dictionary that maps closing brackets to their corresponding opening brackets (e.g., ')' -> '(').
    // - For each character:
    //   - If it is a closing bracket, pop the top element from the stack (or use a sentinel if empty) and compare it with the expected opening bracket; return false on mismatch.
    //   - Otherwise (opening bracket), push it onto the stack.
    // - After processing all characters, the string is valid iff the stack is empty.
    public static bool IsValid(string s)
    {
        Stack<char> stack = new Stack<char>();
        Dictionary<char, char> pairs = new Dictionary<char, char>
        {
            { ')', '(' },
            { '}', '{' },
            { ']', '[' }
        };
        foreach (char c in s)
        {
            if (pairs.ContainsKey(c))
            {
                char topElement = stack.Count > 0 ? stack.Pop() : '#';
                if (topElement != pairs[c])
                {
                    return false;
                }
            }
            else
            {
                stack.Push(c);
            }
        }
        return stack.Count == 0;
    }
}