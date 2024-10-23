#pragma once
#include <iostream>
#include<vector>
#include <string>
#include <algorithm>

class CCustomer;
class CCar;

class CDatabase
{
public:
	CDatabase();

	CCustomer* getCustomer(int Index);
	CCustomer* getCustomer(const std::string& strName);

	CCar* getCar(int Index);
	CCar* getCar(const std::string& strLpn);

	void PrintCustomers();
	void PrintCars();

	void SetCustomerRented(const std::string& strName, CCar* rented, int daysRented);
	void SetCustomerReturn(const std::string& strName, CCar* rented, int daysRented);

private:
	std::vector<CCustomer> vCustomers;
	std::vector<CCar> vCars;
};

