/* Clinic Management System Project */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define noOfSlots 5  // total number of slots

//create a node for patient`s record
struct node{
    char name[100];
    int age;
    char gender[10];
    int ID;
    int slot;
    struct node* link;
};

// create a pointer to point for first node
struct node* root;

//functions prototype
  //admin mode functions
void admin_mode();
void add_patient();
void edit_patient();
void reserve_slot();
void cancel_reservation();

    //user mode functions
void view_patient();
void view_reservations();

//declare global variables
int availableSlots = 5;    // total number of available slots
int arr[5] = {1,2,3,4,5};  //array of available slots


int main()
{
    int mode;
    printf("\n    **Welcome to clinic management system**    \n");
    printf("\n"
           "1. Admin.\n"
           "2. User.\n"
           "Select a mode: ");
    scanf("%d",&mode);
    switch(mode){
    case 1 :
        admin_mode();
        break;
    case 2 :
        user_mode();
        break;
    default :
        printf("Invalid choice.\n");
        break;
    }
    return 0;
}

/* Admin mode operations */
void admin_mode(){
    int i = 0, password;
    while(i >= 0){
            i++;
            printf("Enter a password : ");
            scanf("%d",&password);
            if(password == 1234){
                break;
            }
            if(i == 3){
                printf("Wrong password, please try again later.\n");
                exit(1);
            }
    }
    printf("\nWelcome to admin mode.\n");
    int ch;
    while(1){
        printf("\n"
                "1. Add new patient record.\n"
                "2. Edit patient record.\n"
                "3. Reserve a slot with the doctor.\n"
                "4. Cancel reservation.\n"
                "5. Switch to user mode.\n"
                "6. End the program.\n"
                "Enter your choice : ");
        scanf("%d",&ch);

        switch(ch){
            case 1 :
                add_patient();
                break;

            case 2 :
                edit_patient();
                break;

            case 3 :
                reserve_slot();
                break;

            case 4 :
                cancel_reservation();
                break;

            case 5 :
                user_mode();
                break;

            case 6 :
                exit(1);
                break;
            default :
                printf("Invalid choice.\n");
                break;
        }
    }
}

// Add new patient record
void add_patient(){
    if(availableSlots){
        struct node* temp;
        temp = malloc(sizeof(struct node));

        printf("\n");
        printf("Enter patient`s name : ");
        scanf("%s",&temp->name);
        printf("\n");
        printf("Enter patient`s age : ");
        scanf("%d",&temp->age);
        printf("\n");
        printf("Enter patient`s gender : ");
        scanf("%s",&temp->gender);
        printf("\n");
        printf("Enter patient`s ID : ");
        scanf("%d",&temp->ID);
        printf("\n");

        temp->link = NULL;
        if(root == NULL){
            root = temp;
        }
        else{
            struct node *p,*q;
            p = q = root;
            while(q != NULL){
                if(temp->ID == q->ID){
                    printf("\nThis ID already exists.\n"
                           "please enter new ID: ");
                    scanf("%d",&temp->ID);
                    q = root;
                }
                p = q;
                q = q->link;
            }
            p->link = temp;
        }
    }
    else{
        printf("\nSorry, it`s completed. There are no available slots.\n");
    }

}

// Edit patient record
void edit_patient(){
    struct node* temp,*p;
    int ID;
    printf("\nplease enter the patient`s ID : ");
    scanf("%d",&ID);
    temp = root;
    while(temp != NULL){
        if(ID == temp->ID){
            printf("\n");
            printf("Enter patient`s name : ");
            scanf("%s",&temp->name);
            printf("\n");
            printf("Enter patient`s age : ");
            scanf("%d",&temp->age);
            printf("\n");
            printf("Enter patient`s gender : ");
            scanf("%s",&temp->gender);
            printf("\n");
            return;
        }
        temp = temp->ID;
    }
    printf("\nWrong ID, This ID does not exist.\n");
}

