#ifndef DSAPROJECT_H
#define DSAPROJECT_H
#include <stdbool.h>

typedef struct student {
    char name[50];
    long id_num;
    float grade;
    struct student *next;

} student;

// Function prototypes
bool check_valid_id(student* head,long id);
struct student* createstudent(void); 
void displaylist(struct student*); 
struct student* addstudent(struct student *,char [],long ,float );  
int studentcount(struct student*);
int findstudent(struct student*, long); 
void deletelaststudent(struct student* ); 
void deleteById(struct student** ,long );
void sortlist(struct student* ); 
float averagexam (struct student *); 
void freelist(struct student*); 
void splitlist(struct student*,struct student**, struct student**); 
struct student* mergelists(struct student*, struct student*); 

#endif // DSAPROJECT_H

