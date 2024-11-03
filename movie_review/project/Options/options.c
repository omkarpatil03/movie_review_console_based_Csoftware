#include "options.h"
#include "../StructureResources.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


extern int MainState;
extern int LoginFlag;

//1. Edit Profile
void EditProfile(int *userID){
    FILE *fptr;
    userinfo_t TempUser;

    char UserID[6];
    sprintf(UserID, "%d", *userID);
    UserID[5]= '\0';

    printf("Enter New First Name: ");
    scanf("%s%*c", TempUser.FirstName);

    printf("Enter New Last Name: ");
    scanf("%s%*c", TempUser.LastName);

    printf("Enter New Email Id: ");
    scanf("%s%*c", TempUser.EmailID);

    printf("Enter New Mobile Number: ");
    scanf("%s%*c", TempUser.MobileNo);

    printf("Enter New Birthdate: \r\n");
    printf("Day: ");
    scanf("%d", &TempUser.Date.Day);
    printf("Month: ");
    scanf("%d", &TempUser.Date.Month);
    printf("Year: ");
    scanf("%d", &TempUser.Date.Year);

    fptr = fopen("UsersDatabase/users.txt", "r+");
    //check for same userID
    char TempBufferRead[SIZE];
    memset(TempBufferRead, '\0', SIZE);
        

    while(fread(TempBufferRead, sizeof(char), SIZE, fptr) > 0){    
        //use strstr return NULL if does not get needle in string, if get needle return adress of neddle
        if(strstr(TempBufferRead, UserID) != NULL){
            //This if means we get desired userID
            //get password
            char *token;
            int count = 0;
            int BreakFlag= 0;

            // Use strtok to tokenize based on spaces
            token = strtok(TempBufferRead, " ");
            while (token != NULL) {
                count++;
                    
                // Check if the token is the password
                if (count == 5) {
                    // This will be password
                    strcpy(TempUser.Password , token);
                    fseek(fptr, -(SIZE+1), SEEK_CUR);

                    char TempBufferWrite[SIZE];
                    memset(TempBufferWrite, '\0', SIZE);
                    TempBufferWrite[SIZE-1]= '\n';
                    TempBufferWrite[SIZE-2]= '\r';
                    sprintf(TempBufferWrite, "%d %s %s %s %s %s %d/%d/%d", *userID, TempUser.FirstName, TempUser.LastName,
                                                            TempUser.EmailID, TempUser.Password, TempUser.MobileNo,
                                                            TempUser.Date.Day, TempUser.Date.Month, TempUser.Date.Year);

                    fwrite(TempBufferWrite, sizeof(char), sizeof(TempBufferWrite), fptr);
                    printf("Profile Updated Successful!\r\n");
                    BreakFlag= 1;
                    break;

                }

                // Move to the next token
                token = strtok(NULL, " ");
            }

            if(BreakFlag == 1){
                fclose(fptr);
                break;
            }
        }
    }
    fclose(fptr);    
}

