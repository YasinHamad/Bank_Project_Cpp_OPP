#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen
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

	static clsCurrency _FindCurrencyByCode(string message) {
		string error_message = "Currency doesn't exist, enter another code: ";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

		string currency_code = clsInput::ReadASentence(message);

		while (true) {
			clsCurrency currency = clsCurrency::FindByCurrencyCode(currency_code);
			if (!currency.IsEmpty()) return currency;
			currency_code = clsInput::ReadASentence(error_message);
		}
	}
	static clsCurrency _FindCurrencyByCountry(string message) {
		string error_message = "Currency doesn't exist, enter another country: ";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

		string country_name = clsInput::ReadASentence(message);

		while (true) {
			clsCurrency currency = clsCurrency::FindByCountry(country_name);
			if (!currency.IsEmpty()) return currency;
			country_name = clsInput::ReadASentence(error_message);
		}
	}
	static clsCurrency _FindCurrencyByUserOption(string by_code_message, string by_country_message) {
		int find_by = 0;
		string error_message = "You should enter a number between [1 and 2] : ";
		clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

		find_by = clsInput::ReadIntNumberInRange(1, 2, "Find by currency code or country name? [1/2] : ", error_message);

		if (find_by == 1) {
			return _FindCurrencyByCode(by_code_message);
		}
		else {
			return _FindCurrencyByCountry(by_country_message);
		}
	}

	static clsCurrency _ReadCurrency(enFindBy find_by, string by_country_message, string by_code_message) {
		switch (find_by) {
		case enFindBy::FindByCoutryNameOption: return _FindCurrencyByCountry(by_country_message);
		case enFindBy::FindByCurrencyCodeOption: return _FindCurrencyByCode(by_code_message);
		default: return _FindCurrencyByUserOption(by_code_message, by_country_message);
		}
	}

	static float _ConvertFromDollerToX(float amount, clsCurrency currency) {
		string message = "Convert from USD to " + currency.CurrencyCode + ": ";
		clsOutput::ColorString(message, clsOutput::enColorString::en_attention);

		cout << "\n" << message << "\n";

		_PrintCurrency(currency);
		float result = currency.ConvertFromDollar(amount);

		cout << amount << " USD = " << result << " " << currency.CurrencyCode << "\n";

		return result;

	}
	static float _ConvertFromXToDoller(float amount, clsCurrency currency) {
		string message = "Convert from " + currency.CurrencyCode + " to USD: ";
		clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
		cout << "\n" << message << "\n";

		_PrintCurrency(currency);
		float result = currency.ConvertToDollar(amount);

		cout << amount << " " << currency.CurrencyCode << " = " << result << " USD" << "\n";

		return result;
	}
	static void _ConvertFromXToY(float amount, clsCurrency currency1, clsCurrency currency2) {
		_ConvertFromDollerToX(_ConvertFromXToDoller(amount, currency1), currency2);
	}

public:
	static void ShowScreen() {
		while (true) {
			_PrintHeader("Currency Calculator Screen", _Header_Char, _Window_Length, _Header_Vertical_Length);
			string error_message = "";
			clsCurrency currency1 = _FindCurrencyByCode("Enter currency one code: ");
			clsCurrency currency2 = _FindCurrencyByCode("Enter currency two code: ");

			if(currency1.CurrencyCode == currency2.CurrencyCode) {
				error_message = "You should choose two different currencies.";
				clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);

				cout << error_message << "\n";
				cout << "\n" << "Press any key to repeat . . ." << "\n";
				system("pause>0");
				system("cls");
				continue;
			}
			
			error_message = "You should enter a positive number: ";
			clsOutput::ColorString(error_message, clsOutput::enColorString::en_error);
			float amount = clsInput::ReadFlNumberInRange(1, FLT_MAX, "Enter amount to exchange: ", error_message);
			
			if (currency1.CurrencyCode == "USD") _ConvertFromDollerToX(amount, currency2);
			else if (currency2.CurrencyCode == "USD") _ConvertFromXToDoller(amount, currency1);
			else _ConvertFromXToY(amount, currency1, currency2);

			cout << "\n";
			if (clsInput::ReadBool("Do you want to perform another operation? [y/n]: ")) {
				system("cls");
			}
			else break;

		}

		
	}
};

