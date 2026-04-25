#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
#include "clsCurrencyExchangeScreen.h"

class clsMainScreen : protected clsScreen
{
private:
	enum enOptions {
		ShowClientListOption = 1, AddNewClientOption = 2, DeleteClientOption = 3,
		UpdataClientInfoOption = 4, FindClientOption = 5, TransactionsOption = 6, ManageUsersOption = 7,
		LoginRegisterOption = 8, CurrencyExchangeOption = 9, ExitOption = 10
	};

	static void _PerformAction(enOptions option) {
		system("cls");
		switch (option) {
		case enOptions::ShowClientListOption:   { _ShowAllClientsScreen();      break; }
		case enOptions::AddNewClientOption:     { _ShowAddNewClientScreen();    break; }
		case enOptions::DeleteClientOption:     { _ShowDeleteClientScreen();    break; }
		case enOptions::UpdataClientInfoOption: { _ShowUpdateClientScreen();    break; }
		case enOptions::FindClientOption:       { _ShowFindClientScreen();      break; }
		case enOptions::TransactionsOption:     { _ShowTransactionsMenue();     break; }
		case enOptions::ManageUsersOption:      { _ShowManageUsersMenue();      break; }
		case enOptions::LoginRegisterOption:    { _ShowLoginRegisterScreen();   break; }
		case enOptions::CurrencyExchangeOption: { _ShowCurrencyExchangeScreen();break; }
		case enOptions::ExitOption:             { return _Logout(); }
		default: return ShowMainMenue();
		}
		_GoBackToMainMenue();
	}

	static void _GoBackToMainMenue() {
		cout << "\n\n" << "Press any key to go back . . .";
		system("pause>0");
		ShowMainMenue();
	}
	
	static void _ShowAllClientsScreen() {
		clsClientListScreen::ShowClientList();
	}
	
	static void _ShowAddNewClientScreen() {
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}
	
	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	
	static void _ShowUpdateClientScreen() {
		clsUpdateClientScreen::ShowUpdateClient();
	}
	
	static void _ShowFindClientScreen() {
		clsFindClientScreen::ShowFindClientScreen();
	}
	
	static void _ShowTransactionsMenue() {
		clsTransactionScreen::ShowTransactionsMenue();
	}
	
	static void _ShowManageUsersMenue() {
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _ShowLoginRegisterScreen() {
		clsLoginRegisterScreen::ShowRegisterScreen();
	}
	static void _ShowCurrencyExchangeScreen() {
		clsCurrencyExchangeScreen::ShowMainScreen();
	}
	
	static void _Logout() {
		Global_User = clsUser::Find("");
	}


public:
	static void ShowMainMenue() {

		vector<string> options;
		options.push_back("[01] Show Client List.        ");
		options.push_back("[02] Add New Client.          ");
		options.push_back("[03] Delete Client.           ");
		options.push_back("[04] Update Client Info.      ");
		options.push_back("[05] Find Client.             ");
		options.push_back("[06] Transactions.            ");
		options.push_back("[07] Manage Users.            ");
		options.push_back("[08] Login Register.          ");
		options.push_back("[09] Currency Exchange Screen.");
		options.push_back("[10] Logout.                  ");

		system("cls");
		_PrintHeader("Main Menue Screen", _Header_Char, _Window_Length, _Header_Vertical_Length);
		_PrintBody(options, "Main Menue", _Body_Char, _Window_Length);

		_PerformAction((enOptions)_ReadOptionNumber("Choose what you want to do [1 to 10]: ",
			"Invalid number, choose number between [1] and [10]: ", 1, 10));
	}
};

