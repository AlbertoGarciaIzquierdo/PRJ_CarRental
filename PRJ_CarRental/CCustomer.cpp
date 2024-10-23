#include "CCustomer.h"

CCustomer::CCustomer()
	: m_Name(""), m_Points(0), m_invoice(0.0f)
{
}

CCustomer::CCustomer(const CCustomer& Customer)
	: m_Name(Customer.m_Name), m_Points(Customer.m_Points), m_invoice(Customer.m_invoice), m_rentedCar(Customer.m_rentedCar)
{
}

CCustomer::CCustomer(const std::string& strName)
	: m_Name(strName), m_Points(0), m_invoice(0.0f)
{
}

void CCustomer::addRentedCar(CCar rented, int days)
{
	m_rentedCar.push_back(rented);

	std::string strLpn = rented.getCarPlate();
	auto it = std::find_if(m_rentedCar.begin(), m_rentedCar.end(),
		[strLpn](CCar& car) {
			return car.getCarPlate() == strLpn;
		});

	if (it != m_rentedCar.end())
	{
		it->setRentedDays(days);
		AddInvoice(*it, days);
	}
	else
	{
		std::cout << "Car not found, could erase" << std::endl;
	}
}

void CCustomer::removeRentedCar(CCar rented, int days)
{
	std::string strLpn = rented.getCarPlate();
	auto it = std::find_if(m_rentedCar.begin(), m_rentedCar.end(),
		[strLpn](CCar& car) {
			return car.getCarPlate() == strLpn;
		});

	if (it != m_rentedCar.end())
	{
		int extraDays = days - it->getRentedDays();
		if (extraDays > 0)
			AddTax(*it, days);
		m_rentedCar.erase(it);
	}
	else
	{
		std::cout << "Car not found, could erase" << std::endl;
	}
}

void CCustomer::AddInvoice(CCar& rented, int& days)
{
	switch (rented.getCarType())
	{
	case CarTypes::Type::Premium:
	{
		
		if (days > rented.getRentedDays())
		{
			int extraDays = days - rented.getRentedDays();
			m_invoice += extraDays * (rented.getCarPrice() + (rented.getCarPrice() * 0.2f));
			break;
		}

		m_invoice += rented.getRentedDays() * rented.getCarPrice();
		break;
	}
	case CarTypes::Type::SUV:
	{
		if (days > rented.getRentedDays())
		{
			int extraDays = days - rented.getRentedDays();
			m_invoice += extraDays * (rented.getCarPrice() + (rented.getCarPrice() * 0.6f));
			break;
		}

		if (rented.getRentedDays() > 30)
		{
			m_invoice += rented.getRentedDays() * (rented.getCarPrice() * 0.5f);
			break;
		}

		if (rented.getRentedDays() > 7)
		{
			m_invoice += rented.getRentedDays() * (rented.getCarPrice() * 0.8f);
			break;
		}

		m_invoice += rented.getRentedDays() * rented.getCarPrice();
		break;
	}
	case CarTypes::Type::Small:
	{
		if (days > rented.getRentedDays())
		{
			int extraDays = days - rented.getRentedDays();
			m_invoice += extraDays * (rented.getCarPrice() + (rented.getCarPrice() * 0.3f));
			break;
		}

		if (rented.getRentedDays() > 7)
		{
			m_invoice += rented.getRentedDays() * (rented.getCarPrice() * 0.6f);
			break;
		}

		m_invoice += rented.getRentedDays() * (rented.getCarPrice());
		break;
	}
	default:
		break;
	}
}

void CCustomer::AddTax(CCar& rented, int& days)
{
	switch (rented.getCarType())
	{
	case CarTypes::Type::Premium:
	{
		m_invoice += days * (rented.getCarPrice() + (rented.getCarPrice() * 0.2f));

		break;
	}
	case CarTypes::Type::SUV:
	{
		m_invoice += days * (rented.getCarPrice() + (rented.getCarPrice() * 0.6f));

		break;
	}
	case CarTypes::Type::Small:
	{
		m_invoice += days * (rented.getCarPrice() + (rented.getCarPrice() * 0.3f));

		break;
	}
	default:
		break;
	}
}

void CCustomer::AddPoints(CCar& rented)
{
	switch (rented.getCarType())
	{
	case CarTypes::Type::Premium:
	{
		m_Points += 5;
		break;
	}
	case CarTypes::Type::SUV:
	{
		m_Points += 3;
		break;
	}
	case CarTypes::Type::Small:
	{
		m_Points += 1;
		break;
	}
	default:
		break;
	}
}

CCar* CCustomer::getCar(int Index)
{
	if (Index >= 0 && Index < m_rentedCar.size())
		return &m_rentedCar.at(Index);

	return nullptr;
}

void CCustomer::Print()
{
	std::cout << "\nCustomer info - Name: " << m_Name
		<< ", Points: " << m_Points
		<< ", Rented Car:"; 
	for (CCar car : m_rentedCar)
		std::cout << " " << car.getCarName();
	std::cout << " | Invoice: " << m_invoice << std::endl;
}

void CCustomer::PrintCars()
{
	std::cout << "\nCars Table:\n";

	for (size_t i = 0; i < m_rentedCar.size(); ++i)
	{
		std::cout << i << " - Name: " << m_rentedCar.at(i).getCarName()
			<< " | " << "Plate: " << m_rentedCar.at(i).getCarPlate()
			<< " | " << "Price: " << m_rentedCar.at(i).getCarPrice()
			<< " | " << "Days: " << m_rentedCar.at(i).getRentedDays()
			<< std::endl;
	}
}