//2. Update Password
void UpdatePassword(int *userID){
    FILE *fptr;
    userinfo_t TempUser;

    char UserID[6];
    sprintf(UserID, "%d", *userID);
    UserID[5]= '\0';

    printf("Enter New Password: ");
    scanf("%s%*c", TempUser.Password);

    fptr = fopen("UsersDatabase/users.txt", "r+");
    //check for same userID
    char TempBufferRead[SIZE];
    memset(TempBufferRead, '\0', SIZE);

    while(fread(TempBufferRead, sizeof(char), SIZE, fptr) > 0){
        //use strstr return NULL if does not get needle in string, if get needle return adress of neddle
        if(strstr(TempBufferRead, UserID) != NULL){
            //This if means we get desired userID

            char *token;
            int count = 0;
            int BreakFlag= 0;
            //Use strtok to tokenize based on spaces
            token = strtok(TempBufferRead, " ");
            while (token != NULL) {
                count++;
                if(count == 2){
                    //This will be first Name
                    strcpy(TempUser.FirstName, token);
                }
                else if(count == 3){
                    //This will be last Name
                    strcpy(TempUser.LastName, token);
                }
                else if(count == 4){
                    //This will be email address
                    strcpy(TempUser.EmailID, token);
                }
                else if(count == 6){
                    //this will mobile number
                    strcpy(TempUser.MobileNo, token);
                }
                else if(count == 7){
                    //day
                    char *datePart = strtok(token, "/");
                    TempUser.Date.Day= atoi(datePart);
                    
                    //month
                    datePart = strtok(NULL, "/");
                    TempUser.Date.Month= atoi(datePart);
                    
                    //year
                    datePart = strtok(NULL, "/");
                    TempUser.Date.Year= atoi(datePart);

                    fseek(fptr, -(SIZE+1), SEEK_CUR);

                    char TempBufferWrite[SIZE];
                    memset(TempBufferWrite, '\0', SIZE);
                    TempBufferWrite[SIZE-1]= '\n';
                    TempBufferWrite[SIZE-2]= '\r';
                    sprintf(TempBufferWrite, "%d %s %s %s %s %s %d/%d/%d", *userID, TempUser.FirstName, TempUser.LastName,
                                                            TempUser.EmailID, TempUser.Password, TempUser.MobileNo,
                                                            TempUser.Date.Day, TempUser.Date.Month, TempUser.Date.Year);

                    fwrite(TempBufferWrite, sizeof(char), sizeof(TempBufferWrite), fptr);
                    printf("Password Updated Successful!\r\n");
                    BreakFlag= 1;
                    break;
                }

                // Move to the next token
                token = strtok(NULL, " ");
            }
            if(BreakFlag == 1){
                fclose(fptr);
                break;
            }
        }
    }
}

//5. Display all movies
void DisplayAllMovies(void){
    FILE *fptr;

    char TempBufferRead[1024];
    memset(TempBufferRead, '\0', 1024);

    fptr = fopen("movies/movies.txt", "r");

    while(fread(TempBufferRead, sizeof(char), 1024, fptr) > 0){ 
        char *token;

        // Use strtok to tokenize based on spaces
        
        token = strtok(TempBufferRead, "\n");
        while(token != NULL){
            printf("%s\r\n", token);
            
            //Move to the next token
            token = strtok(NULL, "\n");
        }
    }

    fclose(fptr);
}

