#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"

class clsWithdrawScreen : protected clsScreen
{
private:
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
    static clsBankClient _ReadClient() {
        string account_number = "";
        string error_message = "Account doesn't exist, enter another one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);


        account_number = clsInput::ReadASentence("Enter account number: ");

        while (!clsBankClient::DoesClientExist(account_number)) {
            account_number = clsInput::ReadASentence(error_message);
        }

        return clsBankClient::Find(account_number);
    }

public:
    static void ShowWithdrawScreen() {
        _PrintHeader("Withdraw Screen", _Header_Char, _Window_Length, 2);

        clsBankClient client = _ReadClient();
        _PrintClient(client);

        cout << "\n";
        string error_message = "Invalid amount, enter another one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
        double amount = clsInput::ReadDbNumberInRange(1, DBL_MAX,
            "Enter the amount you want to withdraw: ", error_message);

        char check = 'n';
        check = clsInput::ReadChar("Are you sure you want to perform this transaction? [y/n]: ");
        if (!clsValidate::IsElementInVector({ 'y', 'Y' }, check)) {
            return;
        }

        if (client.Withdraw(amount))
        {
			string success_message = "Withdrew successfully.";
			clsOutput::ColorString(success_message, clsOutput::enColorString::en_sucess);
			cout << "\n" << success_message << "\n";
			cout << "\n" << "New balance is [" << client.AccountBalance << "]" << "\n";
        }
        else
        {
            string error_message = "Current balance is smaller than the given amount.";
            clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
            cout << "\n" << error_message << "\n";
            cout << "\n" << "Amount [" << amount << "]" << "\n";
            cout << "Current balance [" << client.AccountBalance << "]" << "\n";
        }


    }
};

