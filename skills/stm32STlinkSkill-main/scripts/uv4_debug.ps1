param(
    [Parameter(Mandatory = $true)]
    [string]$Project,
    [string]$Target,
    [string]$Log = 'uv4_debug.log',
    [string]$UV4Path = $env:UV4_PATH,
    [switch]$BuildFirst
)

if (-not $UV4Path) { $UV4Path = 'D:\Keil_v5\UV4\UV4.exe' }
if (-not (Test-Path -LiteralPath $UV4Path)) {
    throw "UV4.exe not found: $UV4Path"
}
if (-not (Test-Path -LiteralPath $Project)) {
    throw "Keil project not found: $Project"
}

if ($BuildFirst) {
    $buildArgs = @('-b', $Project)
    if ($Target) {
        $buildArgs += @('-t', $Target)
    }
    $buildArgs += @('-o', $Log)
    & $UV4Path @buildArgs
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }
}

$debugArgs = @('-d', $Project)
if ($Target) {
    $debugArgs += @('-t', $Target)
}
$debugArgs += @('-o', $Log)

Start-Process -FilePath $UV4Path -ArgumentList $debugArgs -WorkingDirectory (Split-Path -Parent $Project)
