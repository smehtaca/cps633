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
  if(!checkPWLength(password) && !isAlphaNumeric(password))
  {
    return 0;
  }
  else if (!checkPWLength(password) && isAlphaNumeric(password))
  {
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
    if(!isalnum(current))
    {
      return 1;
    }
  }
  return 0;
}

int checkPWLength(char* password)
{
  int len;

  len = strlen(password);

  if(len < 12 && len > 4)
  {
      return 0;
  }
  else
  {
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
  int i;

  paddedPW = (char *) malloc(sizeof(char) * MAXSTRLEN+1);
  paddedPW = password;

  int len = MAXSTRLEN - passlen;

  for(i = 0; i < len; i++)
  {
    paddedPW[i + passlen + 1] = '\0';
  }
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
