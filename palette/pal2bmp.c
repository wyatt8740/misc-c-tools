#include <stdio.h>
#include <stdlib.h>

char *alloc_pixmap();
int read_palette(char *filename, char *pixmap);
void write_pixmap(char *pixmap);
void write_header();

/* hardcoded, exactly what mspaint generates for a 24 bit bitmap with
   dimensions of 16 by 4 pixels */
const char bmp_header[54] =
                          { 0x42, 0x4d, 0xf6, 0x00,    0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x36, 0x00,    0x00, 0x00, 0x28, 0x00,
                            0x00, 0x00, 0x10, 0x00,    0x00, 0x00, 0x04, 0x00,
                            0x00, 0x00, 0x01, 0x00,    0x18, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0xc0, 0x00,    0x00, 0x00, 0x23, 0x2e,
                            0x00, 0x00, 0x23, 0x2e,    0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,    0x00, 0x00 };


int main(int argc, char **argv) {
  if(argc > 1) {
    /* allocate for pixel map */
    char *pixmap = alloc_pixmap();
    if(!pixmap)
      return -1;

    int r=read_palette(argv[1], pixmap);
    if(r) {
      fprintf(stderr, "Error: %d\n", r);
      return -2;
    }
    
    write_header();
    write_pixmap(pixmap);
    free(pixmap);

    return 0;
  }
  else {
    fprintf(stderr, "Error: no palette file name was given to convert to BMP.\n");
    return -3;
  }
}

int read_palette(char *filename, char *pixmap){
  /* reverse byte order */


  /* start of row:
     0  palette[0]: pixmap[144]
     1  palette[48]: pixmap[96]
     2  palette[96]: pixmap[48]
     3  palette[144]: pixmap[0]
  */
  
  /* cursor starts at last byte in pixmap array */
  int pixmap_cursor=192;
  FILE *pal_in = fopen(filename, "rb");
  if(!pal_in) {
    fprintf(stderr, "Error opening palette file '%s' for reading.\n", filename);
    return -1;
  }
  else {
    int pixmap_row=3;
    int pixmap_col=0;
    char subpixel[3];
    while(pixmap_row >= 0) {
      /* move to start of row */
      pixmap_cursor = ( 48 * (pixmap_row) );

      for(pixmap_col=0; pixmap_col < 16; pixmap_col++) {
        subpixel[2] = fgetc(pal_in);
        subpixel[1] = fgetc(pal_in);
        subpixel[0] = fgetc(pal_in);

        /* B */
        pixmap[pixmap_cursor] = subpixel[0];
        pixmap_cursor++;

        /* G */
        pixmap[pixmap_cursor] = subpixel[1];
        pixmap_cursor++;

        /* R */
        pixmap[pixmap_cursor] = subpixel[2];
        pixmap_cursor++;
      }
        
      pixmap_col=0;
      pixmap_row--;
    }
    return 0;
  }  
}

/* read a line: move (16 x line#) forward from start of file, then seek back 3, read
   3 bytes, then:
   15 times, do:
     seek back 6
     read 3 out
   when done, move cursor back (16 * 3) to do the above row
*/


char *alloc_pixmap() {
  char *pixmap=malloc(192);
  if(!pixmap) {
    fprintf(stderr, "Error: Failed to allocate memory for pixmap.\n");
  }
  return pixmap;
}

void write_header() {
  int cursor=0;
  while(cursor < 54) {
    putchar(bmp_header[cursor]);
    cursor++;
  }
}

void write_pixmap( char *pixmap ) {
  int cursor=0;
  while(cursor < 192) {
    putchar(pixmap[cursor]);
    cursor++;
  }
}

