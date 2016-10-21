#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

const char* getfield(char* line, int num);
int foundUser(char* username, int num);
int createUser(char* username);
int updatePass(char* username);
void E(char *in, char *out);
char* hash(char* password);
int checkUserNameCrit(char* username);
int checkPWCriteria(char* password);
int isAlphaNumeric(char* password);
int checkPWLength(char* password);
char* pwPadder(char* password);
char* toLowerCase(char* password);


int main(int argc, char* argv[])
{
  char user[33];
  int N;

  N = atoi(argv[1]) - 1;


  printf("Welcome to the OLMHash Program!\n");
  printf("Please begin by entering a username.\n");
  scanf("%s",user); //Check criteria

  if(checkUserNameCrit(user) == 1)
  {
    printf("Invalid username.\n");
    printf("Good bye.\n");
    return 0;
  }

  if(checkUserNameCrit(user))
  {

    printf("The entered username does not meet the username criteria.\n");
    printf("Goodbye.\n");
    return 0;

  }


  FILE* readCSV = fopen("db.csv","r");
  char line[1024];
  char* tmp = (char*)malloc(33);
  while(fgets(line, 1024, readCSV))
  {
    tmp = strdup(line);
    if(strcmp( user,getfield(tmp,1)) == 0) //Found username
    {
      free(tmp);
      fclose(readCSV);
      exit(foundUser(user, N));

    }


  }

  if(createUser(user) == 0)//User account not found thus account must be created
  {
    free(tmp);
    fclose(readCSV);

    printf("New User account created.\n");
    printf("Goodbye.\n");
    exit(0);
  }


  return 0;
}

//Reads and tokenizes CSV
const char* getfield(char* line, int num)
{
    const char* token;
    for (token = strtok(line, ";"); token && *token; token = strtok(NULL, ";\n"))
    {
        if (!--num)
            return token;
    }
    return (const char*) "Not found";
}

//User has been found, ask for password
int foundUser(char* username, int num)
{
  int iter_left = 0;

  if(num <= 0)
  {
    printf("You have exausted all your login attempts.\n");
    printf("Goodbye.\n");
    exit(0);
  }

  char* pass = (char*) malloc(13);
  char* hashpass = (char*) malloc(13);
  char* paddedpass = (char*)malloc(13);


  printf("Please enter the password for this user account.\n");
  scanf("%s",pass); //Hash Password


  while ( checkPWCriteria(pass) == 1)
  {
    printf("Passwords are alphanumeric only. Please try again.\n");
    scanf("%s", pass);
  }

  if ( checkPWCriteria(pass) == 2)
  {
    paddedpass = pwPadder(pass);
    hashpass = hash(paddedpass);

  }

  if(checkPWCriteria(pass) == 0)
  {
    hashpass = hash(pass);
  }

  FILE* readCSV = fopen("db.csv","r");
  char line[1024];
  while(fgets(line, 1024, readCSV))
  {
    char* tmp = strdup(line);

    if( strcmp(hashpass,getfield(tmp,2)) == 0) //Found password
    {
      free(tmp);
      fclose(readCSV);
      free(pass);
      free(hashpass);
     return updatePass(username);
    }

    else // password check loop
    {
      iter_left = num - 1;
      printf("The password you entered is incorrect.\n");
      printf("You have %d tries left.\n",num);
      return foundUser(username, iter_left);

    }
    free(tmp);
    fclose(readCSV);
    free(pass);
    free(hashpass);

  }
  return 0;
}


int createUser(char* username)
{

  char* passNewAcct = (char*)malloc(13);
  char* hashedpass = (char*)malloc(13);
  char* paddedpass = (char*)malloc(13);
  int pw_crit = 0;


  printf("User account does not exist.\n");
  printf("Please enter a password for this user account.\n");
  printf("Passwords may be up to 12 characters.\n");
  printf("No special characters are allowed.\n");
  scanf("%s",passNewAcct);

  pw_crit = checkPWCriteria(passNewAcct);

  if(pw_crit == 0)
  {
    hashedpass = hash(passNewAcct);
  }

  while ( pw_crit == 1)
  {
    printf("Passwords are alphanumeric only. Please try again.\n");
    scanf("%s", passNewAcct);
  }

  if ( pw_crit == 2)
  {
    paddedpass = pwPadder(passNewAcct);
    hashedpass = hash(paddedpass);
  }



    FILE *fp = fopen("db.csv", "a+");

  if(fp == NULL)
  {
    printf("An error occured while creating the user account.\n");
    printf("Goodbye.\n");
    exit(1);
  }


  fprintf(fp, "%s;%s\n", username, hashedpass);
  fclose(fp);
  free(passNewAcct);
  free(hashedpass);
  return 0;
}

