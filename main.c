#include <stdio.h>
#include <string.h>
#include "dsaproject.h"

int main(){
    student* newstudent = createstudent();
    printf("Student name: %s\n", newstudent->name);
    printf("Student ID: %ld\n", newstudent->id_num);
    printf("Student grade: %.2f\n", newstudent->grade);
}