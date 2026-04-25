#pragma once

#include <iostream>
#include <string>

#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login() {
		string error_message = "Invalid username/password .";
		string error_message2 = "";
		string locked_message = "You are locked after 3 failed trails";
		string username = "";
		string password = "";
		int counter = 3;

		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
		clsOutput::ColorString(locked_message, clsOutput::enColorString::en_error);

		while (true) {
			username = clsInput::ReadASentence("Username: ");
			password = clsInput::ReadASentence("Password: ");
			clsUser user = clsUser::Find(username, password);

			if (user.IsEmpty()) {
				cout << error_message << "\n";

				if (counter == 1) {
					cout << locked_message << "\n";
					return false;
				}

				counter--;
				error_message2 = "You have " + to_string(counter) + " trials to login.";
				clsOutput::ColorString(error_message2, clsOutput::enColorString::en_error);
				cout << error_message2 << "\n\n";

				continue;
			}
			Global_User = user;
			Global_User.SaveLogin();
			break;
		}
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		_PrintHeader("Login Screen", _Header_Char, _Window_Length, 2);
		return _Login();
	}
};

