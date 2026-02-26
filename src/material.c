// Autor: Joachim Schneider

#include "material.h"
#include <unistd.h>

tMaterial *createMaterial(const char art_nr[SIZE_ART_NR], const char *art_bez, int best)
{
    tMaterial *mat = malloc(sizeof(tMaterial));
    if (!mat) return NULL;
    strcpy(mat->artNr, art_nr);
    mat->artBez = malloc(strlen(art_bez)+1);
    if (!mat->artBez)
    {
        free(mat);
        return NULL;
    }
    strcpy(mat->artBez, art_bez);
    mat->best = best;
    return mat;
}

int deleteMaterial(void *mat)
{
    if (!mat) return -1;
    if (((tMaterial*)mat)->artBez) free(((tMaterial*)mat)->artBez);
    free(mat);
    mat = NULL;
    return 0;
}

// Compare material to article number
int cmp_nr(const void* pData, const void *val)
{
    const tMaterial* mat = pData;
    return (strcmp(mat->artNr, (const char*) val));
}

// Compare material to article name
int cmp_name(const void* pData, const void *val)
{
    const tMaterial* mat = pData;
    return (strcmp(mat->artBez, (const char*) val));
}

// Compare two materials by article number
int cmp_material_by_nr(const void* pEl1, const void* pEl2)
{
    return (strcmp(((const tMaterial*) pEl1)->artNr, ((const tMaterial*) pEl2)->artNr));
}

// Compare two materials by article name
int cmp_material_by_name(const void* pEl1, const void* pEl2)
{
    return (strcmp(((const tMaterial*) pEl1)->artBez, ((const tMaterial*) pEl2)->artBez));
}

void print_material(const void* pData)
{
    const tMaterial* mat = pData;
    printf("Bezeichnung: %s \nNummer:      %s \nBestand:     %d \n", mat->artBez, mat->artNr, mat->best);
}

// Prints material in one line
void print_material_inline(const void* pData)
{
    const tMaterial* mat = pData;
    printf("%-20s %-10s %10d \n", mat->artBez, mat->artNr, mat->best);
}

tMaterial* getMaterialByNr(tList* pMaterials, const char* art_nr)
{
    return lGet(pMaterials, art_nr, cmp_nr);
}

tMaterial* getMaterialByName(tList* pMaterials, const char* name)
{
    return lGet(pMaterials, name, cmp_name);
}

// Adds material to list or, if extists, adds to its count
// Return Value:    -1  -  Error
//                   1  -  Material existed, count increased
//                   0  -  New material added
int addMaterial(tList* pMaterials, tMaterial *new_mat)
{
    tMaterial *mat_found = NULL;
    if (new_mat->artNr) mat_found = getMaterialByNr(pMaterials, new_mat->artNr);
    if (!mat_found && new_mat->artBez) mat_found = getMaterialByName(pMaterials, new_mat->artBez);
    if (mat_found)
    {
        mat_found->best += new_mat->best;
        printf("%dx '%s' - '%s' hinzugefügt.\nNeuer Bestand: %d.\n", new_mat->best, mat_found->artNr, mat_found->artBez, mat_found->best);
        return 1;
    }
    else 
    {
        if (strlen(new_mat->artNr) != SIZE_ART_NR || new_mat->artBez == "")
        {
            printf("Ungültige Materialdaten. \n - Artikelnummer muss 6 Zeichen lang sein\n - Artikelbezeichnung darf nicht leer sein\n");
            return -1;
        }
        if (lInsert(pMaterials, new_mat))
        {
            printf("Wareneingang fehlgeschlagen\n");
            return -1;
        }
        else printf("Material nicht gefunden.\n%dx Material '%s' - '%s' aufgenommen\n", new_mat->best, new_mat->artNr, new_mat->artBez);
    }
    return 0;
}

// Removes from material count, and deletes, if count falls to 0
int removeMaterial(tList* pMaterials, const char *search_term, int count)
{
    tMaterial *mat = getMaterialByNr(pMaterials, search_term);
    if (!mat) mat = getMaterialByName(pMaterials, search_term);
    if (!mat){
        printf("\nMaterial nicht gefunden. \n");
        return 1;
    }
    else if (mat->best < count){
        printf("\nMaterialbestand zu klein (%d).\n", mat->best);
        return 1;
    }
    else
    {
        mat->best -= count;
        if (mat->best == 0){
            printf("\n%dx Material '%s' - '%s' entfernt. \nKeine Artikel mehr vorhanden. Material wird gelöscht.\n", count, mat->artNr, mat->artBez);
            deleteMaterial(mat);
        }
        else printf("\n%dx Material '%s' - '%s' entfernt. \nNeuer Bestand: %d.\n", count, mat->artNr, mat->artBez, mat->best);
    }
    return 0;
}

// Print all materials
void printMaterials(tList* pMaterials)
{
    tMaterial *matArr[pMaterials->length];
    lToArray(pMaterials, (void *) matArr);
    printf("\n%-20s %-10s %10s \n\n", "Bezeichnung", "Nummer", "Bestand");
    for (int i=0; i<pMaterials->length; i++)
        if (matArr[i])
            print_material_inline(matArr[i]);
}

tList* loadMaterialsFromCSV(char *filepath)
{
    tList* materials = lCreate(cmp_material_by_name, deleteMaterial);

    printf("%s\n", getcwd(NULL, 0));
    FILE *file = fopen(filepath, "r");
    if (!file) return materials;

    // Skip first line (table head)
    char line[128];
    fgets(line, 128, file);

    while (fgets(line, 128, file))
    {   
        char *tok = strtok(line, ",");
        // Read article number (1st field)
        char art_nr[SIZE_ART_NR] = {0};
        if (strlen(tok) != SIZE_ART_NR-1)        {
            printf("ERROR: Ungueltige Artikelnummer in Datei '%s', Zeile %d : '%s'\nZeile wird uebersprungen...\n", 
                filepath, 
                materials->length+2,
                art_nr);
            continue;
        }
        strcpy(art_nr, tok);

        // Read article name (2nd field)
        tok = strtok(NULL, ",");
        if (!tok) {
            printf("ERROR: Ungueltige Artikelbezeichnung in Datei '%s', Zeile %d\nZeile wird uebersprungen...\n", filepath, materials->length+2);
            continue;
        }
        char *art_bez = malloc(strlen(tok)+1);
        strcpy(art_bez, tok);

        // Read count (3rd field)
        tok = strtok(NULL, ",");
        if (!tok || atoi(tok) < 0) {
            printf("ERROR: Ungueltiger Bestand in Datei '%s', Zeile %d\nZeile wird uebersprungen...\n", filepath, materials->length+2);
            continue;
        }

        tMaterial *new_mat = createMaterial(art_nr, art_bez, atoi(tok));
        if (!new_mat) return NULL;

        if (lInsert(materials, new_mat)) return NULL;
    }
    
    fclose(file);

    return materials;
}

int persistMaterialData(tList *pMaterials, char *filepath)
{
    if (!pMaterials->pHead) return 0;
    FILE *file = fopen(filepath, "w+t");
    if (!file) return -1;

    // Table head
    fputs("Artikelnummer,Artikelbezeichnung,Bestand\n", file);

    tMaterial *matArr[pMaterials->length];
    lToArray(pMaterials, (void *) matArr);
    for (int i=0; i<pMaterials->length; i++)
        if (matArr[i])
        {
            char line[128] = {0};
            sprintf(line, "%s,%s,%d\n", matArr[i]->artNr, matArr[i]->artBez, matArr[i]->best);
            if (fputs(line, file) == -1) return -1;
        }
    fclose(file);

    return 0;
}