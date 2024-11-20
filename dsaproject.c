
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
    struct student* head = NULL; // Pointer to the head of the list
    struct student* current = NULL; // Pointer to track the last student
    char stopCondition; // Variable to control the loop

    while (1) { 
        printf("Do you want to add a student? (y/n): ");
        // checks valid input
        while (scanf(" %c", &stopCondition) != 1) { 
            printf("\033[1;31mInvalid input. Please enter a character.\033[0m\n");
            scanf("%*[^\n]"); // clear invalid input
        }
        while (stopCondition != 'y' && stopCondition != 'n') { 
            printf("\033[1;31mInvalid input. Please enter y or n.\033[0m\n");
            scanf(" %c", &stopCondition);
        }
        if (stopCondition == 'n') { // Exit loop if 'n' is entered
            break;
        }

        // Allocate memory for a new student
        struct student* newStudent = (struct student*)malloc(sizeof(struct student));
        if (newStudent == NULL) { 
            printf("\033[1;31mMemory allocation failed!\033[0m\n");
            exit(1);
        }

        // enteringstudent details
        printf("Enter student card ID number: ");
        while (scanf("%ld", &newStudent->id_num) != 1) { // Validate ID input
            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
            scanf("%*[^\n]");
        }
        while (!check_valid_id(head, newStudent->id_num)) { // Check for unique ID
            printf("\033[1;31mID already exists. Please enter a new ID.\033[0m\n");
            scanf("%ld", &newStudent->id_num);
        }
        getchar(); // Clear buffer

        printf("Enter student name: ");
        if (fgets(newStudent->name, MAX, stdin) == NULL) { // Read name input
            printf("Error reading name.\n");
        }
        newStudent->name[strcspn(newStudent->name, "\n")] = 0; // Remove newline from name

        printf("Enter student grade: ");
        while (scanf("%f", &newStudent->grade) != 1) { // Validate grade input
            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
            scanf("%*[^\n]");
        }
        printf("\n");
        getchar(); // Clear buffer

        newStudent->next = NULL; // Initialize next pointer to NULL

        if (head == NULL) { // Check if list is empty
            head = newStudent; // Set new student as the head
        } else {
            current->next = newStudent; // Link new student to the end of the list
        }
        current = newStudent; // Update current to the new student
    }
    return head; // Return the head of the list
}



void displaylist(student* head) {
    if (head == NULL) { // Check if the list is empty
        printf("\033[1;31mNo students to display.\033[0m\n");
        return;
    }
    student* tempr = head; // Pointer to traverse the list
    while (tempr != NULL) { 
        printf("\033[1;32m|------------------------------|\033[0m\n");
        printf("Name: %s\n", tempr->name); 
        printf("ID: %ld\n", tempr->id_num); 
        printf("Grade: %.2f\n", tempr->grade); 
        tempr = tempr->next; // Move to the next student
    }
    printf("\033[1;32m|------------------------------|\033[0m\n");
}

student* addstudent(student* head, char name[], long id, float grade) {
    student* newstudent = (student*)malloc(sizeof(student)); // Allocate memory for new student
    if (newstudent == NULL) { // Check for allocation failure
        printf("\033[1;31mMemory allocation failed!\033[0m\n");
        return head;
    }

    // new student details
    strcpy(newstudent->name, name); // Copy name
    newstudent->id_num = id; // Set ID
    newstudent->grade = grade; // Set grade
    newstudent->next = NULL; // Initialize next pointer to NULL

    if (head == NULL) { // If list is empty
        return newstudent; // New student becomes the head
    }

    student* temp = head; // Pointer goes through list
    while (temp->next != NULL) { // Loop to find the end of the list
        temp = temp->next;
    }
    temp->next = newstudent; // Link the new student at the end of the list
    return head; // Return the head of the list
}


int studentcount(student* head) {
    int count = 0; // Initialize counter to zero
    student* temp = head; // Pointer to traverse the list
    while (temp != NULL) { // Loop until the end of the list
        count++; // Increment counter for each student
        temp = temp->next; // Move to the next student
    }
    return count; // Return the total count
}

int findstudent(student* head, long id) {
    student* temp = head; // Pointer to traverse the list
    int count = 0; // Initialize position counter
    while (temp != NULL) { // Loop through the list
        if (temp->id_num == id) { // Check if the current student matches the ID
            return count; // Return the index of the matching student
        }
        count++; // Increment position counter
        temp = temp->next; // Move to the next student
    }
    return -1; // Return -1 if no match is found
}


