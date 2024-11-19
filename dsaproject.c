
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
    if (head == NULL) {
        printf("No students to display.\n");
        return;
    }
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
     if (head == NULL) {
        printf("The list is empty, nothing to delete.\n");
        printf("Press any key to continue...\n");
        return;
    }
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

void deleteById(struct student **head, long id_num) {
    int index = findstudent(*head, id_num);
    if (index == -1) {
        printf("Student with ID %ld not found.\n", id_num);
        return;
    }

    if (*head == NULL) {
        printf("The list is empty, nothing to delete.\n");
        return;
    }

    if (index == 0) {
        // Delete the first student
        struct student *temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Student with ID %ld deleted from index %d.\n", id_num, index);
        return;
    }

    // Traverse to the student just before the one to delete
    struct student *current = *head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    struct student *temp = current->next; // Node to be deleted
    current->next = temp->next;           // Bypass the node
    free(temp);                           // Free the memory
    printf("Student with ID %ld deleted from index %d.\n", id_num, index);
}

void sortlist(struct student* head) {
    if (head == NULL || head->next == NULL) return; // If the list has 0 or 1 element, no need to sort

    struct student *i, *j;
    long temp_id;
    float temp_grade;
    char temp_name[50];

    // Bubble sort: Traverse through the list and swap nodes as needed
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->id_num > j->id_num) {
                // Swap the entire nodes
                temp_id = i->id_num;
                i->id_num = j->id_num;
                j->id_num = temp_id;

                temp_grade = i->grade;
                i->grade = j->grade;
                j->grade = temp_grade;

                strcpy(temp_name, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, temp_name);
            }
        }
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
