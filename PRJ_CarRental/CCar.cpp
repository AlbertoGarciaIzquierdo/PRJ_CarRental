#include "CCar.h"

CCar::CCar()
	: m_strName(""), m_strPlate(""), m_CarType(CarTypes::Type::Premium)
{
	initCarPrice();
}

CCar::CCar(const CCar& Car)
	: m_strName(Car.getCarName()), m_strPlate(Car.getCarPlate()), m_CarType(Car.getCarType()), m_price(Car.getCarPrice())
{
}

CCar::CCar(const std::string& strName, const std::string& strPlate, CarTypes::Type CarType)
	: m_strName(strName), m_strPlate(strPlate), m_CarType(CarType)
{
	initCarPrice();
}

void CCar::initCarPrice()
{
	switch (m_CarType)
	{
	case CarTypes::Type::Premium:
		m_price = 300.0f;
		break;
	case CarTypes::Type::SUV:
		m_price = 150.0f;
		break;
	case CarTypes::Type::Small:
		m_price = 50.0f;
		break;
	default:
		break;
	}
}

void CCar::Print()
{
	std::cout << "\nCar info - Name: " << m_strName << ", Plate: " << m_strPlate << ", Price: " << m_price << std::endl;
}
