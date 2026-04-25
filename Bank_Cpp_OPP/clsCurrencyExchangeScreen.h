#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInput.h"
#include "clsListCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeOption {
		ListCurrenciesOption = 1, FindCurrencyOption = 2, UpdateRateOption = 3, CurrencyCalculatorOption = 4, MainMenueOption = 5
	};

	static void _PerformAction(enCurrencyExchangeOption option) {
		switch (option) {
		case enCurrencyExchangeOption::ListCurrenciesOption: {
			system("cls");
			_ShowListCurrenciesScreen();
			break;
		}
		case enCurrencyExchangeOption::FindCurrencyOption: { 
			system("cls");
			_ShowFindCurrencyScreen();
			break;
		}
		case enCurrencyExchangeOption::UpdateRateOption: { 
			system("cls");
			_ShowUpdateRateScreen();
			break;
		}
		case enCurrencyExchangeOption::CurrencyCalculatorOption: {
			system("cls");
			_ShowCurrencyCalculatorScreen();
			break;
		}
		case enCurrencyExchangeOption::MainMenueOption: { 
			//_ShowMainMenueScreen();
			return;
		}
		default: return ShowMainScreen();
		}
		return _GoBackToCurrencyExchangeMenue();
	}

	static void _ShowListCurrenciesScreen() {
		clsListCurrenciesListScreen::ShowCurrenciesList();
	}
	static void _ShowFindCurrencyScreen() {
		clsFindCurrencyScreen::ShowFindCurrency();
	}
	static void _ShowUpdateRateScreen() {
		clsUpdateCurrencyRateScreen::ShowScreen();
	}
	static void _ShowCurrencyCalculatorScreen() {
		clsCurrencyCalculatorScreen::ShowScreen();
	}
	//static void _ShowMainMenueScreen() {
	//	//clsMainScreen::ShowMainMenue();
	//}

	static void _GoBackToCurrencyExchangeMenue() {
		cout << "\n\n" << "Press any key to go back . . .";
		system("pause>0");
		ShowMainScreen();
	}

public:
	static void ShowMainScreen() {
		if (!CheckUserPermission(clsUser::enPermissions::CurrencyExchangePermission)) return;

		vector<string> options;
		options.push_back("[1] List Currencies.    ");
		options.push_back("[2] Find Currencies.    ");
		options.push_back("[3] Update Rate.        ");
		options.push_back("[4] Currency Calculator.");
		options.push_back("[5] Main Menue.         ");

		system("cls");
		_PrintHeader("Currency Exchange Main Screen", _Header_Char, _Window_Length, _Header_Vertical_Length);
		_PrintBody(options, "Currency Exchange Menue", _Body_Char, _Window_Length);

		_PerformAction((enCurrencyExchangeOption)_ReadOptionNumber("Choose what you want to do [1 to 5]: ",
			"Invalid number, choose number between [1] and [5]: ", 1, 5));
	}
};

