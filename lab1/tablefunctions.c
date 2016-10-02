#include "tablefunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


char* findCred(char* username)
{
  FILE *fp;
  char user[32];//max 32 characters
  char*  pass = (char*)malloc(12);//exactly 12 characters


  char* result = (char*) malloc(sizeof(char)*1024);//to be returned


  if ((fp = fopen("testfile.txt", "r")) == NULL)
  {//if failed to open file
      exit(1);
  }


  while (fscanf(fp, "%s %s", user, pass) != EOF)
//read username and password
  {

    if(!strcmp(user, username)) //found it
    {

        result = pass;
        fclose(fp);
        return result;



    }
  }

  fclose(fp);
  return result; //somehow this is fine here but like after once it returns to olmhash, the value changes
}

void resetCred(char* username, char* new_pass)
{
  FILE *originalfile = fopen("testfile.txt", "r");
  FILE *newfile = fopen("tempfile.txt","w+");
  char  user[32];//max 32 characters
  char*  pass = (char*)malloc(12);//exactly 12 characters


  while (fscanf(originalfile, "%s %s", user, pass) != EOF)//read username and password
  {
    if (strcmp(user, username) == 0)//if you find the username
    {
      //copy new as the new password and write to the newfile
      fprintf(newfile, "%s %s\n", user, new_pass);
    }
    else
    {
      //write the original line into newfile
      fprintf(newfile, "%s %s \n", user, pass);
    }
  }

  //delete testfile.txt and rename newfile.txt to testfile.txt

  fclose(originalfile);
  fclose(newfile);

  remove("testfile.txt");
  rename("tempfile.txt", "testfile.txt");

}

void newUser(char* username, char* hashpass)
{
  puts("NewUser");
  FILE *db = fopen("testfile.txt", "a+");
    fprintf(db, "%s %s \n", username, hashpass);
  fclose(db);
}
