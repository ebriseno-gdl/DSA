# Run all *-TESTS.exe under x64\Debug using vstest.console and collect diagnostics.
# Usage: from C:\Dev\DSA: powershell -ExecutionPolicy Bypass -File .\scripts\run-all-native-tests.ps1

$root = Join-Path $PSScriptRoot ".." | Resolve-Path
$vstest = "$env:VSINSTALLDIR\Common7\IDE\Extensions\TestPlatform\vstest.console.exe"
if (-not (Test-Path $vstest)) {
  Write-Error "vstest.console.exe not found at $vstest. Ensure Visual Studio environment or set VSINSTALLDIR."
  exit 2
}

$tests = Get-ChildItem -Path (Join-Path $root 'x64\Debug') -Filter "*-TESTS.exe" -Recurse -File
if ($tests.Count -eq 0) { Write-Output "No native test executables found under x64\\Debug"; exit 0 }

foreach ($t in $tests) {
  $diag = "$($t.DirectoryName)\vstest_diag_$($t.BaseName).txt"
  Write-Output "Running: $($t.FullName)"
  & $vstest $t.FullName /Platform:x64 /diag:$diag
  Write-Output "Exit. diag: $diag"
}