
#include <stdio.h>
#include <string.h>
#include "dsaproject.h"
#include <stdlib.h>
#include <unistd.h>
#define MAX 50

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
    struct student *head = NULL;      // Pointer to the head of the list
    struct student *current = NULL;   // Pointer to track the current student in the list
    char stopCondition;           // Variable to control the loop

    while (1) {
        printf("Do you want to add a student? (y/n): ");
        while (scanf(" %c", &stopCondition) != 1) {
            printf("\033[1;31mInvalid input. Please enter a character.\033[0m\n");
            scanf("%*[^\n]");
        }
        while (stopCondition != 'y' && stopCondition != 'n') {
            printf("\033[1;31mInvalid input. Please enter y or n.\033[0m\n");
            scanf(" %c", &stopCondition);
        }
        // Stop adding students if the user inputs n
        if (stopCondition == 'n') {
            break;
        }

        // Allocate memory for a new student node
        struct student *newStudent = (struct student *)malloc(sizeof(struct student));
        if (newStudent == NULL) {
            printf("\033[1;31mMemory allocation failed!\033[0m\n");
            exit(1);
        }

        // Prompt the user for student details
        printf("Enter student card ID number: ");
        while (scanf("%ld", &newStudent->id_num) != 1) {
            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
            scanf("%*[^\n]");
        }
        while (!check_valid_id(head, newStudent->id_num)) {
            printf("\033[1;31mID already exists. Please enter a new ID.\033[0m\n");
            scanf("%ld", &newStudent->id_num);
        }
        getchar();
        printf("Enter student name: ");
        if (fgets(newStudent->name, MAX, stdin) == NULL) {
            printf("Error reading name.\n");
        }
        newStudent->name[strcspn(newStudent->name, "\n")] = 0;
                
        printf("Enter student grade: ");
        while (scanf("%f", &newStudent->grade) != 1) {
            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
            scanf("%*[^\n]");
        }
        printf("\n"); 
        getchar();

        // Initialize the next pointer to NULL
        newStudent->next = NULL;

        // Add the new student to the list
        if (head == NULL) {
            head = newStudent;  // Set the first student as the head
        } else {
            current->next = newStudent;  // Link the new student to the current last student
        }
        current = newStudent;  // Update the current pointer to the new student
    }

    // Return the head of the list
    return head;
}



void displaylist(student* head) {
    if (head == NULL) {
        printf("\033[1;31mNo students to display.\033[0m\n");
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
        printf("\033[1;31mMemory allocation failed!\033[0m\n");
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
    printf("\033[1;32mDeleting the last student...\033[0m\n");
    student* temp = head;
    student* prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL) {
        free(temp);
        free(head);
        temp = NULL;
        head = NULL;

    } else {
        prev->next = NULL;
        free(temp);
    }
                usleep(500000);
    printf("\033[1;32mLast student deleted.\033[0m\n");
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
            printf("\033[1;31mMemory allocation failed!\033[0m\n");
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
    printf("\033[1;34mHigher than 65:\033[0m\n");
    displaylist(*higher);
    printf("\033[1;34mLower than 65:\033[0m\n");
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
}
