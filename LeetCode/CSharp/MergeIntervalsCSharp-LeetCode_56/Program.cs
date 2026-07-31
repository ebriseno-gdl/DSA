/*
 * LeetCode Problem 56: Merge Intervals
 *
 * Given an array of intervals where intervals[i] = [start_i, end_i], merge all
 * overlapping intervals and return an array of the non-overlapping intervals
 * that cover all the intervals in the input.
 *
 * Example 1:
 * Input:  [(1,3), (2,6), (8,10), (15,18)]
 * Output: [(1,6), (8,10), (15,18)]
 *
 * Example 2:
 * Input:  [(1,4), (4,5)]
 * Output: [(1,5)]
 *
 * Example 3:
 * Input:  [(2,5), (1,4), (9,10), (6,9)]
 * Output: [(1,5), (6,10)]
 */

/*
    Implementations overview (what each does, differences, pros/cons)

    1) Sort-then-merge (`MergeBrutForceWithSort`)  BEST ONE
    - What: Sort intervals by start time, then do a single linear pass to merge overlapping intervals.
    - Pros: Efficient in practice; time dominated by sort (O(n log n)), then O(n) merging.
    - Cons: Requires sorting; uses additional collection for output.

    2) Incremental pairwise merge (`MergeBrutForce`)
    - What: Iterate input intervals and try to merge each into an existing merged interval by checking overlap.
    - Pros: Simple and direct to implement.
    - Cons: Worst-case O(n^2) time when many comparisons are required; less efficient on large inputs.
            Fails in some cases (see example 7).

    3) Graph / connected-components (`MergeBruteForceConnectedComponents`)
    - What: Build an undirected graph where nodes are intervals and edges connect overlapping intervals.
            Find connected components (DFS) and merge each component by taking min(start) and max(end).
    - Pros: Models transitive overlap explicitly and is easy to reason about.
    - Cons: Building the graph requires O(n^2) pairwise checks and may use O(n^2) space in dense cases.

    Complexity summary:
    - `MergeBrutForceWithSort`: Time O(n log n), Space O(n)
    - `MergeBrutForce`: Time O(n^2) worst-case, Space O(n)
    - `MergeBruteForceConnectedComponents`: Time O(n^2) to build graph (plus traversal), Space O(n + e) (e = edges, worst O(n^2))
*/
using System;


class Program
{
    // `graph`: adjacency list mapping each interval node to its overlapping neighbors.
    // - Key: `int[]` interval (start, end). Value: list of adjacent intervals that overlap.
    // - Populated by `BuildGraph`; cleared before reuse.
    // - Consumed by DFS traversal when building connected components.
    static IDictionary<int[], List<int[]>> graph =
        new Dictionary<int[], List<int[]>>();

    // `nodesInComp`: component -> intervals mapping.
    // - Key: component id (int). Value: list of `int[]` intervals belonging to that component.
    // - Filled by `MarkComponentDFS` / `BuildComponents`.
    // - Used to compute the merged interval for each connected component.
    static IDictionary<int, List<int[]>> nodesInComp =
        new Dictionary<int, List<int[]>>();

    // `visited`: set of interval nodes already seen during DFS.
    // - Prevents revisiting nodes and stops infinite traversal loops.
    // - Cleared before building components for a fresh run.
    static HashSet<int[]> visited = new HashSet<int[]>();

