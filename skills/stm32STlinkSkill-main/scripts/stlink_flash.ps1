param(
    [Parameter(Mandatory = $true)]
    [string]$Firmware,
    [string]$ProgrammerPath = $env:STM32_PROGRAMMER_CLI,
    [string]$Port = 'SWD',
    [string]$Mode = 'UR',
    [string]$Address = '0x08000000',
    [switch]$NoReset
)

if (-not $ProgrammerPath) { $ProgrammerPath = 'C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe' }
if (-not (Test-Path -LiteralPath $ProgrammerPath)) {
    throw "STM32_Programmer_CLI.exe not found: $ProgrammerPath"
}
if (-not (Test-Path -LiteralPath $Firmware)) {
    throw "Firmware not found: $Firmware"
}

$ext = [System.IO.Path]::GetExtension($Firmware).ToLowerInvariant()
$args = @('-c', "port=$Port", "mode=$Mode", '-w', $Firmware)
if ($ext -eq '.bin') {
    $args += $Address
}
$args += '-v'
if (-not $NoReset) {
    $args += '-rst'
}

& $ProgrammerPath @args
exit $LASTEXITCODE
