#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"
#include "clsValidate.h"

class clsTransferMoneyScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient client)
    {
        string title = "Client Card";
        int additiona_chars_length = clsOutput::ColorString(title, C_INVERT);

        cout << "\n" << clsOutput::FormatString(25 + additiona_chars_length, title, clsOutput::enPosition::center, "-") << "\n";
        cout << "Full Name   : " << client.getFullName() << "\n";
        cout << "Acc. Number : " << client.AccountNumber << "\n";
        cout << "Balance     : " << to_string(client.AccountBalance) << "\n";
        cout << clsOutput::GetChar(25, "-") << "\n";
    }
    static clsBankClient _ReadClient(string message) {
        string account_number = "";
        string error_message = "Account doesn't exist, enter another one: ";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);


        account_number = clsInput::ReadASentence(message);

        while (!clsBankClient::DoesClientExist(account_number)) {
            account_number = clsInput::ReadASentence(error_message);
        }

        return clsBankClient::Find(account_number);
    }

public:
	static void ShowTransferMoneyScreen() {
        _PrintHeader("Transfer Screen", _Header_Char, _Window_Length, 2);

        clsBankClient transfer_from = _ReadClient("Enter account number to transfer from: ");
        _PrintClient(transfer_from);

        cout << "\n";
        clsBankClient transfer_to = _ReadClient("Enter account number to transfer to: ");
        _PrintClient(transfer_to);

        string error_message = "The amount should be between [1 - " + to_string(transfer_from.AccountBalance) + "]";
        clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

        cout << "\n";
        double amount = clsInput::ReadDbNumberInRange(1, transfer_from.AccountBalance, "Enter transfer amount: ", error_message);

        bool check = clsInput::ReadBool("Are you sure you want to perform this operation? [y/n]: ");

        if (!check) return;

        if (transfer_from.Transfer(transfer_to, amount)) {
			cout << "\n";
			string success_message = "Transfer done successfully";
			clsOutput::ColorString(success_message, clsOutput::enColorString::en_sucess);
			cout << success_message << "\n";

			_PrintClient(transfer_from);
			_PrintClient(transfer_to);
        }
        else {
            cout << error_message << "\n";
        }
	}
};

