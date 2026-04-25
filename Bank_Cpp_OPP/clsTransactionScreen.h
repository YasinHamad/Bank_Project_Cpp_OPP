#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInput.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferMoneyScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionScreen : protected clsScreen
{
private:
	enum enTransactionOption {
		DepositeOption = 1, WithdrawOption = 2, TotalBalancesOption = 3, TransferMoney = 4, TransferLogOption = 5, MainMenueOption = 6
	};

	static void _PerformAction(enTransactionOption option) {
		switch (option) {
		case enTransactionOption::DepositeOption: { 
			system("cls");
			_ShowDepositScreen();
			break;
		}
		case enTransactionOption::WithdrawOption: { 
			system("cls");
			_ShowWithdrawScreen();
			break;
		}
		case enTransactionOption::TotalBalancesOption: { 
			system("cls");
			_ShowTotalBalancesScreen();
			break;
		}
		case enTransactionOption::TransferMoney: {
			system("cls");
			_ShowTransferMoneyScreen();
			break;
		}
		case enTransactionOption::TransferLogOption: {
			system("cls");
			_ShowTransferLogScreen();
			break;
		}
		case enTransactionOption::MainMenueOption: { 
			//_ShowMainMenueScreen();
			return;
		}
		default: return ShowTransactionsMenue();
		}
		return _GoBackToTransactionsMenue();
	}

	static void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositeScreen();
	}
	static void _ShowWithdrawScreen() {
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}
	static void _ShowTransferMoneyScreen() {
		clsTransferMoneyScreen::ShowTransferMoneyScreen();
	}
	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}
	//static void _ShowMainMenueScreen() {
	//	//clsMainScreen::ShowMainMenue();
	//}

	static void _GoBackToTransactionsMenue() {
		cout << "\n\n" << "Press any key to go back . . .";
		system("pause>0");
		ShowTransactionsMenue();
	}

public:
	static void ShowTransactionsMenue() {
		if (!CheckUserPermission(clsUser::enPermissions::TransactionsPermission)) return;

		vector<string> options;
		options.push_back("[1] Deposit.       ");
		options.push_back("[2] Withdraw.      ");
		options.push_back("[3] Total Balances.");
		options.push_back("[4] Transfer Money.");
		options.push_back("[5] Transfer Log.  ");
		options.push_back("[6] Main Menue.    ");

		system("cls");
		_PrintHeader("Transactions Screen", _Header_Char, _Window_Length, _Header_Vertical_Length);
		_PrintBody(options, "Transactions Menue", _Body_Char, _Window_Length);

		_PerformAction((enTransactionOption)_ReadOptionNumber("Choose what you want to do [1 to 6]: ",
			"Invalid number, choose number between [1] and [6]: ", 1, 6));
	}
};

