#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
	enum enFindBy { FindByCoutryNameOption = 0, FindByCurrencyCodeOption = 1, TakeOptionFromUser = 2 };

	static void _PrintCurrency(clsCurrency currency) {
		string title = "Currency Card";
		int additiona_chars_length = clsOutput::ColorString(title, C_INVERT);

		cout << "\n" << clsOutput::FormatString(25 + additiona_chars_length, title, clsOutput::enPosition::center, "-") << "\n";
		cout << "Country Name : " << currency.Country << "\n";
		cout << "Currency Code: " << currency.CurrencyCode << "\n";
		cout << "Currency Name: " << currency.CurrencyName << "\n";
		cout << "Rate( 1$ )   : " << to_string(currency.Rate) << "\n";
		cout << clsOutput::GetChar(25, "-") << "\n";
	}

	static clsCurrency _FindCurrencyByCode() {
		string currency_code = clsInput::ReadASentence("Enter currency code : ");
		clsCurrency currency = clsCurrency::FindByCurrencyCode(currency_code);
		return currency;
	}
	static clsCurrency _FindCurrencyByCountry() {
		string country_name = clsInput::ReadASentence("Enter country name : ");
		clsCurrency currency = clsCurrency::FindByCountry(country_name);
		return currency;
	}
	static clsCurrency _FindCurrencyByUserOption() {
		int find_by = 0;
		string error_message = "You should enter a number between [1 and 2] : ";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

		find_by = clsInput::ReadIntNumberInRange(1, 2, "Find by currency code or country name? [1/2] : ", error_message);

		if (find_by == 1) {
			return _FindCurrencyByCode();
		}
		else {
			return _FindCurrencyByCountry();
		}
	}

	static clsCurrency _ReadCurrency(enFindBy find_by) {
		switch (find_by) {
		case enFindBy::FindByCoutryNameOption: return _FindCurrencyByCountry();
		case enFindBy::FindByCurrencyCodeOption: return _FindCurrencyByCode();
		default: return _FindCurrencyByUserOption();
		}
	}

	static void _ShowResult(clsCurrency currency) {
		string error_message = "Currency doesn't exist.";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
		if (currency.IsEmpty()) {
			cout << "\n" << error_message << "\n";
		}
		else {
			_PrintCurrency(currency);
		}
	}

public:
	static void ShowFindCurrency() {
		_PrintHeader("Find Currency Screen", _Header_Char, _Window_Length, _Header_Vertical_Length);

		clsCurrency currency = _ReadCurrency(enFindBy::TakeOptionFromUser);
		_ShowResult(currency);
	}
};