//3. Write a Review
void WriteReview(int *userID){
    FILE *fptr;
    reviewinfo_t review;

    DisplayAllMovies();


    printf("\r\nEnter Movie ID: ");
    scanf("%d", &review.MovieID);

    printf("Enter Rating(out of 10): ");
    scanf("%d", &review.Rating);

    printf("Enter Review: ");
    scanf("%*c%[^\n]", review.Review);

    //timestamp
    time_t current_time;
    // Get current time in seconds
    time(&current_time);

    // Convert to local time
    struct tm *local_time = localtime(&current_time);

    // Format the time as "YYYY-MM-DD HH:MM:SS"
    strftime(review.Modified, sizeof(review.Modified), "%Y/%m/%d %H:%M:%S", local_time);


    fptr = fopen("ReviewsDatabase/reviews.txt", "r");

    if(fptr == NULL){
        //file is not yet created i.e. first review
        fclose(fptr);

        review.ReviewID= 5001;
        fptr= fopen("ReviewsDatabase/reviews.txt", "a");

        char TempBuffer[REVIEW_SIZE];
        memset(TempBuffer, '\0', REVIEW_SIZE);
        TempBuffer[REVIEW_SIZE-1]= '\n';
        TempBuffer[REVIEW_SIZE-2]= '\r';

        sprintf(TempBuffer, "Review [id=%d, movieId=%d, userId=%d, review=%s, rating=%d, modified=%s]", review.ReviewID, review.MovieID, *userID,
                                                 review.Review, review.Rating, review.Modified);

        fwrite(TempBuffer, sizeof(char), sizeof(TempBuffer), fptr);

        printf("Review Saved!\r\n");
    }
    else{
        char TempBufferWrite[REVIEW_SIZE];
        memset(TempBufferWrite, '\0', REVIEW_SIZE);
        TempBufferWrite[REVIEW_SIZE-1]= '\n';
        TempBufferWrite[REVIEW_SIZE-2]= '\r';

        //file is created and just need to append it so open it again in read and append mode
        fptr= fopen("ReviewsDatabase/reviews.txt", "r");

        //set file pointer at end of file
        fseek(fptr, 0, SEEK_END);
        fseek(fptr, -(REVIEW_SIZE+1), SEEK_CUR);

        char TempBufferRead[REVIEW_SIZE];
        memset(TempBufferRead, '\0', REVIEW_SIZE);
        fread(TempBufferRead, sizeof(char), SIZE, fptr);

        char TempReviewID[6];
        int i, j;
        for(i= 0, j=11; i < 5; i++, j++){
            if(TempBufferRead[j] >= 48 && TempBufferRead[j] <= 57){
                TempReviewID[i]= TempBufferRead[j];
            }
            else{
                i++;
                break;
            }
        }
        TempReviewID[i]= '\0';

        review.ReviewID= atoi(TempReviewID);   

        fclose(fptr);

        review.ReviewID++;

        fptr= fopen("ReviewsDatabase/reviews.txt", "a");

        
        sprintf(TempBufferWrite, "Review [id=%d, movieId=%d, userId=%d, review=%s, rating=%d, modified=%s]", review.ReviewID, review.MovieID, *userID,
                                                 review.Review, review.Rating, review.Modified);

        fwrite(TempBufferWrite, sizeof(char), sizeof(TempBufferWrite), fptr);
        
        printf("Review Saved!\r\n");
    }

    fclose(fptr);
}

//6. Display all reviews
void DisplayAllReviews(void){
    FILE *fptr;
    
    char TempBufferRead[REVIEW_SIZE];
    memset(TempBufferRead, '\0', REVIEW_SIZE);

    fptr = fopen("ReviewsDatabase/reviews.txt", "r");

    if(fptr == NULL){
        //No review file is created yet
        printf("Please Write a Reviews!\r\n");
    }
    else{
        while(fread(TempBufferRead, sizeof(char), REVIEW_SIZE, fptr) > 0){ 
            char *token;

            // Use strtok to tokenize based on spaces
            token = strtok(TempBufferRead, "\n");
            while(token != NULL){
                printf("%s\r\n", token);
                
                //Move to the next token
                token = strtok(NULL, "\n");
            }
        }
    }

    fclose(fptr);
}

//7. Display my Reviews
void DisplayMyReviews(int *userID){
    FILE *fptr;

    char UserID[6]= "";
    sprintf(UserID, "%d", *userID);
    UserID[5]= '\0';

    char TempBufferRead[REVIEW_SIZE];
    memset(TempBufferRead, '\0', REVIEW_SIZE);

    fptr = fopen("ReviewsDatabase/reviews.txt", "r");

    int MyreviewFlag= 0;

    if(fptr == NULL){
        //No review file is created yet
        printf("Please Write a Reviews!\r\n");
    }
    else{
        while(fread(TempBufferRead, sizeof(char), REVIEW_SIZE, fptr) > 0){ 
            char *token;

            // Use strtok to tokenize based on spaces
            token = strtok(TempBufferRead, "\n");
            while(token != NULL){

                if(strstr(token, UserID) != NULL){
                    printf("%s\r\n", token);
                    MyreviewFlag= 1;
                }
                //Move to the next token
                token = strtok(NULL, "\n");
            }
        }
    }
    if(MyreviewFlag == 0){
        printf("Please Write a Reviews!\r\n");
    }
    fclose(fptr);
}

