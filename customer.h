#ifndef NORMALUSER_H
#define NORMALUSER_H

#include <iostream>

#include "User.h"
#include "DataBase.h"

class Customer : public User
{
public:
    Customer(const std::string &username, const std::string &password, const std::string &phoneNumber)
        : User(username, password, phoneNumber) {}

    void menu(DataBase &dataBase, User &user) override
    {
        int choice;
        do
        {
            std::cout << "1. View Flights" << std::endl;
            std::cout << "2. Search Flight" << std::endl;
            std::cout << "3. Book Flight" << std::endl;
            std::cout << "4. Cancel Flight" << std::endl;
            std::cout << "5. View Booked Flights" << std::endl;
            std::cout << "6. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                viewFlights(dataBase, user);
                break;
            case 2:
                searchFlight(dataBase, user);
                break;
            case 3:
                bookFlight(dataBase, user);
                break;
            case 4:
                cancelFlight(dataBase, user);
                break;
            case 5:
                viewBookedFlights(dataBase, user);
                break;
            case 6:
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 6);
    }
};

#endif // NORMALUSER_H