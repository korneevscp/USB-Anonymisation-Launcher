Remove-Item -Path "$env:TEMP\*" -Recurse -Force -ErrorAction SilentlyContinue
Clear-RecycleBin -Force -ErrorAction SilentlyContinue
$launcherConfig = Join-Path (Split-Path $MyInvocation.MyCommand.Path -Parent) "..\config"
Remove-Item -Path "$launcherConfig\*.log" -Force -ErrorAction SilentlyContinue
Write-Host "Nettoyage terminé."
