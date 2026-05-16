param(
    [string]$UV4Path = $env:UV4_PATH,
    [string]$ProgrammerPath = $env:STM32_PROGRAMMER_CLI,
    [string]$ArmccDir = $env:ARMCC_DIR
)

if (-not $UV4Path) { $UV4Path = 'D:\Keil_v5\UV4\UV4.exe' }
if (-not $ProgrammerPath) { $ProgrammerPath = 'C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe' }
if (-not $ArmccDir) { $ArmccDir = 'D:\Keil_v5\ARM\arm5_compiler\bin' }

$ok = $true

function Test-ToolPath {
    param([string]$Name, [string]$Path)
    if (Test-Path -LiteralPath $Path) {
        Write-Host "[OK] $Name : $Path"
    } else {
        Write-Host "[MISSING] $Name : $Path"
        $script:ok = $false
    }
}

Test-ToolPath 'Keil UV4' $UV4Path
Test-ToolPath 'STM32 Programmer CLI' $ProgrammerPath
Test-ToolPath 'ARMCC bin dir' $ArmccDir
Test-ToolPath 'ARMCC compiler' (Join-Path $ArmccDir 'armcc.exe')
Test-ToolPath 'ARM linker' (Join-Path $ArmccDir 'armlink.exe')

if ($ok) { exit 0 }
exit 1
