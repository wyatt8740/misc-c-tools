#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char **argv) {
  char redc[4]="000";
  char bluec[4]="000";
  char greenc[4]="000";
  if(argc != 2)
  {
    fprintf(stderr, "Error: I need one argument exactly, in format (R,G,B) with values\nfrom 0-255 for each.\n");
    return 1;
  }
  int i=0;
  int done=0;
  int offset=0;
  /* get red */
  while((argv[1][offset+i]) != '\0' && i<3 && done != 1)
  {
    if(argv[1][offset+i] == ',')
    {
      redc[i]='\0';
      done=1;
    }
    else
    {
      redc[i]=argv[1][offset+i];
    }
    i++;
  }
  offset += i;
  done=0;

  /*green*/
  i=0;
  while((argv[1][offset+i]) != '\0' && i<3 && done != 1)
  {
    if(argv[1][offset+i] == ',')
    {
      greenc[i]='\0';
      done=1;
    }
    else
    {
      greenc[i]=argv[1][offset+i];
    }
    i++;
  }
  offset += i;
  done=0;
  i=0;
  /* get blue */
  while( i<3 && done != 1)
  {
    if(argv[1][offset+i] == ','||argv[1][offset+i] == '\0')
    {
      bluec[i]='\0';
      done=1;
    }
    else
    {
      bluec[i]=argv[1][offset+i];
    }
    i++;
  }
  int red=atoi(redc);
  int green=atoi(greenc);
  int blue=atoi(bluec);
  if(red > 255 || green > 255 || blue > 255)
  {
    fprintf(stderr,"E: I only work on 8 bit RGB values; sorry.\n");
    return 2;
  }
/*  printf("%s %s %s\n",redc,greenc,bluec);*/
  printf("%02X%02X%02X\n",red,green,blue);
  return 0;
}
