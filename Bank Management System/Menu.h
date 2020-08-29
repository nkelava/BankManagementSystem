#ifndef MENU_H
#define MENU_H

#include <conio.h> 

#include "AdminMenu.h"

// FUNCTION PROTOTYPES---------
void AddCustomer();
void DeleteCustomer();
void EditCustomerInformation();
void DepositMoney();
void WithdrawMoney();
void SearchCustomer();
void ListCustomers();
void ManageEmployees();
void ExitProgram();
//-----------------------------

void AddCustomer()
{
    PrintHeader();

    Customer* newCustomer = CreateCustomer();
   
    if (newCustomer == NULL)
    {
        PrintError(8);
    }
    else
    {
        if (CustomersRoot == NULL)
        {
            LastCustomer = CustomersRoot = newCustomer;
        }   
        else 
        {
            LastCustomer->Next = newCustomer;
            LastCustomer = newCustomer;
        }

        printf("\n\n\n\n\t\t\t\t\t       CUSTOMER ADDED SUCCESSFULLY!!!");
    }

    BackspaceOption(FALSE);
}

void DeleteCustomer()
{
    Customer* customer = NULL, *previousCustomer = CustomersRoot;
    int customerID;

    while (TRUE) 
    {
        PrintHeader();

        if (CustomersRoot == NULL)
        {
            PrintError(5);
            break;
        }

        printf("%s", PADDINGTOP);
        EnterID(&customerID, CUSTOMER);

        if ((CheckCustomer(&customer, customerID)))
        {
            if (CustomersRoot->Next == NULL) 
            {
                free(previousCustomer);
                CustomersRoot = NULL;
            }
            else 
            {
                if (previousCustomer == customer)
                {
                    CustomersRoot = customer->Next;
                    free(customer);
                }
                else if (previousCustomer->Next == customer)
                {
                    CustomersRoot = previousCustomer;
                    previousCustomer->Next = customer->Next;
                    free(customer);
                }
                else 
                {
                    for (previousCustomer = CustomersRoot; previousCustomer->Next != customer; previousCustomer = previousCustomer->Next) {}

                    if (customer == LastCustomer)
                    {
                        LastCustomer = previousCustomer;
                    }

                    previousCustomer->Next = customer->Next;
                    customer->Next = NULL;
                    free(customer);
                }
                customer = NULL;
            }

            printf("\n\n\n\n\t\t\t\t\t       CUSTOMER DELETED SUCCESSFULLY!!!");
            BackspaceOption(FALSE);
            break;
        }
        else 
        {
            PrintError(3);
            
            if (BackspaceOption(TRUE))
            {
                break;
            }
        }
    }
}

void EditCustomerInformation()
{
    Customer* customer = NULL;
    char newName[NAMELENGTH];
    float newBalance = 0;
    int customerID, userChoice = -1;

    while (TRUE)
    {
        system("cls");
        PrintHeader();

        printf("%s", PADDINGTOP);
        EnterID(&customerID, CUSTOMER);

        if (CheckCustomer(&customer, customerID))
        {
            printf("\n\n");
            while(userChoice < 0 || userChoice > 2)
            {
                printf("\t\t\t\t  What you want to change (0. Exit 1. Name 2. Surname): ");
                scanf(" %d", &userChoice);
                
                HandleWrongInput();
            }

            switch (userChoice)
            {
            case 0:
                break;
            case 1:
                TakeStringInput("Enter new name:", "", PADDINGLEFT, &newName);
                strncpy(customer->Data.Name, newName, sizeof(newName));
                break;
            case 2:
                TakeStringInput("Enter new surnname:", "", PADDINGLEFT, &newName);
                strncpy(customer->Data.Surname, newName, sizeof(newName));
                break;
            }

            BackspaceOption(FALSE);
            break;
        }
        else
        {
            PrintError(3);  
            
            if (BackspaceOption(TRUE))
            {
                break;
            }
        }
    }
}

void DepositMoney()
{
    Customer* customer = NULL;
    float amount = 0;
    int customerID;

    while (TRUE) 
    {
        PrintHeader();
        printf("%s", PADDINGTOP);

        EnterID(&customerID, CUSTOMER);

        if (CheckCustomer(&customer, customerID)) 
        {
            while(TRUE)
            {
                printf("%sEnter deposit amount: ", PADDINGLEFT);

                if( (scanf(" %f", &amount) == 1))
                {
                    if(amount >= 0)
                    {
                        ClearStreamBuffer();
                        break;
                    }
                }

                HandleWrongInput();
            }

            customer->Data.Balance += amount;

            printf("\n\n\n\n\t\t\t\t\t          DEPOSIT SUCCESSFULL!!!");
            BackspaceOption(FALSE);
            break;
        }
        else 
        {
            PrintError(3);
            
            if (BackspaceOption(TRUE))
            {
                break;
            }
        }

    }
}

