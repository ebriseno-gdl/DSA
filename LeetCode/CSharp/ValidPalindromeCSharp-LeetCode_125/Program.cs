/*
 * LeetCode Problem 125: Valid Palindrome
 *
 * Given a string s, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 * Example 1:
 * Input: "Red"
 * Output: false
 *
 * Example 2:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 *
 * Example 3:
 * Input: " "
 * Output: true
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Two-pointers approach (`IsPalindromeTwoPointers`)
    - What: Use two indices (left and right) moving toward the center, skipping non-alphanumeric characters,
      and compare characters case-insensitively.
    - Pros: Runs in O(n) time and uses O(1) additional space.
    - Cons: Slightly more logic to skip non-alphanumeric characters correctly.

    2) Normalize-and-compare-with-reverse (`IsPalindromeCmpWIthReverse`)
    - What: Build a normalized string containing only lowercase alphanumeric characters, then compare it with its reversed copy.
    - Pros: Simple and easy to understand.
    - Cons: Uses O(n) additional space for the normalized string and its reversed copy.

    Complexity summary:
    - Two-pointers: Time O(n), Space O(1)
    - Normalize-and-compare: Time O(n), Space O(n)
*/
using System;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Enter a string to check if it's a palindrome (or press Enter to use default examples): ");
        string? input = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(input))
        {
            PrintResult(input, IsPalindromeTwoPointers(input));
            PrintResult(input, IsPalindromeCmpWIthReverse(input));
        }
        else 
        {
            // Default examples
            
            // Example 1
            string input1 = "Red";
            PrintResult(input1, IsPalindromeTwoPointers(input1));
            PrintResult(input1, IsPalindromeCmpWIthReverse(input1));

            // Example 2
            string input2 = "A man, a plan, a canal: Panama";
            PrintResult(input2, IsPalindromeTwoPointers(input2));
            PrintResult(input2, IsPalindromeCmpWIthReverse(input2));

            // Example 3
            string input3 = " ";
            PrintResult(input3, IsPalindromeTwoPointers(input3));
            PrintResult(input3, IsPalindromeCmpWIthReverse(input3));

        }

    }

    // Two-pointers approach
    // Time complexity: O(n), where n is the length of the input string.
    // Space complexity: O(1) additional space (in-place pointers), ignoring input/output.
    // Explanation:
    // - Use two indices (left and right) that move toward the center.
    // - Skip non-alphanumeric characters for both pointers.
    // - Compare characters case-insensitively. If any pair differs, the string is not a palindrome.
    // - This method avoids allocating a new string and works in linear time with constant extra space.
    public static bool IsPalindromeTwoPointers(string s)
    {
        Console.WriteLine($"Checking if \"{s}\" is a palindrome using Two Pointers approach...");
        int left = 0;
        int right = s.Length - 1;
        while (left < right)
        {
            // Move left pointer to the next alphanumeric character
            while (left < right && !char.IsLetterOrDigit(s[left]))
            {
                left++;
            }
            // Move right pointer to the previous alphanumeric character
            while (left < right && !char.IsLetterOrDigit(s[right]))
            {
                right--;
            }
            // Compare characters (case-insensitive)
            if (char.ToLower(s[left]) != char.ToLower(s[right]))
            {
                return false; // Not a palindrome
            }
            left++;
            right--;
        }
        return true; // It's a palindrome
    }

    // Normalize-and-compare-with-reverse approach
    // Time complexity: O(n), where n is the length of the input string (building normalized + reversing).
    // Space complexity: O(n) additional space for the normalized string and its reversed copy.
    // Explanation:
    // - Construct a normalized string containing only lowercase alphanumeric characters.
    // - Create a reversed copy of the normalized string and compare them.
    // - This method is simple and straightforward but uses extra memory proportional to the input size.
    public static bool IsPalindromeCmpWIthReverse(string s)
    {
        Console.WriteLine($"Checking if \"{s}\" is a palindrome by comparing with its reverse...");
        // Normalize the string: remove non-alphanumeric characters and convert to lowercase
        var normalized = new StringBuilder();
        foreach (char c in s)
        {
            if (char.IsLetterOrDigit(c))
            {
                normalized.Append(char.ToLower(c));
            }
        }
        string normalizedStr = normalized.ToString();
        // Reverse the normalized string
        char[] charArray = normalizedStr.ToCharArray();
        Array.Reverse(charArray);
        string reversedStr = new string(charArray);
        // Compare the normalized string with its reverse
        return normalizedStr == reversedStr;
    }

    private static void PrintResult(string input, bool result)
    {
        if (result == true)
        { 
            Console.WriteLine($"\"{input}\" is a palindrome.");
        }
        else
        {
            Console.WriteLine($"\"{input}\" is not a palindrome.");
        }
    }
}