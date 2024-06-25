#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "user.h"
#include "flight.h"

namespace fs = std::filesystem;

class DataBase
{
private:
    std::vector<User *> users;
    std::vector<Flight *> flights;
    std::vector<Flight *> bookedFlights;

    fs::path usersFile = fs::path("C:/Users/Lenovo/Desktop/Flight Management System/src/Data/Users");
    fs::path flightsFile = fs::path("C:/Users/Lenovo/Desktop/Flight Management System/src/Data/Flights");
    fs::path bookedFlightsFile = fs::path("C:/Users/Lenovo/Desktop/Flight Management System/src/Data/Booked Flights");
    fs::path folder = fs::path("C:/Users/Lenovo/Desktop/Flight Management System/src/Data");

public:
    DataBase()
    {
        loadUsers();
        loadFlights();
    }
    ~DataBase()
    {
        for (auto user : users)
        {
            delete user;
        }
        for (auto flight : flights)
        {
            delete flight;
        }
        for (auto flight : bookedFlights)
        {
            delete flight;
        }
    }

    void addUser(User *user)
    {
        users.push_back(user);
    }
    void addFlight(Flight *flight)
    {
        flights.push_back(flight);
    }
    void bookFlight(Flight *flight)
    {
        bookedFlights.push_back(flight);
    }
    void loadUsers()
    {
        if (fs::exists(usersFile))
        {
            std::ifstream file(usersFile);
            std::string username;
            std::string password;
            std::string phoneNumber;
            while (file >> username >> password >> phoneNumber)
            {
                users.push_back(new User(username, password, phoneNumber));
            }
            file.close();
        }
    }
    void loadFlights()
    {
        if (fs::exists(flightsFile))
        {
            std::ifstream file(flightsFile);
            std::string flightName;
            std::string date;
            std::string departureTime;
            std::string departureLocation;
            std::string reachingTime;
            std::string reachingLocation;
            double flightPrice;
            while (file >> flightName >> date >> departureTime >> departureLocation >> reachingTime >> reachingLocation >> flightPrice)
            {
                flights.push_back(new Flight(flightName, date, departureTime, departureLocation, reachingTime, reachingLocation, flightPrice));
            }
            file.close();
        }
    }
    void saveUsers()
    {
        if (!fs::exists(folder))
        {
            fs::create_directory(folder);
        }
        std::ofstream file(usersFile);
        for (const auto &user : users)
        {
            file << user->getUsername() << " " << user->getPassword() << " " << user->getPhoneNumber() << std::endl;
        }
        file.close();
    }
    void saveFlights()
    {
        if (!fs::exists(folder))
        {
            fs::create_directory(folder);
        }
        std::ofstream file(flightsFile);
        for (const auto &flight : flights)
        {
            file << flight->getFlightName() << " " << flight->getDate() << " " << flight->getDepartureTime() << " " << flight->getDepartureLocation() << " " << flight->getReachingTime() << " " << flight->getReachingLocation() << " " << flight->getFlightPrice() << std::endl;
        }
        file.close();
    }
    void saveBookedFlights()
    {
        if (!fs::exists(folder))
        {
            fs::create_directory(folder);
        }
        std::ofstream file(bookedFlightsFile);
        for (const auto &flight : bookedFlights)
        {
            file << flight->getFlightName() << " " << flight->getDate() << " " << flight->getDepartureTime() << " " << flight->getDepartureLocation() << " " << flight->getReachingTime() << " " << flight->getReachingLocation() << " " << flight->getFlightPrice() << std::endl;
        }
        file.close();
    }
};

#endif // DATABASE_H