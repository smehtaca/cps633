#include "passwordfunctions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main (void)
{
    int n = 0;
    char userID[32];
    char password[12];
    char newpass[12];
    char * hashpass;

    if(n != 3)
    {
      printf("Enter your userID\n");
      scanf("%s",userID);
      //TODO check if the user id is proper
      if (strcmp(findCred(userID),NULL) != 0) //found it
      {
        printf("UserID found. Enter your old password");
        scanf("%s", password);
        //TODO compute the hash
        char * foundPass = findCred(userID); //check matching password
        if (strcmp(foundPass, password) == 0) //correct password
        {
          printf("Login successful. Enter new password");
          scanf("%s", newpass);
          //TODO hash the new password
          resetPasswd(userID, hashpass);
        }
        else
        {
          //otherwise increment n and go back
          //TODO properly loop this part
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

    //check attempts
    //prompt for user ID and check the table
    //if not found, prompt password for new user (which was just entered)
    //compute hash and add the username and password to the table
    //if user id exists, prompt old password and hash it
    //check if it matches in table
    //if so, ask for a new password and replace it
    //otherwise increment attempts number
    }
}
