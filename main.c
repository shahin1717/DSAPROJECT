
#include <stdio.h> 
#include <string.h> 
#include "dsaproject.h" 
#include "dsaproject.c"
#include <stdlib.h> 
#include <unistd.h> 
#define MAX 50

int main() {

    printf("\033[1;36m");
    printf("\n=============================================================\n");
    printf("\033[0m");

    char welcome[50] = "\tWelcome to the Student Management System\n";
    for (int i = 0; i < strlen(welcome); i++) {
        printf("\033[1;36m%c\033[0m", welcome[i]); 
        usleep(1000); // adds delay for animation effect
    }
    printf("\033[1;36m=============================================================\033[0m\n");
    usleep(600000); // pause to allow users to read the welcome message

    //creates variables for later use
    char c; // store input for returning to the menu
    student* head = NULL; // pointer for main list
    student* highlevel = NULL; // pointer for high-level grade sublist
    student* lowlevel = NULL; // pointer for low-level grade sublist

    while (1) { // main prog loop
        // display menu options
        printf("\t\t\t\033[1;32mMenu:\033[0m\n");
        printf("1. \033[1;34mCreate list\033[0m\n");
        printf("2. \033[1;34mAdd new student\033[0m\n");
        printf("3. \033[1;34mSearch for a student\033[0m\n");
        printf("4. \033[1;34mDisplay student list\033[0m\n");
        printf("5. \033[1;34mSort the list of students by grade\033[0m\n");
        printf("6. \033[1;34mSplit and merge lists by grade\033[0m\n");
        printf("7. \033[1;34mCalculate exam average\033[0m\n");
        printf("8. \033[1;34mDelete last student\033[0m\n");
        printf("9. \033[1;34mDelete by ID\033[0m\n");
        printf("10. \033[1;34mFree lists\033[0m\n");
        printf("11. \033[1;34mExit\033[0m\n");
        printf("\033[1;32m---------------------------------------------\033[0m\n");
        
        int choice; // variable to store user's menu choice

        // input validation loop for the menu choice
        while (1) {
            printf("Enter your choice: ");
            if (scanf("%d", &choice) == 1) { // checks if input is an integer
                break; // exit loop if valid
            } else {
                printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                scanf("%*[^\n]"); // clear the input buffer
            }
        }

        printf("\033[H\033[J");// clear the screen

        // handle menu options with a switch statement
        switch (choice) {
            case 1: { // create list
                freelist(head); // free the existing list to start fresh
                head = NULL;    // reset the head pointer to NULL
                printf("\033[1;32mCreating a new student list...\033[0m\n");
                usleep(500000); // pause for half a second

                head = createstudent(); // assign the new list to hesd

                printf("\033[1;32mList created successfully.\033[0m\n"); 
                break;
            }            

            case 2: { // add student
                printf("\033[1;34mAdding new students...\033[0m\n");
                usleep(500000); // add delay
                char name[50]; // storing student names
                long id; // storing student IDs
                float grade; // storing student grades
                int num; // storing the num of students to add

                printf("Enter number of students to add: ");
                while (scanf("%d", &num) != 1) { // checks if the num of students is int
                    printf("\033[1;31mInvalid input. Please enter a number.\033[0m");
                    scanf("%*[^\n]"); // clear the input buffer
                }

                for (int i = 0; i < num; i++) { // loop to add each student
                    printf("Enter the ID of the student %d: ", i+1);
                    while (scanf("%ld", &id) != 1) { // validate ID input
                        printf("\033[1;31mInvalid input. Please enter a number.\033[0m");
                        scanf("%*[^\n]");
                    }
                    while (!check_valid_id(head, id)) { // ensure ID is not aldeady in use
                        printf("\033[1;33mID already used. Enter a different ID: \033[0m");
                        while (scanf("%ld", &id) != 1) {
                            printf("\033[1;31mInvalid input. Please enter a number.\033[0m");
                            scanf("%*[^\n]");
                        }
                    }
                    getchar(); // clear newline left by scanf
                    printf("Enter the name of the student %d: ", i+1);
                    if (fgets(name, MAX, stdin) == NULL) { // read student's name
                        printf("Error reading name.\n");
                    }
                    name[strcspn(name, "\n")] = 0; // remove trailing newline from name
                        
                    printf("Enter the grade of the student %d: ", i+1);
                    while (scanf("%f", &grade) != 1) { // validate grade input
                        printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                        scanf("%*[^\n]");
                    }

                    head = addstudent(head, name, id, grade); // add student to the list
                }
                printf("\033[1;32mStudents added successfully.\033[0m\n");
                break;
            }
            case 3: { // find student by id
                printf("\033[1;34mSearching for a student...\033[0m\n"); 
                usleep(500000); // pause for half a second

                int id_search; // variable to store the ID 
                printf("Enter the ID of the student you want to search for: ");
                while (scanf("%d", &id_search) != 1) { 
                    // validate if the input is an integer
                    printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n"); 
                    scanf("%*[^\n]"); // clear the input buffer
                }

                student* temp2 = head; // pointer to traverse the list
                int index = findstudent(head, id_search); // get the index of the student in the list

                if (index == -1) {
                    // Check if the student was not found
                    printf("\033[1;31mStudent not found.\033[0m\n"); 
                } else {
                    // If the student is found traverse to the specific index
                    for (int i = 0; i < index; i++) {
                        temp2 = temp2->next; // move to the next student
                    }

                    printf("\033[1;34mStudent Details:\033[0m\n");
                    printf("Name: %s\n", temp2->name); 
                    printf("ID: %ld\n", temp2->id_num);
                    printf("Grade: %.2f\n", temp2->grade);
                }
                break; 
            }

            case 4: {// display the list of students
                printf("\033[1;34mDisplaying student list...\033[0m\n"); 
                usleep(500000); 
                displaylist(head);
                break; 
            }

            case 5: { // sort the student list by grades
                printf("\033[1;32mSorting the list by grade...\033[0m\n"); 
                usleep(500000); 
                sortlist(head); 
                printf("\033[1;32mList sorted by grade.\033[0m\n"); 
                break; 
            }

            case 6: { // split and merge sub-lists by grades
                printf("\033[1;33mSplitting and merging sub-lists...\033[0m\n"); 
                usleep(500000); 
                splitlist(head, &highlevel, &lowlevel); 
                printf("\033[1;33mMerged two sub-lists sorted by grade:\033[0m\n"); 
                displaylist(mergelists(highlevel, lowlevel)); 
                break; 
            }

            case 7: { // calculate the average grade of students
                printf("\033[1;34mCalculating exam average...\033[0m\n"); 
                usleep(500000); 
                float ave = averagexam(head); // calculate the average grade
                printf("\033[1;34mAverage exam score: %.2f\033[0m\n", ave); 

                // compare the average score 
                if (ave > 65) {
                    printf("The average is greater than 65.\n"); // average is above 65
                } else if (ave < 50) {
                    printf("The average is less than 50.\n"); // average is below 50
                } else {
                    printf("The average is between 50 and 65.\n"); // average falls within the range
                }
                break; 
            }

            case 8: { // delete the last student in the list
                printf("\033[1;31mDeleting the last student...\033[0m\n");
                usleep(500000); 
                deletelaststudent(head); 
                printf("\033[1;32mLast student deleted successfully.\033[0m\n"); 
                break;
            } 
            case 9: { // delete a student by their ID
                if (head == NULL) {
                    // if the list is empty, inform the user
                    printf("\033[1;31mList is empty.\033[0m\n");
                    break; 
                }
                printf("\033[1;32mDeleting student by ID...\033[0m\n"); 
                usleep(500000); 

                long id_num; // variable to store the ID to delete
                printf("Enter the ID of the student you want to delete: ");
                while (scanf("%ld", &id_num) != 1) {
                    // validate the input to ensure it's a number
                    printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n"); 
                    scanf("%*[^\n]"); // clear the input buffer
                }

                if (findstudent(head, id_num) == -1) {
                    // check if the student with the given ID exists
                    printf("\033[1;31mStudent not found.\033[0m\n"); 
                } else {
                    // if the student is found, proceed to delete
                    deleteById(&head, id_num);
                    usleep(500000); 
                    printf("\033[1;32mStudent deleted successfully.\033[0m\n"); 
                }
                break; 
            }

            case 10: { // free all the lists
                printf("\033[1;31mFreeing all lists...\033[0m\n"); 
                usleep(500000); 
                freelist(head); 
                freelist(highlevel);
                freelist(lowlevel);

                // set all list pointers to NULL
                head = NULL;
                highlevel = NULL;
                lowlevel = NULL;

                printf("\033[1;32mAll student data cleared.\033[0m\n"); 
                break; 
            }

            case 11: { // exit the program
                printf("\t\t\t\033[1;32;40mThanks for using the Student Management System!!!\03\033[0m\n"); 
                printf("\t\t\033[1;40mCreated by Alakparov Shahin, Alizada Fidan, Aliyeva Nazrin\033[0m\n"); // credits
                printf("\t\t\t\t\033[1;40mExiting program...\02\033[0m\n"); 
                exit(1); // exit the program with exit code 1
                break;
            }

            default: { // invalid menu choices
                printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
                usleep(200000); 
                break; 
            }
        }


        // prompt user to press any key to return to the menu
        printf("Press any key to return to the menu...\n");
        getchar(); 
        c = getchar();
        printf("\033[H\033[J"); // clear the screen
    }
}