void WithdrawMoney()
{
    Customer* customer = NULL;
    float amount;
    int customerID;

    while (TRUE) 
    {
        PrintHeader();
        printf("%s", PADDINGTOP);
        
        EnterID(&customerID, CUSTOMER);

        if (CheckCustomer(&customer, customerID))
        {           
            while(TRUE)
            {
                printf("%sEnter amount to withdraw: ", PADDINGLEFT);
                    
                if (scanf(" %f", &amount) == 1)
                {
                    if (amount >= 0)
                    {
                        ClearStreamBuffer();
                        break;
                    }
                }

                HandleWrongInput();
            }

            if (CheckBudget(customer, amount)) 
            {   
                customer->Data.Balance -= amount;
                printf("\n\n\n\n\n\n\n\t\t\t\t\t\t   WITHDRAWAL SUCCESSFULL!!!");
                BackspaceOption(FALSE);
                break;
            }

            PrintError(4);
            printf("\n%sAccount balance: %.2f", PADDINGLEFT, customer->Data.Balance);

            if (BackspaceOption(TRUE))
            {
                break;
            }
        }   
        else
        {
            PrintError(3);
            
            if (BackspaceOption(TRUE))
            {
                break;
            }
        }
    }
}

void SearchCustomer()
{
    Customer* customer = NULL;
    int customerID, userChoice;
        
    while (TRUE)
    {
        system("cls");
        PrintHeader();
        printf("\n\n\n\n\n\n\n", PADDINGTOP);

        EnterID(&customerID, CUSTOMER);

        if (CheckCustomer(&customer, customerID))
        {
            system("cls");
            PrintHeader();
            
            printf("%sCUSTOMER ID         NAME                SURNAME             BALANCE\n\t\t\t    _______________________________________________________________________\n\n", LISTOFFSET);
            printf("\n\t\t\t         %d", customer->Data.ID);
            PrintSpaces(LISTROWLENGTH - 3 - NumberOfDigits(customer->Data.ID));
            printf("%s", customer->Data.Name);
            PrintSpaces(LISTROWLENGTH - strlen(customer->Data.Name));
            printf("%s", customer->Data.Surname);
            PrintSpaces(LISTROWLENGTH - strlen(customer->Data.Surname));
            printf("%.2f\n", customer->Data.Balance);

            BackspaceOption(FALSE);
            break;
        }
        else
        {
            PrintError(3);
            
            if(BackspaceOption(TRUE))
            {
                break;
            }
        }
    }
}

void ListCustomers()
{
    PrintHeader();
    printf("%sCUSTOMER ID         NAME                SURNAME             BALANCE\n\t\t\t    ________________________________________________________________________\n\n", LISTOFFSET);

    for (Customer* customer = CustomersRoot; customer != NULL; customer = customer->Next)
    {
        printf("\n\t\t\t         %d", customer->Data.ID);
        PrintSpaces(LISTROWLENGTH - 3 - NumberOfDigits(customer->Data.ID));
        printf("%s", customer->Data.Name);
        PrintSpaces(LISTROWLENGTH - strlen(customer->Data.Name));
        printf("%s", customer->Data.Surname);
        PrintSpaces(LISTROWLENGTH - strlen(customer->Data.Surname));
        printf("%.2f\n", customer->Data.Balance);
    }

    BackspaceOption(FALSE);
}

void ManageEmployees()
{
    char userChoice;
    Employee* previousEmployee = currentEmployee;
    Authority authorityLevel;

    do
    {
        authorityLevel = Login();
    } while (authorityLevel != ADMIN);

    void(*func_PtrArr[])() = { AddEmployee, DeleteEmployee, EditEmployeeInformation, SearchEmployee, ListEmployees };

    do {
        PrintOptions(ADMIN);     // Admin menu screen
        userChoice = _getch();
        system("cls");

        if (userChoice > 48 && userChoice < 54)
        {
            (*func_PtrArr[userChoice - 49])();

            // Update file with every change so we have new data to work with
            // No need for update if executed functions aren't changing data
            if (userChoice < 52)
            {
                UpdateEmployeesFileData();
            }
        }
    } while (userChoice != 54);
    // When we exit admin menu prev employee is kept in temp variable, it can be employee with admin status from the start 
    // but there is a case where we enter admin menu from normal employee login so it would be overwritten  
    currentEmployee = previousEmployee;
}

void ExitProgram()
{
    PrintHeader();
    printf("%s\n\n\n\t\t\t\t\t\t  PROGRAM IS CLOSING!!!", PADDINGTOP);
    printf("\n\n\t\t\t\t\t        ENJOY YOUR DAY!!! GOODBYE :)");
    Sleep(2000);
    system("cls");
}

#endif // MENU_H


