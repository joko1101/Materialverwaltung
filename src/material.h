#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// Autor: Joachim Schneider

#include "ringlist.h"

#define SIZE_ART_NR (6 + 1)

typedef struct material {
    char artNr[SIZE_ART_NR];
    char* artBez;
    int best;
} tMaterial;

// Material "constructor"
tMaterial *createMaterial(const char art_nr[SIZE_ART_NR], const char *art_bez, int best);

// Material "destructor"
int deleteMaterial(void *mat);

tMaterial* getMaterialByNr(tList* pMaterials, const char* art_nr);

tMaterial* getMaterialByName(tList* pMaterials, const char* name);

tList* loadMaterialsFromCSV(char *filepath);

int persistMaterialData(tList *pMaterials, char *filepath);

#endif // _MATERIAL_H_