    static void Main(string[] args)
    {
        Console.Write("Enter the array of intervals (or press Enter to use default examples) (example of input: \'(2,5) (1,4) (9,10) (6,9)\' ): ");
        string? line = Console.ReadLine();
        if (!string.IsNullOrWhiteSpace(line))
        {
            // Split the input string into tokens based on spaces, removing any empty entries
            string[] tokens = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            // Create a list to hold the parsed intervals
            var intervals = new List<int[]>();
            // Process each token to extract the start and end values of the intervals
            foreach (string token in tokens)
            {
                string trimmed = token.Trim('(', ')');
                string[] parts = trimmed.Split(',');
                if (parts.Length == 2 && int.TryParse(parts[0], out int start) && int.TryParse(parts[1], out int end))
                {
                    intervals.Add(new int[] { start, end });
                }
                else
                {
                    Console.WriteLine($"Invalid interval format: {token}");
                    return;
                }
            }
            // Convert the list of intervals to a 2D array for easier processing
            int[][] input = intervals.ToArray();

            var output = MergeBrutForceWithSort(input);

            PrintIntervals("Output", output);

        }
        else
        {
            // Default example

            // Example 1:
            int[][] input1 = new int[][]
            {
                new int[] { 2, 5 },
                new int[] { 1, 4 },
                new int[] { 9, 10 },
                new int[] { 6, 9 }
            };
            PrintIntervals("Input 1", input1);
            var output1A = MergeBrutForce(input1);
            PrintIntervals("Output 1", output1A);
            var output1B = MergeBruteForceConnectedComponents(input1);
            PrintIntervals("Output 1", output1B);
            var output1C = MergeBrutForceWithSort(input1);
            PrintIntervals("Output 1", output1C);

            // Example 2:
            int[][] input2 = new int[][]
            {
                new int[] { 1, 3 },
                new int[] { 2, 6 },
                new int[] { 8, 10 },
                new int[] { 15, 18 }
            };
            Console.WriteLine(""); 
            PrintIntervals("Input 2", input2);
            var output2A = MergeBrutForce(input2);
            PrintIntervals("Output 2", output2A);
            var output2B = MergeBruteForceConnectedComponents(input2);
            PrintIntervals("Output 2", output2B);
            var output2C = MergeBrutForceWithSort(input2);
            PrintIntervals("Output 2", output2C);

            // Example 3:
            int[][] input3 = new int[][]
            {
                new int[] { 1, 9 },
                new int[] { 2, 5 },
                new int[] { 19, 20 },
                new int[] { 10, 11 },
                new int[] { 12, 20 },
                new int[] { 0, 3 },
                new int[] { 0, 1 },
                new int[] { 0, 2 }
            };
            Console.WriteLine("");
            PrintIntervals("Input 3", input3);
            var output3A = MergeBrutForce(input3);
            PrintIntervals("Output 3", output3A);
            var output3B = MergeBruteForceConnectedComponents(input3);
            PrintIntervals("Output 3", output3B);
            var output3C = MergeBrutForceWithSort(input3);
            PrintIntervals("Output 3", output3C);

            // Example 4:
            int[][] input4 = new int[][]
            {
                new int[] { 1, 3 },
                new int[] { 2, 6 },
                new int[] { 8, 10 },
                new int[] { 15, 18 }
            };
            Console.WriteLine("");
            PrintIntervals("Input 4", input4);
            var output4A = MergeBrutForce(input4);
            PrintIntervals("Output 4", output4A);
            var output4B = MergeBruteForceConnectedComponents(input4);
            PrintIntervals("Output 4", output4B);
            var output4C = MergeBrutForceWithSort(input4);
            PrintIntervals("Output 4", output4C);

            // Example 5:
            int[][] input5 = new int[][]
            {
                new int[] { 1, 4 },
                new int[] { 4, 5 }
            };
            Console.WriteLine("");
            PrintIntervals("Input 5", input5);
            var output5A = MergeBrutForce(input5);
            PrintIntervals("Output 5", output5A);
            var output5B = MergeBruteForceConnectedComponents(input5);
            PrintIntervals("Output 5", output5B);
            var output5C = MergeBrutForceWithSort(input5);
            PrintIntervals("Output 5", output5C);

            // Example 6:
            int[][] input6 = new int[][]
            {
                new int[] { 4, 7 },
                new int[] { 1, 7 }
            };
            Console.WriteLine("");
            PrintIntervals("Input 6", input6);
            var output6A = MergeBrutForce(input6);
            PrintIntervals("Output 6", output6A);
            var output6B = MergeBruteForceConnectedComponents(input6);
            PrintIntervals("Output 6", output6B);
            var output6C = MergeBrutForceWithSort(input6);
            PrintIntervals("Output 6", output6C);

            // Example 7:
            int[][] input7 = new int[][]
            {
                new int[] { 2, 3 },
                new int[] { 4, 5 },
                new int[] { 6, 7 },
                new int[] { 8, 9 },
                new int[] { 1, 10 },
            };
            Console.WriteLine("");
            PrintIntervals("Input 7", input7);
            var output7A = MergeBrutForce(input7);
            PrintIntervals("Output 7", output7A);
            var output7B = MergeBruteForceConnectedComponents(input7);
            PrintIntervals("Output 7", output7B);
            var output7C = MergeBrutForceWithSort(input7);
            PrintIntervals("Output 7", output7C);

        }
    }

