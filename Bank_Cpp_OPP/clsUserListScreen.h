#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsUser.h"

class clsUserListScreen : protected clsScreen
{
private:

public:
	static void ShowUsersList() {
        vector<clsUser> users = clsUser::GetUsersList();
        vector<vector<string>> _table_data;

        string _header_title = "Users List Screen";
        string _sub_title = "(" + to_string(users.size()) + ") User(s).";
        _PrintHeader(_header_title, _Header_Char, _Window_Length, 2, _sub_title);

        _table_data.push_back({ "Username", "Full name", "Phone", "Email", "Password", "Persmissions" });

        for (clsUser& c : users) {
            _table_data.push_back({
                c.Username, c.getFullName(), c.Phone, c.Email, c.Password, to_string(c.Permissions)
                });
        }

        cout << "\n";
        clsOutput::MakeTable(_table_data, clsOutput::enPosition::left, true);

        if (users.empty()) {
            string message = "No users in the system.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
            cout << "\n" << message << "\n";
        }
	}

};

