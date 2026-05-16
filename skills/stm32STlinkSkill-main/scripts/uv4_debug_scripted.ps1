param(
    [Parameter(Mandatory = $true)]
    [string]$Project,
    [string]$Target = 'Target 1',
    [string]$InitFile,
    [string[]]$Breakpoint = @(),
    [string[]]$Watch = @(),
    [string[]]$Evaluate = @(),
    [string]$Log,
    [switch]$Reset,
    [switch]$Run,
    [string]$RunTo,
    [int]$StepInto = 0,
    [int]$StepOver = 0,
    [int]$StepOut = 0,
    [switch]$ExitWhenDone,
    [switch]$BuildFirst,
    [string]$UV4Path = $env:UV4_PATH
)

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

if (-not $InitFile) {
    $projectDir = Split-Path -Parent ([System.IO.Path]::GetFullPath($Project))
    $InitFile = Join-Path $projectDir 'codex_debug.ini'
}

& (Join-Path $scriptDir 'uv4_make_debug_ini.ps1') `
    -Output $InitFile `
    -Breakpoint $Breakpoint `
    -Watch $Watch `
    -Evaluate $Evaluate `
    -Log $Log `
    -Reset:$Reset `
    -Run:$Run `
    -RunTo $RunTo `
    -StepInto $StepInto `
    -StepOver $StepOver `
    -StepOut $StepOut `
    -ExitWhenDone:$ExitWhenDone

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

& (Join-Path $scriptDir 'uv4_set_debug_ini.ps1') -Project $Project -InitFile $InitFile
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

& (Join-Path $scriptDir 'uv4_debug.ps1') -Project $Project -Target $Target -BuildFirst:$BuildFirst -UV4Path $UV4Path
exit $LASTEXITCODE
