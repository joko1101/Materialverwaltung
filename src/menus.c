// Autor: Joachim Schneider

#include "menus.h"

void menuDisplay(tList *materials, FD_Materialverwaltung *fdui)
{
    fl_clear_browser(fdui->browser);
    fl_add_browser_line(fdui->browser, "\n\
 BEZEICHNUNG                   | ARTIKELNUMMER       | BESTAND\n\
-------------------------------+---------------------+---------\n\
                               |                     |         ");
            // 30                               20                     10
    if (materials->length > 0)
    {
        tMaterial *matArr[materials->length];
        lToArray(materials, (void *) matArr);
        char line[128];
        for (int i=0; i<materials->length; i++)
            if (matArr[i])
            {
                sprintf(line, " %-30s| %-20s| %7d ", matArr[i]->artBez, matArr[i]->artNr, matArr[i]->best);
                fl_add_browser_line(fdui->browser, line);
                sprintf(line, " %30s| %20s| %7s ", "", "", "");
                fl_add_browser_line(fdui->browser, line);
            }
        }
}

void menuSearch(tList* materials, FD_Materialverwaltung *fdui)
{
    fl_clear_browser(fdui->browser);
    tMaterial *mat = getMaterialByNr(materials, fl_get_input(fdui->input_nr));   // search_term for article number first
    if (!mat) mat = getMaterialByName(materials, fl_get_input(fdui->input_name));   // If not found, search_term for name
    if (mat)
    {
        fl_add_browser_line_f(fdui->browser, "Bezeichnung: %s \nNummer:      %s \nBestand:     %d \n", mat->artBez, mat->artNr, mat->best);   
    }
    else
    {
        fl_add_browser_line(fdui->browser, "Material nicht gefunden.");
    }
}

void menuAdd(tList* materials, FD_Materialverwaltung *fdui)
{
    fl_clear_browser(fdui->browser);
    tMaterial *new_mat = createMaterial(
        fl_get_input(fdui->input_nr), 
        fl_get_input(fdui->input_name), 
        atoi(fl_get_input(fdui->input_count)));
    if (!new_mat)
    {
        fl_show_messages("Materialerstellung fehlgeschlagen.");
        return;
    }

    tMaterial *mat_found = NULL;
    if (new_mat->artNr) mat_found = getMaterialByNr(materials, new_mat->artNr);
    if (!mat_found && new_mat->artBez) mat_found = getMaterialByName(materials, new_mat->artBez);
    if (mat_found)
    {
        // If only one parameter was given, or both match the same material, increase count
        if ((*new_mat->artNr    != 0 && strcmp(mat_found->artNr, new_mat->artNr) == 0) ||
            (*new_mat->artBez   != 0 && strcmp(mat_found->artBez, new_mat->artBez) == 0))
        {
            if (new_mat->best <= 0){
                fl_add_browser_line(fdui->browser, "Ungueltige Anzahl zum Hinzufuegen.\n");
                deleteMaterial(new_mat);
                return;
            }
            // Increase material count
            mat_found->best += new_mat->best;
            fl_add_browser_line_f(fdui->browser, "\
Material hinzugefuegt:\n\n\
%dx %s\n\
Artikelnummer: %s\n\n\
Neuer Bestand: %d\
", new_mat->best, mat_found->artBez, mat_found->artNr, mat_found->best);
            deleteMaterial(new_mat);
            return;
        }

        // Assumption: Attempt to register new material
        if (!strcmp(mat_found->artNr, new_mat->artNr) || !strcmp(mat_found->artBez, new_mat->artBez))
        {
            fl_add_browser_line(fdui->browser, "Artikelnummer oder -bezeichnung existiert bereits.");
            deleteMaterial(new_mat);
            return;
        }
    }
    // Register new material
    if (strlen(new_mat->artNr) != SIZE_ART_NR-1 || new_mat->best <= 0)
    {
        fl_add_browser_line(fdui->browser, "\
Ungueltige Materialdaten. \n\
- Artikelnummer muss 6 Zeichen lang sein\n\
- Anzahl muss groesser als 0 sein\n");
        deleteMaterial(new_mat);
    } 
    else if (lInsert(materials, new_mat)) 
    {
        fl_add_browser_line(fdui->browser, "Wareneingang fehlgeschlagen\n");
        deleteMaterial(new_mat);
    } 
    else fl_add_browser_line_f(fdui->browser, "\
Neues Material registriert:\n\n\
Artikelnummer: %s\n\
Bezeichnung: %s\n\
Anzahl: %d\n\
", new_mat->artNr, new_mat->artBez, new_mat->best);
    return;
}

void menuRemove(tList* materials, FD_Materialverwaltung *fdui)
{
    fl_clear_browser(fdui->browser);
    tMaterial *mat = getMaterialByNr(materials, fl_get_input(fdui->input_nr));   // search_term for article number first
    if (!mat) mat = getMaterialByName(materials, fl_get_input(fdui->input_name));   // If not found, search_term for name
    int count = atoi(fl_get_input(fdui->input_count));
    if (count <= 0){
        fl_add_browser_line(fdui->browser, "Ungueltige Anzahl zum Entfernen.\n");
        return;
    }
    if (!mat) fl_add_browser_line(fdui->browser, "Material nicht gefunden. \n");
    else if (mat->best < count) fl_add_browser_line_f(fdui->browser, "Materialbestand zu klein (%d).\n", mat->best);
    else
    {
        mat->best -= count;
        if (mat->best == 0){
            fl_add_browser_line_f(fdui->browser, "\
Material entfernt:\n\n\
%dx %s\n\
Artikelnummer: %s\n\n\
Neuer Bestand: 0.\n\
Material wird geloescht...\n\
", count, mat->artBez, mat->artNr);
            lRemove(materials, mat);
        }
        else fl_add_browser_line_f(fdui->browser, "\
Material entfernt:\n\n\
%dx %s\n\
Artikelnummer: %s\n\n\
Neuer Bestand: %d.\n\
", count, mat->artBez, mat->artNr, mat->best);
    }
}