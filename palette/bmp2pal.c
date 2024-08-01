#include <stdio.h>
#include <stdlib.h>

char *alloc_palette();
int read_bmp(char *filename, char *palette);
void write_palette(char *palette);

int main(int argc, char **argv) {
  if(argc > 1) {
    char *palette = alloc_palette();
    if(!palette)
      return -1;

    int r=read_bmp(argv[1], palette);
    if(r < 0 ) {
      fprintf(stderr, "Error in read_bmp(). Probably seek related.\n");
      return -2;
    }

    write_palette(palette);
    free(palette);

    return 0;
  }
  else {
    fprintf(stderr, "Error: no bitmap file name was given to convert to palette.\n");
    return -3;
  }
}

char *alloc_palette() {
  char *palette=malloc(192);
  if(!palette) {
    fprintf(stderr, "Error: Failed to allocate memory for palette.\n");
  }
  return palette;
}

int read_bmp(char *filename, char *palette){
  int palette_cursor=192;
  FILE *bmp_in = fopen(filename, "rb");
  if(!bmp_in) {
    fprintf(stderr, "Error opening bitmap file '%s' for reading.\n", filename);
    return -1;
  }
  int r=fseek(bmp_in,54L,SEEK_SET);
  if(r == -1) {
    fprintf(stderr, "Error seeking in bitmap file.\n");
    return -2;
  }
  else {
    int palette_row=3;
    int palette_col=0;
    char subpixel[3];
    while(palette_row >= 0) {
      /* move to start of row */
      palette_cursor = ( 48 * (palette_row) );

      for(palette_col=0; palette_col < 16; palette_col++) {
        subpixel[2] = fgetc(bmp_in);
        subpixel[1] = fgetc(bmp_in);
        subpixel[0] = fgetc(bmp_in);

        /* B */
        palette[palette_cursor] = subpixel[0];
        palette_cursor++;

        /* G */
        palette[palette_cursor] = subpixel[1];
        palette_cursor++;

        /* R */
        palette[palette_cursor] = subpixel[2];
        palette_cursor++;
      }
        
      palette_col=0;
      palette_row--;
    }
    return 0;
  }
}


void write_palette( char *palette ) {
  int cursor=0;
  while(cursor < 192) {
    putchar(palette[cursor]);
    cursor++;
  }
}