void deletelaststudent(student* head) {
    if (head == NULL) {
        printf("The list is empty, nothing to delete.\n"); 
        printf("Press any key to continue...\n");
        getchar(); 
        char c;
        c = getchar(); 
        return; 
    }

    printf("\033[1;32mDeleting the last student...\033[0m\n");

    student* temp = head; // Temporary pointer to go though the list
    student* prev = NULL; // Pointer to keep track of the previous node

    // Traverse the list to reach the last node
    while (temp->next != NULL) {
        prev = temp; // Update the previous node
        temp = temp->next; // Move to the next node
    }

    // If the list has only one student
    if (prev == NULL) {
        free(temp); // free the only node in the list
        free(head); // free the head pointer
        temp = NULL; // set the temporary pointer to NULL
        head = NULL; // set the head pointer to NULL
    } else {
        prev->next = NULL; // remove the last node from the list
        free(temp); // free the memory of the last node
    }

    usleep(500000); // Pause for half a second for user experience
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
    // If the list is empty or contains only one student, there's no need to sort
    if (head == NULL || head->next == NULL) return;

    struct student *i, *j; // Pointers to go through through the list
    long temp_id; // for swapping ID
    float temp_grade; // for swapping grade
    char temp_name[50]; // for swapping name

    // Bubble sort: Traverse the list and compare adjacent students
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            // Compare the grades of two students (sorting in descending order)
            if (i->grade < j->grade) {
                // Swap IDs
                temp_id = i->id_num;
                i->id_num = j->id_num;
                j->id_num = temp_id;

                // Swap grades
                temp_grade = i->grade;
                i->grade = j->grade;
                j->grade = temp_grade;

                // Swap names
                strcpy(temp_name, i->name); 
                strcpy(i->name, j->name);   
                strcpy(j->name, temp_name); 
            }
        }
    }
}


float averagexam(student* head) {
    student* temp = head; // Pointer to traverse the student list
    float sum = 0;        // Variable to store the sum of student grades
    int count = 0;        // Variable to count the number of students

    // Traverse the list and accumulate the grades
    while (temp != NULL) {
        sum += temp->grade; 
        count++;           
        temp = temp->next;  
    }    

    if (count == 0) {// Check if the list is empty
        printf("\033[1;31mNo students in the list to calculate the average.\033[0m\n");
        return 0; 
    }

    return sum / count;
}



void splitlist(struct student *head, struct student **higher, struct student **lower) {
    *higher = NULL;  // Initialize the list for students with grades >= 65
    *lower = NULL;   // Initialize the list for students with grades < 65
    struct student *current = head;  // Pointer to traverse the original list

    while (current != NULL) {
        // Allocate memory for a new student node
        struct student *newNode = (struct student *)malloc(sizeof(struct student));
        if (newNode == NULL) {
            printf("\033[1;31mMemory allocation failed!\033[0m\n");  
            exit(1);
        }

        // copy data from the current student to the new node
        strcpy(newNode->name, current->name); 
        newNode->id_num = current->id_num;   
        newNode->grade = current->grade;   
        newNode->next = NULL;            

        // Add the new node to the correct list based on grade
        if (current->grade >= 65) {
            if (*higher == NULL) {
                *higher = newNode;  // If the higher list is empty, make the new node the head
            } else {
                // Traverse to the end of the higher list and add the new node
                struct student *temp = *higher;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        } else {
            if (*lower == NULL) {
                *lower = newNode;  // If the lower list is empty, make the new node the head
            } else {
                // Traverse to the end of the lower list and add the new node
                struct student *temp = *lower;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }

        current = current->next;  // Move to the next student in the original list
    }

    // Sort both lists based on grade
    sortlist(*lower);  
    sortlist(*higher); 

    printf("\033[1;34mHigher than 65:\033[0m\n");
    displaylist(*higher);  
    printf("\033[1;34mLower than 65:\033[0m\n");
    displaylist(*lower); 
}

struct student* mergelists(struct student *lower, struct student *higher) {

    if (lower == NULL) return higher; 
    if (higher == NULL) return lower; 

    struct student *current = lower;
    
    // Traverse to the end of the lower list
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = higher; // attach higher list directly to lower

    return lower;  
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
