#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char* findCred(char* username,int field)
{
  FILE *fp;
  char user[32];//max 32 characters
  char pass[12];//exactly 12 characters
  int N;
  char* result;//to be returned

  result = NULL;

  if ((fp = fopen("testfile.txt", "r")) == NULL)
  {//if failed to open file
      exit(1);
  }

  while (fscanf(fp, "%s %s %d", user, pass, N) != EOF)//read username and password
  {
    if(strcmp(user, username) == 0) //found it
    {
      if(field == 2) result = pass;
      if(field == 3) sprintf(result, "%d", N);
      break;

    }
  }

  fclose(fp);
  return result;
}

void resetCred(char* username, char* new_pass, int new_iter)
{
  FILE *originalfile = fopen("testfile.txt", "r");
  FILE *newfile = fopen("tempfile.txt","wt");
  char  user[32];//max 32 characters
  char  pass[12];//exactly 12 characters
  int N;

  while (fscanf(originalfile, "%s %s %d", user, pass,N) != EOF)//read username and password
  {
    if (strcmp(user, username) == 0)//if you find the username
    {
      //copy new as the new password and write to the newfile
      fprintf(newfile, "%s %s %d\n", user, new_pass,new_iter);
    }
    else
    {
      //write the original line into newfile
      fprintf(newfile, "%s %s %d\n", user, pass, N);
    }
  }

  //delete testfile.txt and rename newfile.txt to testfile.txt

  fclose(originalfile);
  fclose(newfile);

  remove("testfile.txt");
  rename("tempfile.txt", "testfile.txt");

}

void newUser(char* username, char* hashpass, int iterations)
{
  FILE *originalfile = fopen("testfile.txt", "r");
  FILE *newfile = fopen("tempfile.txt","wt");

  char user[32];//max 32 characters
  char pass[12];//exactly 12 characters
  int N;

  while (fscanf(originalfile, "%s %s %d", user, pass,N) != EOF)//read username and password
  {
    //write the original line into newfile
      fprintf(newfile, "%s %s %d\n", user, pass,N);
  }
  //write the new user into the end of the file
  fprintf(newfile, "%s %s %d\n", username, hashpass, iterations);

  //delete testfile.txt and rename newfile.txt to testfile.txt

  fclose(originalfile);
  fclose(newfile);

  remove("testfile.txt");
  rename("tempfile.txt", "testfile.txt");
}
