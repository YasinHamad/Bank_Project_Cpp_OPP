#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInput.h"

class clsAddNewUserScreen : protected clsScreen
{
private:


    static void _ReadUserData(clsUser& user) {
        user.FirstName = clsInput::ReadASentence("Enter first name: ");
        user.LastName = clsInput::ReadASentence("Enter last name: ");
        user.Phone = clsInput::ReadASentence("Enter phone: ");
        user.Email = clsInput::ReadASentence("Enter email: ");
        user.Password = clsInput::ReadASentence("Enter password: ");
        user.Permissions = _ReadUserPermissions();
    }

    static void _AskForPermission(string message, int& permission, int value) {
        char check = 'a';
        // get out of the loop if the user enterd 'n'
        // add the permission value if the user entered 'y'
        // stuck int the loop otherwise
        while (true) {
            cout << message;
            cin >> check;
            if (tolower(check) != 'y' && tolower(check) != 'n') {
                string message = "Invalid input.";
                clsOutput::ColorString(message, clsOutput::enColorString::en_error);
                cout << message << "\n";
                continue;
            }
            if (tolower(check) == 'y') permission += value;
            break;
        }
    }

    static int _ReadUserPermissions() {
        int permissions = 0;
        _AskForPermission("Do you want to give this user full access to the system? [y/n]: ", permissions, -1);
        if (permissions == -1) return permissions;

        cout << "\n" << "Do you want to give access to: " << "\n\n";

        _AskForPermission("Show client list [y/n]: ", permissions, (int)clsUser::enPermissions::ShowClientListPermission);
        _AskForPermission("Add new client [y/n]: ", permissions, (int)clsUser::enPermissions::AddNewClientPermission);
        _AskForPermission("Delete client [y/n]: ", permissions, (int)clsUser::enPermissions::DeleteClientPermission);
        _AskForPermission("Update client [y/n]: ", permissions, (int)clsUser::enPermissions::UpdataClientInfoPermission);
        _AskForPermission("Find client [y/n]: ", permissions, (int)clsUser::enPermissions::FindClientPermission);
        _AskForPermission("Transactions [y/n]: ", permissions, (int)clsUser::enPermissions::TransactionsPermission);
        _AskForPermission("Manage users [y/n]: ", permissions, (int)clsUser::enPermissions::ManageUsersPermission);
        _AskForPermission("Show login registers list[y/n]: ", permissions, (int)clsUser::enPermissions::ShowLoginRegisterListPermission);
        _AskForPermission("Currency Exchange[y/n]: ", permissions, (int)clsUser::enPermissions::CurrencyExchangePermission);

        return permissions;
    }

    static void _PrintUser(clsUser user)
    {
        string title = "User Card";
        int additiona_chars_length = clsOutput::ColorString(title, C_INVERT);

        cout << "\n" << clsOutput::FormatString(25 + additiona_chars_length, title, clsOutput::enPosition::center, "-") << "\n";
        cout << "FirstName   : " << user.FirstName << "\n";
        cout << "LastName    : " << user.LastName << "\n";
        cout << "Full Name   : " << user.getFullName() << "\n";
        cout << "Email       : " << user.Email << "\n";
        cout << "Phone       : " << user.Phone << "\n";
        cout << "Password    : " << user.Password << "\n";
        cout << "Username    : " << user.Username << "\n";
        cout << "Permissions : " << to_string(user.Permissions) << "\n";
        cout << clsOutput::GetChar(25, "-") << "\n";
    }

public:
    static void ShowAddNewUserScreen() {
        string username = "";
        string error_message = "User exists, enter another one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

        _PrintHeader("Add New User", _Header_Char, _Window_Length, 2);

        username = clsInput::ReadASentence("Enter username: ");

        while (clsUser::DoesUserExist(username)) {
            username = clsInput::ReadASentence(error_message);
        }

        string title = "Fill user info: ";
        clsOutput::ColorString(title, C_UNDERLINE);
        clsOutput::ColorString(title, C_DARK_YELLOW_B);
        clsOutput::ColorString(title, C_WHITE);
        cout << "\n" << title << "\n\n";

        clsUser user = clsUser::GetAddNewUserObject(username);

        _ReadUserData(user);

        clsUser::enSaveResult save_resutl = user.Save();

        switch (save_resutl)
        {
        case clsUser::en_succeeded:
        {
            string message = "User added successfully.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_sucess);
            cout << "\n" << message << "\n";
            _PrintUser(user);
            break;
        }
        case clsUser::en_faild_empty_object: {
            string message = "Can't save an empty user.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_error);
            cout << "\n" << message << "\n";
            break;
        }
        case clsUser::en_faild_account_number_exist: {
            string message = "Username exists.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_error);
            cout << "\n" << message << "\n";
            break;
        }
        default:
            exit(-1);
        }
    }

};

