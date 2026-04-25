#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"

class clsFindClientScreen : protected clsScreen
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
	static void ShowFindClientScreen() {
		if (!CheckUserPermission(clsUser::enPermissions::FindClientPermission)) return;

		string exit_message = "Enter 'exit' to exit.";
		clsOutput::ColorString(exit_message, clsOutput::enColorString::en_attention);
		string account_number = "";
		string error_message = "Account doesn't exist, enter another one: ";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

		_PrintHeader("Update Client Screen", _Header_Char, _Window_Length, 2);
		
		cout << "\n" << exit_message << "\n\n";

		account_number = clsInput::ReadASentence("Enter account number: ");
		if (account_number == "exit") return;

		while (!clsBankClient::DoesClientExist(account_number)) {
			account_number = clsInput::ReadASentence(error_message);
			if (account_number == "exit") return;
		}

		clsBankClient client = clsBankClient::Find(account_number);
		_PrintClient(client);
	}
};

