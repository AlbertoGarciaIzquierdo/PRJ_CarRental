#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CCar.h"

class CCustomer
{
public:
	CCustomer();
	CCustomer(const CCustomer& Customer);
	CCustomer(const std::string& strName);

	inline std::string getCustomerName() { return m_Name; }

	inline int getCustomerPoints() const { return m_Points; }
	inline void AddCustomerPoints(int quantity) { m_Points++; }

	inline std::vector<CCar>& getRentedCar() { return m_rentedCar; }
	void addRentedCar(CCar rented, int days = 0);
	void removeRentedCar(CCar rented, int days = 0);

	inline float getInvoice() { return m_invoice; }

	void AddInvoice(CCar& rented);
	void AddTax(CCar& rented, int& days);
	void AddPoints(CCar& rented);

	CCar* getCar(int Index);

	void Print();
	void PrintCars();

private:
	std::string m_Name;
	std::vector<CCar> m_rentedCar;
	float m_invoice;
	int m_Points;
};

