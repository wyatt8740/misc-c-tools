#include <stdio.h>
#include <stdlib.h>
#include "fanlimit.h"
#include "file_io.h"

/* saves a few bytes versus using a preprocessor definition: */
char *LIMIT_ADJUST_PATH="/sys/devices/platform/temperatures/limit_adjust";
int main(int argc, char **argv) {
  if(argc > 1)
    return set_limit_info(argv[1]);
  else {
    return print_limit_info();
  }
  return 0;
}

/* FILE *file_open(char *path, char *mode) {
  FILE *lim_adj = fopen(path, mode);
  if(lim_adj == NULL) {
    fprintf(stderr,"Error opening %s\n", path);
  }  
  return lim_adj;
} */

int set_limit_info( char *new_value ) {
  FILE *lim_adj = file_open( LIMIT_ADJUST_PATH, "wb" );
  /* FILE *lim_adj=fopen(LIMIT_ADJUST_PATH,"wb"); */
  if(lim_adj) {
    fprintf(lim_adj, new_value);
    fclose(lim_adj);
    return 0;
  }
  return 1;
}

int print_limit_info() {
  /* fprintf(stderr,"Error: I need an argument to write to sysfs.\n");*/
/*  FILE *lim_adj=fopen(LIMIT_ADJUST_PATH,"r");*/
  FILE *lim_adj = file_open( LIMIT_ADJUST_PATH, "r");
  if(lim_adj) {
    int c='\0';
    while((c = fgetc(lim_adj)) != EOF) {
      putchar(c);
    }
    return 0;
  }
  return 1;
  /* putchar('\n'); */ /* seems to have one already */
}
