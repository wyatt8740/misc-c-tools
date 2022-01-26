#include <stdio.h>

/* this adds a new line to an openvpn config file from stdin containing the
   string passed as an argument. Prints to stdout. Appends wherever it finds
   the first blank line. */


int nextchr='\0';
int chr='\0';
int prevchr='\0';
int tmp;

int grab(void);
void add_line(char *to_add);

/* getchar wrapper */
int grab(void) {
  if(chr != EOF) {
    prevchr=chr;
    tmp=getchar();
    if(tmp != EOF) {
      nextchr=getchar();
      ungetc(nextchr,stdin);
    }
    return tmp;
  }
  else return EOF;
}

/* advance to next line */
void add_line( char *to_add ) {
  int notfound=1;
  while( notfound && (chr=grab()) != EOF)
  {
    if(chr == '\n' && nextchr == '\n')
    {
      notfound=0;
      printf("\n%s\n",to_add);
    }
    else putchar(chr);
  }
  /* and now the rest of the file */
  while((chr=grab()) != EOF) putchar(chr);
}

int main(int argc, char **argv) {
  if(argc > 1)
  {
    add_line(argv[1]);
    return 0;
  }
  else
  {
    fprintf(stderr,"E: Give an argument containing the parameter you want to add.\n");
    return 1;
  }
}