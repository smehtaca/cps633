#include "passwordfunctions.h"
#include "hashfunctions.h"
#include "userfunctions.h"
#include "tablefunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{

    char* userID = (char*) malloc(sizeof(char)*13);
    char* password = (char*) malloc(sizeof(char)*33);
    char* newpass = (char*) malloc(sizeof(char)*33);
    char* hashpass = (char*)malloc(sizeof(char)*1024);
    char* foundPass = (char*) malloc(sizeof(char)*1024);
    char input[24];
    int iter = 0;
    int login;
    int found;
    char* hashed;
    char* result;
    int n = 1;


    printf("Enter your userID\n");
    scanf("%s",userID);

    if(checkUIDCriteria(userID))
    {
      printf("Your user id is invalid. Bye.\n");
      return 0;
    }

    result = findCred(userID,3);
    found = strcmp(result,"");

    n = 5; //Using atoi kills it
    if (found != 0) //found it
    {

      result = findCred(userID,2);

      for(int i = 0; i < n; i++)
      {
        printf("UserID found. Enter your old password\n");
        scanf("%s", password);

          foundPass = findCred(userID,2); //for some reason never returns a proper result
          puts(foundPass);

          char firstBlock[5], secondBlock[5], thirdBlock[5];

          strncpy(firstBlock,password,4);
          firstBlock[5] = '\0';

          strncpy(secondBlock,password+4,4);
          secondBlock[5] = '\0';

          strncpy(thirdBlock,password+8,4);
          thirdBlock[5] = '\0';

          hashed = computeHash(firstBlock,secondBlock,thirdBlock);
          puts(hashed);
          login = strcmp(foundPass, password);//should compare foundPass and hashed
          if(!login) break;

        }

        if((login != 0) && (found != 0))
        {
          printf("You have exausted all login attempts. Bye.\n");
          return 0;
        }

        if ((login == 0 ) && (found != 0)) //correct password
        {
          printf("Login successful.\n");
          printf("Enter pass or attempts to change password or number of login attempts\n");
          scanf("%s",input);
          if(!strcmp(input,"pass"))
          {
            printf("Enter new password\n");
            scanf("%s", newpass);
            while(checkPWCriteria(newpass))
            {
              printf("Passwords are alphanumeric only. Please try again.\n");
              scanf("%s", newpass);
            }
          }
          if(!strcmp(input,"attempts"))
          {
            printf("Enter new attempt limit\n");
            scanf("%d", &iter);
          }

            resetCred(userID, newpass, iter);
            return 0;
          }

        if( found == 0)//not found
        {
          printf("Username not found. Please enter a password for this user\n");
          scanf("%s", password);

          while(checkPWCriteria(password))
          {
            printf("Passwords are alphanumeric only. Please try again.\n");
            scanf("%s", password);
          }

          printf("Please enter login attempt limit for this user\n");
          scanf("%d", &iter);

          char firstBlock[5], secondBlock[5], thirdBlock[5];

          strncpy(firstBlock,password,4);
          firstBlock[5] = '\0';

          strncpy(secondBlock,password+4,4);
          secondBlock[5] = '\0';

          strncpy(thirdBlock,password+8,4);
          thirdBlock[5] = '\0';

          hashpass = computeHash(firstBlock,secondBlock,thirdBlock);
          newUser(userID, hashpass, iter);
          return 0;
        }


}

}
