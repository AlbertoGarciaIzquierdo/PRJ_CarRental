// PRJ_CarRental.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CHttpServer.h"
#include "CDatabase.h"
#include "CCustomer.h"
#include "CCar.h"

int getIndexFromUser()
{
    int index;
    std::cout << "Select index: ";
    std::cin >> index;
    return index;
}

int main()
{
    std::string strCarName = "";
    CDatabase* pDatabase = new CDatabase();

    CHttpServer srvCarRenting(pDatabase);
    srvCarRenting.StartServer();
    httplib::Client* pClient = new httplib::Client("localhost", 8080);

    pDatabase->PrintCustomers();

    CCustomer* selCustomer(pDatabase->getCustomer(getIndexFromUser()));


    int nAction = 1;
    while (nAction == 1 || nAction == 2 || nAction == 3)
    {
        std::cout << "\n\n---------------------------------------------------------------------------------------" << std::endl;
        selCustomer->Print();
        std::cout << "\n1 - Rent || 2 - Return || 3 - Change User || Default - Exit" << std::endl;
        nAction = getIndexFromUser();

        if (nAction == 1)
        {
            pDatabase->PrintCars();

            CCar* selCar = pDatabase->getCar(getIndexFromUser());
            int days = 1;
            std::cout << "For how many days would you rent it: ";
            std::cin >> days;

            if (selCar != nullptr)
            {
                selCar->Print();

                httplib::Params params = {
                    {"plate-id", selCar->getCarPlate()},
                    {"days-rented", std::to_string(days)},
                    {"user-name", selCustomer->getCustomerName()}
                };

                httplib::Result res;
                res = pClient->Get("/CarRenting/Rent", params, httplib::Headers());

                std::cout << res->body << std::endl;
            }
            else
            {
                std::cout << "Car not found in DB" << std::endl;
            }
        }

        if (nAction == 2)
        {
            selCustomer->PrintCars();

            CCar* selCar = selCustomer->getCar(getIndexFromUser());
            int days = 1;
            std::cout << "For how many days have you rent it: ";
            std::cin >> days;

            if (selCar != nullptr)
            {
                selCar->Print();

                httplib::Params params = {
                    {"plate-id", selCar->getCarPlate()},
                    {"days-rented", std::to_string(days)},
                    {"user-name", selCustomer->getCustomerName()}
                };

                httplib::Result res;
                res = pClient->Get("/CarRenting/Return", params, httplib::Headers());

                std::cout << res->body << std::endl;
            }
            else
            {
                std::cout << "Car not found in DB" << std::endl;
            }
        }

        if (nAction == 3)
        {
            pDatabase->PrintCustomers();

            selCustomer = pDatabase->getCustomer(getIndexFromUser());
            selCustomer->Print();
        }
    }

    delete(pDatabase);
    delete(pClient);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
