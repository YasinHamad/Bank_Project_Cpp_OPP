#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"

class clsClientListScreen : protected clsScreen
{
private:

public:
	static void ShowClientList() {
        if (!CheckUserPermission(clsUser::enPermissions::ShowClientListPermission)) return;

        vector<clsBankClient> clients = clsBankClient::GetClientsList();
        vector<vector<string>> _table_data;

        string _header_title = "Client List Screen";
        string _sub_title = "(" + to_string(clients.size()) + ") Client(s).";
        _PrintHeader(_header_title, _Header_Char, _Window_Length, 2, _sub_title);

        _table_data.push_back({ "Account number", "Client name", "Phone", "Email", "Pin code", "Balance" });

        for (clsBankClient& c : clients) {
            _table_data.push_back({
                c.AccountNumber, c.getFullName(), c.Phone, c.Email, c.PinCode, "$ " + to_string(c.AccountBalance)
                });
        }

        cout << "\n";
        clsOutput::MakeTable(_table_data, clsOutput::enPosition::left, true);

        if (clients.empty()) {
            string message = "No clients in the system.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
            cout << "\n" << message << "\n";
        }
	}
};

