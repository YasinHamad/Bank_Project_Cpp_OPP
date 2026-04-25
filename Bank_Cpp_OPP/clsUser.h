#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "clsString.h"
#include "clsPerson.h"
#include "clsFiles.h"
#include "clsOutput.h"

#define UsersData "users.txt"
#define LogRegister "log_register.txt"

class clsUser : public clsPerson
{
public:
	enum enSaveResult { en_faild_empty_object = 0, en_succeeded = 1, en_faild_account_number_exist };
	enum enPermissions {
		AllPermissions = -1,
		ShowClientListPermission = 1, AddNewClientPermission = 2, DeleteClientPermission = 4,
		UpdataClientInfoPermission = 8, FindClientPermission = 16, TransactionsPermission = 32, ManageUsersPermission = 64,
		ShowLoginRegisterListPermission = 128, CurrencyExchangePermission = 256
	};
	struct stLogin {
		string date;
		string username;
		string password;
		string permissions;
	};

private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _Username;
	string _Password;
	int _Permissions;

	bool _MarkForDelete = false;

	static clsUser _ConvertLineToUserObject(string line, string separator = "#||#") {
		vector<string> data = clsString::Split(line, separator);

		return clsUser
		(
			enMode::UpdateMode, data[0], data[1], data[2], data[3], data[4], clsUtil::Decrypt(data[5], 5), stoi(data[6])
		);
	}

	static string _ConvertUserObjectToLine(clsUser user, string separator = "#||#") {
		string result = "";
		result += user.FirstName + separator;
		result += user.LastName + separator;
		result += user.Email + separator;
		result += user.Phone + separator;
		result += user.Username + separator;
		result += clsUtil::Encrypt(user.Password, 5) + separator;
		result += to_string(user.Permissions);
		return result;
	}

	static vector<clsUser> _LoadUsersDataFromFile() {
		vector<clsUser> users;
		fstream my_file;
		string line = "";

		my_file.open(UsersData, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {
				users.push_back(_ConvertLineToUserObject(line));
			}
			my_file.close();
		}

		return users;
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsUser _Find(string user_name, string password, bool with_password) {
		fstream my_file;
		string line = "";

		my_file.open(UsersData, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {
				clsUser user = _ConvertLineToUserObject(line);
				if (user.Username == user_name && (!with_password || password == user.Password)) {
					my_file.close();
					return user;
				}
			}
			my_file.close();
		}

		return _GetEmptyUserObject();
	}

	static void _SaveUsersToFile(vector<clsUser> _data) {
		fstream my_file;
		my_file.open(UsersData, ios::out);

		if (my_file.is_open()) {
			for (clsUser& c : _data) {
				if (!c._MarkForDelete) my_file << _ConvertUserObjectToLine(c) << endl;
			}
			my_file.close();
		}
	}

	static void _AddLineToFile(string line) {
		fstream my_file;
		my_file.open(UsersData, ios::out | ios::app);

		if (my_file.is_open()) {
			my_file << line << endl;
			my_file.close();
		}
	}

	void _Update() {
		vector<clsUser> data = _LoadUsersDataFromFile();

		for (clsUser& c : data) {
			if (c.Username == this->Username) {
				c = *this;
				break;
			}
		}

		_SaveUsersToFile(data);
	}

	void _AddNewObject() {
		_AddLineToFile(_ConvertUserObjectToLine(*this));
	}

	static string _ConvertUserObjectToLogRegisterLine(clsUser user, string separator = "#||#") {
		string result = "";

		result += clsDate::GetSystemDateTime() + separator;
		result += user.Username + separator;
		result += clsUtil::Encrypt(user.Password, 5) + separator;
		result += to_string(user.Permissions);
		return result;
	}

	static stLogin _ConvertLoginRecordToStruct(string line, string separator = "#||#") {
		vector<string> data = clsString::Split(line, separator);

		stLogin log_item;
		log_item.date = data[0];
		log_item.username = data[1];
		log_item.password = clsUtil::Decrypt(data[2], 5);
		log_item.permissions = data[3];

		return log_item;
	}

	static vector<stLogin> _LoadLoginRegistersList() {
		vector<stLogin> data;
		fstream my_file;
		string line = "";

		my_file.open(LogRegister, ios::in);

		if (my_file.is_open()) {
			while (getline(my_file, line)) {
				data.push_back(_ConvertLoginRecordToStruct(line));
			}
			my_file.close();
		}
		return data;
	}

public:
	clsUser(enMode Mode, string Firstname, string Lastname, string Phone, string Email, string Username, string Password, int Permissions) :
		clsPerson(Firstname, Lastname, Email, Phone){
		this->_Username = Username;
		this->_Password = Password;
		this->_Permissions = Permissions;
		this->_Mode = Mode;
	}

	string getUsername() { return _Username; }
	void setUsername(string Username) { this->_Username = Username; }
	__declspec(property(get = getUsername, put = setUsername)) string Username;

	string getPassword() { return _Password; }
	void setPassword(string Password) { this->_Password = Password; }
	__declspec(property(get = getPassword, put = setPassword)) string Password;

	int getPermissions() { return _Permissions; }
	void setPermissions(int Permissions) { this->_Permissions = Permissions; }
	__declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

	bool IsEmpty() { return this->_Mode == enMode::EmptyMode; }

	bool MarkedForDeleted() { return _MarkForDelete; }

	static clsUser Find(string username) {
		return _Find(username, "", false);
	}
	static clsUser Find(string username, string password) {
		return _Find(username, password, true);
	}

	static bool DoesUserExist(string username) {
		clsUser user = Find(username);
		return (!user.IsEmpty());
	}

	void SaveLogin() {
		clsFiles::AddLineToFile(_ConvertUserObjectToLogRegisterLine(*this), LogRegister);
	}

	enSaveResult Save() {
		switch (_Mode) {
		case enMode::EmptyMode: return enSaveResult::en_faild_empty_object;
		case enMode::UpdateMode: {
			_Update();
			return enSaveResult::en_succeeded;
		}
		case enMode::AddNewMode: {
			if (DoesUserExist(Username)) return enSaveResult::en_faild_account_number_exist;
			_AddNewObject();
			_Mode = enMode::UpdateMode;
			return enSaveResult::en_succeeded;
		}
		default: exit(-1);
		}
	}

	bool Delete() {
		if (!DoesUserExist(Username)) return 0;
		_MarkForDelete = true;
		_Update();
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string username) {
		return clsUser(
			enMode::AddNewMode, "", "", "", "", username, "", 0
		);
	}

	static vector<clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool CanUserEnter(enPermissions permission) {
		if (permission == enPermissions::AllPermissions) return true;
		return ((permission & Permissions) == permission);
	}

	static vector<stLogin> GetLoginRegistersList() {
		return _LoadLoginRegistersList();
	}
};

