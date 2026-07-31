/*
 * LeetCode Problem 11: Container With Most Water
 *
 * Given n non-negative integers a1, a2, ..., an where each represents a point at coordinate (i, ai).
 * n vertical lines are drawn such that the two endpoints of line i are at (i, 0) and (i, ai).
 * Find two lines, which together with the x-axis form a container, such that the container contains the most water.
 *
 * Example 1:
 * Input: [1,8,6,2,5,4,8,3,7]
 * Output: 49
 *
 * Example 2:
 * Input: [1,1]
 * Output: 1
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Brute-force approach (`MaxAreaBruteForde`)
    - What: Evaluate every pair of lines (i, j) and compute area = min(height[i], height[j]) * (j - i).
    - Pros: Straightforward and easy to implement; useful for small inputs and correctness checks.
    - Cons: Inefficient for large arrays due to quadratic time.

    2) Two-pointer approach (`MaxAreaTwoPointer`)
    - What: Use two pointers (`left` and `right`) initialized at the array ends; compute area and move the pointer at the shorter line inward.
    - Pros: Optimal linear-time solution (O(n)) with constant extra space.
    - Cons: Requires the two-pointer insight; slightly less obvious than brute force.

    Complexity summary:
    - Brute-force: Time O(n^2), Space O(1)
    - Two-pointer: Time O(n), Space O(1)
*/
using System;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Enter a list of heights separated by spaces (or press Enter to use default examples): ");
        string? line = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(line))
        {
            string[] tokens = line.Split(' ');
            int[] heights = Array.ConvertAll(tokens, int.Parse);
            Console.WriteLine($"Max area (Brute Force): {MaxAreaBruteForde(heights)}");
            Console.WriteLine($"Max area (Two Pointer): {MaxAreaTwoPointer(heights)}");
        }
        else
        {
            // Default example

            // Example 1
            int[] heights1 = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
            Console.WriteLine($"Max area (Brute Force): {MaxAreaBruteForde(heights1)}");
            Console.WriteLine($"Max area (Two Pointer): {MaxAreaTwoPointer(heights1)}");

            // Example 2
            int[] heights2 = { 1, 1 };
            Console.WriteLine($"Max area (Brute Force): {MaxAreaBruteForde(heights2)}");
            Console.WriteLine($"Max area (Two Pointer): {MaxAreaTwoPointer(heights2)}");
        }
    }

    /*
        Brute-force approach (`MaxAreaBruteForde`)
        - What: Evaluate every pair of lines (i, j) and compute area = min(height[i], height[j]) * (j - i).
        - Pros: Straightforward and easy to implement; good for small inputs or correctness checks.
        - Cons: Examines all pairs, so it's inefficient for large arrays.

        Complexity:
        - Time: O(n^2) — nested loops over the height array.
        - Space: O(1) additional space.

        Explanation:
        - Iterate i from 0 to n-1 and j from i+1 to n-1, compute the area for each pair, and keep the maximum found.
    */
    static int MaxAreaBruteForde(int[] height)
    {
        int maxArea = 0;
        for (int i = 0; i < height.Length; i++)
        {
            for (int j = i + 1; j < height.Length; j++)
            {
                int currentArea = Math.Min(height[i], height[j]) * (j - i);
                maxArea = Math.Max(maxArea, currentArea);
            }
        }
        return maxArea;
    }

    /*
        Two-pointer approach (`MaxAreaTwoPointer`)
        - What: Maintain two pointers (`left` and `right`) at the ends of the array and move the pointer at the shorter line inward.
        - Pros: Optimal linear-time solution with constant extra space.
        - Cons: Slightly more subtle reasoning about which pointer to move, but optimal for production.

        Complexity:
        - Time: O(n) — each pointer moves at most n steps.
        - Space: O(1) additional space.

        Explanation:
        - Start with `left = 0` and `right = n - 1`. At each step compute area and update the maximum.
          Move the pointer that points to the shorter height, because only that movement can possibly increase the area compared to the current pair.
    */
    static int MaxAreaTwoPointer(int[] height)
    {
        int left = 0;
        int right = height.Length - 1;
        int maxArea = 0;
        while (left < right)
        {
            int currentArea = Math.Min(height[left], height[right]) * (right - left);
            maxArea = Math.Max(maxArea, currentArea);
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }
}