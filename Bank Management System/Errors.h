#ifndef ERROR_H
#define ERROR_H

#include "Display.h"

// MACROS-------------------------------------
#define ERROROFFSET "\n\n\n\n\n\n\n\n\t\t\t\t"
#define OPTIONOFFSET "\n\n"
//--------------------------------------------


void PrintError(int ErrorID)
{
	PrintHeader();

	switch (ErrorID) {
	case 1:
		printf("%s  ERROR OPENING FILE!!! CHECK FILE NAME AND FILE LOCATION!\n\n\t\t\t\t  ERROR OPENING FILE!!! CHECK FILE NAME AND FILE LOCATION!\n\n\t\t\t\t  ERROR OPENING FILE!!! CHECK FILE NAME AND FILE LOCATION!%s\a\a\a", ERROROFFSET, OPTIONOFFSET);
		break;
	case 2:
		printf("%s\t\tEMPLOYEE DOES NOT EXIST!!!\n\n\t\t\t\t\t\tEMPLOYEE DOES NOT EXIST!!!\n\n\t\t\t\t\t\tEMPLOYEE DOES NOT EXIST!!!%s\a\a\a", ERROROFFSET, OPTIONOFFSET);
		break;
	case 3:
		printf("%s\t\tCUSTOMER DOES NOT EXIST!!!\n\n\t\t\t\t\t\tCUSTOMER DOES NOT EXIST!!!\n\n\t\t\t\t\t\tCUSTOMER DOES NOT EXIST!!!%s\a\a\a", ERROROFFSET, OPTIONOFFSET);
		break;
	case 4:
		printf("%s\tBALANCE IS INSUFFICIENT FOR A WITHDRAWAL!!!\n\n\t\t\t\t\tBALANCE IS INSUFFICIENT FOR A WITHDRAWAL!!!\n\n\t\t\t\t\tBALANCE IS INSUFFICIENT FOR A WITHDRAWAL!!!%s\a\a\a", ERROROFFSET, OPTIONOFFSET);
		break;
	case 5:
		printf("%s\t    THERE ARE NO ACCOUNTS TO DELETE!!!\n\n\t\t\t\t\t    THERE ARE NO ACCOUNTS TO DELETE!!!\n\n\t\t\t\t\t    THERE ARE NO ACCOUNTS TO DELETE!!!\a\a\a", ERROROFFSET);
		break;
	case 6:
		printf("%s\t\t  WRONG ID!!! TRY AGAIN!\n\n\t\t\t\t\t\t  WRONG ID!!! TRY AGAIN!\n\n\t\t\t\t\t\t  WRONG ID!!! TRY AGAIN!\a\a\a", ERROROFFSET);
		break;
	case 7:
		printf("%s\t        WRONG PASSWORD!!! TRY AGAIN!\n\n\t\t\t\t\t        WRONG PASSWORD!!! TRY AGAIN!\n\n\t\t\t\t\t        WRONG PASSWORD!!! TRY AGAIN!\a\a\a", ERROROFFSET);
		break;
	case 8:
		printf("%s\t       CAN'T ADD!!! NOT ENOUGH MEMORY!\n\n\t\t\t\t\t       CAN'T ADD!!! NOT ENOUGH MEMORY!\n\n\t\t\t\t\t       CAN'T ADD!!! NOT ENOUGH MEMORY!\a\a\a", ERROROFFSET);
		break;
	}
	Sleep(2000);
}

#endif // ERROR_H


