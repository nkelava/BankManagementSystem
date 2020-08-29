#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Errors.h"

// MACROS----------------------------------------------------
#define LOWER 100
#define UPPER 10000
#define RANDOMFUNCTION (rand() % (UPPER - LOWER + 1)) + LOWER
#define LISTOFFSET "\n\n\n\n\n\t\t\t      "
//-----------------------------------------------------------

// FUNCTION PROTOTYPES---------------------------
void TakeStringInput(char*, char*, char*, char*);
Customer* AllocateCustomerNode();
Customer* CreateCustomer();
Employee* AllocateEmployeeNode();
Employee* CreateEmployee();
void DeleteNodes();
int CheckEmployee(Employee**, int);
int CheckCustomer(Customer**, int);
int CheckBudget(Customer*, float);
int RandomGenerator(Authority);
int CheckOldPassword(Employee*, char*);
void EnterPassword(char*);
int  ClearStreamBuffer();
void HandleWrongInput();
void EnterID(int*, int);
Authority Login();
Authority CheckLogin(int, char*);
void PrintSpaces(int);
int NumberOfDigits(int);
//-------------------------------------------------


void TakeStringInput(char* text, char *paddingtop, char* paddingleft, char* data)
{
	printf("%s", paddingtop);

	while (TRUE)
	{
		printf("%s%s ", paddingleft, text);
		
		if (scanf(" %[a-zA-Z]", data) == 1)
		{
			ClearStreamBuffer();
			break;
		}

		HandleWrongInput();
	}
}

Customer* AllocateCustomerNode()
{
	return ((Customer*)malloc(sizeof(Customer)));
}

Customer* CreateCustomer()
{
	Customer* newCustomer = AllocateCustomerNode();

	if (newCustomer == NULL) return NULL;

	newCustomer->Next = NULL;
	newCustomer->Data.ID = RandomGenerator(CUSTOMER);

	TakeStringInput(" Enter name:", PADDINGTOP, PADDINGLEFT, &newCustomer->Data.Name);
	TakeStringInput(" Enter surname:", "", PADDINGLEFT, &newCustomer->Data.Surname);
	
	newCustomer->Data.Balance = 0;

	return newCustomer;
}

Employee* AllocateEmployeeNode()
{
	return ((Employee*)malloc(sizeof(Employee)));
}

Employee* CreateEmployee()
{
	Employee* newEmployee = AllocateEmployeeNode();

	if (newEmployee == NULL) return NULL;

	newEmployee->Next = NULL;
	newEmployee->Data.ID = RandomGenerator(EMPLOYEE);
	
	TakeStringInput(" Enter name:", PADDINGTOP, PADDINGLEFT, &newEmployee->Data.Name);
	TakeStringInput(" Enter surname:", "", PADDINGLEFT, &newEmployee->Data.Surname);
	
	printf("%s Enter password: ", PADDINGLEFT);
	scanf(" %15s", newEmployee->Data.Password);
	
	while(TRUE)	
	{
		printf("%s Enter aministration level ( 1 - admin, 2 - normal): ", PADDINGLEFT);
		scanf(" %d", &newEmployee->Data.AuthorityLevel);

		if (newEmployee->Data.AuthorityLevel == 1 || newEmployee->Data.AuthorityLevel == 2)
		{
			break;		
		}
		
		printf("\033[A\33[2K");
	}

	return newEmployee;
}

void DeleteNodes()
{
	Customer* currentCustomerNode = CustomersRoot;
	Employee* currentEmployeeNode = EmployeesRoot;

	CustomersRoot = NULL;   // Set both roots to null so it doesn't point to nothing
	EmployeesRoot = NULL;
	
	for (Customer* nextNode; currentCustomerNode != NULL; currentCustomerNode = nextNode)  // Go through list and free every node
	{ 
		nextNode = currentCustomerNode->Next;
		free(currentCustomerNode)	;
	}

	for (Employee* nextNode; currentEmployeeNode != NULL; currentEmployeeNode = nextNode)  // Go through list and free every node
	{
		nextNode = currentEmployeeNode->Next;
		free(currentEmployeeNode);
	}
}

