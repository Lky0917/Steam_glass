param(
    [Parameter(Mandatory = $true)]
    [string]$Output,
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
    [switch]$ExitWhenDone
)

$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("/* Generated Keil debug initialization file. */")

function Expand-List {
    param([string[]]$Items)
    $expanded = New-Object System.Collections.Generic.List[string]
    foreach ($item in $Items) {
        if (-not $item) { continue }
        foreach ($part in ($item -split ',')) {
            $trimmed = $part.Trim()
            if ($trimmed) { $expanded.Add($trimmed) }
        }
    }
    return @($expanded)
}

$Breakpoint = Expand-List $Breakpoint
$Watch = Expand-List $Watch
$Evaluate = Expand-List $Evaluate

if ($Log) {
    $logFull = [System.IO.Path]::GetFullPath($Log)
    $lines.Add("LOG >$logFull")
}

if ($Reset) {
    $lines.Add("RESET")
}

foreach ($bp in $Breakpoint) {
    if ($bp) { $lines.Add("BS $bp") }
}

foreach ($watchExpr in $Watch) {
    if ($watchExpr) { $lines.Add("WS 1, $watchExpr") }
}

foreach ($evalExpr in $Evaluate) {
    if ($evalExpr) { $lines.Add("EVAL $evalExpr") }
}

if ($StepOver -gt 0) {
    $lines.Add("P $StepOver")
}

if ($StepInto -gt 0) {
    $lines.Add("T $StepInto")
}

for ($i = 0; $i -lt $StepOut; $i++) {
    $lines.Add("O")
}

if ($RunTo) {
    $lines.Add("G,$RunTo")
} elseif ($Run) {
    $lines.Add("G")
}

if ($Log) {
    $lines.Add("LOG OFF")
}

if ($ExitWhenDone) {
    $lines.Add("EXIT")
}

$outFull = [System.IO.Path]::GetFullPath($Output)
$outDir = Split-Path -Parent $outFull
if ($outDir -and -not (Test-Path -LiteralPath $outDir)) {
    New-Item -ItemType Directory -Path $outDir | Out-Null
}

[System.IO.File]::WriteAllLines($outFull, $lines, [System.Text.Encoding]::ASCII)
Write-Host $outFull
