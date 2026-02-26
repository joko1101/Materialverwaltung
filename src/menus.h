#ifndef _MENUS_H_
#define _MENUS_H_

// Autor: Joachim Schneider

#include "material.h"
#include "ui.h"

void menuDisplay(tList *materials, FD_Materialverwaltung *fdui);

void menuSearch(tList *materials, FD_Materialverwaltung *fdui);

void menuAdd(tList *materials, FD_Materialverwaltung *fdui);

void menuRemove(tList *materials, FD_Materialverwaltung *fdui);

#endif /* _MENUS_H_ */