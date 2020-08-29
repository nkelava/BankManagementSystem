#ifndef DISPLAY_H
#define DISPLAY_H

#include <ctype.h>
#include <time.h>
#include <windows.h>

#include "Structures.h"

// MACROS------------------------------------------------------------
#define PADDINGTOP "\n\n\n\n\n\n"
#define PADDINGLEFT "\t\t\t\t\t           "
#define PADDINGTOPLEFTONE "\n\n\n\n\n\n\t\t                         "
#define PADDINGTOPLEFTTWO "\n\n\n\n\n\n\t\t             "
//-------------------------------------------------------------------

// FUNCTION PROTOTYPES-----------------
void PrintHeader();
void PrintTime();
void PrintOptions(Employee, Authority);
int BackspaceOption(int);
//-------------------------------------


void PrintHeader()
{
	system("cls");
	printf("\n--------------------------------------------------- FINISH LINE BANK ---------------------------------------------------\n");
	PrintTime();
	
	if (currentEmployee != NULL)
	{
		printf("\n  %s %s", currentEmployee->Data.Name, currentEmployee->Data.Surname);
	}
}

void PrintTime()
{		
	time_t rawtime;
	struct tm* info;
	char buffer [50];

	time(&rawtime);

	strftime(buffer, 80, "%a/%x\t     %I:%M%p", info = localtime(&rawtime));
	printf("\t\t\t\t\t\t\t\t\t\t\t   %s", buffer);
}

void PrintOptions(Authority authorityLevel)
{
	PrintHeader();

	if(authorityLevel == ADMIN)
	{
		printf("%s%s      OPTIONS:\n\n\n\t\t\t\t\t\t   1. Add employee\n\t\t\t\t\t\t   2. Delete employee\n\t\t\t\t\t\t   3. Edit employee information\n\t\t\t\t\t\t   4. Get employee information\n\t\t\t\t\t\t   5. List of employees\n\t\t\t\t\t\t   6. EXIT\n\n\n", PADDINGTOP, PADDINGLEFT);
	}
	else
	{
		printf("%s%s      OPTIONS:\n\n\n\t\t\t\t\t\t   1. Add customer\n\t\t\t\t\t\t   2. Delete customer\n\t\t\t\t\t\t   3. Edit customer information\n\t\t\t\t\t\t   4. Deposit money\n\t\t\t\t\t\t   5. Withdraw money\n\t\t\t\t\t\t   6. Get customer information\n\t\t\t\t\t\t   7. View all customers\n\t\t\t\t\t\t   8. Manage employees\n\t\t\t\t\t\t   9. EXIT\n\n\n", PADDINGTOP, PADDINGLEFT);
	}
}

int BackspaceOption(int tryAgain)
{
	char backChoice;

	if (tryAgain == FALSE)
	{
		printf("%s  Press ANYTHING to go to options menu...", PADDINGTOPLEFTONE);
	
		while ((backChoice = _getch()) != 8)
		{
			Sleep(10);
		}
		return TRUE;
	}
	else
	{
		printf("%s Press ANYTHING to go to options menu or SPACE to try again...", PADDINGTOPLEFTTWO);

		return (isspace(backChoice = _getch())) ? FALSE : TRUE;
	}
}

#endif // DISPLAY_H


