#include "passwordfunctions.h"
#include "hashfunctions.h"
#include "tablefunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int32_t randnum;
char user[32];

int32_t authenticate(char* userID)
{
  user = userID;
  return randnum;
}

void randnumgen(void)
{
  randnum = (int32_t) rand();
}

void hashCompare(void)
{
  //TODO: figure out parameter type and copy the code of client.c
    //then compare the hashes and print the result
}
