$base = Split-Path $MyInvocation.MyCommand.Path -Parent
Remove-Item -Path "$base\..\tools\*" -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item -Path "$base\..\config\*" -Recurse -Force -ErrorAction SilentlyContinue
Write-Host "Panic Button exécuté."
