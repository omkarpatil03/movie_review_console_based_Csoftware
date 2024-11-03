#include "signup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void SignUpPage(userinfo_t *user){
    FILE *fptr;

    printf("Enter First Name: ");
    scanf("%s%*c", user->FirstName);

    printf("Enter Last Name: ");
    scanf("%s%*c", user->LastName);

    printf("Enter Email Id: ");
    scanf("%s%*c", user->EmailID);

    printf("Enter Password: ");
    scanf("%s%*c", user->Password);

    printf("Enter Mobile Number: ");
    scanf("%s%*c", user->MobileNo);

    printf("Enter Birthdate: \r\n");
    printf("Day: ");
    scanf("%d", &user->Date.Day);
    printf("Month: ");
    scanf("%d", &user->Date.Month);
    printf("Year: ");
    scanf("%d", &user->Date.Year);

    fptr = fopen("UsersDatabase/users.txt", "r");

    if(fptr == NULL){
        //file is not yet created i.e. first signup
        fclose(fptr);
        
        user->UserID = 1001;
        fptr= fopen("UsersDatabase/users.txt", "a");

        char TempBuffer[SIZE];
        memset(TempBuffer, '\0', SIZE);
        TempBuffer[SIZE-1]= '\n';
        TempBuffer[SIZE-2]= '\r';


        sprintf(TempBuffer, "%d %s %s %s %s %s %d/%d/%d", user->UserID, user->FirstName, user->LastName,
                                                user->EmailID, user->Password, user->MobileNo,
                                                user->Date.Day, user->Date.Month, user->Date.Year);


        fwrite(TempBuffer, sizeof(char), sizeof(TempBuffer), fptr);                                        
    }
    else{
        //check for duplicate email and phone number
        char TempBufferRead[SIZE];
        memset(TempBufferRead, '\0', SIZE);
        

        while(fread(TempBufferRead, sizeof(char), SIZE, fptr) > 0){
            //testing
            //printf("%s", TempBufferRead);
            
            //use strstr return NULL if does not get needle in string, if get needle return adress of neddle
            if(strstr(TempBufferRead, user->EmailID) != NULL){
                printf("This Email ID is already in use!\r\n");
                fclose(fptr);
                return;
            }
        }    
        
        fclose(fptr);

        {
            char TempBufferWrite[SIZE];
            memset(TempBufferWrite, '\0', SIZE);
            TempBufferWrite[SIZE-1]= '\n';
            TempBufferWrite[SIZE-2]= '\r';

            //file is created and just need to append it so open it again in read and append mode
            fptr= fopen("UsersDatabase/users.txt", "r");

            //set file pointer at end of file
            fseek(fptr, 0, SEEK_END);
            fseek(fptr, -(SIZE+1), SEEK_CUR);

            fread(TempBufferRead, sizeof(char), SIZE, fptr);

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
            user->UserID= atoi(TempUserID);   

            fclose(fptr);

            user->UserID++;

            fptr= fopen("UsersDatabase/users.txt", "a");

            sprintf(TempBufferWrite, "%d %s %s %s %s %s %d/%d/%d", user->UserID, user->FirstName, user->LastName,
                                                    user->EmailID, user->Password, user->MobileNo,
                                                    user->Date.Day, user->Date.Month, user->Date.Year);

            fwrite(TempBufferWrite, sizeof(char), sizeof(TempBufferWrite), fptr);                                       
        }
    }
    
    //close file
    fclose(fptr);
}