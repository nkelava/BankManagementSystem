#include <stdio.h>
#include <stdlib.h>

#include "Menu.h"

// TODO:
// Add search by name/surname
// Map everything as hash table (v.2)


int main()
{
    char userChoice = 0;

    ImportDataAndLogin();  // Creates 2 lists(customers, employees) and does login

    void(*func_PtrArr[])() = { AddCustomer, DeleteCustomer, EditCustomerInformation, 
                               DepositMoney, WithdrawMoney, SearchCustomer, 
                               ListCustomers, ManageEmployees, ExitProgram };

    do {
        system("cls");
        srand(time(NULL));
        PrintOptions(EMPLOYEE);     // Main employee menu screen
        userChoice = _getch();

        if(userChoice > 48 && userChoice < 58)
        {
            (*func_PtrArr[userChoice - 49])();

            // Update file with every change so we have new data to work with in any time
            // No need for update if executed functions aren't changing data
            if (userChoice < 54)
            {
                UpdateCustomersFileData();
            }
        }
    }while(userChoice != 57);

    DeleteNodes();

    return 0;
}



