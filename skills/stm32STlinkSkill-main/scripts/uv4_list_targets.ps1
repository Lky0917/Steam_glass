param(
    [Parameter(Mandatory = $true)]
    [string]$Project
)

if (-not (Test-Path -LiteralPath $Project)) {
    throw "Keil project not found: $Project"
}

[xml]$xml = Get-Content -LiteralPath $Project
$targets = @($xml.Project.Targets.Target.TargetName) | Where-Object { $_ }

if ($targets.Count -eq 0) {
    Write-Host "No targets found in project: $Project"
    exit 1
}

foreach ($target in $targets) {
    Write-Host $target
}
