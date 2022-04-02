#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <conio.h>

#include "../../Shared/SharedFunctions.h"

// ------------ FUNCTION PROTOTYPES ------------
void AppLogin();
void ManageEmployeesLogin();
Role Login();
void EnterPassword(char*);
Role ValidateLoginCredentials(int, char*);
// ---------------------------------------------


void AppLogin()
{
	Role role = 0;

	do  {
		role = Login();
	} while (role != ADMIN && role != EMPLOYEE);
}


void ManageEmployeesLogin()
{
	Role role = 0;
	
	do {
		role = Login();
	} while (role != ADMIN);
}


Role Login()
{
	int employeeID;
	char password[PASSWORD_MAX_LENGTH] = "";

	PrintHeader();
	printf("%s%s       LOGIN\n\n\n", PADDINGTOP, PADDINGLEFT);

	EnterID(&employeeID, EMPLOYEE);
	EnterPassword(&password);

	return (ValidateLoginCredentials(employeeID, password));
}


void EnterPassword(char* password)
{
	int index = -1, inputLength = PASSWORD_MAX_LENGTH - 1;

	printf("%sEnter password: ", PADDINGLEFT);

	do {
		password[++index] = _getch();
		printf("*");
	} while (password[index] != '\r' && index < inputLength);

	password[index] = '\0';
}


Role ValidateLoginCredentials(int employeeID, char* password)
{
	// RETURN VALUEs:
	// 0 - something went wrong
	// 1 - admin
	// 2 - employee

	for (Employee* employee = EmployeesRoot; employee != NULL; employee = employee->Next) {
		if (employee->Data.ID == employeeID) {
			if (!strcmp(employee->Data.Password, password)) {
				currentEmployee = employee;
				return employee->Data.Role;
			}

			PrintError(7); // Wrong password
			return FALSE;
		}
	}

	PrintError(6); // Wrong ID 
	return FALSE;
}


#endif // LOGIN_H
