#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "clsString.h"
#include "clsPerson.h"
#include "clsFiles.h"
#include "clsOutput.h"

#define ClientData "clients.txt"
#define TransferLog "log_transfer.txt"

class clsBankClient : public clsPerson
{
public:
	enum enSaveResult { en_faild_empty_object = 0, en_succeeded = 1 , en_faild_account_number_exist};
	struct stTransferOpration {
		string date;
		string source_account_number;
		string destination_account_number;
		double amount;
		double source_balance;
		double destination_balance;
		string username;
	};

private:
	enum enMode{ EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string line, string separator = "#||#") {
		vector<string> data = clsString::Split(line, separator);

		return clsBankClient
		(
			enMode::UpdateMode, data.at(0), data.at(1), data.at(2), data.at(3), data.at(4), data.at(5), stof(data.at(6))
		);
	}
	static string _ConvertClientObjectToLine(clsBankClient client, string separator = "#||#") {
		string result = "";
		result += client.FirstName + separator;
		result += client.LastName + separator;
		result += client.Email + separator;
		result += client.Phone + separator;
		result += client.AccountNumber + separator;
		result += client.PinCode + separator;
		result += to_string(client.AccountBalance);
		return result;
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {
		vector<clsBankClient> clients;
		fstream my_file;
		string line = "";

		my_file.open(ClientData, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {
				clients.push_back(_ConvertLineToClientObject(line));
			}
			my_file.close();
		}

		return clients;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0.0);
	}

	static clsBankClient _Find(string AccountNumber, string PinCode, bool with_pin_code) {
		fstream my_file;
		string line = "";

		my_file.open(ClientData, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {
				clsBankClient client = _ConvertLineToClientObject(line);
				if (client.AccountNumber == AccountNumber && (!with_pin_code || PinCode == client.PinCode)) {
					my_file.close();
					return client;
				}
			}
			my_file.close();
		}

		return _GetEmptyClientObject();
	}

	static void _SaveClientsToFile(vector<clsBankClient> _data) {
		fstream my_file;
		my_file.open(ClientData, ios::out);

		if (my_file.is_open()) {
			for (clsBankClient& c : _data) {
				if(!c._MarkedForDelete) my_file << _ConvertClientObjectToLine(c) << endl;
			}
			my_file.close();
		}
	}

	static void _AddLineToFile(string line) {
		fstream my_file;
		my_file.open(ClientData, ios::out | ios::app);

		if (my_file.is_open()) {
			my_file << line << endl;
			my_file.close();
		}
	}

	void _Update() {
		vector<clsBankClient> data = _LoadClientsDataFromFile();

		for (clsBankClient& c : data) {
			if (c.AccountNumber == this->AccountNumber) {
				c = *this;
				break;
			}
		}

		_SaveClientsToFile(data);
	}

	void _AddNewObject() {
		_AddLineToFile(_ConvertClientObjectToLine(*this));
	}

	static string _ConvertToTransferLogRecord(clsBankClient source, clsBankClient destination, double amount, string username, string separator = "#||#") {
		string result = "";
		
		result += clsDate::GetSystemDateTime() + separator;
		result += source.AccountNumber + separator;
		result += destination.AccountNumber + separator;
		result += to_string(amount) + separator;
		result += to_string(source.AccountBalance) + separator;
		result += to_string(destination.AccountBalance) + separator;
		result += username;

		return result;
	}

	static stTransferOpration _ConvertToTransferStruct(string line) {
		vector<string> _data = clsString::Split(line, "#||#");

		stTransferOpration _transfer_operation;

		_transfer_operation.date = _data[0];
		_transfer_operation.source_account_number = _data[1];
		_transfer_operation.destination_account_number = _data[2];
		_transfer_operation.amount = stod(_data[3]);
		_transfer_operation.source_balance = stod(_data[4]);
		_transfer_operation.destination_balance = stod(_data[5]);
		_transfer_operation.username = _data[6];

		return _transfer_operation;
	}

	static void _LogTransferOperation(clsBankClient source, clsBankClient destination, double amount, string username) {
		clsFiles::AddLineToFile(_ConvertToTransferLogRecord(source, destination, amount, username), TransferLog);
	}

	static vector<stTransferOpration> _LoadTransferOprationsAsStructs() {
		string line = "";
		fstream my_file;
		vector<stTransferOpration> data;

		my_file.open(TransferLog, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {
				data.push_back(_ConvertToTransferStruct(line));
			}
			my_file.close();
		}
		return data;
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
	: clsPerson(FirstName, LastName, Email, Phone) {
		this->_Mode = Mode;
		this->_AccountNumber = AccountNumber;
		this->_PinCode = PinCode;
		this->_AccountBalance = AccountBalance;
	}

	string getAccountNumber() { return _AccountNumber; }
	__declspec(property(get = getAccountNumber)) string AccountNumber;

	string getPinCode() { return _PinCode; }
	void setPinCode(string PinCode) { this->_PinCode = PinCode; }
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	float getAccountBalance() { return _AccountBalance; }
	void setAccountBalance(float AccountBalance) { this->_AccountBalance = AccountBalance; }
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	bool IsEmpty() { return this->_Mode == enMode::EmptyMode; }

	static clsBankClient Find(string AccountNumber) {
		return _Find(AccountNumber, "", false);
	}
	static clsBankClient Find(string AccountNumber, string PinCode) {
		return _Find(AccountNumber, PinCode, true);
	}

	static bool DoesClientExist(string AccountNumber) {
		clsBankClient client = Find(AccountNumber);
		return (!client.IsEmpty());
	}

	enSaveResult Save() {
		switch (_Mode) {
		case enMode::EmptyMode: return enSaveResult::en_faild_empty_object;
		case enMode::UpdateMode: {
			_Update();
			return enSaveResult::en_succeeded;
		}
		case enMode::AddNewMode: {
			if (DoesClientExist(AccountNumber)) return enSaveResult::en_faild_account_number_exist;
			_AddNewObject();
			_Mode = enMode::UpdateMode;
			return enSaveResult::en_succeeded;
		}
		default: exit(-1);
		}
	}

	bool Delete() {
		if (!DoesClientExist(AccountNumber)) return 0;
		_MarkedForDelete = true;
		_Update();
		*this = _GetEmptyClientObject();
		return true;
	}

	static clsBankClient GetAddNewClientObject(string account_number) {
		return clsBankClient(
			enMode::AddNewMode, "", "", "", "", account_number, "", 0.0
		);
	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		vector<clsBankClient> clients = GetClientsList();
		double result = 0.0;

		for (clsBankClient& c : clients) {
			result += c.AccountBalance;
		}
		return result / clients.size();
	}

	void Deposit(double amount)
	{
		_AccountBalance += amount;
		Save();
	}
	bool Withdraw(double amount)
	{
		if (!clsValidate::IsNumberBetween(amount, 1.0, (double)this->AccountBalance)) return false;
		_AccountBalance -= amount;
		Save();
		return true;
	}

	bool Transfer(clsBankClient& transfer_to, double amount) {
		if (!(amount >= 1 && amount <= AccountBalance)) return false;
		if (this->AccountNumber == transfer_to.AccountNumber) return false;

		transfer_to.Deposit(amount);
		Withdraw(amount);

		_LogTransferOperation(*this, transfer_to, amount, Global_User.Username);
		return true;
	}

	static vector<stTransferOpration> GetTransferLogs() {
		return _LoadTransferOprationsAsStructs();
	}





};

