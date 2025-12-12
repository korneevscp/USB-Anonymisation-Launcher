# USB Anonymisation Launcher



**USB Anonymisation Launcher** est un outil portable pour Windows conçu pour :

- Lancer Tor Portable depuis une clé USB
- Effectuer un nettoyage du système
- Offrir un bouton d’urgence **Panic Button** pour effacer rapidement les traces

L’outil fonctionne directement depuis la clé USB, sans installation.

---

## Fonctionnalités

- Lancement direct de **Tor Portable**  
- Nettoyage complet via un script PowerShell  
- **Panic Button** pour suppression rapide de fichiers sensibles  
- Interface sombre (fond noir) avec boutons cyan  
- Logs intégrés pour suivre toutes les actions  
- Portable : aucun besoin d’installation  
- Compatible Windows 10 et 11

---


## Installation

1. Placer Tor Portable dans `tools/tor-portable/Browser/firefox.exe`  
2. Placer les scripts PowerShell dans `tools/` et `panic/`  
3. Lancer `launcher.exe` depuis la clé USB  

## Fichiers à inclure

- `ttt.cpp`  
- `launcher.exe` (optionnel)  
- `tools/cleanup.ps1`  
- `panic/panic_wipe.ps1`  
- `config/settings.json` et `config/panic.flag`  

##  info 
install tor dans tools/tor....






