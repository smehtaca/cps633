#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Uses tableReader to check is user exists
int checkUserExists(char* userID)
{

  return 0;
}

//Checks if user id is between 4 and 32 characters
int checkUIDCriteria(char* userID)
{
  int len;
  len = strlen(userID);
  if (len > 32 || len < 4)
     return 0;
  else return 1;
}
