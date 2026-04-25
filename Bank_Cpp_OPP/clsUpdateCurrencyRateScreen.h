#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	enum enFindBy{ FindByCoutryNameOption = 0, FindByCurrencyCodeOption = 1 , TakeOptionFromUser = 2};

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
		string error_message = "Currency doesn't exist, enter another code: ";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

		string currency_code = clsInput::ReadASentence("Enter currency code : ");

		while (true) {
			clsCurrency currency = clsCurrency::FindByCurrencyCode(currency_code);
			if (!currency.IsEmpty()) return currency;
			currency_code = clsInput::ReadASentence(error_message);
		}
	}
	static clsCurrency _FindCurrencyByCountry() {
		string error_message = "Currency doesn't exist, enter another country: ";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

		string country_name = clsInput::ReadASentence("Enter country name : ");

		while (true) {
			clsCurrency currency = clsCurrency::FindByCountry(country_name);
			if (!currency.IsEmpty()) return currency;
			country_name = clsInput::ReadASentence(error_message);
		}
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

public:
	static void ShowScreen() {
		_PrintHeader("Update Currency Screen", _Header_Char, _Window_Length, _Header_Vertical_Length);

		clsCurrency currency = _ReadCurrency(enFindBy::FindByCurrencyCodeOption);

		_PrintCurrency(currency);

		bool check = clsInput::ReadBool("Are you sure you want to update the rate of this currency? [y/n]: ");
		if (!check) return;

		string message = "Update Currency Rate: ";
		string error_message = "The rate should be positive.";
		string success_message = "Currency rate updated successfully.";
		clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
		clsOutput::ColorString(success_message, clsOutput::enColorString::en_sucess);

		cout << "\n" << message << "\n\n";

		double new_rate = clsInput::ReadDbNumberInRange(0, DBL_MAX, "Enter new rate: ", error_message);

		currency.UpdateRate(new_rate);

		cout << "\n" << success_message << "\n";
		_PrintCurrency(currency);
	}
};

