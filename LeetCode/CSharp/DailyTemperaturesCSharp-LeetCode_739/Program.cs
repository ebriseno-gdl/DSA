/*
 * LeetCode Problem 739: Daily Temperatures
 *
 * Given an array `temperatures`, return an array `answer` such that `answer[i]` is the number of days
 * you have to wait after day `i` to get a warmer temperature. If there is no future day for which
 * this is possible, put `0` instead.
 *
 * Example 1:
 * Input:  [73, 74, 75, 71, 69, 72, 76, 73]
 * Output: [1, 1, 4, 2, 1, 1, 0, 0]
 *
 * Example 2:
 * Input:  [30, 40, 50, 60]
 * Output: [1, 1, 1, 0]
 *
 * Example 3:
 * Input:  [30, 60, 90]
 * Output: [1, 1, 0]
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Brute-force (`DailyTemperaturesBruteForce`)
    - What: For each day, scan forward to find the first future day with a strictly higher temperature.
    - Time complexity: O(n^2) in the worst case.
    - Space complexity: O(n) for the output array, O(1) extra workspace.
    - Pros: Simple and straightforward.
    - Cons: Quadratic time makes it impractical for large inputs.

    2) Monotonic stack (`DailyTemperaturesMonotonicStack`)
    - What: Maintain a monotonic decreasing stack of indices whose next warmer day is unknown.
      Iterate left-to-right; when the current day's temperature is higher than the temperature at the
      index on top of the stack, pop and set the answer for that index to (currentDay - index).
    - Time complexity: O(n), each index is pushed and popped at most once.
    - Space complexity: O(n) for the stack and O(n) for the output array.
    - Pros: Linear time and efficient for large inputs.
    - Cons: Slightly more complex logic than brute-force.

    Complexity summary:
    - Brute-force: Time O(n^2), Space O(n)
    - Monotonic stack: Time O(n), Space O(n)
*/
using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Enter a list of daily temperatures separated by spaces (or press Enter to use default examples): ");
        string? line = Console.ReadLine();
        if (!string.IsNullOrEmpty(line))
        {
            string[] tokens = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            int[] temperatures = Array.ConvertAll(tokens, int.Parse);

        }
        else
        {
            // Default example

            // Example 1
            int[] prices1 = { 73, 74, 75, 71, 69, 72, 76, 73 };
            int[] answer1A = DailyTemperaturesBruteForce(prices1);
            Console.WriteLine($"Answer to \'{string.Join(", ", prices1)}\' is \'{string.Join(", ", answer1A)}\'");
            int[] answer1B = DailyTemperaturesMonotonicStack(prices1);
            Console.WriteLine($"Answer to \'{string.Join(", ", prices1)}\' is \'{string.Join(", ", answer1B)}\'");

            // Example 2
            int[] prices2 = { 30, 40, 50, 60 };
            int[] answer2A = DailyTemperaturesBruteForce(prices2);
            Console.WriteLine($"Answer to \'{string.Join(", ", prices2)}\' is \'{string.Join(", ", answer2A)}\'");
            int[] answer2B = DailyTemperaturesMonotonicStack(prices2);
            Console.WriteLine($"Answer to \'{string.Join(", ", prices2)}\' is \'{string.Join(", ", answer2B)}\'");

            // Example 3
            int[] prices3 = { 30, 60, 90 };
            int[] answer3A = DailyTemperaturesBruteForce(prices3);
            Console.WriteLine($"Answer to \'{string.Join(", ", prices3)}\' is \'{string.Join(", ", answer3A)}\'");
            int[] answer3B = DailyTemperaturesMonotonicStack(prices3);
            Console.WriteLine($"Answer to \'{string.Join(", ", prices3)}\' is \'{string.Join(", ", answer3B)}\'");


        }
    
    }

    /* DailyTemperaturesBruteForce
     * Time complexity: O(n^2), where n is the number of days.
     * Space complexity: O(n) for the output array (answer). Uses O(1) additional workspace.
     * Description:
     * - For each day, scan forward through subsequent days to find the first day with a strictly higher temperature.
     * - Record the number of days waited (futureDay - day) in the answer array; leave 0 if none found.
     * - Simple, straightforward implementation that directly follows the problem statement.
     * Pros/Cons:
     * - Pros: Easy to implement and reason about.
     * - Cons: Quadratic time makes it impractical for large inputs.
     */
    public static int[] DailyTemperaturesBruteForce(int[] temperatures)
    {
        Console.WriteLine("DailyTemperaturesBruteForce...");
        int[] answer = new int[temperatures.Length];
        for (int day = 0; day < temperatures.Length-1; day++ )
        {
            for (int futureDay = day+1; futureDay < temperatures.Length; futureDay++)
            {
                if (temperatures[futureDay] > temperatures[day])
                {
                    answer[day] = futureDay - day;
                    break;
                }
            }

        }
        return answer;
    }

    /* DailyTemperaturesMonotonicStack
     * Time complexity: O(n), where n is the number of days.
     * Space complexity: O(n) for the stack and O(n) for the output array (answer).
     * Description:
     * - Use a monotonic decreasing stack that stores indices of days whose next warmer day is not yet found.
     * - Iterate days left-to-right; for each current day, pop indices while the current temperature is higher than
     *   the temperature at the index on top of the stack. For each popped index, set answer[index] = currentDay - index.
     * - Push the current day index onto the stack to await a future warmer day.
     * Pros/Cons:
     * - Pros: Linear time and efficient for large inputs.
     * - Cons: Slightly more complex logic than the brute-force approach.
     */
    public static int[] DailyTemperaturesMonotonicStack(int[] temperatures)
    {
        Console.WriteLine("DailyTemperaturesMonotonicStack...");
        int[] answer = new int[temperatures.Length];
        Stack<int> stack = new Stack<int>();

        for (int currDay = 0; currDay < temperatures.Length; currDay++)
        {
            int currTemp = temperatures[currDay];
            while (stack.Count() > 0 && temperatures[stack.Peek()] < currTemp)
            {
                int prevDay = stack.Pop();
                answer[prevDay] = currDay - prevDay;
            }
            stack.Push(currDay);
        }
        return answer;
    }
}