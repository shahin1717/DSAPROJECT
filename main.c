    #include <stdio.h>
    #include <string.h>
    #include "dsaproject.h"

    int main(){
        char c;
        student* head = NULL;
        student* highlevel = NULL;
        student* lowlevel = NULL;
        while(1){
        printf("Menu:\n");
        printf("1. Enter students\n");
        printf("2. Add new student\n");
        printf("3. Search for a student\n");
        printf("4. Display student list\n");
        printf("5. Sort the list of students by grade\n");
        printf("6. Split the list into two sub-lists according to grades (<65 and >=65)\n");
        printf("   a. Sort sub-lists by grade\n");
        printf("   b. Merge the two sub-lists by grade order\n");
        printf("7. Calculate exam average\n");
        printf("8. Delete last student\n");
        printf("9. Delete by ID\n");
        printf("10.Free lists\n");
        printf("11. Exit\n");
        printf("Enter your choice: "); 
        int choice;
        scanf("%d", &choice);
        printf("\033[H\033[J"); 
        switch(choice) {
        
            case 1:
                printf("Enter the number of students in the first room: ");
                int n;
                scanf("%d", &n);
                for(int i = 0; i < n; i++){ 
                    char name[50];
                    long id;
                    float grade;
                    printf("Enter the name of the student: ");
                    scanf("%s", name);
                    printf("Enter the ID of the student: ");
                    scanf("%ld", &id);
                    printf("Enter the grade of the student: ");
                    scanf("%f", &grade);
                student* newstudent = createstudent();
                strcpy(newstudent->name, name);
                newstudent->id_num = id;
                newstudent->grade = grade;

                if (head == NULL) {
                    head = newstudent;
                } else {
                    student* temp = head;
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next= newstudent;
                }
                        }
              
                break;
            case 2:
                char name[50];
                long id;
                float grade;
                printf("Enter data to add student: \n");
                printf("Enter the name of the student: ");
                scanf("%s", name);
                printf("Enter the ID of the student: ");
                scanf("%ld", &id);
                printf("Enter the grade of the student: ");
                scanf("%f", &grade);
                head = addstudent(head, name, id, grade);
                break;
            case 3:
                student* temp = head;
                int id_search;
                printf("Enter the ID of the student you want to search for: ");
                scanf("%d", &id_search);
                int index = findstudent(head, id_search);
                if (index == -1) {
                    printf("Student not found.\n");
                } else {
                    for (int i = 0; i < index; i++) {
                        temp = temp->next;
                    }
                    printf("Name: %s\n", temp->name);
                    printf("ID: %ld\n", temp->id_num);
                    printf("Grade: %.2f\n", temp->grade);   
                }
                break;
            case 4:
                displaylist(head);
                printf("Press any key to continue...\n");
                getchar();
                c=getchar();
                printf("\033[H\033[J"); 

                break;
            case 5:
                sortlist(head);
                printf("List sorted by grade.\n");
                printf("Press any key to continue...\n");
                getchar();
                c=getchar();
                printf("\033[H\033[J"); 
                break;
            case 6:
                // Split the list into two sub-lists according to grades
                break;
            case 7:
                float ave=averagexam(head);
                if(ave>65){
                    printf("The average of the exam is greater than 65\n");
                }
                else if(ave<50){
                    printf("The average of the exam is less than 50\n");
                }
                else{
                    printf("The average of the exam is between 50 and 65\n");
                }
                break;
            case 8:
                deletelaststudent(head);
                break;
            case 9:
                printf("Enter the ID of the student you want to delete: ");
                long id_num;
                scanf("%ld", &id_num);
                deleteById(&head, id_num);
                break;
            case 10:

                break;
            case 11:
                // Exit
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        

            
        
    


    }
        

    }
