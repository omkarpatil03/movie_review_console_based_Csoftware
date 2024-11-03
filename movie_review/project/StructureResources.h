#ifndef StructureResources_H_
#define StructureResources_H_

#include <stdint.h>
#include <time.h>

typedef struct Date{
    int Day;
    int Month;
    int Year; 
}date_t;

typedef struct UserInfo{
    int UserID;

    char FirstName[16];
    char LastName[16];
    char EmailID[64];
    char Password[16];
    char MobileNo[16];
    date_t Date;

}userinfo_t;

typedef struct ReviewInfo{
    int ReviewID;

    int MovieID;
    char Review[128];
    int Rating;
    int UserID;
    
    char Modified[32];
}reviewinfo_t;

typedef struct Shares{
    int ReviewID;
    int UserID;
}shares_t;

#define     SIZE            (sizeof(userinfo_t) + 2)
#define     REVIEW_SIZE     (sizeof(reviewinfo_t) + 52)
#define     SHARE_SIZE      (sizeof(shares_t) + 22)

#endif