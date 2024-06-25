#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "flight.h"
#include "database.h"

class User
{
protected:
    std::string username;
    std::string password;
    std::string phoneNumber;

public:
    User(const std::string &username, const std::string &password, const std::string &phoneNumber)
        : username(username), password(password), phoneNumber(phoneNumber) {}

    virtual ~User() = default; // Ensure proper cleanup of derived classes

    std::string getUsername() const
    {
        return username;
    }

    std::string getPassword() const
    {
        return password;
    }

    std::string getPhoneNumber() const
    {
        return phoneNumber;
    }

    void viewFlights(DataBase &dataBase, User &user) {
    };
    void searchFlight(DataBase &dataBase, User &user) {};
    std::string toString() {};
    virtual void menu(DataBase &dataBase, User &user) {};
};

#endif // USER_H