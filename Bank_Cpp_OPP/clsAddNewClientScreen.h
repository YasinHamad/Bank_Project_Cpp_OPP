#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientData(clsBankClient& client) {
        client.FirstName = clsInput::ReadASentence("Enter first name: ");
        client.LastName = clsInput::ReadASentence("Enter last name: ");
        client.Phone = clsInput::ReadASentence("Enter phone: ");
        client.Email = clsInput::ReadASentence("Enter email: ");
        client.PinCode = clsInput::ReadASentence("Enter pin code: ");
        string error_message = "Invalid input, please enter a valide one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
        client.AccountBalance = clsInput::ReadDbNumberInRange(0, FLT_MAX, "Enter account balance: ", error_message);
    }

    static void _PrintClient(clsBankClient client)
    {
        string title = "Client Card";
        int additiona_chars_length = clsOutput::ColorString(title, C_INVERT);

        cout << "\n" << clsOutput::FormatString(25 + additiona_chars_length, title, clsOutput::enPosition::center, "-") << "\n";
        cout << "FirstName   : " << client.FirstName << "\n";
        cout << "LastName    : " << client.LastName << "\n";
        cout << "Full Name   : " << client.getFullName() << "\n";
        cout << "Email       : " << client.Email << "\n";
        cout << "Phone       : " << client.Phone << "\n";
        cout << "Acc. Number : " << client.AccountNumber << "\n";
        cout << "Password    : " << client.PinCode << "\n";
        cout << "Balance     : " << to_string(client.AccountBalance) << "\n";
        cout << clsOutput::GetChar(25, "-") << "\n";
    }

public:
    static void ShowAddNewClientScreen() {
        if (!CheckUserPermission(clsUser::enPermissions::AddNewClientPermission)) return;

        string account_number = "";
        string error_message = "Account exists, enter another one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
        
        _PrintHeader("Add New Client", _Header_Char, _Window_Length, 2);

        account_number = clsInput::ReadASentence("Enter account number: ");

        while (clsBankClient::DoesClientExist(account_number)) {
            account_number = clsInput::ReadASentence(error_message);
        }

        string title = "Fill client info: ";
        clsOutput::ColorString(title, C_UNDERLINE);
        clsOutput::ColorString(title, C_DARK_YELLOW_B);
        clsOutput::ColorString(title, C_WHITE);
        cout << "\n" << title << "\n\n";

        clsBankClient client = clsBankClient::GetAddNewClientObject(account_number);

        _ReadClientData(client);

        clsBankClient::enSaveResult save_resutl = client.Save();

        switch (save_resutl)
        {
        case clsBankClient::en_succeeded:
        {
            string message = "Account added successfully.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_sucess);
            cout << "\n" << message << "\n";
            _PrintClient(client);
            break;
        }
        case clsBankClient::en_faild_empty_object: {
            string message = "Can't save an empty account.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_error);
            cout << "\n" << message << "\n";
            break;
        }
        case clsBankClient::en_faild_account_number_exist: {
            string message = "Account number exists.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_error);
            cout << "\n" << message << "\n";
            break;
        }
        default:
            exit(-1);
        }
    }

};

