#include "CDatabase.h"
#include "CCar.h"
#include "CCustomer.h"

CDatabase::CDatabase()
{
	// Meto en la DB algunos customers y algunos vehiculos
	// Customers
	vCustomers.push_back(CCustomer("Alberto"));
	vCustomers.push_back(CCustomer("Kevin"));
	vCustomers.push_back(CCustomer("Ana"));
	vCustomers.push_back(CCustomer("Sanna"));
	vCustomers.push_back(CCustomer("Victor"));
	vCustomers.push_back(CCustomer("Maria"));

	//Vehiculos
	vCars.push_back(CCar("BMW 7", "LPN001", CarTypes::Type::Premium));
	vCars.push_back(CCar("Kia Sorento", "LPN002", CarTypes::Type::SUV));
	vCars.push_back(CCar("Nissan Juke", "LPN003", CarTypes::Type::SUV));
	vCars.push_back(CCar("Seat Ibiza", "LPN004", CarTypes::Type::Small));
}

CCustomer* CDatabase::getCustomer(int Index)
{
	if (Index >= 0 && Index < vCustomers.size())
		return &vCustomers.at(Index);

	if (vCustomers.size() > 0)
	{
		std::cout << "Customer not found in DB... Using default value" << std::endl;
		return &vCustomers.at(0);
	}

	return nullptr;
}

CCustomer* CDatabase::getCustomer(const std::string& strName)
{
	auto it = std::find_if(vCustomers.begin(), vCustomers.end(),
		[strName](CCustomer& customer) {
			return customer.getCustomerName() == strName;
		});

	if (it != vCustomers.end()) 
	{
		return &(*it);
	}
	else 
	{
		return nullptr;
	}
}



CCar* CDatabase::getCar(int Index)
{
	if (Index >= 0 && Index < vCars.size())
		return &vCars.at(Index);

	return nullptr;
}

CCar* CDatabase::getCar(const std::string& strLpn)
{
	auto it = std::find_if(vCars.begin(), vCars.end(),
		[strLpn](CCar& car) {
			return car.getCarPlate() == strLpn;
		});

	if (it != vCars.end())
	{
		return &(*it);
	}
	else
	{
		return nullptr;
	}
}

void CDatabase::PrintCustomers()
{
	std::cout << "\nCustomers Table:\n";

	for (size_t i = 0; i < vCustomers.size(); ++i)
	{
		std::cout << i << " - Name: " << vCustomers.at(i).getCustomerName()
			<< " | Points: " << vCustomers.at(i).getCustomerPoints()
			<< " | Rented Car: ";
			for (CCar car : vCustomers.at(i).getRentedCar())
				std::cout << " " << car.getCarName();
			std::cout << " | Invoice: " << vCustomers.at(i).getInvoice() 
			<< std::endl;
	}
}

void CDatabase::PrintCars()
{
	std::cout << "\nCars Table:\n";

	for (size_t i = 0; i < vCars.size(); ++i)
	{
		std::cout << i << " - Name: " << vCars.at(i).getCarName() 
			<< " | " << "Plate: " << vCars.at(i).getCarPlate() 
			<< " | " << "Price: " << vCars.at(i).getCarPrice() 
			<< std::endl;
	}
}

void CDatabase::SetCustomerRented(const std::string& strName, CCar* rented, int daysRented)
{
	CCustomer* currentCustomer = getCustomer(strName);
	if (currentCustomer != nullptr)
	{
		currentCustomer->addRentedCar(*rented, daysRented);
		currentCustomer->AddPoints(*rented);
	}
}

void CDatabase::SetCustomerReturn(const std::string& strName, CCar* rented, int daysRented)
{
	CCustomer* currentCustomer = getCustomer(strName);
	if (currentCustomer != nullptr)
	{
		currentCustomer->removeRentedCar(*rented, daysRented);
	}
}
