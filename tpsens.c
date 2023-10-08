/*
   Trackpoint sensitivity setter/getter.
   Needs either root (setuid, for instance) or appropriate permissions on the
   trackpoint's 'sensitivity' file in sysfs. Or an appropriate entry in
   sudoers (or doas).
   For X201 thinkpad, but might work for other systems too.
   On my laptops:
   NMB keyboard should use 200 sensitivity; Chicony should use 227.

   From udev/hwdb.d/70-pointingstick.hwdb:
   > Note these come with 2 revisions of keyboard, with the trackpoints having
   > a different sensitivity in the different revisions. 1.25 is a bit slow for
   > the least sensitive revision, but it is better to be a bit slow than too
   > fast.

   The Libinput driver ignores POINTINGSTICK_CONST_ACCEL nowadays, so the only
   thing we can do is adjust sensitivity (unless using evdev).

   With the soft rim ("golf tee") cap:
   The NMB keyboard should use 200 sensitivity; Chicony should use 227.

   With the "pencil eraser" cap (from Unicomp or vintage IBM equipment):
   I set 255 on the Chicony board. Assuming 227 would be good on NMB.
*/

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
  FILE *sens_file;
  char *sens_filename;
  /* could save a few bytes in the compiled binary to do it this way: */
  char *default_sens_path="/sys/devices/platform/i8042/serio1/sensitivity";
  
  sens_filename = getenv("TPSENS_PATH");
  
  if(!sens_filename) {
    sens_filename = default_sens_path;
  }
  if(sens_filename[0] == '\0') {
    /* empty string, treat as if unset */
    sens_filename = default_sens_path;
  }
  int siz;
  switch(argc) {
  case 2:
    siz = atoi(argv[1]);
    /* write */
    if (siz < 1 || siz > 255) {
      fprintf(stderr, "Error: refusing to write non-numerical or values "
              "outside of '0 < n < 256'.\n");
      return 2;
    }
    sens_file = fopen(sens_filename,"w");
    if(sens_file) {
      fputs(argv[1], sens_file);
      fclose(sens_file);
      printf("%s\n", argv[1]);
      return 0;
    }
    else {
      fprintf(stderr,"Error opening file '%s'!\nMake sure appropriate write "
              "permissions are set.\n", sens_filename);
      return 1;
    }
    break;
  case 1:
    /* read */
    sens_file = fopen(sens_filename,"r");
    if(sens_file) {
      char sens_value[4]; /* max value is 255, so this works I think */
      fgets(sens_value, 4, sens_file);
      fclose(sens_file);
      printf("%s\n",sens_value);
      return 0;
    }
    else {
      fprintf(stderr,"Error opening file '%s'!\n", sens_filename);
      return 1;
    }
    break;
  default:
    fprintf(stderr,"Error: Zero or one argument(s) should be provided.\n");
    return 1;
  }
}
