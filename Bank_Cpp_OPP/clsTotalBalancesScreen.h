#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:

public:
	static void ShowTotalBalancesScreen() {
        vector<clsBankClient> clients = clsBankClient::GetClientsList();
        //vector<clsBankClient> clients;
        vector<vector<string>> _table_data;
        double _total_balances = clsBankClient::GetTotalBalances();


        string subtitle = "Client list ( " + to_string(clients.size()) + " ) client(s).";
        _PrintHeader("Total Balances Screen", _Header_Char, _Window_Length, 2, subtitle);

        _table_data.push_back({ "Account number", "Client name", "Balance" });

        for (clsBankClient& c : clients) {
            _table_data.push_back({
                c.AccountNumber, c.getFullName(), "$ " + to_string(c.AccountBalance)
                });
        }

        cout << "\n";
        clsOutput::MakeTable(_table_data, clsOutput::enPosition::left, true);

        if (clients.empty()) {
            string message = "No clients in the system.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
            cout << "\n" << message << "\n";
        }
        else {
            cout << "\nTotal Balances = $ " << _total_balances;
            cout << " (" << clsUtil::NumberToText(round(_total_balances)) << " Dollars)" << "\n";
        }
	}
};

