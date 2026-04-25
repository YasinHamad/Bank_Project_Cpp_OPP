#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "clsScreen.h"
#include "clsCurrency.h"

class clsListCurrenciesListScreen : protected clsScreen
{
private:

public:
	static void ShowCurrenciesList() {
        vector<clsCurrency> currencies = clsCurrency::GetCurrenciesList();
        vector<vector<string>> _table_data;

        string _header_title = "Currencies List Screen";
        string _sub_title = "(" + to_string(currencies.size()) + ") Currency.";
        _PrintHeader(_header_title, _Header_Char, _Window_Length, 2, _sub_title);

        _table_data.push_back({ "Country", "Code", "Name", "Rate/(1$)"});

        for (clsCurrency& c : currencies) {
            _table_data.push_back({
                c.Country, c.CurrencyCode, c.CurrencyName, to_string(c.Rate)
                });
        }

        cout << "\n";
        clsOutput::MakeTable(_table_data, clsOutput::enPosition::left, false);

        if (currencies.empty()) {
            string message = "No currencies in the system.";
            clsOutput::ColorString(message, clsOutput::enColorString::en_attention);
            cout << "\n" << message << "\n";
        }
	}


};

