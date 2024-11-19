
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
    newstudent->next = NULL; // Initialize the next pointer to NULL

    return newstudent;}

void displaylist(student* head) {
    student* tempr = head;
    while( tempr != NULL) {
        printf("Name: %s\n", tempr->name);
        printf("ID: %ld\n", tempr->id_num);
        printf("Grade: %.2f\n", tempr->grade);
        printf("\n");
        tempr = tempr->next;
    }
}
student* addstudent(student* head, char name[], long id, float grade) {
    student* newstudent = createstudent();
    strcpy(newstudent->name, name);
    newstudent->id_num = id;
    newstudent->grade = grade;
    student* temp = head;
    if (head == NULL) {
        head = newstudent;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newstudent;
    }
    return head;
}

int studentcount(student* head) {
    int count = 0;
    student* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int findstudent(student* head, long id) {
    student* temp = head;
    int count = 0;
    while (temp != NULL) {
        if (temp->id_num == id) {
            return count;
        }
        count++;
        temp = temp->next;
    }
    return -1;
}

void deletelaststudent(student* head) {
    student* temp = head;
    student* prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL) {
        free(temp);
        head = NULL;
    } else {
        prev->next = NULL;
        free(temp);
    }
}

void sortlist(student* head) {
    student* temp1 = head;
    student* temp2 = NULL;
    float tempGrade;
    while (temp1 != NULL) {
        temp2 = temp1->next;
        while (temp2 != NULL) {
            if (temp1->grade > temp2->grade) {
                // Swap grades
                tempGrade = temp1->grade;
                temp1->grade = temp2->grade;
                temp2->grade = tempGrade;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

float averagexam(student* head) {
    student* temp = head;
    float sum = 0;
    int count = 0;
    while (temp != NULL) {
        sum += temp->grade;
        count++;
        temp = temp->next;
    }
    return sum / count;
}