    // Brute-force with sorting approach (`MergeBrutForceWithSort`)
    // Time complexity: O(n log n) due to sorting (where n is number of intervals), then a linear pass to merge.
    // Space complexity: O(n) additional space for the output collection (plus O(log n) stack for Array.Sort in typical implementations).
    // Explanation:
    // - Sort intervals by start time.
    // - Iterate the sorted intervals once, appending non-overlapping intervals and merging overlapping ones by extending the end.
    // - Pros: Simple, efficient for large inputs because sorting makes merging linear after ordering.
    // - Cons: Requires sorting; not strictly in-place if output collection is separate.
    public static int[][] MergeBrutForceWithSort(int[][] intervals)
    {
        Console.WriteLine("Merging intervals using brute force with sorting...");
        Array.Sort(intervals, (a, b) => Comparer<int>.Default.Compare(a[0], b[0]));
        LinkedList<int[]> merged = new LinkedList<int[]>();
        foreach (int[] interval in intervals)
        {
            // if the list of merged intervals is empty or if the current
            // interval does not overlap with the previous, append it
            if (merged.Count == 0 || merged.Last.Value[1] < interval[0])
            {
                merged.AddLast(interval);
            }
            // otherwise, there is overlap, so we merge the current and previous
            // intervals
            else
            {
                merged.Last.Value[1] =
                    Math.Max(merged.Last.Value[1], interval[1]);
            }
        }

        return merged.ToArray();
    }

    // Brute-force pairwise merge approach (`MergeBrutForce`)
    // Time complexity: O(n^2) in the worst case because for each interval we may compare against many merged intervals.
    // Space complexity: O(n) additional space for the merged list (output).
    // Explanation:
    // - Iterate through each input interval and attempt to merge it with an existing merged interval by checking overlap.
    // - If it overlaps, update the existing merged interval's bounds; otherwise, append as a new merged interval.
    // - Pros: Straightforward and easy to implement; may be acceptable for small inputs.
    // - Cons: Poor worst-case performance (quadratic) when many intervals cause repeated scans of the merged list.
    public static int[][] MergeBrutForce(int[][] intervals)
    {
        Console.WriteLine("Merging intervals using brute force...");
        List<int[]> merged = new List<int[]>();
        foreach (int[] interval in intervals)
        {
            bool mergedFlag = false;
            for (int i = 0; i < merged.Count; i++)
            {
                if (merged[i][1] >= interval[0] && merged[i][0] <= interval[1])
                {
                    merged[i][0] = Math.Min(merged[i][0], interval[0]);
                    merged[i][1] = Math.Max(merged[i][1], interval[1]);
                    mergedFlag = true;
                    break;
                }
            }
            if (!mergedFlag)
            {
                merged.Add(interval);
            }
        }
        return merged.ToArray();
    }

    // Graph / connected-components approach (`MergeBruteForceConnectedComponents`)
    // Time complexity: O(n^2) to build the overlap graph (pairwise overlap checks). DFS and merging are O(n + e) where e is number of edges.
    // Space complexity: O(n + e) for the adjacency representation and component storage; in worst-case e = O(n^2).
    // Explanation:
    // - Build an undirected graph where each interval is a node and edges connect overlapping intervals.
    // - Find connected components (e.g., with DFS); intervals in the same component all overlap transitively.
    // - For each component, compute the merged interval by taking min(start) and max(end).
    // - Pros: Conceptually maps the merging problem to graph connectivity; useful to reason about transitive overlaps.
    // - Cons: Expensive to construct for large n (quadratic edges), and uses more memory in dense-overlap cases.
    public static int[][] MergeBruteForceConnectedComponents(int[][] intervals)
    {
        Console.WriteLine("Merging intervals using brute force by Connected Components...");

        // clear previous state before building a new graph/components
        graph.Clear();
        nodesInComp.Clear();
        visited.Clear();

        BuildGraph(intervals);
        BuildComponents(intervals);
        List<int[]> merged = new List<int[]>(); 
        for (int i = 0; i < nodesInComp.Count; i++)
        {
            merged.Add(MergeNodes(nodesInComp[i]));
        }

        return merged.ToArray();
    }

