#include<stdio.h>
#include<stdlib.h>
#include<string.h>

<<<<<<< HEAD
int findCred (char* str);
void resetPasswd(char* old, char* new);
//Method will search for either a username or password
int findCred (char * str)
=======
char * findCred (char * username)
>>>>>>> Alex's_Branch_3
{
  FILE *fp;
  char * user[32];//max 32 characters
  char * pass[12];//exactly 12 characters
  char * result;//to be returned

  result = NULL;

<<<<<<< HEAD
  if ((fp = fopen("testfile.txt", "r")) == NULL)
  {//if failed to open file
      return(-1);
  }

  while (!feof(fp))
  {
    //fscanf(fp, %32s, buf);//read a string, max 32 chars
    fgets(buf,32,fp);
    if(strcmp(str,buf))
    {
      fclose(fp);
      return 0;//found it
=======
  if (fp = fopen("testfile.txt", "r") == NULL)
  {//if failed to open file
      exit(1);
  }

  while (fscanf(fp, "%s %s", user, pass) != EOF)//read username and password
  {
    if(strcmp(user, username) == 0) //found it
    {
      result = pass;
      break;
>>>>>>> Alex's_Branch_3
    }
  }

  fclose(fp);
  return result;
}

void resetPasswd(char* username, char* new)
{
  FILE *originalfile = fopen("testfile.txt", "r");
  FILE *newfile = fopen("tempfile.txt","wt");
  char * user[32];//max 32 characters
  char * pass[12];//exactly 12 characters

  while (fscanf(originalfile, "%s %s", user, pass) != EOF)//read username and password
  {
    if (strcmp(user, username) == 0)//if you find the username
    {
      //copy new as the new password and write to the newfile
      fprintf(newfile, "%s %s\n", user, new);
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

  char * user[32];//max 32 characters
  char * pass[12];//exactly 12 characters

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
