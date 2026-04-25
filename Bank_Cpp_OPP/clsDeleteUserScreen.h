#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInput.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
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
    static void ShowDeleteUserScreen() {
        string username = "";
        string error_message = "User doesn't exist, enter another one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

        _PrintHeader("Delete User Screen", _Header_Char, _Window_Length, 2);

        username = clsInput::ReadASentence("Enter username: ");

        while (!clsUser::DoesUserExist(username)) {
            username = clsInput::ReadASentence(error_message);
        }

        clsUser user = clsUser::Find(username);
        _PrintUser(user);

        if (!clsInput::ReadBool("Are you sure you want to delete this user? [y/n]: ")) return;

        string message = "";
        if (user.Delete()) {
            message = "User deleted successfully.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_sucess);
        }
        else {
            message = "Error deleting the user.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_error);
        }
        cout << "\n" << message << "\n";
        _PrintUser(user);
    }
};

