/*
 * LeetCode Problem 121: Best Time to Buy and Sell Stock
 *
 * Given an array `prices` where `prices[i]` is the price of a given stock on the i-th day,
 * find the maximum profit you can achieve by buying on one day and selling on another later day.
 * Return the maximum profit (0 if no profitable transaction is possible).
 *
 * Example 1:
 * Input: [7, 1, 5, 3, 6, 4]
 * Output: 5
 *
 * Example 2:
 * Input: [7, 6, 4, 3, 1]
 * Output: 0
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Brute-force approach (`MaxProfitBruteForce`)
    - What: Consider every pair of days (buy i, sell j with j > i) and compute profit = prices[j] - prices[i].
    - Pros: Simple and easy to reason about.
    - Cons: Time complexity O(n^2) — not suitable for large inputs.

    2) One-pass approach (`MaxprofitOnePass`)
    - What: Scan once while maintaining the minimum price seen so far and the maximum profit achievable.
    - Pros: Time O(n), Space O(1) — optimal and practical.
    - Cons: Solves only the single-transaction variant of the problem.

    Complexity summary:
    - Brute-force: Time O(n^2), Space O(1)
    - One-pass: Time O(n), Space O(1)
*/
using System;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Enter a list of prices separated by spaces (or press Enter to use default examples): ");
        string? line = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(line))
        {
            string[] tokens = line.Split(' ');
            int[] prices = Array.ConvertAll(tokens, int.Parse);
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices)} (Brute Force): {MaxProfitBruteForce(prices)}");
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices)} (One Pass): {MaxprofitOnePass(prices)}");
        }
        else
        {
            // Default example

            // Example 1
            int[] prices1 = { 7, 1, 5, 3, 6, 4 };
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices1)} (Brute Force): {MaxProfitBruteForce(prices1)}");
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices1)} (One Pass): {MaxprofitOnePass(prices1)}");

            // Example 2
            int[] prices2 = { 7, 6, 4, 3, 1 };
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices2)} (Brute Force): {MaxProfitBruteForce(prices2)}");
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices2)} (One Pass): {MaxprofitOnePass(prices2)}");

            // Example 3
            int[] prices3 = { 4, 7, 6, 3, 4, 4 };
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices3)} (Brute Force): {MaxProfitBruteForce(prices3)}");
            Console.WriteLine($"Max profit of prices {string.Join(", ", prices3)} (One Pass): {MaxprofitOnePass(prices3)}");
        }
    }

    // Brute-force approach (MaxProfitBruteForce)
    // Time complexity: O(n^2), where n is the number of prices.
    // Space complexity: O(1) additional space.
    // Explanation:
    // - Consider every possible pair of buy (i) and sell (j) with j > i and compute profit = prices[j] - prices[i].
    // - Track the maximum profit seen. If all pairs yield non-positive profit, return 0.
    // - Pros: Simple and straightforward; easy to reason about and verify.
    // - Cons: Quadratic time makes it unsuitable for large inputs.
    public static int MaxProfitBruteForce(int[] prices)
    {
        int maxProfit = 0;
        for (int i = 0; i < prices.Length -1 ; i++)
        {
            for (int j = i + 1; j < prices.Length; j++)
            {
                int profit = prices[j] - prices[i];
                if (profit > maxProfit)
                {
                    maxProfit = profit;
                }
            }
        }
        return maxProfit;
    }

    // One-pass (single scan) approach (MaxprofitOnePass)
    // Time complexity: O(n), where n is the number of prices.
    // Space complexity: O(1) additional space.
    // Explanation:
    // - Maintain the minimum price seen so far while scanning the array from left to right.
    // - For each price, compute the profit if sold at the current price (current - minPrice) and update maxProfit if larger.
    // - Update minPrice when a new lower price is encountered.
    // - Pros: Linear time and constant extra space; best practical solution for this problem.
    // - Cons: None significant for this problem; relies on the guarantee of single buy/sell transaction.
    public static int MaxprofitOnePass(int[] prices)
    {
        int minPrice = int.MaxValue;
        int maxProfit = 0;
        for (int i = 0; i < prices.Length; i++)
        {
            if (prices[i] < minPrice)
            {
                minPrice = prices[i];
            }
            else if (prices[i] - minPrice > maxProfit)
            {
                maxProfit = prices[i] - minPrice;
            }
        }
        return maxProfit;
    }
}