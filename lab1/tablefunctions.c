#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Method can search for either a username or password
int findCred (char * str)
{
  FILE *fp;
  char buf[33]; //buffer for username. Username can be up to 32 characters, add null that's 33
  //not sure if leaving space for the null is necessary or not

  if (fp = fopen("testfile.txt", "r") == NULL){//if failed to open file
      return(-1);
  }

  while (!feof(fp)) {
    fscanf(fp, "%32s", buf);//read a string, max 32 chars
    if(strcmp(str,buf)){
      fclose(fp);
      return 0;//found it
    }

  }
  fclose(fp);
  return 1;//didn't find it
}

void resetPasswd(char* new, char* username)
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
