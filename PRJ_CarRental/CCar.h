#pragma once
#include <iostream>
#include <string>

namespace CarTypes {
    enum class Type {
        Premium,
        SUV,
        Small
    };
}

class CCar
{
public:
    CCar();
    CCar(const CCar& Car);
    CCar(const std::string& strName, const std::string& strPlate, CarTypes::Type CarType);
    
    inline std::string getCarName() const { return m_strName; }
    inline std::string getCarPlate() const { return m_strPlate; }
    inline CarTypes::Type getCarType() const { return m_CarType; }
    inline float getCarPrice() const { return m_price; }
    inline void setRentedDays(int rentedDays) { m_rentedDays = rentedDays; }
    inline int getRentedDays() { return m_rentedDays; }
    void initCarPrice();

    void Print();

private:
    std::string m_strName;
	std::string m_strPlate;
	CarTypes::Type m_CarType;
	float m_price;
    int m_rentedDays = 1;
};
