#include <stdio.h>
#include <string.h>
void doQuote(FILE *stream);

/* make 'gendered' quote marks out of ascii-style ones. */
int main(int argc, char **argv)
{
  FILE *stream=0;
  if(argc > 1) /* if cli args passed, read from file instead of stdin unless '-'*/
  {
    int i=1;
    while(i<argc)
    {
      if(strncmp(argv[i],"-", strlen("-"))) /* if not -; don't worry about strncmp */
      {
        /* remember strncmp returns 0 on matches so we don't invert */
        /* note to self: would it be good to add 'b' to the mode here?
           Are there win32/DOS users that need to use regexes in scripts? */
        stream=fopen(argv[i],"r");
        if(stream==0) /* if null returned */
        {
          fprintf(stderr,"Error: couldn't open file %s for reading.\n",argv[i]);
          return 1;
        }
      }
      else
      {
        stream=stdin; /* interpret '-' as 'use stdin' */
      }
      doQuote(stream);
      i++;
    }
  }
  else
  {
    doQuote(stdin);
  }
  return 0;
}

void doQuote(FILE *stream)
{
  int quoteState=0; /* 0: not in quote 1: in quote */
  int chr=0;
  while((chr = getc(stream)) != EOF)
  {
    if(chr=='"'){
      if(quoteState)
      {
        printf("”"); /* more than 1 byte, so we can't use putchar(). */
        quoteState=0; /* no longer in a quote. */
      }
      else
      {
        printf("“");
        quoteState=1; /* starting a quote. */
      }
    }
    else { /* just print any non-quote chars */
      putchar(chr);
    }
  }
  if(stream != stdin && stream != stderr) /* yes I want pointer comparison */
  {
    fclose(stream);
  }
}
