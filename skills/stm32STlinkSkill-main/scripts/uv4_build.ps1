param(
    [Parameter(Mandatory = $true)]
    [string]$Project,
    [string]$Target,
    [string]$Log = 'uv4_build.log',
    [string]$UV4Path = $env:UV4_PATH
)

if (-not $UV4Path) { $UV4Path = 'D:\Keil_v5\UV4\UV4.exe' }
if (-not (Test-Path -LiteralPath $UV4Path)) {
    throw "UV4.exe not found: $UV4Path"
}
if (-not (Test-Path -LiteralPath $Project)) {
    throw "Keil project not found: $Project"
}

$args = @('-b', $Project)
if ($Target) {
    $args += @('-t', $Target)
}
$args += @('-o', $Log)

& $UV4Path @args
exit $LASTEXITCODE