// Reserve a slot with the doctor
void reserve_slot(){
    struct node* temp;
    int i, j =0;
    int ID;
    temp = root;
    if(temp == NULL){
        printf("\nThere are no patients.\n");
    }
    else{
        printf("\nEnter patient`s ID : ");
        scanf("%d",&ID);
        printf("\n");
        while(temp!= NULL){
            if(ID == temp->ID){
                for(i=1;i<= noOfSlots ; i++,j++){
                    switch(arr[j]){
                        case 1 :
                            printf("1. 2:00 PM : 2:30 PM.\n");
                            break;

                        case 2 :
                            printf("2. 2:30 PM : 3:00 PM.\n");
                            break;

                        case 3 :
                            printf("3. 3:00 PM : 3:30 PM.\n");
                            break;

                        case 4 :
                            printf("4. 4:00 PM : 4:30 PM.\n");
                            break;

                        case 5 :
                            printf("5. 4:30 PM : 5:00 PM.\n");
                            break;
                    }
                }
                printf("Select a slot : ");
                scanf("%d",&temp->slot);
                arr[temp->slot-1] = 0;
                availableSlots--;
                return;
            }
            else{
                temp = temp->link;
            }
        }
        printf("\nThis is wrong ID.\n");
    }
}

// Cancel reservation
void cancel_reservation(){
    struct node* temp;
    int ID;
    temp = root;
    if(temp == NULL){
        printf("\nThere are no patients.\n");
    }
    else{
        printf("\nEnter patient`s ID : ");
        scanf("%d",&ID);
        while(temp!= NULL){
            if(ID == temp->ID){
                arr[temp->slot-1] = temp->slot;
                availableSlots++;
                return;
            }
            else{
                temp = temp->link;
            }
        }
        printf("\nThis is wrong ID.\n");
    }
}

/* User mode operations */
void user_mode(){
    printf("\nWelcome to user mode.\n");
    int ch;
    while(1){
        printf("\n"
               "1. View patient record.\n"
               "2. View today reservations.\n"
               "3. Switch to admin mode.\n"
               "4. End the program.\n"
               "Enter your choice : ");
        scanf("%d",&ch);

        switch(ch){
            case 1 :
                view_patient();
                break;

            case 2 :
                view_reservations();
                break;

            case 3 :
                admin_mode();
                break;

            case 4 :
                exit(1);
                break;
            default :
                printf("\nInvalid choice.\n");
                break;
        }
    }
}

// View patient record.
void view_patient(){
    struct node *temp;
    int ID;
    temp = root;
    if(temp == NULL){
        printf("\nThere are no patients.\n");
    }
    else{
        printf("\nEnter patient ID : ");
        scanf("%d",&ID);
        while(temp!= NULL){
            if(ID == temp->ID){
                printf("\n%s%15s%20s%28s\n","ID","Name","Age","Gender");
                printf("%2d%15s%20d%28s\n",temp->ID,temp->name,temp->age,temp->gender);
                return;
            }
            else{
                temp = temp->link;
            }
        }
        printf("\nThis is wrong ID.\n");
    }
}

// View today’s reservations
void view_reservations(){
    struct node *temp;
    int slot;
    temp = root;
    if(temp == NULL){
        printf("\nThere are no patients.\n");
    }
    else{
        printf("ID: reservation slot:\n");
        while(temp!= NULL){
           switch(temp->slot){
            case 1 :
               printf("%d   2:00 PM : 2:30 PM.\n",temp->ID);
               break;

            case 2 :
               printf("%d   2:30 PM : 3:00 PM.\n",temp->ID);
               break;

            case 3 :
               printf("%d   3:00 PM : 3:30 PM.\n",temp->ID);
               break;

            case 4 :
               printf("%d   4:00 PM : 4:30 PM.\n",temp->ID);
               break;

            case 5 :
               printf("%d   4:30 PM : 5:00 PM.\n",temp->ID);
               break;

            default :
                break;
           }
           temp = temp->link;
        }
    }
}
