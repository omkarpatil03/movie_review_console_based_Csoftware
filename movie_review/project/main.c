#include <stdio.h>
#include <stdint.h>
#include "StructureResources.h"
#include "signUp\signup.h"
#include "signIn\signin.h"
#include "Options\options.h"

int MainState= 0;
int LoginFlag= 0;

int main(void){
    userinfo_t UserForSignUp;
    userinfo_t UserForSignIn;

    do{ 
        if(LoginFlag == 0){
            printf("\r\nChoose Option to SignIn/SignUp:\r\n");
            printf("0. Exit\r\n");
            printf("1. SignIn\r\n");
            printf("2. SignUp\r\n");
            
            printf("\r\nEnter choice:");
            scanf("%d", &MainState);
        }

        switch(MainState){
            case 1:
                SignInPage(&UserForSignIn);
            break;

            case 2:
                SignUpPage(&UserForSignUp);
            break;

            case 0:
                printf("Thank You!\r\n");
            break;

            case 100:
                //Login successful state
                Options(&UserForSignIn.UserID);
            break;

            case 250:
                //logout state
            break;

            default:
                printf("Please enter valid option!\r\n");
            break;
        }

    }while(MainState != 0);

    return 0;
}