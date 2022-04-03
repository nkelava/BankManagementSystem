# Bank Management System

Bank managment system project is a mini console based application developed using C programming language.
It is useful for managing customer bank accounts but there is also admin panel for managing employees.
Main data strcuture used in this project is linked list and all data is saved/read in/from files located in `./src/Data` folder.

<br/>

## Instructions

After you [clone the repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository) you can open and run the application in any IDE that can run C/C++ files.
<br/><br/>When the application starts you will be prompted with login panel where you have to enter employee ID and password.
You can use default login credentials that I provided in [section](#default-login-credentials) below or you can add a new employee/admin record in [Employees.txt](src/Data/Employees.txt) file.
That file can me modified but make sure you follow the right syntaxt --> `EmployeeId FirstName LastName Password RoleId`. Roles can be found [here](src/Enums/RoleEnum.h).
<br/><br/>If the login is successful you will see a main menu (options are listed in [Features section](#features) below).
Final important thing to mention is `Manage employees option` and that option leads you to admin panel where you can manage employees.
That't it. Thanks for visiting the repository and I hope you will enjoy using and playing with the app.

<br/>

## Default Login Credentials

Id             | Password
---------------|---------------------
0              | admin

<br/>

## Features

- Employee/Admin login
- Create new customer account
- Get customer account details
- Update customer account
- Delete customer account
- View customer list
- All above but for employees too
- Deposit money on account
- Withdraw money from account

