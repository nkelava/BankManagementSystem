#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Auth/Login/Login.h"
#include "Menus/MainMenu.h"

// TODO:
// Add search by name/surname
// Map everything as hash table (v.2)


int main()
{
    char userOptionChoice = 0;

    ImportDataFromFiles();
    DisableConsoleResizing();
    AppLogin();

    void(*func_PtrArr[])() = { AddCustomer, DeleteCustomer, EditCustomerInformation,
                               DepositMoney, WithdrawMoney, SearchCustomer,
                               ListCustomers, ManageEmployees, ExitProgram 
    };

    do {
        system("cls");
        srand(time(NULL));

        PrintOptions(EMPLOYEE);     // Main employee menu screen
        userOptionChoice = _getch();

        if(userOptionChoice > 48 && userOptionChoice < 58) {
            (*func_PtrArr[userOptionChoice - 49])();

            // Update file with every change so we have new data to work with in any time
            // No need for update if executed functions aren't changing data
            if (userOptionChoice < 54) {
                UpdateCustomersFileData();
            }
        }
    } while(userOptionChoice != 57);

    DeleteDataNodes();

    return 0;
}
