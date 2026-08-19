# N-Queens (LeetCode 51) — C# Implementations Overview

Short overview
- All implementations use row-by-row backtracking: choose a column for the current row, test for conflicts, recurse, and undo the placement. Conflict trackers (HashSet, bool arrays, or bitmasks) prune the search and reduce explored states.

Implementations (summary)
- `SolveNQueens1_JaggedHash`  
  Backtracking with a jagged `char[][]` board and `HashSet<int>` trackers for columns, main-diagonals and anti-diagonals. Easiest to read and debug; `HashSet` has more overhead.

- `SolveNQueens2_Array2D`  
  Same idea but uses a `char[,]` 2D array for slightly better locality. Trackers remain `HashSet<int>`.

- `SolveNQueens3_BoolArr`  
  Uses `bool[]` arrays for columns and diagonals (index-mapped). O(1) low-overhead checks without `HashSet` cost; needs diagonal index mapping.

- `SolveNQueens4_BitMask`  
  Uses integer bitmasks for columns/diagonals with a `char[,]` board for output. Very fast (bitwise ops) and minimal per-check cost; limited by integer bit width (use `long` for larger N).

- `SolveNQueens5_JaggedBM`  
  Hybrid: jagged `char[][]` board + bitmask trackers. Readable board representation combined with fast mask checks.

- `SolveNQueens6_Compact`  
  Mask-first, allocation-minimizing variant that builds rows on-the-fly and avoids storing a full board during search. Lowest memory churn and best runtime constants for typical N.

Which to use
- Best speed/memory: `SolveNQueens6_Compact`.  
- Best balance (clarity + performance): `SolveNQueens4_BitMask` / `SolveNQueens5_JaggedBM`.  
- Best for teaching/readability: `SolveNQueens1_JaggedHash` / `SolveNQueens2_Array2D`.

How conflict checks are performed (columns & diagonals)
- Common idea: a queen at (row, col) threatens
  - same column: `col`
  - main diagonal: `row - col`
  - anti-diagonal: `row + col`

- HashSet approach (`HashSet<int> cols, diags, antiDiags`)
  - Check: `if (cols.Contains(col) || diags.Contains(row - col) || antiDiags.Contains(row + col)) skip`
  - Mark/unmark on choose/unchoose: `cols.Add(col)` / `cols.Remove(col)` (same for diagonals).

- Bool array approach (`bool[] cols, bool[] diags, bool[] antiDiags`)
  - Map diagonals to non-negative indices:
    - main diagonal index = `row - col + (n - 1)` (range 0..2n-2)
    - anti diagonal index = `row + col` (range 0..2n-2)
  - Check: `if (cols[col] || diags[diagIdx] || antiDiags[antiIdx]) skip`
  - Set/unset bools when placing/removing a queen.

- Bitmask approach (integers or longs)
  - Represent occupancy as bits; e.g. `colsMask`, `diagMask`, `antiMask`.
  - Check using bitwise AND:
    - `if ((colsMask & (1 << col)) != 0 || (diagMask & (1 << diagIdx)) != 0 || (antiMask & (1 << antiIdx)) != 0) skip`
  - Place by OR-ing the bit and pass updated masks into recursion:
    - `Backtrack(row + 1, colsMask | (1 << col), diagMask | (1 << diagIdx), antiMask | (1 << antiIdx))`

Practical notes
- Diagonal mapping: unify `row - col` to a non-negative index using an offset `(n - 1)` when storing in arrays or masks.
- Use `long` (64-bit) masks if N can exceed 31; otherwise 32-bit int suffices for small N.
- All methods still perform exponential search in worst case; trackers only reduce constant factors and prune many invalid branches.

Examples
- Example 1
  - Input: `N = 4`
  - Output (two solutions):
    - [ ".Q..", "...Q", "Q...", "..Q." ]
    - [ "..Q.", "Q...", "...Q", ".Q.." ]

- Example 2
  - Input: `N = 1`
  - Output:
    - [ "Q" ]

Diagonal value boards (8×8)
- The tables below use 0-based row/column indices (rows 0..7, cols 0..7).
- Main diagonal value = (row - col). Equal values lie on the same main diagonal.
- Anti-diagonal value = (row + col). Equal values lie on the same anti-diagonal.

Main diagonal values (row - col)

| r\c | 0  | 1   | 2   | 3   | 4   | 5   | 6   | 7   |
|-----|----:|----:|----:|----:|----:|----:|----:|----:|
| 0   | 0  | -1  | -2  | -3  | -4  | -5  | -6  | -7  |
| 1   | 1  | 0   | -1  | -2  | -3  | -4  | -5  | -6  |
| 2   | 2  | 1   | 0   | -1  | -2  | -3  | -4  | -5  |
| 3   | 3  | 2   | 1   | 0   | -1  | -2  | -3  | -4  |
| 4   | 4  | 3   | 2   | 1   | 0   | -1  | -2  | -3  |
| 5   | 5  | 4   | 3   | 2   | 1   | 0   | -1  | -2  |
| 6   | 6  | 5   | 4   | 3   | 2   | 1   | 0   | -1  |
| 7   | 7  | 6   | 5   | 4   | 3   | 2   | 1   | 0   |

Anti-diagonal values (row + col)

| r\c | 0  | 1   | 2   | 3   | 4   | 5   | 6   | 7   |
|-----|----:|----:|----:|----:|----:|----:|----:|----:|
| 0   | 0  | 1   | 2   | 3   | 4   | 5   | 6   | 7   |
| 1   | 1  | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| 2   | 2  | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
| 3   | 3  | 4   | 5   | 6   | 7   | 8   | 9   | 10  |
| 4   | 4  | 5   | 6   | 7   | 8   | 9   | 10  | 11  |
| 5   | 5  | 6   | 7   | 8   | 9   | 10  | 11  | 12  |
| 6   | 6  | 7   | 8   | 9   | 10  | 11  | 12  | 13  |
| 7   | 7  | 8   | 9   | 10  | 11  | 12  | 13  | 14  |


When bool[] arrays are used as conflict trackers, they need length 2*n - 1 for diagonals:

- Main-diagonal values computed as row - col range from -(n-1) to +(n-1) (inclusive). That is 2n-1 distinct values. To use an indexable array we offset to a non-negative index: diagIdx = row - col + (n - 1).
- Anti-diagonal values computed as row + col range from 0 to 2*(n-1) (inclusive). That is also 2n-1 distinct values. We use antiIdx = row + col.
- Therefore both trackers require arrays of length 2*n - 1 so every possible diagonal maps to a unique boolean slot and conflict checks stay O(1) using diags[diagIdx] / antiDiags[antiIdx].
- Example (n=8): row - col ∈ [-7..7] → offset by 7 → indices [0..14]; row + col ∈ [0..14] → indices [0..14].

This guarantees a direct, collision-free mapping from (row,col) to a single index per diagonal, enabling constant-time occupancy checks and updates.