int CheckCustomer(Customer** customer, int enteredID)
{
	for (Customer* iter = CustomersRoot; iter != NULL; iter = iter->Next) 
	{
		if (iter->Data.ID == enteredID) 
		{
			*customer = iter;
			return TRUE;
		}
	}
	return FALSE;
}

int CheckEmployee(Employee** employee, int enteredID)
{
	for (Employee* iter = EmployeesRoot; iter != NULL; iter = iter->Next)
	{
		if (iter->Data.ID == enteredID)
		{
			*employee = iter;
			return TRUE;
		}
	}
	return FALSE;
}

int CheckBudget(Customer* customer, float amount)
{
	return (customer->Data.Balance >= amount) ? TRUE : FALSE;
}

int RandomGenerator(Authority accountType)
{
	int randomNumber = RANDOMFUNCTION, flag = FALSE;

	if(accountType == CUSTOMER)
	{
		if (CustomersRoot != NULL && CustomersRoot->Next != NULL)
		{
			do
			{
				for (Customer* customer = CustomersRoot; customer != NULL; customer = customer->Next)
				{
					if (customer->Data.ID == randomNumber)
					{
						flag = TRUE;
						break;
					}
				}
				
				if (flag)
				{
					randomNumber = RANDOMFUNCTION;
				}
			} while(flag == TRUE);
		}
	}
	else
	{
		if (EmployeesRoot != NULL && EmployeesRoot->Next != NULL)
		{
			do
			{
				for (Employee* employee = EmployeesRoot; employee != NULL; employee = employee->Next)
				{
					if (employee->Data.ID == randomNumber)
					{
						flag = TRUE;
						break;
					}
				}

				if (flag)
				{
					randomNumber = RANDOMFUNCTION;
				}
			} while (flag == TRUE);
		}
	}
	return randomNumber;
}

int CheckOldPassword(Employee* employee, char* password)
{
	return (strcmp(employee->Data.Password, password) == 0) ? TRUE : FALSE;
}

void EnterPassword(char* password)
{
	int index = -1, inputLength = PASSWORDLENGTH - 1;

	printf("%sEnter password: ", PADDINGLEFT);

	do {
		password[++index] = _getch();
		printf("*");
	} while (password[index] != '\r' && index < inputLength);

	password[index] = '\0';
}

int ClearStreamBuffer()
{
	int c;

	while ((c = getchar()) != EOF && c != '\n');
}

void HandleWrongInput()
{
	ClearStreamBuffer();
	printf("\033[A\33[2K");
}

void EnterID(int* ID, int msg)
{
	while (TRUE)
	{
		printf("%sEnter %s ID: ", PADDINGLEFT, (msg == EMPLOYEE) ? "employee" : "customer");
		
		if (scanf(" %d", &(*ID)) == 1)
		{
			ClearStreamBuffer();
			break;
		}

		HandleWrongInput();
	}
}

Authority Login()
{
	int employeeID;
	char password[PASSWORDLENGTH] = "";
	
	PrintHeader();
	printf("%s%s       LOGIN\n\n\n", PADDINGTOP, PADDINGLEFT);

	EnterID(&employeeID, EMPLOYEE, PADDINGLEFT);
	EnterPassword(&password);

	return (CheckLogin(employeeID, password));
}

Authority CheckLogin(int employeeID, char* password) 
{
	// RETURN: 0 - something went wrong, 1 - admin, 2 - employee
	for (Employee* employee = EmployeesRoot; employee != NULL; employee = employee->Next)
	{
		if (employee->Data.ID == employeeID)
		{
			if (!strcmp(employee->Data.Password, password))
			{
				currentEmployee = employee;
				return employee ->Data.AuthorityLevel;
			}
			else
			{
				PrintError(7); // Wrong password
				return FALSE;
			}
		}
	}
	PrintError(6); // Wrong ID 
	return FALSE; 
}

void PrintSpaces(int spaceLength)
{
	while(spaceLength > 0)
	{
		printf(" ");
		--spaceLength;
	}
}

int NumberOfDigits(int num)
{
	int counter = 0;

	if (num == 0)
	{
		return 1;
	}

	for (int i = 1; i <= num; i *= 10)
	{
		++counter;
	}

	return counter;
}

#endif // FUNCTIONS_H


