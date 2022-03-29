#include <stdio.h>
#include <stdlib.h>
#include "temp.h"
#include "file_io.h"

/* saves a few bytes versus using a preprocessor definition: */
char *SENSOR1_TEMP="/sys/devices/platform/temperatures/sensor1_temperature";
char *SENSOR1_FANSPEED="/sys/devices/platform/temperatures/sensor1_fan_speed";
char *SENSOR2_TEMP="/sys/devices/platform/temperatures/sensor1_temperature";
char *SENSOR2_FANSPEED="/sys/devices/platform/temperatures/sensor1_fan_speed";
int main(int argc, char **argv) {
  if(argc > 1) {
    fprintf(stderr,"Error: no arguments should be passed.\n");
    return 1;
  }
  else {
    return ( temp_print_info("Sensor 1: Temperature:\t", SENSOR1_TEMP) |
             temp_print_info("          Fan Speed:\t", SENSOR1_FANSPEED) |
             temp_print_info("Sensor 2: Temperature:\t", SENSOR2_TEMP) |
             temp_print_info("          Fan Speed:\t", SENSOR2_FANSPEED) );
  }
}

int temp_print_info( char *desc, char *path ) {
  /* fprintf(stderr,"Error: I need an argument to write to sysfs.\n");*/
/*  FILE *lim_adj=fopen(LIMIT_ADJUST_PATH,"r");*/
  FILE *lim_adj = file_open( path, "r");
  if(lim_adj) {
    printf("%s",desc);
    int c='\0';
    while((c = fgetc(lim_adj)) != EOF) {
      putchar(c);
    }
    return 0;
  }
  return 1;
  /* putchar('\n'); */ /* seems to have one already */
}
