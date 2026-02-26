#include "ui.h"
#include "material.h"

FD_Materialverwaltung *fd_Materialverwaltung;


void myexit(void)
{
    if (!fd_Materialverwaltung->data_altered) return; 
    persistMaterialData(fd_Materialverwaltung->materials, fd_Materialverwaltung->filepath);
    if ( fl_form_is_visible( fd_Materialverwaltung->Materialverwaltung ) )
        fl_hide_form( fd_Materialverwaltung->Materialverwaltung );
    lDelete(fd_Materialverwaltung->materials);
    fl_free(fd_Materialverwaltung);
    fl_finish();
}

/***************************************
 ***************************************/

int
main( int    argc,
      char * argv[ ] )
      {
    atexit(myexit);
    fl_initialize( &argc, argv, 0, 0, 0 );
    fd_Materialverwaltung = create_form_Materialverwaltung( );

    if (argv[1] == NULL) {
        fprintf(stderr, "No filepath provided. Using default: ./data/bestand.csv\n");
        fd_Materialverwaltung->filepath = "./data/bestand.csv";
    } else if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".csv")) {
        fprintf(stderr, "Warning: Provided filepath is no CSV file. Using default: ./data/bestand.csv\n");
        fd_Materialverwaltung->filepath = "./data/bestand.csv";
    } else fd_Materialverwaltung->filepath = argv[1];

    fd_Materialverwaltung->materials = loadMaterialsFromCSV(fd_Materialverwaltung->filepath);
    fd_Materialverwaltung->data_altered = 0;

    fl_show_form( fd_Materialverwaltung->Materialverwaltung, FL_PLACE_CENTERFREE, FL_FULLBORDER, "Materialverwaltung" );

    fl_clear_browser(fd_Materialverwaltung->browser);
    fl_add_browser_line(fd_Materialverwaltung->browser, HELP_TEXT);
    fd_Materialverwaltung->state = STATE_HELP;

    fl_do_forms( );
    
    if ( fl_form_is_visible( fd_Materialverwaltung->Materialverwaltung ) )
        fl_hide_form( fd_Materialverwaltung->Materialverwaltung );
    fl_free( fd_Materialverwaltung );
    fl_finish( );

    return 0;
}
