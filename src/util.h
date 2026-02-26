#ifndef _UTIL_H_
#define _UTIL_H_

// Autor: Joachim Schneider

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <forms.h>

#define HELP_TEXT "\
Materialverwaltung\n\n\
Hinweise zur Benutzung:\n\
- Artikelnummern bestehen aus 6 alphanumerischen Zeichen\n\
- Umlaute in den Daten koennen zu Fehlverhalten fuehren\n\
- Beim Start kann Dateipfad zu einer CSV-Datei als Parameter uebergeben werden\n\
    - Nicht vorhandene Datei wird beim Speichervorgang neu angelegt\n\
    - Verwendung einer Default-Datei bei nicht angegebenem Dateipfad\n\n\
Funktionen:\n\
- Gesamten Bestand anzeigen\n\
    - Zeile anklicken, um Eingabefelder auszufuellen\n\
- Material suchen (nach Artikelnummer oder Bezeichnung)\n\
- Material hinzufuegen:\n\
    - Bestand vorhandener Materialien erhoehen\n\
    - neues Material registrieren\n\
- Material entfernen: Bestand vorhandener Materialien verringern (nach Artikelnummer oder Bezeichnung)\n\n\
\n\
Autor: Joachim Schneider\n\
"

// Deprecated
void clearTerminal(char *header);

#endif // _UTIL_H_
