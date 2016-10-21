#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int32_t authenticate(char* userID);
void randnumgen(void);
void hashCompare(char * clientResult);
char* hash(char * password);
void E(char *in, char *out);
char * F(char* hashpw, int32_t ranNum);
const char* getfield(char* line, int num);

int32_t randnum;
char username[33];

int32_t authenticate(char* userID)
{
  strcpy(username,userID);
  randnumgen();
  return randnum;
}

void randnumgen(void)
{
  randnum = (int32_t) rand();
}

void hashCompare(char * clientResult)
{
  char* hashTablePass = (char*) malloc(13);
  //find hash password from the table
  //compute serverResult = hash ^ randnum; Haven't declared result yet
  FILE* readCSV = fopen("db.csv","r");
  char line[1024];
  while(fgets(line, 1024, readCSV))
  {
    char* tmp = strdup(line);
    if(strcmp(username, getfield(tmp,1)) == 0) //Found user
    {
      hashTablePass = getfield(line,2);
      //printf("%s\n", hashTablePass);
      free(tmp);
      fclose(readCSV);
    }
  }
  //then compare the hashes and print the result
  printf("Comparing: %s\n",clientResult);
  printf("With: %s\n",F(hashTablePass, randnum));
  if(strcmp(clientResult, F(hashTablePass, randnum)) == 0)
  {
    printf("Access Granted\n");
  }
  else
  {
    printf("Access Denied\n");
  }
}

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

//same stuff as in olmhash
char* hash(char * password)
{
	char *hash = (char*)calloc(13,1);
  int n = 3;
	//iterate through every 4 byte chunk and perform the hashing function
	for (int i = 0; i < n; i++)
	{
		E(&password[4*i], &hash[4*i]);
	}
	return hash;
}

void E(char *in, char *out)
{
  out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
  out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
  out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
  out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}

char * F(char* hashpw, int32_t ranNum)
{
  char * resulting = (char*)calloc(13,1);//extra for null
  char * hashHolder = (char*)calloc(13,1);
  hashHolder = strdup(hashpw);
  int32_t originalRanNum = ranNum;//save me the trouble of learning too much about bit shifting
  int i, n;//n will be what chunk of ranNum I'm using, m is what char of hashpw
  int m = 0;
  for (n = 0; n < 3; n++)
  {
    for (i = 0; i < 4; i++)
    {
      resulting[m] = hashHolder[m] ^ ranNum;//do it 
      m++;//next char
      ranNum = ranNum >> 8;//shift
    }
    ranNum = originalRanNum;//reset
  }
  free(hashHolder);
  return resulting;
}
