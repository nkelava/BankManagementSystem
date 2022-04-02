#ifndef ENTITYSTRUCTURES_H
#define ENTITYSTRUCTURES_H

#include "../Enums/RoleEnum.h"

// MACROS----------------------
#define NAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 16
// ----------------------------


typedef struct _CustomerData
{
    int ID;
    char Name[NAME_MAX_LENGTH], Surname[NAME_MAX_LENGTH];
    float Balance;
} CustomerData;


typedef struct _EmployeeData
{
    int ID;
    Role Role;
    char Name[NAME_MAX_LENGTH], Surname[NAME_MAX_LENGTH];
    char Password[PASSWORD_MAX_LENGTH];
} EmployeeData;


typedef struct _Customer
{
    CustomerData Data;
    struct _Customer* Next;
} Customer;


typedef struct _Employee
{
    EmployeeData Data;
    struct _Employee* Next;
} Employee;


Customer* CustomersRoot = NULL;
Employee* EmployeesRoot = NULL;

Customer* LastCustomer = NULL;
Employee* LastEmployee = NULL;

Employee* currentEmployee = NULL;


#endif // ENTITYSTRUCTURES_H
