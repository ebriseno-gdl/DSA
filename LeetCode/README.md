# LeetCode (project folder)

Purpose
- Contain implementations and explanations of problems from https://leetcode.com/.

Overview
- Implements LeetCode solutions in C# and C++ and provides corresponding unit tests.
- Each problem is a standalone console application project with project-root documentation (some of them applies to both C# and C++).
- Each unit-test project depends only on its corresponding problem project.

LeetCode folder structure
- `CSharp/` — C# console projects implementing solutions.
- `Cpp/` — C++ console projects implementing solutions.
- `UnitTests/CSharp/` — NUnit test projects for C# solutions.
- `UnitTests/Cpp/` — Google Test projects for C++ solutions.

Project & naming convention
- Problem Solution Project name format:
  - `<Short Problem Description>[CSharp|Cpp]-LeetCode_<LeetCode #>`
  - Example: `TwoSumCSharp-LeetCode_01`, `PermutationsCpp-LeetCode_46`
- Test projects follow the same name with `-TESTS` appended:
  - Example: `TwoSumCSharp-LeetCode_01-TESTS`

Per-project documentation (applies to both C# and C++)
- Each C# problem project root contains the LeetCode problem statement.
- Additional explanatory material about the approach and edge-cases, if needed, can be included in the project root.
- Comments in Source files (`*.cs` or `*.cpp`).
- Typical files you will find in a project root:t
  - `ProblemStatement.md` — problem text copied from LeetCode (only in the C# project, but applies to C++ project too).
  - `SolutionNotes.md` or `README.md` or image/diagram files — additional explanation, complexity analysis, and implementation notes.
  - Source files (`*.cs` or `*.cpp`, headers) — include comments in header file and in solution method describing the algorithm and its time/space complexity.
  - Project file
  
Program behavior in problem projects
- Each problem project has a `Main` (C#) or `main` (C++) that:
  - Runs the LeetCode solution method using the same parameter protocol as the LeetCode problem, and
  - Either prompts for input to test the method or executes hard-coded example tests.
- Projects may include multiple solution variants; header comments document trade-offs.
- Designs favor easy execution of example cases from the problem statement.

Build & test, contribution, and repository policies
- Topics related to Build & test, Contributing & branches, Notes about content ownership, Git / .gitignore guidance, and Contact / Maintainers are documented in the main repository README. See the repository root README (e.g., `C:\Dev\DSA\README.md` or `../README.md`) for those policies and instructions.

License / Ownership notes
- Problem statements are copied from LeetCode for convenience and study. See the main README for notes on content ownership and licensing.

Contact / Maintainers
- See the main repository README for maintainer/contact information and contribution guidelines.

