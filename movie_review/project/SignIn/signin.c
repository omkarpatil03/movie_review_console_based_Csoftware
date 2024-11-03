#include "signin.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


extern int LoginFlag;
extern int MainState;


void SignInPage(userinfo_t *user){
    FILE *fptr;

    printf("Enter Email ID: ");
    scanf("%s%*c", user->EmailID);

    printf("Enter Password: ");
    scanf("%s%*c", user->Password);

    fptr = fopen("UsersDatabase/users.txt", "r");

    if(fptr == NULL){
        //file is not yet created i.e. first signup
        printf("Register your account!\r\n");
        fclose(fptr);
    }
    else{
        //check emailid and password with data base
        char TempBufferRead[SIZE];
        memset(TempBufferRead, '\0', SIZE);

        while(fread(TempBufferRead, sizeof(char), SIZE, fptr) > 0){
            //testing
            //printf("%s", TempBufferRead);
            if( (strstr(TempBufferRead, user->EmailID) != NULL) &&
                (strstr(TempBufferRead, user->Password) != NULL) ){
                printf("Login Successful!\r\n");
                LoginFlag= 1;
                MainState= 100;

                //return user ID
                char TempUserID[6];
                int i;
                for(i= 0; i < 5; i++){
                    if(TempBufferRead[i] >= 48 && TempBufferRead[i] <= 57){
                        TempUserID[i]= TempBufferRead[i];
                    }
                    else{
                        i++;
                        break;
                    }
                }
                    
                TempUserID[i]= '\0';
                //store UserID
                user->UserID= atoi(TempUserID);    

                fclose(fptr);
                return;
            }

        }
        fclose(fptr);

        if(LoginFlag == 0){
            printf("Sorry, your EmailId/Password was incorrect. Please double-check your EmailID/Password.\r\n");
            return;
        }
    }
}