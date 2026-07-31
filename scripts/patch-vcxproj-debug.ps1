# Patch all *-TESTS.vcxproj files to ensure Debug|x64 and Debug|Win32 produce PDBs.
# Usage: Open PowerShell as needed and run: .\scripts\patch-vcxproj-debug.ps1

Set-StrictMode -Version Latest
$root = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent
Push-Location $root

$projFiles = Get-ChildItem -Path .. -Filter "*-TESTS.vcxproj" -Recurse -File

if ($projFiles.Count -eq 0) {
    Write-Output "No *-TESTS.vcxproj files found."
    Pop-Location
    return
}

foreach ($file in $projFiles) {
    Write-Output "Processing: $($file.FullName)"
    # backup
    Copy-Item -Path $file.FullName -Destination ($file.FullName + ".bak") -Force

    [xml]$xml = Get-Content $file.FullName
    $ns = $xml.Project.NamespaceURI

    foreach ($cfg in @("Debug|x64","Debug|Win32")) {
		$cond = "'`$(Configuration)|`$(Platform)'=='$cfg'"

        # find or create ItemDefinitionGroup with matching Condition
        $groups = @()
        if ($xml.Project.ItemDefinitionGroup) {
            $groups = @($xml.Project.ItemDefinitionGroup)
        }
        $group = $groups | Where-Object { $_.Condition -eq $cond } | Select-Object -First 1

        if (-not $group) {
            $group = $xml.CreateElement("ItemDefinitionGroup", $ns)
            $group.SetAttribute("Condition", $cond)
            $xml.Project.AppendChild($group) | Out-Null
        }

        # ensure ClCompile element exists and set DebugInformationFormat
        $cl = $group.SelectSingleNode("ClCompile", $null)
        if (-not $cl) {
            $cl = $xml.CreateElement("ClCompile", $ns)
            $group.AppendChild($cl) | Out-Null
        }
        $dif = $cl.SelectSingleNode("DebugInformationFormat", $null)
        if (-not $dif) {
            $dif = $xml.CreateElement("DebugInformationFormat", $ns)
            $cl.AppendChild($dif) | Out-Null
        }
        $dif.InnerText = "ProgramDatabase"

        # ensure Link element exists and set GenerateDebugInformation and ProgramDatabaseFile
        $link = $group.SelectSingleNode("Link", $null)
        if (-not $link) {
            $link = $xml.CreateElement("Link", $ns)
            $group.AppendChild($link) | Out-Null
        }
        $gdi = $link.SelectSingleNode("GenerateDebugInformation", $null)
        if (-not $gdi) {
            $gdi = $xml.CreateElement("GenerateDebugInformation", $ns)
            $link.AppendChild($gdi) | Out-Null
        }
        $gdi.InnerText = "true"

        $pdb = $link.SelectSingleNode("ProgramDatabaseFile", $null)
        if (-not $pdb) {
            $pdb = $xml.CreateElement("ProgramDatabaseFile", $ns)
            $link.AppendChild($pdb) | Out-Null
        }
        $pdb.InnerText = '$(OutDir)$(TargetName).pdb'
    }

    # Save back (preserve UTF-8)
    $xml.Save($file.FullName)
    Write-Output "Patched and saved: $($file.FullName) (backup: $($file.FullName).bak)"
}

Pop-Location
Write-Output "Done. Rebuild solution and run tests."