/* idea: detect if an argument is probably a path to a file. If it is,
   translate to a wine path. Otherwise, leave it alone. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void pathify(char *);
void winepath(char *);

int main(int argc, char **argv)
{
  int i=1;
  while(i<argc)
  {
    pathify(argv[i]);
    i++;
  }
}

void pathify(char *str)
{
/* if it looks like it's probably a path, run winepath on it. Otherwise just
   print the line verbatim with a null terminator for xargs -0 */
  if(str[0]=='-')
  {
    printf("%s", str);
    putchar(0);
    return;
  }
  else if(str[0]=='/')
  {
    /* trickier, but most windows/dos args like this are single-character so
       we'll just ignore it if the string length is exactly 2. */
    if(strlen(str)==2)
    {
      printf("%s",str);
      putchar(0);
      return;
    }
  }
  /* fall-throughs get executed */
  winepath(str);
}

void winepath(char *str)
{
  char c;
  /* execlp("winepath", (const char*) str, (const char *) NULL);*/
  char *run_string=(char *)malloc((sizeof(char)) * strlen(str) + strlen("winepath -w \"\"") + 2); /* + 2 because '%s' is two chars and we might only have a one char replacement for it, also +1 for the null terminator */
  sprintf(run_string, "winepath -w \"%s\"", str);
  FILE *fp=popen(run_string, "r");
  if(fp==NULL)
  {
    fprintf(stderr, "E: unable to open process\n");
    free(run_string);
    return;
  }
  while( (c=fgetc(fp)) != EOF)
  {
/* strip newlines and replace with null terminators. Note that obviously this
   will break down if you have files with newlines. So don't do that.
   I might be able to look ahead and use ungetc() so that in the case of
   multiple newlines in a row we can determine that only the last one should
   be a null terminator, but I'm feeling tired right now. */
    if(c=='\n')
    {
      putchar(0);
    }
    else {
      putchar(c);
    }
  }
  pclose(fp);
  free(run_string);
  return;
}
