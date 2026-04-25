#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsString.h"

using namespace std;

#define CurrenciesData "currencies.txt"
#define Separator "#||#"

class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enum enFind { enFindByCountryName = 0, enFindByCurrencyCode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertRecordToCurrency(string line, string separator = Separator) {
		vector<string> data = clsString::Split(line, separator);

		return clsCurrency (
			enMode::UpdateMode, data[0], data[1], data[2], stof(data[3])
		);
	}
	static string _ConvertCurrencyToRecord(clsCurrency currency, string separator = Separator) {
		string result = "";

		result += currency.Country + separator;
		result += currency.CurrencyCode + separator;
		result += currency.CurrencyName + separator;
		result += to_string(currency.Rate);

		return result;
	}

	static vector<clsCurrency> _LoadCurrenciesFromFile() {
		fstream my_file;
		vector<clsCurrency> data;
		string line = "";

		my_file.open(CurrenciesData, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {
				data.push_back(_ConvertRecordToCurrency(line));
			}

			my_file.close();
		}

		return data;
	}
	static void _SaveCurrenciesToFile(vector<clsCurrency> data) {
		fstream my_file;

		my_file.open(CurrenciesData, ios::out);
		
		if (my_file.is_open()) {
			for (clsCurrency& c : data) {
				my_file << _ConvertCurrencyToRecord(c) << endl;
			}

			my_file.close();
		}
	}

	void _Update() {
		vector<clsCurrency> data = _LoadCurrenciesFromFile();

		for (clsCurrency& c : data) {
			if (c.CurrencyCode == CurrencyCode) { c = *this; break; }
		}

		_SaveCurrenciesToFile(data);
	}

	static clsCurrency GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0.0);
	}

	static clsCurrency _Find(enFind find_by, string country_name = "", string currency_code = "") {
		fstream my_file;
		string line = "";

		if(find_by == enFind::enFindByCurrencyCode) clsString::UpperStringByRef(currency_code);
		if(find_by == enFind::enFindByCountryName) clsString::UpperStringByRef(country_name);

		my_file.open(CurrenciesData, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {

				clsCurrency currency = _ConvertRecordToCurrency(line);

				switch (find_by) {
				case enFind::enFindByCurrencyCode: {
					if (currency.CurrencyCode == currency_code) { my_file.close(); return currency; }
					break;
				}
				case enFind::enFindByCountryName: {
					if (clsString::UpperString(currency.Country) == country_name) { my_file.close(); return currency; }
					break;
				}
				}
			}
			my_file.close();
		}
		return GetEmptyCurrencyObject();
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		this->_Mode = Mode;
		this->_Country = Country;
		this->_CurrencyCode = CurrencyCode;
		this->_CurrencyName = CurrencyName;
		this->_Rate = Rate;
	}

	string getCountry() { return _Country; }
	__declspec(property(get = getCountry)) string Country;

	string getCurrencyCode() { return _CurrencyCode; }
	__declspec(property(get = getCurrencyCode)) string CurrencyCode;

	string getCurrencyName() { return _CurrencyName; }
	__declspec(property(get = getCurrencyName)) string CurrencyName;

	float getRate() { return _Rate; }
	__declspec(property(get = getRate)) float Rate;

	bool IsEmpty() { return this->_Mode == enMode::EmptyMode; }

	void UpdateRate(float new_rate) {
		this->_Rate = new_rate;
		_Update();
	}

	static clsCurrency FindByCountry(string country) {
		return _Find(enFind::enFindByCountryName, country, "");
	}
	static clsCurrency FindByCurrencyCode(string currency_code) {
		return _Find(enFind::enFindByCurrencyCode, "", currency_code);
	}

	static bool DoesCurrencyExist(string currency_code) {
		clsCurrency currency = FindByCurrencyCode(currency_code);
		return (!currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList() { return _LoadCurrenciesFromFile(); }

	float ConvertToDollar(float amount) {
		return amount / Rate;
	}
	float ConvertFromDollar(float amount) {
		return amount * Rate;
	}
	float ConvertTo(clsCurrency currency, float amount) {
		return (ConvertToDollar(amount) * currency.Rate);
	}
};


