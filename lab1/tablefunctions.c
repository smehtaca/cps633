#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Method will search for either a username or password
int findCred (char * str)
{
  FILE *fp;
  char buf[33]; //buffer for username. Username can be up to 32 characters, add null that's 33

  if (fp = fopen("testfile.txt", "r") == NULL){//if failed to open file
      return(-1);
  }

  while (!feof(fp)) {
    fscanf(fp, %32s, buf);//read a string, max 32 chars
    if(strcmp(str,buf)){
      fclose(fp);
      return 0;//found it
    }

  }
  fclose(fp);
  return 1;//didn't find it
}


void resetPasswd(char* old, char* new)
{
  //find the old password in the file and write the new one in its place
}