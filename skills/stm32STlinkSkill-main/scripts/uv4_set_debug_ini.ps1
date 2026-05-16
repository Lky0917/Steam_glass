param(
    [Parameter(Mandatory = $true)]
    [string]$Project,
    [string]$InitFile,
    [switch]$Clear,
    [switch]$NoBackup
)

if (-not (Test-Path -LiteralPath $Project)) {
    throw "Keil project not found: $Project"
}

$uvoptx = [System.IO.Path]::ChangeExtension($Project, '.uvoptx')
if (-not (Test-Path -LiteralPath $uvoptx)) {
    throw "Keil option file not found: $uvoptx"
}

if (-not $Clear) {
    if (-not $InitFile) {
        throw "InitFile is required unless -Clear is used."
    }
    if (-not (Test-Path -LiteralPath $InitFile)) {
        throw "Debug initialization file not found: $InitFile"
    }
    $initFull = [System.IO.Path]::GetFullPath($InitFile)
} else {
    $initFull = ''
}

$enc = New-Object System.Text.UTF8Encoding($false)
$text = [System.IO.File]::ReadAllText($uvoptx, $enc)

if (-not $NoBackup) {
    $stamp = Get-Date -Format 'yyyyMMdd_HHmmss'
    Copy-Item -LiteralPath $uvoptx -Destination "$uvoptx.bak_$stamp"
}

if ($text -notmatch '<tIfile>.*?</tIfile>') {
    throw "Could not find <tIfile> in $uvoptx"
}

$escaped = [System.Security.SecurityElement]::Escape($initFull)
$updated = [System.Text.RegularExpressions.Regex]::Replace(
    $text,
    '<tIfile>.*?</tIfile>',
    "<tIfile>$escaped</tIfile>",
    1
)

[System.IO.File]::WriteAllText($uvoptx, $updated, $enc)
Write-Host "Updated: $uvoptx"
Write-Host "tIfile : $initFull"
