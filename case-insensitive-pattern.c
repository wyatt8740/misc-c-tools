/*
 * By Wyatt Ward; 23 Nov 2020. I hereby release this program into the public
 * domain. If you really like it, or use it in something then please consider
 * reaching out to me/letting me know, if you can. I like to hear from people.
 * But there's no pressure and you are certainly not obligated to. It'd just
 * be fun for me to hear about what my code is helping with.
 *
 * Input: text to make case insensitive, either to stdin or as argument(s). If
 * multiple arguments are given the result will be printed with spaces as
 * separators. If no arguments are passed, then stdin will be read; otherwise,
 * if argument(s) are passed, then stdin will _NOT_ be read.
 */

#include <stdio.h>  /* putchar/getchar */
#include <ctype.h>  /* toupper/tolower */
#include <string.h> /* strlen */

void generate_insensitive(int curchar);
void piperead();

int main(int argc, char **argv)
{
  if(argc > 1)
  {
    for(int i=1; i<argc; i++)
    {
      for(int j=0; j<strlen(argv[i]); j++)
      {
        generate_insensitive(argv[i][j]);
      }
      if((i+1)<argc) /* if not the last argument */
      {
        putchar(' ');
      }
    }
    putchar('\n');
    return 0;
  }
  else /* no arguments were passed, read from stdin */
  {
    piperead();
    return 0;
  }
}

void piperead()
{
  int curchar='\0';
  while((curchar=getchar()) != EOF)
  {
    generate_insensitive(curchar);
  }
}

/* prints to stdout. Non-alphabetical chars are printed as they were input. */
void generate_insensitive(int curchar)
{
  if(isalpha(curchar))
  {
    putchar((int)'[');
    putchar(toupper(curchar));
    putchar(tolower(curchar));
    putchar((int)']');
  }
  else
  {
    putchar(curchar);
  }
}
