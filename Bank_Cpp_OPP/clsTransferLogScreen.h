#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:

public:
	static void ShowTransferLogScreen() {
        vector<clsBankClient::stTransferOpration> transfer_log = clsBankClient::GetTransferLogs();
        vector<vector<string>> _table_data;

        string _header_title = "Transfer Log List Screen";
        string _sub_title = "(" + to_string(transfer_log.size()) + ") Record(s).";
        _PrintHeader(_header_title, _Header_Char, _Window_Length, 2, _sub_title);

        _table_data.push_back({ "Date/Time", "Source Account", "Destination Account", "Amount",
        "Source Balance", "Destination Balance", "User"});

        for (clsBankClient::stTransferOpration& c : transfer_log) {
            _table_data.push_back({
                c.date, c.source_account_number, c.destination_account_number, to_string(c.amount),
                to_string(c.source_balance), to_string(c.destination_balance), c.username
            });
        }

        cout << "\n";
        clsOutput::MakeTable(_table_data, clsOutput::enPosition::left, false);

        if (transfer_log.empty()) {
            string message = "No transfer operations in the system.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
            cout << "\n" << message << "\n";
        }
	}
};

