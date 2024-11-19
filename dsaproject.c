#include "dsaproject.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_valid_id(student* head,long id) {
    student* temp = head;
    while (temp != NULL) {
        if (temp->id_num == id) {
            return false; // ID already used
        }
        temp = temp->next;
    }
    return true;
} 

student* createstudent(void) {
    // Dynamically allocate memory for the student
    student* newstudent = (student*)malloc(sizeof(student));
    if (newstudent == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // Exit if memory allocation fails
    }
    newstudent->next = NULL;
    printf("Enter the name of the student: ");
    scanf("%s", newstudent->name);
    printf("Enter the ID of the student: ");
    scanf("%ld", &newstudent->id_num);   
    printf("Enter the grade of the student: ");
    scanf("%f", &newstudent->grade);
        
    return newstudent;
    }



void displaylist(student* head) {
    if (head == NULL) {
        printf("No students to display.\n");
        return;
    }
    student* tempr = head;
    while( tempr != NULL) {
        printf("\033[1;32m|------------------------------|\033[0m\n");
        printf("Name: %s\n", tempr->name);
        printf("ID: %ld\n", tempr->id_num);
        printf("Grade: %.2f\n", tempr->grade);
        tempr = tempr->next;
    }
        printf("\033[1;32m|------------------------------|\033[0m\n");
    
}
student* addstudent(student* head, char name[], long id, float grade) {
    // Dynamically allocate memory for a new student
    student* newstudent = (student*)malloc(sizeof(student));
    if (newstudent == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    // Initialize new student data
    strcpy(newstudent->name, name);
    newstudent->id_num = id;
    newstudent->grade = grade;
    newstudent->next = NULL;

    // Add to the end of the list
    if (head == NULL) {
        // If the list is empty, the new student becomes the head
        return newstudent;
    }

    // Traverse to the end of the list
    student* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newstudent; // Add the new student at the end
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
        getchar();
        char c;
        c=getchar();
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
            // Compare by grade instead of ID
            if (i->grade < j->grade) {
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


void splitlist(struct student *head, struct student **higher, struct student **lower) {
    *higher = NULL;  // initialize list for higher than 65
    *lower = NULL;   // initialize list for lower than 65
    struct student *current = head;

    while (current != NULL) {
        struct student *newNode = (struct student *)malloc(sizeof(struct student));
        if (newNode == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        // copy the current student's data to the new node
        strcpy(newNode->name, current->name);
        newNode->id_num = current->id_num;
        newNode->grade = current->grade;
        newNode->next = NULL;

        // add to the end of correct list 
        if (current->grade >= 65) {
            if (*higher == NULL) {
                *higher = newNode;
            } else {
                struct student *temp = *higher;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        } else {
            if (*lower == NULL) {
                *lower = newNode;
            } else {
                struct student *temp = *lower;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        current = current->next; // move to the next student in the full list
    }
    sortlist(*lower); // sort students that got less than 65
    sortlist(*higher); // sort students that got more than 65

    // Print the higher and lower lists
    printf("[1;34mHigher than 65:\033[0m\n");
    displaylist(*higher);
    printf("1;34mLower than 65:\033[0m\n");
    displaylist(*lower);
}

struct student* mergelists(struct student *lower, struct student *higher) {
    // Sort the individual lists if required (by grade)

    if (lower == NULL) return higher;  // if lower list is empty, return higher
    if (higher == NULL) return lower;  // if higher list is empty, return lower

    struct student *current = lower;
    
    // Traverse to the end of the lower list
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Merge the higher list to the end of the lower list
    current->next = higher; // attach higher list directly to lower

    return lower;  // Return the merged list
}

void freelist(struct student* head) {
    struct student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);  // Free the current node
    }
    head = NULL;  // Set the head to NULL after freeing
    printf("List freed.\n");
}

