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

## Arborescence sur la clé USB

USB-Anon-Launcher/
│
├─ launcher.exe # EXE compilé du launcher
├─ ttt.cpp # Code source C++
├─ tools/
│ ├─ tor-portable/
│ │ └─ Browser/
│ │ └─ firefox.exe # Tor Portable déjà extrait
│ └─ cleanup.ps1 # Script PowerShell pour nettoyage
├─ panic/
│ └─ panic_wipe.ps1 # Script PowerShell pour Panic Button
└─ config/
├─ settings.json # Fichier de configuration
└─ panic.flag # Fichier utilisé par le Panic Button



