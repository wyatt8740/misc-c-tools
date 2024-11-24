#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/* create a "press any key to continue" prompt that doesn't depend on enter being pressed */
/* basically the DOS 'pause' command */

int main(int argc, char **argv) {
  printf("Press any key to continue: ");
  struct termios config;
  if(  tcgetattr(0, &config) < 0) {
    fprintf(stderr,"Error of some sort at startup\n");
  }
  config.c_lflag &= !(ICANON | ECHO);
  tcsetattr(0, TCSAFLUSH, &config);
  getchar();
  config.c_lflag |= (ICANON | ECHO);
  tcsetattr(0, TCSANOW, &config);
  putchar('\n');
}
