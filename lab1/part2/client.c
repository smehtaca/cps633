#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>



void main(void)
{//begin
  int foundUserFlag = 0;
  char user[33];

printf("\nPlease note that this part of the lab has a bug we were unable to fix.\nAs such, to give you at least a program that almost conforms to the requiremens,\nthe hashing has been disabled (but not the F function where the XOR logic is).\nPlease make sure your db file has a user whose password is plaintext instead of hashed for this to work.\n\n");


  printf("Enter your username\n");
  scanf("%s",user);
  //reusing code from olmhash
  FILE* readCSV = fopen("db.csv","r");
  char line[1024];
  char* tmp = (char*)malloc(33);
  while(fgets(line, 1024, readCSV))
  {
    tmp = strdup(line);
    if(strcmp( user,getfield(tmp,1)) == 0) //Found username
    {
      free(tmp);
      foundUserFlag = 1;
      break;
    }
  }
  fclose(readCSV);
  if (foundUserFlag == 0)//never found user
  {
    printf("Username not found, please rerun the program to try again\n");
    exit(1);
  }

  int32_t randumnumber = authenticate(user);

  char* pass = (char*) malloc(13);
  char* hashpass = (char*) malloc(13);

  printf("User account found.\n");
  printf("Please enter the password for this user account.\n");
  scanf("%s",pass);
  hashpass = hash(pass);//Hashing functions are in server.c
  hashCompare(F(pass, randumnumber));//this is where I disabled hashing to get the program to work
}