//This function is called in Edit review function and Share review & Shared review with me
void DisplayReview(int reviewID){
    FILE *fptr;

    char ReviewID[6]= "";
    sprintf(ReviewID, "%d", reviewID);
    ReviewID[5]= '\0';

    char TempBufferRead[REVIEW_SIZE];
    memset(TempBufferRead, '\0', REVIEW_SIZE);

    fptr = fopen("ReviewsDatabase/reviews.txt", "r");

    int ValidReview= 0;

    while(fread(TempBufferRead, sizeof(char), REVIEW_SIZE, fptr) > 0){ 
        char *token;

        // Use strtok to tokenize based on spaces
        token = strtok(TempBufferRead, "\n");
        while(token != NULL){

            if(strstr(token, ReviewID) != NULL){
                printf("%s\r\n", token);
                ValidReview= 1;
            }
            //Move to the next token
            token = strtok(NULL, "\n");
        }
    }
    if(ValidReview == 0){
        printf("Please Enter Valid Review Id!\r\n");
    }
    fclose(fptr);
}

//4. Edit a review
void EditMyReview(int *userID){
    FILE *fptr;
    reviewinfo_t review;

    DisplayMyReviews(userID);

    int TempReviewID= 0;
    printf("Enter review Id to be edited: ");
    scanf("%d", &TempReviewID);

    char ReviewID[6]= "";
    sprintf(ReviewID, "%d", TempReviewID);
    ReviewID[5]= '\0';

    DisplayReview(TempReviewID);

    

    printf("Enter New Rating(out of 10): ");
    scanf("%d", &review.Rating);

    printf("Enter New Review: ");
    scanf("%*c%[^\n]", review.Review);

    //timestamp
    time_t current_time;
    // Get current time in seconds
    time(&current_time);

    // Convert to local time
    struct tm *local_time = localtime(&current_time);

    // Format the time as "YYYY-MM-DD HH:MM:SS"
    strftime(review.Modified, sizeof(review.Modified), "%Y/%m/%d %H:%M:%S", local_time);

    char TempBufferRead[REVIEW_SIZE];
    memset(TempBufferRead, '\0', REVIEW_SIZE);

    fptr = fopen("ReviewsDatabase/reviews.txt", "r+");

    while(fread(TempBufferRead, sizeof(char), REVIEW_SIZE, fptr) > 0){
        if(strstr(TempBufferRead, ReviewID) != NULL){

            char TempMovieID[3];

            char *temp= strstr(TempBufferRead, "movieId=");

            TempMovieID[0]= temp[8];
            TempMovieID[1]= temp[9];
            TempMovieID[2]= '\0';

            review.MovieID= atoi(TempMovieID);

            fseek(fptr, -(REVIEW_SIZE+1), SEEK_CUR);    

            char TempBufferWrite[REVIEW_SIZE];
            memset(TempBufferWrite, '\0', REVIEW_SIZE);
            TempBufferWrite[REVIEW_SIZE-1]= '\n';
            TempBufferWrite[REVIEW_SIZE-2]= '\r';

            sprintf(TempBufferWrite, "Review [id=%d, movieId=%d, userId=%d, review=%s, rating=%d, modified=%s]",
                                        TempReviewID, review.MovieID, *userID,
                                        review.Review, review.Rating, review.Modified);

            fwrite(TempBufferWrite, sizeof(char), sizeof(TempBufferWrite), fptr);

            printf("Review updated!\r\n");

            break;    
        }
    }
    fclose(fptr);
}

//Show user and their email --> This function is called in Share review 
void ShowUser_Email(){
    FILE *fptr;

    fptr = fopen("UsersDatabase/users.txt", "r");
    //check for same userID
    char TempBufferRead[SIZE];
    memset(TempBufferRead, '\0', SIZE);

    while(fread(TempBufferRead, sizeof(char), SIZE, fptr) > 0){
        char *token;
        int count = 0;

        // Use strtok to tokenize based on spaces
        token = strtok(TempBufferRead, " ");
        while(token != NULL){
            count++;

            if(count == 1){
                printf("[User ID=%s,", token);
            }
            else if(count == 2){
                printf("User= %s ", token);
            }
            else if(count == 3){
                printf("%s, ", token);
            }
            else if(count == 4){
                printf("User Email=%s]\r\n", token);    
            }

            token = strtok(NULL, " ");
        }
    }
}

