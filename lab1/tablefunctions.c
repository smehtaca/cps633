#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char * findCred (char * username)

{
  FILE *fp;
  char user[32];//max 32 characters
  char pass[12];//exactly 12 characters
  char* result;//to be returned

  result = NULL;

  if ((fp = fopen("testfile.txt", "r")) == NULL)
  {//if failed to open file
      exit(1);
  }

  while (fscanf(fp, "%s %s", user, pass) != EOF)//read username and password
  {
    if(strcmp(user, username) == 0) //found it
    {
      result = pass;
      break;

    }
  }

  fclose(fp);
  return result;
}

void resetPasswd(char* username, char* new_pass)
{
  FILE *originalfile = fopen("testfile.txt", "r");
  FILE *newfile = fopen("tempfile.txt","wt");
  char  user[32];//max 32 characters
  char  pass[12];//exactly 12 characters

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
      fprintf(newfile, "%s %s\n", user, pass);
    }
  }

  //delete testfile.txt and rename newfile.txt to testfile.txt

  fclose(originalfile);
  fclose(newfile);

  remove("testfile.txt");
  rename("tempfile.txt", "testfile.txt");

}

void newUser(char * username, char * hashpass)
{
  FILE *originalfile = fopen("testfile.txt", "r");
  FILE *newfile = fopen("tempfile.txt","wt");

  char  user[32];//max 32 characters
  char  pass[12];//exactly 12 characters

  while (fscanf(originalfile, "%s %s", user, pass) != EOF)//read username and password
  {
    //write the original line into newfile
      fprintf(newfile, "%s %s\n", user, pass);
  }
  //write the new user into the end of the file
  fprintf(newfile, "%s %s\n", username, hashpass);

  //delete testfile.txt and rename newfile.txt to testfile.txt

  fclose(originalfile);
  fclose(newfile);

  remove("testfile.txt");
  rename("tempfile.txt", "testfile.txt");
}
