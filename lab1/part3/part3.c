#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define POSSIBILITIES 1679616 //36^4 (because I included 0-9)
#define NUM_CHARS 36

void createPassTable();
void createHashTable();
void E(char *in, char *out);
char * search(char * hashpass);

char hashTable[POSSIBILITIES][5];//4 is number of characters per string
char passTable[POSSIBILITIES][5];//the 5th is for null term (is this needed?)
const char alphaNums[] = {'0','1','2','3','4','5','6','7','8','9','A','B',
      'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
      'U','V','W','X','Y','Z'};
//Note: I read afterwards that we weren't told to include 0-9 in this,
//but I already did and what's the harm?

void main (void)
{
  char* input = (char*) malloc(sizeof(char)*4);
  createPassTable();
  printf("Sample password: %s\n", passTable[1000000]);//1000000 is a good test num as you get 2 L's
  createHashTable();
  printf("Hash of sample password: %s\n", hashTable[1000000]);

  printf("Give me a hashed password (only first four characters will be read)\n");
  fscanf(stdin,"%4s", input);
  printf("The password is: %s\n",search(input));
  //ask for input of a hash
  //search the hashTable for a match
  //use its index to find the match in the passTable
  //print this entry in passTable
}

char * search(char * hashpass)
{
  //loop through the entire hashpass and compare for a match
  //once you get a match, return passTable at that index
  int i;
  for (i = 0; i<POSSIBILITIES;i++)
  {
    if(strcmp(hashTable[i], hashpass) == 0)
    {
      return passTable[i];
    }
  }
  printf("Failed to find. Make sure hash actually has a password counterpart\n");
  exit(-1);
}

void createHashTable()
{//Hash each password with the E function
  int i;
  for (i = 0; i<POSSIBILITIES; i++)
  {
    E(passTable[i], hashTable[i]);
  }
}

void createPassTable()
{
  int x = 0;// is where in the table to store the next array
  int i;//The longest loop I've ever written
  for (i = 0; i<NUM_CHARS;i++)
  {
    int j;
    for (j = 0;j<NUM_CHARS;j++)
    {
      int k;
      for(k = 0;k<NUM_CHARS;k++)
      {
        int l;
        for (l = 0;l<NUM_CHARS;l++)
        {
          passTable[x][0] = alphaNums[i];//building the string
          passTable[x][1] = alphaNums[j];
          passTable[x][2] = alphaNums[k];
          passTable[x][3] = alphaNums[l];
          x++;
        }
      }
    }
  }
}

void E(char *in, char *out)
{
  out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
  out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
  out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
  out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}
