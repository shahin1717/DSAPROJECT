#include "dsaproject.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



struct student* addstudent(struct student *head, char name[], long id_num, float grade) {
    // Allocate memory for a new student node
    struct student *newStudent = (struct student *)malloc(sizeof(struct student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Set the fields of the new student
    strcpy(newStudent->name, name);
    newStudent->id_num = id_num;
    newStudent->grade = grade;
    newStudent->next = NULL;  // New student will be the last node, so next is NULL

    // Check if the list is empty (head is NULL)
    if (head == NULL) {
        // If the list is empty, the new student becomes the head
        return newStudent;
    } else {
        // Traverse to the end of the list
        struct student *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Append the new student to the end
        current->next = newStudent;
    }

    // Return the head of the list
    return head;
}
// Function to create a student list
struct student* createstudent(void) {
    struct student *head = NULL;      // Pointer to the head of the list
    struct student *current = NULL;   // Pointer to track the current student in the list
    char stopCondition[10];           // Variable to control the loop

    while (1) {
        printf("Do you want to add a student? (yes/no): ");
        scanf("%s", stopCondition);

        // Stop adding students if the user inputs "no"
        if (strcmp(stopCondition, "no") == 0) {
            break;
        }

        // Allocate memory for a new student node
        struct student *newStudent = (struct student *)malloc(sizeof(struct student));
        if (newStudent == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }

        // Prompt the user for student details
        printf("Enter student name: ");
        scanf("%s", newStudent->name);
        printf("Enter student card ID number: ");
        scanf("%ld", &newStudent->id_num);
        printf("Enter student grade: ");
        scanf("%f", &newStudent->grade);

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

void display(struct student* head) {
    struct student *current = head;
    while (current != NULL) {
        printf("Name: %s, ID: %ld, Grade: %.2f\n", current->name, current->id_num, current->grade);
        current = current->next;
    }
}



struct student* addstudent(struct student *head, char name[], long id_num, float grade) {
    // Allocate memory for a new student node
    struct student *newStudent = (struct student *)malloc(sizeof(struct student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Set the fields of the new student
    strcpy(newStudent->name, name);
    newStudent->id_num = id_num;
    newStudent->grade = grade;
    newStudent->next = NULL;  // New student will be the last node, so next is NULL

    // Check if the list is empty (head is NULL)
    if (head == NULL) {
        // If the list is empty, the new student becomes the head
        return newStudent;
    } else {
        // Traverse to the end of the list
        struct student *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Append the new student to the end
        current->next = newStudent;
    }

    // Return the head of the list
    return head;
}

int studentcount(struct student *head) {
    int count = 0;
    struct student *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int findstudent(struct student *head, long id_num) {
    int index = 0;
    struct student *current = head;
    while (current != NULL) {
        if (current->id_num == id_num) {
            return index; // Return the index if the ID is found
        }
        index++;
        current = current->next;
    }
    return -1; // Return -1 if the ID is not found in the list
}
int findstudent(struct student *head, long id_num) {
    int index = 0;
    struct student *current = head;
    while (current != NULL) {
        if (current->id_num == id_num) {
            return index; // Return the index if the ID is found
        }
        index++;
        current = current->next;
    }
    return -1; // Return -1 if the ID is not found in the list
}

// Function to delete a student from the list by ID
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
void deletelaststudent(struct student *head) {
    // Check if the list is empty
    if (head == NULL) {
        printf("The list is empty, nothing to delete.\n");
        return;
    }

    // Check if the list has only one student
    if (head->next == NULL) {
        free(head);
        head = NULL; // This does not affect the caller; use a double pointer for real modification
        printf("Last student deleted. The list is now empty.\n");
        return;
    }

    // Traverse to the second last student
    struct student *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    // Free the memory of the last student and set the second last student's next to NULL
    free(current->next);
    current->next = NULL;
    printf("Last student deleted.\n");
}

void sortlist(struct student* head) {
    if (head == NULL || head->next == NULL) return; // If the list has 0 or 1 element, no need to sort

    struct student *i, *j;
    long temp_id;
    float temp_grade;
    char temp_name[50];

    // Bubble sort: Traverse through the list and swap data as needed
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->id_num > j->id_num) {
                // Swap the id_num
                temp_id = i->id_num;
                i->id_num = j->id_num;
                j->id_num = temp_id;

                // Swap the grade
                temp_grade = i->grade;
                i->grade = j->grade;
                j->grade = temp_grade;

                // Swap the name
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
}

struct student* mergelists(struct student *lower, struct student *higher) {
    sortlist(lower); // sort students that got less that 65
    sortlist(higher); // sort students that got more that 65

    if (lower == NULL) return higher;
    if (higher == NULL) return lower;

    struct student *current = lower;
    while (current->next != NULL) // merges them by adding higher list to the end of lower list
    {
        current = current->next;
    }
    current->next = higher->next;    

    return lower;
}