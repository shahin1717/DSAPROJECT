#include "dsaproject.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
student* createstudent(void) {
    // Dynamically allocate memory for the student
    student* newstudent = (student*)malloc(sizeof(student));
    if (newstudent == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // Exit if memory allocation fails
    }

    // Get input for the student details
    printf("Enter student name: ");
    scanf("%49s", newstudent->name); // Limit input size to prevent overflow
    printf("Enter student ID: ");
    scanf("%ld", &newstudent->id_num);
    printf("Enter student grade: ");
    scanf("%f", &newstudent->grade);
    
    newstudent->next = NULL; // Initialize the next pointer to NULL

    return newstudent;}