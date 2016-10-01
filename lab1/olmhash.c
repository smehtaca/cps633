#include "passwordfunctions.h"
#include "hashfunctions.h"
#include "userfunctions.h"
#include "tablefunctions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main (void)
{

    int n = 0;
    char userID[32];
    char password[12];
    char newpass[12];
    char* hashpass = NULL;
    char input[24];
    int iter;
    int login;

      printf("Enter your userID\n");
      scanf("%s",userID);
      if(checkUIDCriteria(userID))
      {
        printf("Your user id is invalid. Bye.");
        return 0;
      }
      char* result = findCred(userID,3);
      if (strcmp(result,"") != 0) //found it
      {
        for(int i = 0; i < atoi(result); i++)
        {
          printf("UserID found. Enter your old password");
          scanf("%s", password);

          char * foundPass = findCred(userID,2); //check matching password
          login = strcmp(foundPass, password);
          if(!login) break;
        }

        if(login)
        {
          printf("You have exausted all login attempts. Bye.");
          return 0;
        }

        if (!login) //correct password
        {
          printf("Login successful.");
          printf("Enter pass or attempts to change password or number of login attempts");
          scanf("%s",input);
          if(strcmp(input,"pass"))
          {
            printf("Enter new password");
            scanf("%s", newpass);
          }
          else if(strcmp(input,"attempts"))
          {
            printf("Enter new attempt limit");
            scanf("%d", iter);
          }

          while(checkPWCriteria(newpass))
          {
            printf("Passwords are alphanumeric only. Please try again.");
            scanf("%s", newpass);
          }

          resetCred(userID, hashpass, iter);
        }

      }
      else//not found
      {
        printf("Username not found. Please enter a password for this user\n");
        scanf("%s", password);
        //TODO check if the password is proper
        //TODO compute the hash
        newUser(userID, hashpass);
      }
    //if not found, prompt password for new user (which was just entered)
    //compute hash and add the username and password to the table
    //if user id exists, prompt old password and hash it
    //check if it matches in table
    //if so, ask for a new password and replace it
    //otherwise increment attempts number


}
