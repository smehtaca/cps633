#include "passwordfunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXSTRLEN 12
#define MINSTRLEN 4
#define BLOCKSIZE 4

int checkPWCriteria(char* password);
int isAlphaNumeric(char* password);
int checkPWLength(char* password);
char* pwPadder(char* password);
char* toLowerCase(char* password);


//Checks if password is between 4 and 12 characters and alphanumeric
int checkPWCriteria(char* password)
{
  printf("In checkPWCriteria\n");
  if(checkPWLength(password) == 0 && isAlphaNumeric(password) == 0)
  {
    printf("In if 1: \n");
    return 0;
  }
  else if (!checkPWLength(password) == 1 && isAlphaNumeric(password) == 0)
  {
printf("Calling padder: \n");
    char* padded = pwPadder(password);
    return checkPWCriteria(padded);
  }
  else
  {
      return 1;
  }
}

//Checks if password is alphanumeric
int isAlphaNumeric(char* password)
{
  int len = strlen(password);
  int current, i;
  for(i = 0; i < len; i++)
  {
    current = password[i];
    if(isalnum(current) == 0)
    {
      printf("In alphanum return 1\n");
      return 1;
    }
  }
  printf("In alphanum return 0\n");
  return 0;
}

int checkPWLength(char* password)
{
  int len;

  len = strlen(password);
printf("in checkPWLength\n");
  if(len <= 12 && len >= 4)
  {
    printf("returning 0\n");
      return 0;
  }
  else
  {
    printf("returning 1\n");
    return 1;
  }
}

//Paddes password with \0
char* pwPadder(char* password)
{
  int i;
  char* paddedPW;
  paddedPW = NULL;
  int passlen = strlen(password);

printf("In padder: \n");
  paddedPW = (char *) malloc(sizeof(char) * MAXSTRLEN+1);
  paddedPW = password;

  int len = MAXSTRLEN - passlen;

  for(i = 0; i < len; i++)
  {
    paddedPW[i + passlen + 1] = 'a';
  }
printf("In padder: %s\n", paddedPW);
  return paddedPW;
}

//Converts Upper case letters in password to lower case
char* toLowerCase(char* password)
{
  char* lowerCasePW;
  lowerCasePW = NULL;
  lowerCasePW = (char *) malloc(sizeof(char) * MAXSTRLEN+1);
  int len = strlen(password);
  int current, i;
  if(len == MAXSTRLEN)
  {
    lowerCasePW[len+1] = '\0';
  }
  for(i = 0; i < len; i++)
  {
    current = password[i];
    if(isupper(current))
    {
      lowerCasePW[i] = tolower(current);
    }
  }
  return lowerCasePW;
}