//8. Display review shared with me
void DisplayReviewSharedwithMe(int *userID){
    FILE *fptr;

    char UserID[6]= "";
    sprintf(UserID, "%d", *userID);
    UserID[5]= '\0';

    fptr = fopen("ShareReviewsDatabase/shares.txt", "r");

    int Review_flag= 0;
    if(fptr == NULL){
        printf("No review has been Shared with You\r\n");
    }
    else{
        char TempBufferRead[SHARE_SIZE];
        memset(TempBufferRead, '\0', SHARE_SIZE);

        while(fread(TempBufferRead, sizeof(char), SHARE_SIZE, fptr) > 0){
            if(strstr(TempBufferRead, UserID) != NULL){
                char TempReviewID[6];
                char *temp= strstr(TempBufferRead, "Review_id=");

                TempReviewID[0]= temp[10];
                TempReviewID[1]= temp[11];
                TempReviewID[2]= temp[12];
                TempReviewID[3]= temp[13];
                TempReviewID[4]= temp[14];
                TempReviewID[5]= '\0';

                int ReviewID= atoi(TempReviewID);

                DisplayReview(ReviewID);
                Review_flag= 1;
            }
        }
    }

    if(Review_flag == 0){
        printf("No review has been Shared with You\r\n");
    }
    fclose(fptr);
}

