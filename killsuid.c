#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* for kill(3): */
#include <signal.h>

/* we have to parse ps(1) for portability. >:( */

/* note that this will not catch it if the program you're finding a PID of
   has argv[0] starting with a full path (/usr/bin for instance).

   This will also fail if the program name/path has spaces in it. This should
   be fixable by making the program search for the last region of spaces on
   a line and separate there. */

char *read_line(FILE *stream, int *chr);
pid_t get_proc_pid(char *prog_name);
char *get_proc_name(char *ps_line_in); /* mallocs */
char *get_proc_pid_str(char *ps_line_in); /* does not malloc */
int kill_proc_by_name(char *proc_name);

int main(int argc, char **argv) {
    char supplicant_name[]="wpa_supplicant";
    char vpn_name[]="openvpn";

    /* returns 0 if both were killed. Otherwise, returns the bitwise OR of:
       00000001: failed to kill openvpn
       00000010: failed to kill wpa_supplicant
       so, in brief:
     _________________________________.
     |     |         KILLED:          |
     |rtrn |__________________________|
     |code | wpa_supplicant | openvpn |
     |_____|________________|_________|
     |  0  |        Y       |    Y    |
     |_____|________________|_________|
     |  1  |        Y       |    N    |
     |_____|________________|_________|
     |  2  |        N       |    Y    |
     |_____|________________|_________|
     |  3  |        N       |    N    |
     |_____|________________|_________|
    */
    return (
      (kill_proc_by_name(supplicant_name) << 1) |
      (kill_proc_by_name(vpn_name))
      );
}

int kill_proc_by_name(char *proc_name) {
  pid_t proc_pid=get_proc_pid(proc_name);
  int retcode=-1;
  if(proc_pid==0) {
    fprintf(stderr,"Note: %s PID not found; not killing.\n",proc_name);
    retcode=-1;
  }
  else {
    fprintf(stderr,"Attempting to kill %s (PID: %zu).\n",proc_name,proc_pid);
    /* see signal.h(7POSIX) */
    retcode=kill(proc_pid, SIGTERM);
  }
  /* return 1 if failed, 0 if successful. */
  /* normally, kill(3) returns -1 if failed and 0 if successful. */
  return (retcode ? 1 : 0);
}


/* pid_t %zu */
pid_t get_proc_pid(char *prog_name) {
  /* security flaw: system() call */
  FILE *ps_output=popen("/bin/ps -A -o 'comm= pid='", "r");
  char *out;
  char *pid_str;
  char *name_str;
  pid_t pid;
  int currchar=' ';
  while(currchar != EOF) {
    out=read_line(ps_output, &currchar);
    name_str=get_proc_name(out);
    pid_str=get_proc_pid_str(out);
    pid=atoi(pid_str);
    if(!strncmp(prog_name, name_str, strlen(prog_name) + 1)) { /* +1 for null */
      /* match found, clean up memory allocations and return */
      free(out);
      free(name_str);
      pclose(ps_output);
      return pid;
    }
    free(out);
    free(name_str);
  }
  pclose(ps_output);
  return 0; /* CHECK FOR THIS, DO NOT KILL INIT (pid=0). pid_t is unsigned. */
}

/* this function allocates a string that is returned. */
char *read_line(FILE *stream, int *chr) {
  /* start with 22 chars and null terminator. On my test this was enough to
     avoid all reallocations (on my machine). */
  /* I have also verified correct behavior with smaller initial values and
     in cases where reallocation must occur. */
  size_t line_size=23;
  char *linebuf=(char*)malloc(sizeof(char) * line_size);
  if(linebuf==NULL) {
    fprintf(stderr,"Error malloc'ing!\n");
    exit(1);
  }
  size_t i=0;
/*  int chr=' ';*/
  while(((*chr=getc(stream)) != EOF) && *chr != '\n') {
    if(i == line_size) { /* leave room for terminator */
      line_size++;
      linebuf=realloc(linebuf,line_size);
      if(linebuf == NULL) {
        fprintf(stderr,"Error realloc'ing!\n");
        exit(1);
      }
    }
    linebuf[i]=*chr;
    i++;
  }
  /* add null terminator */
  if(i==line_size) {
    line_size++;
    linebuf=realloc(linebuf,line_size);
  }
  linebuf[i]='\0';
  return linebuf;
}

/* this DOES NOT malloc a string. */
char *get_proc_pid_str(char *ps_line_in) {
  /* get second column */
  int i=0;
  while(!isspace(ps_line_in[i]) && i < strlen(ps_line_in)) {
    i++;
  }
  while(isspace(ps_line_in[i]) && i < strlen(ps_line_in)) {
    i++;
  }
  return ps_line_in + (sizeof(char) * i);
}

/* this malloc's a string. */
char *get_proc_name(char *ps_line_in) {
  size_t i=0;
  while(!isspace(ps_line_in[i]) && i < strlen(ps_line_in)) {
    i++;
  }
  char *retname=(char*)malloc(sizeof(char) * (i+1));
  if(retname == NULL) {
    fprintf(stderr,"ERROR malloc'ing in get_proc_name()\n");
    exit(1);
  }
  strncpy(retname,ps_line_in,i);
  retname[i]='\0';
  return retname;
}