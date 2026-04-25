#pragma once

#include "clsScreen.h"
#include "clsString.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

public:
	static void ShowRegisterScreen() {
		if (!CheckUserPermission(clsUser::enPermissions::ShowLoginRegisterListPermission)) return;

        vector<clsUser::stLogin> logins = clsUser::GetLoginRegistersList();
        vector<vector<string>> _table_data;

        string _header_title = "Login Register List Screen";
        string _sub_title = "(" + to_string(logins.size()) + ") Record(s).";
        _PrintHeader(_header_title, _Header_Char, _Window_Length, 2, _sub_title);

        _table_data.push_back({ "Date/Time", "Username", "Password", "Persmissions" });

        for (clsUser::stLogin& c : logins) {
            _table_data.push_back({
                c.date, c.username, c.password, c.permissions
                });
        }

        cout << "\n";
        clsOutput::MakeTable(_table_data, clsOutput::enPosition::left, false);

        if (logins.empty()) {
            string message = "No logins in the system.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
            cout << "\n" << message << "\n";
        }
	}
};

