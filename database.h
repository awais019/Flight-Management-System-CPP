#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "user.h"
#include "flight.h"
#include "customer.h"

std::vector<std::string> split(const std::string &s, const std::string &delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);
    while (end != std::string::npos)
    {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }
    if (start < s.length())
    {
        tokens.push_back(s.substr(start));
    }
    return tokens;
}

namespace fs = std::filesystem;

class DataBase
{
private:
    std::vector<User *> users;
    std::vector<Flight *> flights;
    std::vector<Flight *> bookedFlights;

    fs::path usersFile = fs::path("./data/users.txt");
    fs::path flightsFile = fs::path("data/flights.txt");
    fs::path bookedFlightsFile = fs::path("./data/bookedFlights.txt");
    fs::path folder = fs::path("./data");

public:
    DataBase()
    {
        loadUsers();
        loadFlights();
        loadBookedFlights();
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
        saveUsers();
    }
    void addFlight(Flight *flight)
    {
        flights.push_back(flight);
        saveFlights();
    }
    void addBookFlight(Flight *flight)
    {
        bookedFlights.push_back(flight);
        saveBookedFlights();
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
    void loadBookedFlights()
    {
        if (fs::exists(bookedFlightsFile))
        {
            std::ifstream file(bookedFlightsFile);
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
    void deleteBookedFlight(int index)
    {
        if (index >= 0 && index < bookedFlights.size())
        {
            bookedFlights.erase(bookedFlights.begin() + index);
        }
        saveBookedFlights();
    }
    int getBookedFlight(string flightName)
    {
        for (int i = 0; i < bookedFlights.size(); i++)
        {
            if (bookedFlights.at(i)->getFlightName() == flightName)
            {
                return i;
            }
        }
        return -1;
    }
    Flight *getBookedFlight(int i)
    {
        return bookedFlights.at(i);
    }

    void getBookedFlight()
    {
        string text1 = "";
        try
        {
            ifstream br1(bookedFlightsFile);
            string s1;
            while (getline(br1, s1))
            {
                text1 += s1;
            }
            br1.close();
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
        }
        if (!text1.empty())
        {
            vector<string> a1 = split(text1, "<NewFlight/>");
            for (const auto &s : a1)
            {
                Flight flight = parseFlight(s);
                bookedFlights.push_back(&flight);
            }
        }
    }
    void getFlight()
    {
        string text1 = "";
        try
        {
            ifstream br1(flightsFile);
            string s1;
            while (getline(br1, s1))
            {
                text1 += s1;
            }
            br1.close();
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
        }
        if (!text1.empty())
        {
            vector<string> a1 = split(text1, "<NewFlight/>");
            for (const auto &s : a1)
            {
                Flight flight = parseFlight(s);
                flights.push_back(&flight);
            }
        }
    }

    Flight parseFlight(string s)
    {
        vector<string> a = split(s, "<N/>");
        Flight flight;
        flight.setFlightName(a[0]);
        flight.setDate(a[1]);
        flight.setDepartureTime(a[2]);
        flight.setDepartureLocation(a[3]);
        flight.setReachingTime(a[4]);
        flight.setReachingLocation(a[5]);
        flight.setFlightPrice(stod(a[6]));
        return flight;
    }
    vector<Flight *> getAllFlights()
    {
        return flights;
    }
    vector<Flight *> getAllBookedFlights()
    {
        return bookedFlights;
    }

    void deleteFlight(int i)
    {
        if (i >= 0 && i < flights.size())
        {
            flights.erase(flights.begin() + i);
        }
        saveFlights();
    }
    int getFlight(string flightName)
    {
        for (int i = 0; i < flights.size(); i++)
        {

            if (flights.at(i)->getFlightName() == flightName)

            {
                return i;
            }
        }
        return -1;
    }

    Flight *getFlight(int i)
    {
        return flights.at(i);
    }

    bool userExists(string name)
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users.at(i)->getUsername() == name)
            {
                return true;
            }
        }
        return false;
    }

    int login(string username, string password)
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users.at(i)->getUsername() == username && users.at(i)->getPassword() == password)
            {
                return i;
            }
        }
        return -1;
    }

    User *getUser(int n)
    {
        return users.at(n);
    }

    void getUsers()
    {
        std::string text1 = "";
        try
        {
            std::ifstream br1(usersFile);
            std::string s1;
            while (std::getline(br1, s1))
            {
                text1 += s1;
            }
            br1.close();
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
        if (!text1.empty())
        {
            std::vector<std::string> a1 = split(text1, "<NewUser/>");
            for (std::string s : a1)
            {
                std::vector<std::string> a2 = split(s, "<N/>");
                if (a2[3] == "Admin")
                {
                    User *user = new Admin(a2[0], a2[1], a2[2]);
                    users.push_back(user);
                }
                else
                {
                    User *user = new Customer(a2[0], a2[1], a2[2]);
                    users.push_back(user);
                }
            }
        }
    }
};

#endif // DATABASE_H