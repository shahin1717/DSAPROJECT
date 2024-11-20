int main() {
    printf("\033[1;36m");
    printf("\n=============================================================\n");
    printf("\033[0m");
    printf("\033[1;36m W"); usleep(100000);
    printf("e"); usleep(100000);
    printf("l"); usleep(100000);
    printf("c"); usleep(100000);
    printf("o"); usleep(100000);
    printf("m"); usleep(100000);
    printf("e"); usleep(100000);
    printf(" to the Student Management System\033[0m\n");
    printf("\033[1;36m=============================================================\033[0m\n");
    usleep(500000);

    char c;
    student* head = NULL;
    student* highlevel = NULL;
    student* lowlevel = NULL;

    while (1) {
        printf("\t\t\t\033[1;32mMenu:\033[0m\n");
        printf("1. \033[1;34mEnter students\033[0m\n");
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
        
        int choice;

        // input validation loop
        while (1) {
            printf("Enter your choice: ");
            if (scanf("%d", &choice) == 1) {
                break;
            } else {
                printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                scanf("%*[^\n]"); // Clear the input buffer
            }
        }

        // Clear screen
        printf("\033[H\033[J"); 

        switch (choice) {
            case 1:
                {
                    printf("\033[1;32mCreating a student list...\033[0m\n");
                    usleep(500000);
                    student* temp = createstudent();
                    if (head == NULL) {
                        head = temp;
                    } else {
                        student* temp2 = head;
                        while (temp2->next != NULL) {
                            temp2 = temp2->next;
                        }
                        temp2->next = temp;
                    }
                    printf("\033[1;32mList created successfully.\033[0m\n");
                }
                break;
            case 2:
                {
                    printf("\033[1;34mAdding new students...\033[0m\n");
                    usleep(500000);
                    char name[50];
                    long id;
                    float grade;
                    int num;

                    printf("Enter number of students to add: ");
                    while (scanf("%d", &num) != 1) {
                        printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                        scanf("%*[^\n]"); // Clear the input buffer
                    }

                    for (int i = 0; i < num; i++) {
                        printf("Enter the name of the student %d: ", i+1);
                        scanf("%s", name);
                        printf("Enter the ID of the student %d: ", i+1);
                        while (scanf("%ld", &id) != 1) {
                            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                            scanf("%*[^\n]");
                        }
                        while (!check_valid_id(head, id)) {
                            printf("\033[1;33mID already used. Enter a different ID: \033[0m");
                            while (scanf("%ld", &id) != 1) {
                                printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                                scanf("%*[^\n]");
                            }
                        }
                        printf("Enter the grade of the student %d: ", i+1);
                        while (scanf("%f", &grade) != 1) {
                            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                            scanf("%*[^\n]");
                        }

                        head = addstudent(head, name, id, grade);
                    }
                    printf("\033[1;32mStudents added successfully.\033[0m\n");
                }
                break;
            case 3:
                {
                    printf("\033[1;34mSearching for a student...\033[0m\n");
                    usleep(500000);
                    int id_search;
                    printf("Enter the ID of the student you want to search for: ");
                    while (scanf("%d", &id_search) != 1) {
                        printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                        scanf("%*[^\n]");
                    }
                    student* temp2 = head;
                    int index = findstudent(head, id_search);
                    if (index == -1) {
                        printf("\033[1;31mStudent not found.\033[0m\n");
                    } else {
                        for (int i = 0; i < index; i++) {
                            temp2 = temp2->next;
                        }
                        printf("\033[1;34mStudent Details:\033[0m\n");
                        printf("Name: %s\n", temp2->name);
                        printf("ID: %ld\n", temp2->id_num);
                        printf("Grade: %.2f\n", temp2->grade);
                    }
                }
                break;
            case 4:
                printf("\033[1;34mDisplaying student list...\033[0m\n");
                usleep(500000);
                displaylist(head);
                break;
            case 5:
                printf("\033[1;32mSorting the list by grade...\033[0m\n");
                usleep(500000);
                sortlist(head);
                printf("\033[1;32mList sorted by grade.\033[0m\n");
                break;
            case 6:
                printf("\033[1;33mSplitting and merging sub-lists...\033[0m\n");
                usleep(500000);
                splitlist(head, &highlevel, &lowlevel);
                printf("\033[1;33mMerged two sub-lists sorted by grade:\033[0m\n");
                displaylist(mergelists(highlevel, lowlevel));
                break;
            case 7:
                {
                    printf("\033[1;34mCalculating exam average...\033[0m\n");
                    usleep(500000);
                    float ave = averagexam(head);
                    printf("\033[1;34mAverage exam score: %.2f\033[0m\n", ave);
                    if (ave > 65) {
                        printf("The average is greater than 65.\n");
                    } else if (ave < 50) {
                        printf("The average is less than 50.\n");
                    } else {
                        printf("The average is between 50 and 65.\n");
                    }
                }
                break;
            case 8:
                printf("\033[1;32mDeleting the last student...\033[0m\n");
                usleep(500000);
                deletelaststudent(head);
                printf("\033[1;32mLast student deleted.\033[0m\n");
                break;
            case 9:
                {
                    printf("\033[1;32mDeleting student by ID...\033[0m\n");
                    usleep(500000);
                    long id_num;
                    printf("Enter the ID of the student you want to delete: ");
                    while (scanf("%ld", &id_num) != 1) {
                        printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
                        scanf("%*[^\n]");
                    }
                    deleteById(&head, id_num);
                    if (findstudent(head, id_num) == -1)
                        printf("\033[1;31mStudent not found.\033[0m\n");
                    else 
                        printf("\033[1;32mStudent deleted successfully.\033[0m\n");
                }
                break;
            case 10:
                printf("\033[1;31mFreeing all lists...\033[0m\n");
                usleep(500000);
                freelist(head);
                head = NULL;
                printf("\033[1;32mAll student data cleared.\033[0m\n");
                break;
            case 11:
                printf("\t\t\t\033[1;32;40mThanks for using the Student Management System!!!\03\033[0m\n");
                printf("\t\t\033[1;40mCreated by Alakparov Shahin, Alizada Fidan, Aliyeva Nazrin\033[0m\n"); 
                printf("\t\t\t\t\033[1;40mExiting program...\02\033[0m\n");
                exit(1);
                break;
            default:
                printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
                usleep(200000);
        }

        printf("Press any key to return to the menu...\n");
        getchar();
        c = getchar();
        printf("\033[H\033[J"); 
    }
}

