#pragma once

#include <iostream>
#include <string>

#include "InterfaceCommunication.h"

using namespace std;

class clsPerson : public InterfaceCommunication
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	clsPerson(string FirstName, string LastName, string Email, string Phone) {
		this->_FirstName = FirstName;
		this->_LastName = LastName;
		this->_Email = Email;
		this->_Phone = Phone;
	}

	string getFirstName() { return _FirstName; }
	void setFirstName(string FirstName) { this->_FirstName = FirstName; }
	__declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	string getLastName() { return _LastName; }
	void setLastName(string LastName) { this->_LastName = LastName; }
	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	string getEmail() { return _Email; }
	void setEmail(string Email) { this->_Email = Email; }
	__declspec(property(get = getEmail, put = setEmail)) string Email;

	string getPhone() { return _Phone; }
	void setPhone(string Phone) { this->_Phone = Phone; }
	__declspec(property(get = getPhone, put = setPhone)) string Phone;

	string getFullName() { return getFirstName() + " " + getLastName(); }

	void SendEmail(string title, string body) {

	}
	void SendFax(string title, string body) {

	}
	void SendSMS(string title, string body) {

	}
};

