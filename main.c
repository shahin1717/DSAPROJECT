        int main(){
            
            printf("\t\033[1;36mWelcome to the Student Management Systems\033[0m\n");
            puts("");
            puts("");
            char c;
            student* head = NULL;
            student* highlevel = NULL;
            student* lowlevel = NULL;
            while(1){
            printf("\t\t\t\033[1;32mMenu:\033[0m\n");
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
            while (1){
                if(scanf("%d", &choice)==1){
                    break;
                }
                else{
                    printf("Invalid input. Please enter a number.\n");
                    scanf("%*[^\n]"); // Clear the input buffer
                }
            }
            printf("\033[H\033[J"); 
            switch(choice) {
            
                case 1:
                    student* temp = createstudent();
                    if(head==NULL){
                        head=temp;
                    }
                    else{
                        student* temp2=head;
                        while(temp2->next!=NULL){
                            temp2=temp2->next;
                        }
                        temp2->next=temp;
                    }
                    printf("List created.\n");
                    printf("Press any key to continue...\n");
                    getchar();
                    c=getchar();
                    break;
                case 2:
                    char name[50];
                    long id;
                    float grade;
                    printf("Enter number of students: \n");
                    int num;
                    while (1){
                        if(scanf("%d", &num)==1){
                            break;
                        }
                        else{
                            printf("Invalid input. Please enter a number.\n");
                            scanf("%*[^\n]"); // Clear the input buffer
                        }
                    }
                    for(int i=0; i<num; i++){
                    printf("Enter the name of the student: ");
                    scanf("%s", name);
                    printf("Enter the ID of the student: ");
                    while (1){
                        if(scanf("%ld", &id)==1){
                            break;
                        }
                        else{
                            printf("Invalid input. Please enter a number.\n");
                            scanf("%*[^\n]"); // Clear the input buffer
                        }
                    }
                    while(!check_valid_id(head, id)){
                        printf("ID already used. Enter a different ID: ");
                        while (1){
                            if(scanf("%ld", &id)==1){
                                break;
                            }
                            else{
                                printf("Invalid input. Please enter a number.\n");
                                scanf("%*[^\n]"); // Clear the input buffer
                            }
                        }
                    }
                    printf("Enter the grade of the student: ");
                    while (1){
                        if(scanf("%d", &num)==1){
                            break;
                        }
                        else{
                            printf("Invalid input. Please enter a number.\n");
                            scanf("%*[^\n]"); // Clear the input buffer
                        }
                    }
                    head = addstudent(head, name, id, grade);}
                    break;
                case 3:
                    student* temp2 = head;
                    int id_search;
                    printf("Enter the ID of the student you want to search for: ");
                    while (1){
                        if(scanf("%d", &id_search)==1){
                            break;
                        }
                        else{
                            printf("Invalid input. Please enter a number.\n");
                            scanf("%*[^\n]"); // Clear the input buffer
                        }
                    }
                    int index = findstudent(head, id_search);
                    if (index == -1) {
                        printf("Student not found.\n");
                    } else {
                        for (int i = 0; i < index; i++) {
                            temp2 = temp2->next;
                        }
                        printf("Name: %s\n", temp2->name);
                        printf("ID: %ld\n", temp2->id_num);
                        printf("Grade: %.2f\n", temp2->grade);   
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
                    splitlist(head, &highlevel, &lowlevel);
                    printf("\033[1;33mMerged two sub-lists.\033[0m\n");
                    displaylist(mergelists(highlevel, lowlevel));
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
                    while (1){
                        if(scanf("%ld", &id_num)==1){
                            break;
                        }
                        else{
                            printf("Invalid input. Please enter a number.\n");
                            scanf("%*[^\n]"); // Clear the input buffer
                        }
                    }
                    deleteById(&head, id_num);
                    break;
                case 10:
                    freelist(head);
                    break;
                case 11:
                    printf("\t\t\t\033[1;32;40mThanks for using the Student Management System!!!\03\033[0m\n");
                    printf("\t\t\033[1;40mCreated by Alakparov Shahin, Alihzade Fidan, Aliyeva Nazrin\033[0m\n"); 
                    printf("\t\t\t\t\033[1;40mExiting program...\02\033[0m\n");
                    exit(1);
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
        }
