#include "passwordfunctions.h"
#include "hashfunctions.h"
#include "tablefunctions.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void main(void)
{//begin
  int32_t randumnumber = authenticate("alex54");
  //TODO: hash function here, waiting for updated part 1
  //bitwise XOR in C is "^" as in c = a ^ b;
  //send result to hashCompare();
}
