#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersOption {
		ListUsersOption = 1, AddNewUserOption = 2, DeleteUserOption = 3, UpdateUserOption = 4, FindUserOption = 5, BackToMainMenueOption = 6
	};

	static void _PerformAction(enManageUsersOption option) {
		switch (option) {
		case enManageUsersOption::ListUsersOption:       { system("cls"); _ShowListUsersScreen();  break; }
		case enManageUsersOption::AddNewUserOption:      { system("cls"); _ShowAddNewUserScreen(); break; }
		case enManageUsersOption::DeleteUserOption:      { system("cls"); _ShowDeleteUserScreen(); break; }
		case enManageUsersOption::UpdateUserOption:      { system("cls"); _ShowUpdateUserScreen(); break; }
		case enManageUsersOption::FindUserOption:        { system("cls"); _ShowFindUserScreen();   break; }
		case enManageUsersOption::BackToMainMenueOption: { return; }
		default: return ShowManageUsersMenue();
		}
		return _GoBackToManageUsersMenue();
	}

	static void _ShowListUsersScreen() {
		clsUserListScreen::ShowUsersList();
	}
	static void _ShowAddNewUserScreen() {
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	static void _ShowDeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindUserScreen() {
		clsFindUserScreen::ShowFindUserScreen();
	}
	//static void _ShowMainMenueScreen() {
	//	//clsMainScreen::ShowMainMenue();
	//}

	static void _GoBackToManageUsersMenue() {
		cout << "\n\n" << "Press any key to go back . . .";
		system("pause>0");
		ShowManageUsersMenue();
	}

public:
	static void ShowManageUsersMenue() {
		if (!CheckUserPermission(clsUser::enPermissions::ManageUsersPermission)) return;

		vector<string> options;
		options.push_back("[1] List Uers.   ");
		options.push_back("[2] Add New User.");
		options.push_back("[3] Delete User. ");
		options.push_back("[4] Update User. ");
		options.push_back("[5] Find User.   ");
		options.push_back("[6] Main Menue.  ");

		system("cls");
		_PrintHeader("Manage Users Screen", _Header_Char, _Window_Length, _Header_Vertical_Length);
		_PrintBody(options, "Manage Users Menue", _Body_Char, _Window_Length);

		_PerformAction((enManageUsersOption)_ReadOptionNumber("Choose what you want to do [1 to 6]: ",
			"Invalid number, choose number between [1] and [6]: ", 1, 6));
	}
};

