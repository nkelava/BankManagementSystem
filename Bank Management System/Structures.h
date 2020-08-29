#ifndef STRUCTURES_H
#define STRUCTURES_H

// MACROS----------------
#define NAMELENGTH 50
#define PASSWORDLENGTH 16
//-----------------------


typedef enum _Authority { ADMIN = 1, EMPLOYEE, CUSTOMER } Authority;

typedef struct _CustomerData
{
    int ID;
    char Name[NAMELENGTH], Surname[NAMELENGTH];
    float Balance;
}CustomerData;

typedef struct _EmployeeData
{
    int ID;
    Authority AuthorityLevel;
    char Name[NAMELENGTH],  Surname[NAMELENGTH];
    char Password[PASSWORDLENGTH];
}EmployeeData;

typedef struct _Customer
{
    CustomerData Data;
    struct _Customer* Next;
}Customer;

typedef struct _Employee
{
    EmployeeData Data;
    struct _Employee* Next;
}Employee;

Customer* CustomersRoot = NULL;
Employee* EmployeesRoot = NULL;

Customer* LastCustomer = NULL;
Employee* LastEmployee = NULL;

Employee* currentEmployee = NULL;

#endif // STRUCTURES_H


