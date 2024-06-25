#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
using namespace std;

class Flight
{
private:
    string flightName;
    string date;
    string departureTime;
    string departureLocation;
    string reachingTime;
    string reachingLocation;
    double flightPrice;

public:
    Flight(const string &flightName, const string &date, const string &departureTime,
           const string &departureLocation, const string &reachingTime, const string &reachingLocation,
           double flightPrice);

    string getFlightName()
    {
        return flightName;
    }

    void setFlightName(string flightName)
    {
        this->flightName = flightName;
    }

    string getDate()
    {
        return date;
    }

    void setDate(string date)
    {
        this->date = date;
    }

    string getDepartureTime()
    {
        return departureTime;
    }

    void setDepartureTime(string departureTime)
    {
        this->departureTime = departureTime;
    }

    string getDepartureLocation()
    {
        return departureLocation;
    }

    void setDepartureLocation(string departureLocation)
    {
        this->departureLocation = departureLocation;
    }

    string getReachingTime()
    {
        return reachingTime;
    }

    void setReachingTime(string reachingTime)
    {
        this->reachingTime = reachingTime;
    }

    string getReachingLocation()
    {
        return reachingLocation;
    }

    void setReachingLocation(string reachingLocation)
    {
        this->reachingLocation = reachingLocation;
    }

    double getFlightPrice()
    {
        return flightPrice;
    }

    void setFlightPrice(double flightPrice)
    {
        this->flightPrice = flightPrice;
    }

    string tostring()
    {
        string text = "Flight Name: " + flightName + "\n" +
                      "Date: " + date + "\n" +
                      "Departure Time: " + departureTime + "\n" +
                      "Departure Location: " + departureLocation + "\n" +
                      "Reaching Time: " + reachingTime + "\n" +
                      "Reaching Location " + reachingLocation + "\n" +
                      "Price: " + to_string(flightPrice);
        return text;
    }

    string tostring2()
    {
        string text = flightName + "<N/>" + date + "<N/>" + departureTime + "<N/>" + departureLocation + "<N/>" + reachingTime +
                      "<N/>" + reachingLocation + "<N/>" + to_string(flightPrice);
        return text;
    }
};

#endif // FLIGHT_H