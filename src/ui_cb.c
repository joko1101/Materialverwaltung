#include "ui.h"
#include "menus.h"

// TABLE_LINE_INDEX - Transform browser line number to material index
#define TBL_LN_IDX(x) ((x)-1)%2==0 ? ((x)-1)/2-2 : -1

/* Callbacks and freeobj handlers for form Materialverwaltung */


/***************************************
 ***************************************/

void
cb_quit( FL_OBJECT * obj,
         long        data )
{
    exit(0);
}


/***************************************
 ***************************************/

void
cb_nr( FL_OBJECT * obj,
          long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
}

/***************************************
 ***************************************/

void
cb_name( FL_OBJECT * obj,
          long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
}

/***************************************
 ***************************************/

void
cb_count( FL_OBJECT * obj,
          long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
}

/***************************************
 ***************************************/

void
cb_search( FL_OBJECT * obj,
           long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
    fdui->state = STATE_SEARCH;
    menuSearch(fdui->materials, fdui);
}


/***************************************
 ***************************************/

void
cb_in( FL_OBJECT * obj,
       long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
    fdui->state = STATE_ADD;
    menuAdd(fdui->materials, fdui);
    fdui->data_altered = 1;
}


/***************************************
 ***************************************/

void
cb_browser( FL_OBJECT * obj,
           long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
}

void
cb_browser_dblclick( FL_OBJECT * obj,
                     long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
    if (fdui->state != STATE_DISPLAY) return;
    int mat_idx = TBL_LN_IDX(fl_get_browser(obj)); // -1 for header line
    if (mat_idx < 0) return;
    tMaterial mat = *(tMaterial *)lGetByIndex(fdui->materials, mat_idx);
    fl_set_input( fdui->input_nr, mat.artNr);
    fl_set_input( fdui->input_name, mat.artBez);
    char buf[20];
    sprintf(buf, "%d", mat.best);
    fl_set_input( fdui->input_count, buf);
}

/***************************************
 ***************************************/

void
cb_display( FL_OBJECT * obj,
            long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
    fdui->state = STATE_DISPLAY;
    menuDisplay(fdui->materials, fdui);
}


/***************************************
 ***************************************/

void
cb_out( FL_OBJECT * obj,
        long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
    fdui->state = STATE_REMOVE;
    menuRemove(fdui->materials, fdui);
    fdui->data_altered = 1;
}

/***************************************
 ***************************************/

void
cb_clear( FL_OBJECT * obj,
        long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
    fl_set_input( fdui->input_nr, "");
    fl_set_input( fdui->input_name, "");
    fl_set_input( fdui->input_count, "");
}

void
cb_help( FL_OBJECT * obj,
        long        data )
{
    FD_Materialverwaltung *fdui = (FD_Materialverwaltung*)data;
    fdui->state = STATE_HELP;
    fl_clear_browser(fdui->browser);
    fl_add_browser_line(fdui->browser, HELP_TEXT);
}
