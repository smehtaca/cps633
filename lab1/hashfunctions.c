#include "hashfunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* computeHash(char block0[4],char block1[4], char block2[4]);
void E(char *in, char *out);

//Calls E function with each block and combines the hased hashed_blocks into one hash
char* computeHash(char block0[4],char block1[4], char block2[4])
{
  char *hashed_blocks = (char*) malloc(4);
  char *hashed = (char*) malloc(12);

  E(block0, hashed_blocks);
  strcat(hashed,hashed_blocks);

  printf("In hash: %s\n", hashed );

  E(block1, hashed_blocks);
  strcat (hashed,hashed_blocks);

printf("In hash: %s\n", hashed );

  E(block2, hashed_blocks);
  strcat (hashed,hashed_blocks);

printf("In hash: %s\n", hashed );

  return hashed;
}


/********************* E function *************************/
// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out)
{
  out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
  out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
  out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
  out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}
