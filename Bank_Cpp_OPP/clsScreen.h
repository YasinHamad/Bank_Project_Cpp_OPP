#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsOutput.h"
#include "clsInput.h"
#include "Global.h"


class clsScreen
{
protected:
	static const string _Header_Char;
	static const string _Body_Char;
	static const int _Window_Length;
	static const int _Header_Vertical_Length;

protected:
	static void _PrintHeader(string title, string line_char, int line_width, int vertical_spaces = 1, string sub_title = "") {
		cout << clsOutput::GetChar(line_width, line_char);
		cout << clsOutput::GetChar(vertical_spaces, "\n");

		//int additional_chars_to_title = clsOutput::ColorString(title, clsOutput::enColorString::en_invert);
		cout << clsOutput::FormatString(line_width, title, clsOutput::enPosition::center);

		if (!sub_title.empty())
		{
			//int additional_chars_to_subtitle = clsOutput::ColorString(sub_title, clsOutput::enColorString::en_invert);
			//if (!title.empty()) cout << "\n";
			cout << "\n" << clsOutput::FormatString(line_width, sub_title, clsOutput::enPosition::center);
		}
		cout << clsOutput::GetChar(vertical_spaces, "\n");

		cout << clsOutput::GetChar(line_width, line_char);
		cout << endl;

		// print date and user
		if (vertical_spaces == 2) {
			cout << "\n";
			clsDate _todays_date;
			string todays_date = _todays_date.PrintDateLong();
			string current_user = Global_User.Username;

			todays_date = "{" + todays_date + "}";
			current_user = "{" + current_user + "}";

			clsOutput::ColorString(todays_date, clsOutput::enColorString::en_invert);
			clsOutput::ColorString(current_user, clsOutput::enColorString::en_invert);

			cout << "Date: " << todays_date << "\n";
			cout << "User: " << current_user << "\n\n";
		}
	}
	
	static void _PrintBody(vector<string> options, string title, string line_char, int line_width) {
		_PrintHeader(title, line_char, line_width);

		for (string& option : options) {
			cout << clsOutput::FormatString(line_width, option, clsOutput::enPosition::left) << "\n";
		}

		cout << clsOutput::GetChar(line_width, _Header_Char);
		cout << endl;
	}

	static int _ReadOptionNumber(string enter_message, string error_message, int from, int to) {
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
		return clsInput::ReadIntNumberInRange(from, to, enter_message, error_message);
	}

	static bool CheckUserPermission(clsUser::enPermissions permission) {
		if (Global_User.CanUserEnter(permission)) {
			return true;
		}
		_PrintHeader("Access denied, contact your admin.", _Header_Char, _Window_Length, 2);
		return false;
	}
	
};

const string clsScreen::_Header_Char = "=";
const string clsScreen::_Body_Char = "-";
const int clsScreen::_Window_Length = 70;
const int clsScreen::_Header_Vertical_Length = 2;

