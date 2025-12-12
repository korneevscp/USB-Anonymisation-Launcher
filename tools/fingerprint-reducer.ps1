Write-Host 'Réduction d’empreinte locale...'

Set-ItemProperty -Path "HKCU:\Software\Microsoft\Windows\CurrentVersion\Explorer" -Name 'ShellState' -Value 0 -ErrorAction SilentlyContinue
Disable-WindowsErrorReporting -ErrorAction SilentlyContinue

Write-Host 'Terminé.'