//9. Share review
void ShareReview(int *userID){
    FILE *fptr;

    DisplayMyReviews(userID);

    int TempReviewID= 0;

    printf("Enter Review Id to be share: ");
    scanf("%d", &TempReviewID);

    DisplayReview(TempReviewID);

    ShowUser_Email();

    // Pointer to hold the array of user IDs
    int *user_ids = NULL;   
    int id, count = 0;
    // Start with a capacity of 1 -> as 0 can be at first place
    int capacity = 1;       

    // Allocate initial memory for the array
    user_ids = (int *)malloc(capacity * sizeof(int));
    if (user_ids == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter user ids to share review with (enter 0 to end): ");

    while (1) {
        scanf("%d", &id);

        // Stop when user enters 0 
        if(id == 0){
            break;
        }
        else if(id == 0 && count == 0){
            free(user_ids);
            printf("Review Shared with 0 users successfully.\r\n");
            return;
        }

        // Expand the array if the count reaches the current capacity
        if (count == capacity) {
            capacity *= 2;  // Double the capacity
            int *temp = realloc(user_ids, capacity * sizeof(int));
            if (temp == NULL) {
                printf("Memory reallocation failed.\n");
                free(user_ids);
                return;
            }
            user_ids = temp;
        }

        // Store the user ID in the array
        user_ids[count++] = id;
    }

    fptr = fopen("ShareReviewsDatabase/shares.txt", "a");

    //store info in file
    for (int i = 0; i < count; i++) {
        char TempBuffer[SHARE_SIZE];
        memset(TempBuffer, '\0', SHARE_SIZE);
        TempBuffer[SHARE_SIZE-1]= '\n';
        TempBuffer[SHARE_SIZE-2]= '\r';

        sprintf(TempBuffer, "Review_id=%d, User_id=%d", TempReviewID, user_ids[i]);
        fwrite(TempBuffer, sizeof(char), sizeof(TempBuffer), fptr);
    }

    printf("Review Shared with %d users successfully.\r\n", count);

    free(user_ids);
    fclose(fptr);
}

//10. delete a review --> only wanted data tobe rewrite in another file
void DeleteReview(int *userID){
    FILE *fptr;

    DisplayMyReviews(userID);

    int TempReviewID= 0;

    printf("Enter Review Id to be delete: ");
    scanf("%d", &TempReviewID);

    char ReviewID[6]= "";
    sprintf(ReviewID, "%d", TempReviewID);
    ReviewID[5]= '\0';

    DisplayReview(TempReviewID);

    fptr= fopen("ReviewsDatabase/reviews.txt", "r");

    //create and open temporary file to transfer data
    FILE *Tempfile= fopen("ReviewsDatabase/temp.txt", "w");

    char TempBufferRead[REVIEW_SIZE];
    memset(TempBufferRead, '\0', REVIEW_SIZE);

    while(fread(TempBufferRead, sizeof(char), REVIEW_SIZE, fptr) > 0){
        if(strstr(TempBufferRead, ReviewID) == NULL){
            fwrite(TempBufferRead, sizeof(char), sizeof(TempBufferRead), Tempfile);
        }
    }
    fclose(fptr);
    fclose(Tempfile);

    // Replace original file with temp file
    // Delete the original file
    remove("ReviewsDatabase/reviews.txt");       
    // Rename temp file to original filename
    rename("ReviewsDatabase/temp.txt", "ReviewsDatabase/reviews.txt");  

    //All delete shared review from share-database
    fptr= fopen("ShareReviewsDatabase/shares.txt", "r");

    //create and open temporary file to transfer data
    Tempfile= fopen("ShareReviewsDatabase/temp.txt", "w");

    char TempBuffer[SHARE_SIZE];
    memset(TempBuffer, '\0', SHARE_SIZE);

    while(fread(TempBuffer, sizeof(char), SHARE_SIZE, fptr) > 0){
        if(strstr(TempBuffer, ReviewID) == NULL){
            fwrite(TempBuffer, sizeof(char), sizeof(TempBuffer), Tempfile);
        }
    }

    fclose(fptr);
    fclose(Tempfile);

    // Replace original file with temp file
    // Delete the original file
    remove("ShareReviewsDatabase/shares.txt");       
    // Rename temp file to original filename
    rename("ShareReviewsDatabase/temp.txt", "ShareReviewsDatabase/shares.txt");

    printf("Review Deleted successfully!\r\n");
}

void Options(int *userID){
    int OptionState= 0;

    do{
        printf("\r\n0. Log Out\r\n");
        printf("1. Edit Profile\r\n");
        printf("2. Change Password\r\n");
        printf("3. Write a Review\r\n");
        printf("4. Edit Review\r\n");
        printf("5. Display all Movies\r\n");
        printf("6. Display all Reviews\r\n");
        printf("7. Display my Reviews\r\n");
        printf("8. Display Reviews shared with me\r\n");
        printf("9. Share a Review\r\n");
        printf("10. Delete a Review\r\n");

        printf("\r\nEnter choice:");
        scanf("%d", &OptionState);

        switch(OptionState){
            case 0:
                printf("Logout Successful!\r\n");
                LoginFlag= 0;
                OptionState= 0;
                MainState= 250;
            break;

            case 1:
                EditProfile(userID);
                OptionState= -1;
            break;

            case 2:
                UpdatePassword(userID);
                OptionState= -1;
            break;
            
            case 3:
                WriteReview(userID);
                OptionState= -1;
            break;

            case 4:
                EditMyReview(userID);
                OptionState= -1;
            break;

            case 5:
                DisplayAllMovies();
                OptionState= -1;
            break;

            case 6:
                DisplayAllReviews();
                OptionState= -1;
            break;

            case 7:
                DisplayMyReviews(userID);
                OptionState= -1;
            break;

            case 8:
                DisplayReviewSharedwithMe(userID);
                OptionState= -1;
            break;

            case 9:
                ShareReview(userID);
                OptionState= -1;
            break;

            case 10:
                DeleteReview(userID);
                OptionState= -1;
            break;

            case -1:
                //do nothing state
            break;

            default:
                printf("Please enter valid option!\r\n");
            break;
        }
    }while(OptionState != 0);
    
}