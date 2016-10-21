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
