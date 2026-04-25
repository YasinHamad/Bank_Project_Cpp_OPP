#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"

class clsDeleteClientScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& client)
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
    static void ShowDeleteClientScreen() {
        if (!CheckUserPermission(clsUser::enPermissions::DeleteClientPermission)) return;

        string account_number = "";
        string error_message = "Account doesn't exist, enter another one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

        _PrintHeader("Delete Client Screen", _Header_Char, _Window_Length, 2);

        account_number = clsInput::ReadASentence("Enter account number: ");

        while (!clsBankClient::DoesClientExist(account_number)) {
            account_number = clsInput::ReadASentence(error_message);
        }

        clsBankClient client = clsBankClient::Find(account_number);
        _PrintClient(client);

        if (!clsInput::ReadBool("Are you sure you want to delete this client? [y/n]: ")) return;

        string message = "";
        if (client.Delete()) {
            message = "Account deleted successfully.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_sucess);
        }
        else {
            message = "Error deleting the client.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_error);
        }
        cout << "\n" << message << "\n";
        _PrintClient(client);
    }
};

