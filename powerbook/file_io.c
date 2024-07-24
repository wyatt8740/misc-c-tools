/* common helper function */
#include <stdio.h>
FILE *file_open(char *path, char *mode) {
  FILE *fil = fopen(path, mode);
  if(fil == NULL) {
    fprintf(stderr,"Error opening %s\n", path);
  }  
  return fil;
}
