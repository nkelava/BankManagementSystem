#ifndef FILE_H
#define FILE_H

#include "Functions.h"

// FUNCTION PROTOTYPES ------------
void ImportDataAndLogin();
void CheckFile(FILE*);
void ImportDataFromCustomersFile();
void UpdateCustomersFileData();
void ImportDataFromEmployeesFile();
void UpdateEmployeesFileData();
// --------------------------------


void ImportDataAndLogin()
{
    Authority authorityLevel;

    ImportDataFromEmployeesFile();

    do
    {
        authorityLevel = Login();
    } while (authorityLevel != ADMIN && authorityLevel != EMPLOYEE);

    ImportDataFromCustomersFile();
}

void CheckFile(FILE* FilePointer)
{
    if (!FilePointer)
    {
        PrintError(1);
        system("exit");
    }
}

void ImportDataFromCustomersFile()
{
    Customer* newCustomer = AllocateCustomerNode();
    FILE* FilePointer = fopen("Customers.txt", "r");

    CheckFile(FilePointer);

    while (fscanf(FilePointer, "%d %s %s %f", &newCustomer->Data.ID, &newCustomer->Data.Name,
                            &newCustomer->Data.Surname, &newCustomer->Data.Balance) == 4) 
    {
        newCustomer->Next = NULL;
        // Case if there is no customers
        if (CustomersRoot == NULL)
        {
            LastCustomer = CustomersRoot = newCustomer;
        }
        else
        {
            LastCustomer->Next = newCustomer;
            LastCustomer = newCustomer;
        }
        newCustomer = AllocateCustomerNode();
    }

    fclose(FilePointer);
}

void UpdateCustomersFileData()
{
    FILE* FilePointer = fopen("Customers.txt", "w");

    CheckFile(FilePointer);

    for (Customer* customer = CustomersRoot; customer != NULL; customer = customer->Next)
    {
        fprintf(FilePointer, "%d %s %s %.2f\n", customer->Data.ID, customer->Data.Name, 
                                            customer->Data.Surname, customer->Data.Balance);
    }

    fclose(FilePointer);
}

void ImportDataFromEmployeesFile()
{
    Employee* newEmployee = AllocateEmployeeNode();
    FILE* FilePointer = fopen("Employees.txt", "r");

    CheckFile(FilePointer);

    while (fscanf(FilePointer, "%d %s %s %s %d", &newEmployee->Data.ID, &newEmployee->Data.Name,
        &newEmployee->Data.Surname, &newEmployee->Data.Password, &newEmployee->Data.AuthorityLevel) == 5)
    {
        newEmployee->Next = NULL;
        // Case if there is no employees
        if (EmployeesRoot == NULL)
        {
            LastEmployee = EmployeesRoot = newEmployee;
        }
        else
        {
            LastEmployee->Next = newEmployee;
            LastEmployee = newEmployee;
        }
        newEmployee = AllocateEmployeeNode();
    }

    fclose(FilePointer);
}

void UpdateEmployeesFileData()
{
    FILE* FilePointer = fopen("Employees.txt", "w");

    CheckFile(FilePointer);
    
    for (Employee* employee = EmployeesRoot; employee != NULL; employee = employee->Next)
    {
        fprintf(FilePointer, "%d %s %s %s %d\n", employee->Data.ID, employee->Data.Name,
                                             employee->Data.Surname, employee->Data.Password, 
                                             employee->Data.AuthorityLevel);
    }

    fclose(FilePointer);
}

#endif // FILE_H


