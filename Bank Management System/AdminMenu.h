#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "File.h"

// MACROS---------------
#define LISTROWLENGTH 20
//----------------------

// FUNCTION PROTOTYPES---------
void AddEmployee();
void DeleteEmployee();
void EditEmployeeInformation();
void SearchEmployee();
void ListEmployees();
//-----------------------------


void AddEmployee()
{
    PrintHeader();

    Employee* newEmployee = CreateEmployee();

    if (newEmployee == NULL)
    {
        PrintError(8);
    }
    else
    {
        if (EmployeesRoot == NULL)
        {
            LastEmployee = EmployeesRoot = newEmployee;
        }
        else
        {
            LastEmployee->Next = newEmployee;
            LastEmployee = newEmployee;
        }

        printf("\n\n\n\n\t\t\t\t\t       EMPLOYEE ADDED SUCCESSFULLY!!!");
    }

    BackspaceOption(FALSE);
}

void DeleteEmployee()
{
    Employee* employee;
    Employee* previousEmployee = EmployeesRoot;
    int employeeID;

    while (TRUE)
    {
        PrintHeader();

        if (EmployeesRoot == NULL)
        {
            PrintError(5);
            break;
        }

        printf("%s", PADDINGTOP);
        EnterID(&employeeID, EMPLOYEE);

        if ((CheckEmployee(&employee, employeeID)))
        {
            if (EmployeesRoot->Next == NULL)
            {
                free(previousEmployee);
                EmployeesRoot = NULL;
            }
            else
            {
                if (previousEmployee == employee)
                {
                    CustomersRoot = employee->Next;
                    free(employee);
                }
                else if (previousEmployee->Next  == employee)
                {
                    EmployeesRoot = previousEmployee;
                    previousEmployee->Next = employee->Next;
                    free(employee);
                }
                else
                {
                    for (previousEmployee = EmployeesRoot; previousEmployee->Next != employee; previousEmployee = previousEmployee->Next) {}

                    if (employee == LastEmployee)
                    {
                        LastEmployee = previousEmployee;
                    }

                    previousEmployee->Next = employee->Next;
                    employee->Next = NULL;
                    free(employee);
                }
                employee = NULL;
            }
            printf("\n\n\n\n\t\t\t\t\t       EMPLOYEE DELETED SUCCESSFULLY!!!");
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

void EditEmployeeInformation()
{
    Employee* employee = NULL;
    char newName[NAMELENGTH], oldPassword[PASSWORDLENGTH];
    float newBalance = 0;
    int employeeID, userChoice = -1;

    while (TRUE)
    {
        system("cls");
        PrintHeader();
        
        printf("%s", PADDINGTOP);
        EnterID(&employeeID, EMPLOYEE);

        if (CheckEmployee(&employee, employeeID))
        {
            printf("\n\n");
            
            while (TRUE)
            {
                printf("\t\t\tWhat you want to change (0-Exit, 1-Name 2-Surname, 3-Authority level, 4-Password): ");

                if (scanf(" %d", &userChoice) == 1)
                {
                    if (userChoice > -1 && userChoice < 5)
                    {
                        ClearStreamBuffer();
                        break;
                    }
                }
                HandleWrongInput();
            }

            printf("\033[A\33[2K");

            switch (userChoice)
            {
            case 0:
                break;
            case 1:
                TakeStringInput("Enter new name:", "", PADDINGLEFT, &newName);
                strncpy(employee->Data.Name, newName, sizeof(newName));
                break;
            case 2:
                TakeStringInput("Enter new surname:", "", PADDINGLEFT, &newName);
                strncpy(employee->Data.Surname, newName, sizeof(newName));
                break;
            case 3:
                while(TRUE)
                {
                    printf("%sEnter level of authority(1-admin, 2-employee):", PADDINGLEFT);
                    scanf(" %d", &employee->Data.AuthorityLevel);

                    if (employee->Data.AuthorityLevel > 0 && employee->Data.AuthorityLevel < 3)
                    {    
                        break;
                    }
                    printf("\033[A\33[2K");
                }
                break;
            case 4:
                printf("%sEnter old password:", PADDINGLEFT);
                if (CheckOldPassword(employee, oldPassword))
                {
                    printf("%sEnter new password:", PADDINGLEFT);
                    scanf(" %s", &employee->Data.Password);
                }
                else
                {
                    PrintError(6);
                }
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

void SearchEmployee()
{
    Employee* employee = NULL;
    int employeeID, userChoice;

    while(TRUE)
    {
        system("cls");
        PrintHeader();

        printf("%s", PADDINGTOP);
        EnterID(&employeeID, EMPLOYEE);

        if (CheckEmployee(&employee, employeeID))
        {
            system("cls");
            PrintHeader();

            printf("%sEMPLOYEE ID         NAME                SURNAME             AUTHORITY\n\t\t        _______________________________________________________________________\n\n", LISTOFFSET);
            printf("\n\t\t\t         %d", employee->Data.ID);
            PrintSpaces(LISTROWLENGTH - 3 - NumberOfDigits(employee->Data.ID));
            printf("%s", employee->Data.Name);
            PrintSpaces(LISTROWLENGTH - strlen(employee->Data.Name));
            printf("%s", employee->Data.Surname);
            PrintSpaces(LISTROWLENGTH - strlen(employee->Data.Surname));
            printf("%s", (employee->Data.AuthorityLevel == ADMIN) ? "ADMIN" : "EMPLOYEE");

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

void ListEmployees()
{
    PrintHeader();
    printf("%sEMPLOYEE ID          NAME                SURNAME             AUTHORITY\n\t\t            ___________________________________________________________________________\n\n", LISTOFFSET);
    
    for (Employee* employee = EmployeesRoot; employee != NULL; employee = employee->Next)
    {
        printf("\n\t\t\t          %d", employee->Data.ID);
        PrintSpaces(LISTROWLENGTH - 3 - NumberOfDigits(employee->Data.ID));
        printf("%s", employee->Data.Name);
        PrintSpaces(LISTROWLENGTH - strlen(employee->Data.Name));
        printf("%s", employee->Data.Surname);
        PrintSpaces(LISTROWLENGTH - strlen(employee->Data.Surname));
        printf("%s", (employee->Data.AuthorityLevel == ADMIN) ? "ADMIN" : "EMPLOYEE");
    }
       
    BackspaceOption(FALSE);
}

#endif // ADMINMENU_H


