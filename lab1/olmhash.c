#include "passwordfunctions.h"
#include "hashfunctions.h"
#include "userfunctions.h"
#include "tablefunctions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main (void)
{
  char* test = "password";
  printf("\n");
  checkPWCriteria(test);
}
