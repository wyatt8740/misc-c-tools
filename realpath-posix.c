#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include <libgen.h> /* for basename(3) in error messages */
#include <string.h> /* for str(n)dup(3) - to copy strings so basename()
                       doesn't tamper with things */

void errmsg(char *message);
char *invoke_name;

int main(int argc, char **argv)
{
  invoke_name = argv[0];
  if(argc == 2)
  {
    char *to_resolve = argv[1];
    /* char *restrict full_path[PATH_MAX + 1]; */
    /* POSIX says that if the resolved_name arg is null pointer, it will allocate
       for us. */
    char *restrict full_path = realpath(to_resolve, NULL);
    if(full_path == NULL)
    {
      char *e_fmt = "Cannot find file %s";
      size_t str_size = snprintf(NULL, 0, e_fmt, to_resolve);
      char *e_msg = malloc(str_size + 1);
      sprintf(e_msg, e_fmt, to_resolve);
      errmsg(e_msg);
      free(e_msg);
      return 2;
    }
    else
    {
      printf("%s\n",full_path);
      free(full_path);
    }
    return 0;
  }
  else /* argc != 2 */
  {
    errmsg("Please pass exactly one argument (a path to resolve).");
    return 1;
  }
}

void errmsg(char *message)
{
  char *progname = strdup(invoke_name);
  char *basename_out = basename(progname);
  fprintf(stderr, "E: %s: %s\n", basename_out, message);
  free(progname); /* posix basename() does not do a malloc */
}
