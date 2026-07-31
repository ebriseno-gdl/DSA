# DSA (root)

### Overview
- Collection of algorithm & data-structure solutions and tests.
- Mixed projects: C# (.NET 10) and C++ with unit tests (NUnit for C#, Google Test for C++).
- Solution: `DSA.slnx` in the repository root.
- Primary content under `LeetCode/`. Future folders: `Codility/`, `DS/`.

### Repository layout
- `LeetCode/` contains solutions for problems from https://leetcode.com/.
  - `CSharp/` - C# Console projects implementing LeetCode problems
  - `Cpp/` - C++ Console projects implementing LeetCode problems
  - `UnitTests/CSharp/` - NUnit test projects for C# implementations
  - `UnitTests/Cpp/` - Google Test projects for C++ implementations
- `Codility/` - will mirror the structure of `LeetCode/` for problems from https://www.codility.com/
- `DS/` - (future) data-structure experiments and examples
- `README.md`, `LICENSE`, `.gitignore`, `.gitattributes`

- #### Notes
  - More detail about `LeetCode/` and its subfolders can be found in `LeetCode/README.md`.

### Build & test

- Projects are independent: each problem implementation is a standalone console project. Test projects depend only on their corresponding problem implementation project. You can:
  - Build and test the entire solution (recommended only when many changes affect multiple projects).
  - Build and test a single implementation project and its corresponding test project (the more used: faster for focused changes or when building or understanding the solution/implementation for a problem or a data structure).
  - Typical workflow: restore packages → build and run implementation(s) → build and run test project(s).
  - CI is not needed for the projects on this repository (because projects are independent).
  
- Visual Studio 2022/2026 (IDE) steps
  - Install required workloads/components (Visual Studio Installer):
    - __.NET Desktop Development__ (for C# / .NET 10)
    - __Desktop development with C++__
    - __C++ CMake tools for Windows__ (if using CMake)
    - Optional test adapters: `NUnit 3 Test Adapter`, `Google Test Adapter`
  - Open the solution file `DSA.slnx` from the repository root in Visual Studio 2022/2026.
  - Build the solution and run tests from Test Explorer.

- Recommended command-line examples (run from the repository root — "working directory"):
  - Restore packages for all managed projects in solution (C# problem and NUnit test projects):
    - `dotnet restore ./DSA.slnx`
  - Build all managed projects in solution (C# problem and NUnit test projects):
    - `dotnet build ./DSA.slnx -c Release|Debug`
  - Build all C++ problem projects in solution (MSVC) on Windows (C++ problem and Google Test projects):
    - `msbuild ./DSA.slnx /p:Configuration=Release|Debug`
	- Note: will build also managed projects in solution (C# problem and NUnit test projects) if `dotnet restore ./DSA.slnx` was run before.
  - Build a C# problem project:
    - `dotnet build .\<Platform>\CSharp\<ProjectName>\<ProjectName>.csproj -c Release|Debug`
  - Build a C++ problem project:
    - `msbuild .\<Platform>\Cpp\<Project>\<Project>.vcxproj /p:Configuration=Release|Debug /p:OutDir=<Working directory>\Build\Release\ /p:IntDir=<Working directory>\<Platform>\Cpp\<Project>\Build\Obj\`	
  - Build a C# test (NUnit) project:
    - `dotnet build .\<Platform>\UnitTests\CSharp\<ProjectName>\<ProjectName>.csproj -c Release|Debug`
  - Build a C++ test (Google Test) project:
    - `msbuild .\<Platform>\UnitTests\Cpp\<Project>\<Project>.vcxproj /p:Configuration=Release|Debug  /p:OutDir=<Working directory>\Build\Release\ /p:IntDir=<Working directory>\<Platform>\UnitTests\Cpp\<Project>\Build\Obj\`  
  - Run the executable of a C# or C++ problem:
    - Locate the corresponding exe file and execute it 
  - Run a C# test (NUnit):
    - `dotnet test ./<Platform>/UnitTests/CSharp/<Project> -c Release|Debug`
  - Run a C++ test (Google Test):
    - Locate the corresponding exe file and execute it

- Cross-platform
  - C# projects are SDK-style and can be built with the `dotnet` CLI on Windows/Linux/macOS.
  - C++ projects can be built with CMake on Linux/macOS; for native Visual C++ `.vcxproj` builds use MSVC on Windows.

### Contributing & branches
- Use feature branches: `feature/<topic>` (example: `feature/fix-two-sum`).
- Open a Pull Request targeting `main`. The `main` branch is protected: merges require passing CI checks and the configured number of approver reviews. Keep your branch up-to-date with `main` if required by branch protection.

### Notes about content ownership
- This repository contains implementations/solutions for platform problems (LeetCode and, in the future, Codility). Problem statements and platform content remain property of their respective platforms. This repo contains solution code and commentary only — see `LICENSE` for license specifics.

### Git / ignore notes
- If a folder (e.g., `packages/`, `bin/`, `obj/`, `build/`) is already tracked by Git, remove it from the index before relying on `.gitignore`:
  - `git rm -r --cached packages`
  - `git add .gitignore`
  - `git commit -m "Ignore packages"`

### Contact / Maintainers
- Owner & Maintainer: Edmundo Briseno — GitHub: `@ebriseno-gdl` — Email: `edmundo.briseno@gmail.com`  
- Preferred contact: open an issue or create a pull request. Typical response time: ~48 hours.
- Responsibilities: primary maintainer, CI and release management, code review.