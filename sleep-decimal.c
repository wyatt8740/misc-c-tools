#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* atof */
#include <math.h>   /* modf, floor(double) */
#include <time.h>
int main(int argc, char **argv)
{
  double duration;
  duration=atof(argv[1]); /* dangerous games */
  if(argc > 1 && argc < 3)
  {
    /* valid number of arguments passed; proceed. */
    /* first, convert decimal number of seconds into seconds and nanoseconds
       for our timespec (nanosleep() uses a timespec struct). */
    double whole_secs_float;
    double fractional_secs = modf(duration, &whole_secs_float);
    /* int whole_secs = floor(whole_secs_float); */
    int whole_secs = (int)whole_secs_float; /* more dangerous games */
    long whole_nsecs = (long)(1000000000 * fractional_secs);
    struct timespec TS;
    /* reminder: 0.1 seconds is 100,000,000 nS */
    TS.tv_sec=(time_t)whole_secs;
    TS.tv_nsec=whole_nsecs;
    nanosleep(&TS, NULL);
  }
  else
  {
    fprintf(stderr,"Error: exactly one parameter should be passed: a time duration to sleep for.\n");
    return 1;
  }
  return 0;
}
