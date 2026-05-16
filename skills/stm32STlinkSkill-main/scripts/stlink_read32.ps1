param(
    [Parameter(Mandatory = $true)]
    [string]$Address,
    [int]$Count = 16,
    [string]$ProgrammerPath = $env:STM32_PROGRAMMER_CLI,
    [string]$Port = 'SWD',
    [string]$Mode = 'UR'
)

if (-not $ProgrammerPath) { $ProgrammerPath = 'C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe' }
if (-not (Test-Path -LiteralPath $ProgrammerPath)) {
    throw "STM32_Programmer_CLI.exe not found: $ProgrammerPath"
}

& $ProgrammerPath -c "port=$Port" "mode=$Mode" -r32 $Address $Count
exit $LASTEXITCODE