    // Check if two intervals overlap (inclusive).
    // Time complexity: O(1)
    // Space complexity: O(1)
    // Params:
    // - `a`: first interval as int[2] {start, end}
    // - `b`: second interval as int[2] {start, end}
    // Returns: true if intervals overlap or touch, false otherwise.
    // Notes: Uses the common inclusive-overlap condition `a[0] <= b[1] && b[0] <= a[1]`.
    private static bool Overlap(int[] a, int[] b)
    {
        return a[0] <= b[1] && b[0] <= a[1];
    }

    // Build an undirected adjacency list mapping each interval to all intervals that overlap it.
    // Time complexity: O(n^2) due to pairwise overlap checks (n = intervals.Length).
    // Space complexity: O(n + e) for the adjacency lists (e = number of overlap edges).
    // Params:
    // - `intervals`: input array of intervals.
    // Side effects:
    // - Populates the `graph` dictionary where each key is an interval and the value is the list of adjacent (overlapping) intervals.
    private static void BuildGraph(int[][] intervals)
    {
        foreach (var interval in intervals)
        {
            graph[interval] = new List<int[]>();
        }

        for (int i = 0; i < intervals.Length; i++)
        {
            for (int j = 0; j < intervals.Length; j++)
            {
                if (Overlap(intervals[i], intervals[j]))
                {
                    graph.TryGetValue(intervals[i], out var val);
                    if (val != null)
                    {
                        val.Add(intervals[j]);
                    }

                    graph.TryGetValue(intervals[j], out val);
                    if (val != null)
                    {
                        val.Add(intervals[i]);
                    }
                }
            }
        }
    }

    // Merge a collection of intervals that belong to the same connected component.
    // Time complexity: O(k) where k is number of nodes in `nodes`.
    // Space complexity: O(1) extra (returns a new int[2] representing merged interval).
    // Params:
    // - `nodes`: list of intervals in one connected component.
    // Returns: a single interval [minStart, maxEnd] that covers all `nodes`.
    private static int[] MergeNodes(List<int[]> nodes)
    {
        int minStart = nodes[0][0];
        foreach (var node in nodes)
        {
            minStart = Math.Min(minStart, node[0]);
        }

        int maxEnd = nodes[0][1];
        foreach (var node in nodes)
        {
            maxEnd = Math.Max(maxEnd, node[1]);
        }

        return new int[] { minStart, maxEnd };
    }

    // Iterative DFS to mark all intervals reachable from `start` as part of the same component.
    // Time complexity: O(n + e) over the traversal where e is number of edges visited.
    // Space complexity: O(n) for `visited` and stack in worst case.
    // Params:
    // - `start`: starting interval node.
    // - `stack`: stack used for iterative DFS (caller provides an empty Stack).
    // - `compNumber`: component identifier; visited nodes are added to `nodesInComp[compNumber]`.
    // Side effects:
    // - Marks visited intervals in `visited` and appends them to `nodesInComp[compNumber]`.
    private static void MarkComponentDFS(int[] start, Stack<int[]> stack,
                                  int compNumber)
    {
        stack.Push(start);
        while (stack.Count != 0)
        {
            int[] node = stack.Pop();
            if (!visited.Contains(node))
            {
                visited.Add(node);
                if (!nodesInComp.ContainsKey(compNumber))
                {
                    nodesInComp.Add(compNumber, new List<int[]>());
                }

                nodesInComp.TryGetValue(compNumber, out var val);
                val.Add(node);
                List<int[]> nodes = null;
                graph.TryGetValue(node, out nodes);
                foreach (var child in nodes)
                {
                    stack.Push(child);
                }
            }
        }
    }

    // Discover all connected components by iterating intervals and invoking DFS for unvisited nodes.
    // Time complexity: O(n + e) overall (dominated by graph traversal).
    // Space complexity: O(n + e) for component storage and visited state.
    // Params:
    // - `intervals`: input array of intervals to process.
    // Side effects:
    // - Fills `nodesInComp` with component -> list of intervals mappings.
    private static void BuildComponents(int[][] intervals)
    {
        int compNumber = 0;
        Stack<int[]> stack = new Stack<int[]>();
        foreach (var interval in intervals)
        {
            if (!visited.Contains(interval))
            {
                MarkComponentDFS(interval, stack, compNumber);
                compNumber++;
            }
        }
    }

    private static void PrintIntervals(string prompt, int[][] intervals)
    {
        Console.Write(prompt + ": ");
        foreach (var interval in intervals)
        {
            Console.Write($"({interval[0]},{interval[1]}) ");
        }
        Console.WriteLine("");
    }
}