int updatePass(char* username)
{

  char line[1024];
  char* new_pass = (char*) malloc(13);
  char* hashedpass = (char*)malloc(13);
  char* padded = (char*)malloc(13);

  printf("Please enter a new password.\n");
  scanf("%s",new_pass);

  if(checkPWCriteria(new_pass) == 0)
  {
    hashedpass = hash(new_pass);
  }


  while( checkPWCriteria(new_pass) == 1)
  {
    printf("Passwords are alphanumeric only. Please try again.\n");
    scanf("%s", new_pass);
  }

  if ( checkPWCriteria(new_pass) == 2)
  {
    padded = pwPadder(new_pass);

    hashedpass = hash(padded);
  }




  FILE* db = fopen("db.csv","r");
  FILE* new_db = fopen("new.csv","w+");

  char* tmp = (char*)malloc(1024);

  while(fgets(line,1024,db))
  {
    tmp = strdup(line);
    if(strcmp(username,getfield(tmp,1)) != 0) //Not found username yet
    {
      fputs(line,new_db);
    }
  }



  free(tmp);

  fprintf(new_db,"%s;%s\n",username,hashedpass); //append data to file
  fclose(db);
  fclose(new_db);
  free(new_pass);
  free(hashedpass);
  free(padded);

  remove("db.csv");
  rename("new.csv","db.csv");

  printf("Your new password has been set.\n");
  printf("Goodbye.\n");

  return 0;
}

/********************* E function *************************/
// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out)
{
  //make the input characters uppercase.
	char c0 = toupper(in[0]);
	char c1 = toupper(in[1]);
	char c2 = toupper(in[2]);
	char c3 = toupper(in[3]);

	out[0] = (c0 & 0x80) ^ (((c0 >> 1) & 0x7F) ^ ((c0) & 0x7F));
	out[1] = ((c1 & 0x80) ^ ((c0 << 7) & 0x80)) ^ (((c1 >> 1) & 0x7F) ^ ((c1) & 0x7F));
	out[2] = ((c2 & 0x80) ^ ((c1 << 7) & 0x80)) ^ (((c2 >> 1) & 0x7F) ^ ((c2) & 0x7F));
	out[3] = ((c3 & 0x80) ^ ((c2 << 7) & 0x80)) ^ (((c3 >> 1) & 0x7F) ^ ((c3) & 0x7F));
}

char* hash(char * password){

	char *hash = (char*)calloc(13,1);
  int n = 3;
	//if the allocation fails print error message
	if (hash == NULL)
	{
		printf("Setting password failed\n");
		return hash;
	}

	//iterate through every 4 byte chunk and perform the hashing function
	for (int i = 0; i < n; i++)
	{
		E(&password[4*i], &hash[4*i]);
	}
	return hash;
}

int checkUserNameCrit(char* username)
{
  int len = strlen(username);
  if(len < 4 || len > 32 ) return 1;
  else return 0;
}

//Checks if password is alphanumeric
int isAlphaNumeric(char* password)
{
  int len = strlen(password);
  int current, i;
  for(i = 0; i < len; i++)
  {
    current = password[i];
    if(isalnum(current) == 0) //If not alnum ecounteres non-zero,it returns 0
    {
      return 1;
    }
  }
  return 0;
}

int checkPWLength(char* password)
{
  int len = 0;

  len = strlen(password);

  if(len == 12) //return 0 if meets criteria
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


  char* paddedPW;
  paddedPW = NULL;
  int passlen = strlen(password);

  if(passlen == 12)
  {
    return password;
  }


  paddedPW = (char *) malloc(13);
  paddedPW = password;

  int len = 12 - passlen; // Max pass length less one sub current password length

  for(int i = 0; i < len; i++)
  {
    paddedPW[i + passlen + 1] = '\0';
  }
  paddedPW[12] = '\0';

  return paddedPW;
}

//Checks if password is between 4 and 12 characters and alphanumeric
int checkPWCriteria(char* password)
{



  if( (checkPWLength(password) == 0) && (isAlphaNumeric(password) == 0))
  {
    return 0;
  }
  else if ( ( checkPWLength(password) == 1) && (isAlphaNumeric(password) == 0))
  {
    return 2;
  }
  else
  {
    return 1;
  }
}
