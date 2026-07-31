/*
 * LeetCode Problem 49: Group Anagrams
 *
 * Given an array of strings strs, group the anagrams together. You can return the answer in any order.
 *
 * Example 1:
 * Input: ["eat","tea","tan","ate","nat","bat"]
 * Output: [["eat","tea","ate"],["tan","nat"],["bat"]]
 *
 * Example 2:
 * Input: [""]
 * Output: [[""]]
 *
 * Example 3:
 * Input: ["a"]
 * Output: [["a"]]
 *
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Sort-based key (`GroupAnagramsSortBased`)
    - What: For each word, sort its characters to produce a canonical key (e.g. "eat" -> "aet"),
      then group original words by that key in a dictionary.
    - Pros: Simple and easy to implement; works for arbitrary character sets.
    - Cons: Sorting each word costs O(K log K) per word (K = word length).

    2) Character-count key (`GroupAnagramsCountBased`)
    - What: For each word, compute a frequency/count signature (e.g. counts of 'a'..'z')
      and serialize that signature as the key for grouping.
    - Pros: Runs in O(K) per word (no sorting), better for longer words when alphabet is small.
    - Cons: Key construction and assumptions about the alphabet (here lowercase a-z).
           Slightly more complex to implement.

    Complexity summary:
    - Sort-based: Time O(N * K log K), Space O(N * K)
    - Count-based: Time O(N * K), Space O(N * K)
*/

using System;
using System.Collections.Generic;
using System.Text;

class Program
{
    static void Main(string[] args)
    {

        Console.Write("Enter a list of strings separated by spaces (or press Enter to use default examples): ");
        string? line = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(line))
        {
            var items = line
            .Split((char[]?)null, StringSplitOptions.RemoveEmptyEntries); // splits on whitespace

            var output = GroupAnagramsCountBased(items);
            foreach (var group in output)
            {
                Console.WriteLine($"[{string.Join(", ", group)}]");
            }
        }
        else
        {
            var input1 = new string[] { "eat", "tea", "tan", "ate", "nat", "bat" };
            var output1 = GroupAnagramsCountBased(input1);
            Console.WriteLine("Example 1:");
            foreach (var group in output1)
            {
                Console.WriteLine($"[{string.Join(", ", group)}]");
            }
            var input2 = new string[] { "" };
            var output2 = GroupAnagramsCountBased(input2);
            Console.WriteLine("\nExample 2:");
            foreach (var group in output2)
            {
                Console.WriteLine($"[{string.Join(", ", group)}]");
            }
            var input3 = new string[] { "a" };
            var output3 = GroupAnagramsCountBased(input3);
            Console.WriteLine("\nExample 3:");
            foreach (var group in output3)
            {
                Console.WriteLine($"[{string.Join(", ", group)}]");
            }
        }
    }

    // Method to group anagrams together using sorted character representation as the key
    // Time complexity: O(N * K log K), where N is the number of strings and K is the maximum length of a string
    // Space complexity: O(N * K), where N is the number of strings and K is the maximum length of a string
    // Explanation: We use a dictionary to group anagrams by their sorted character representation.
    //              For each word, we sort its characters to create a key and add the original word
    //              to the corresponding anagram group in the dictionary.
    //              Finally, we convert the dictionary values to a list of lists for the final output.
    public static IList<IList<string>> GroupAnagramsSortBased(string[] strs)
    {
        // Use a dictionary to group anagrams by their sorted character representation
        //Dictionary<string, List<string>> anagramGroups = new Dictio
        //nary<string, List<string>>();
        Dictionary<string, List<string>> anagramGroups = new Dictionary<string, List<string>>();
        foreach (string word in strs)
        {
            // Sort the characters of the word to create a key for anagram grouping
            char[] charArray = word.ToCharArray();
            Array.Sort(charArray);
            string key = new string(charArray);

            // Add the original word to the corresponding anagram group in the dictionary
            if (!anagramGroups.TryGetValue(key, out List<string>? list))
            {
                list = new List<string>();
                anagramGroups[key] = list;
            }
            anagramGroups[key].Add(word);
            //if (!anagramGroups.ContainsKey(key))
            //{
            //    anagramGroups[key] = new List<string>();
            //}
            //anagramGroups[key].Add(word);
        }
        // Convert the dictionary values to a list of lists for the final output
        return new List<IList<string>>(anagramGroups.Values);
        /*
        var result = new List<IList<string>>();
        foreach (var group in anagramGroups.Values)
        {
            result.Add(group);
        }
        return result;
        */
    }

    // Method to group anagrams together using character count as the key
    // Time complexity: O(N * K), where N is the number of strings and K is the maximum length of a string
    // Space complexity: O(N * K), where N is the number of strings and K is the maximum length of a string
    // Explanation: We use a dictionary to group anagrams by their character count representation.
    //              For each word, we create a character count array to represent the frequency of each character,
    //              and build a key as a string representation of the character counts. We then add the original word
    //              to the corresponding anagram group in the dictionary.
    //              Finally, we convert the dictionary values to a list of lists for the final output.
    // Note: This method can be more efficient than sorting for longer strings, as it runs in O(K) time for each word, where K is the length of the word.
    //       However, it may use more space due to the character count array and the string representation of the key.
    //       This method assumes that the input strings consist of lowercase letters only. If the input can contain uppercase letters or other characters, the character count array and key generation would need to be adjusted accordingly.
    //       In practice, the sorting method is often simpler and sufficient for most cases, while the character count method can be beneficial for specific scenarios with longer strings or a limited character set.
    public static IList<IList<string>> GroupAnagramsCountBased(string[] strs)
    {
        // Use a dictionary to group anagrams by their sorted character representation
        //Dictionary<string, List<string>> anagramGroups = new Dictionary<string, List<string>>();
        Dictionary<string, List<string>> anagramGroups = new Dictionary<string, List<string>>();
        foreach (string word in strs)
        {
            // Create a character count array to represent the frequency of each character in the word
            int[] charCount = new int[26]; // Assuming only lowercase letters
            foreach (char c in word)
            {
                charCount[c - 'a']++;
            }

            // Create a key for anagram grouping based on the character count array
            // Build the key as a string representation of the character counts, separated by a special character
            StringBuilder keyBuilder = new StringBuilder();
            for (int i = 0; i < charCount.Length; i++)
            {
                keyBuilder.Append((char)(i + 'a'));
                keyBuilder.Append(charCount[i]);
            }
            string key = keyBuilder.ToString();

            // Add the original word to the corresponding anagram group in the dictionary
            if (!anagramGroups.TryGetValue(key, out List<string>? list))
            {
                list = new List<string>();
                anagramGroups[key] = list;
            }
            anagramGroups[key].Add(word);
            //if (!anagramGroups.ContainsKey(key))
            //{
            //    anagramGroups[key] = new List<string>();
            //}
            //anagramGroups[key].Add(word);
        }
        // Convert the dictionary values to a list of lists for the final output
        return new List<IList<string>>(anagramGroups.Values);
        /*
        var result = new List<IList<string>>();
        foreach (var group in anagramGroups.Values)
        {
            result.Add(group);
        }
        return result;
        */
    }
}

