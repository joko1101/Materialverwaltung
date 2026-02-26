# Materialverwaltung

## Setup
```bash 
git clone https://github.com/joko1101/Materialverwaltung && cd Materialverwaltung
```
```bash
. build
```
```bash
. start <optional: Dateipfad>
```
- Datenformate:
    - Artikelnummer: **6 alphanumerischen Zeichen**
    - **ACHTUNG**: Umlaute in den Daten können zu Fehlverhalten führen
- Beim Start kann ein Dateipfad zu einer CSV-Datei als Parameter übergeben werden  
    - Nicht vorhandene Datei wird beim Speichervorgang neu angelegt  
    - Verwendung einer Default-Datei bei nicht angegebenem Dateipfad
- Debuggen:
    - ```. build -g```
    - ```. .env_setup```
    - Starten mit Debugger

## Funktionen
- **Gesamten Bestand anzeigen**
  - Zeile anklicken, um Eingabefelder auszufüllen
- **Material suchen** (nach Artikelnummer oder Bezeichnung)
- **Material hinzufügen**
  - Bestand vorhandener Materialien erhöhen (nach Artikelnummer oder Bezeichnung)
  - Neues Material registrieren (Artikelnummer **und** Bezeichnung benötigt)
- **Material entfernen**
  - Bestand vorhandener Materialien verringern (nach Artikelnummer oder Bezeichnung)

---


**Autor:** Joachim Schneider
