#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t calcsum();

int main(int argc, char **argv)
{
  uint32_t sum=calcsum();
  printf("%x\n",(uint8_t)sum);
  fprintf(stderr,"%x (decimal: %lu)\n",(uint8_t)sum,(uint8_t)sum);
  return 0;
}

uint32_t calcsum() {
  uint32_t sum=0;
  uint32_t c=0;
  
  uint32_t last=0;
  int i=0;
  while(!feof(stdin) && i < 5){
    c=getchar(); /* skip four bytes that aren't part of sum (and a fifth, the "command" byte) */
    i++;
  }
  while((!feof(stdin)) && ((c=getchar()) != EOF)) {
    if(c == 0367 ) { /*0xf7*/
      sum=sum-last;
      goto endfound;
    }
    else {
      printf("%x + ",(uint8_t)c);
      sum = sum + c;
    }
    last=c;
  }
endfound:
/*      if(c == 0367)
        {
        c = c - last;
        }*/
  /* 128 - chk % 128 and then removes topmost byte (& 0x7f) */
  return (0200 - (sum & 0377) % 0200); 

/* 0x80 - (sum & 0xff) */
}
