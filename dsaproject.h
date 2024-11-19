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
struct student* createstudent(void); 
void displaylist(struct student*); 
struct student* addstudent(struct student *,char [],long ,float ); 
int studentcount(struct student*);
int findstudent(struct student*, long); 
void deletelaststudent(struct student* ); 
void sortlist(struct student* ); 
float averagexam (struct student *); 
void splitlist(struct student*,struct student**, struct student**); 
struct student* mergelists(struct student*, struct student*); 
bool check_valid_id(student*,long );
void freelist(struct student* );
void deleteById(struct student**, long);
#endif // DSAPROJECT_H
