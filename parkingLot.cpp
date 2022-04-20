#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class ParkingLot{

    int parkingLotId;
    int carCapacity;
    int bikeCapacity;
    // vector<Parking> parkingSlots;
    vector<Vehicle> vehiclesList;
    RateChart ratechart;
};

class RateChart{
    int perHourBike;
    int perHourCar;
    int perHourHeavy;
};

class Vehicle{
    string vehicleId;
    VehicleType type;
    vector<ParkingInfo> parkingHistory;
};

enum VehicleType{Bike,Car,Heavy};

class ParkingInfo{

    Vehicle vehicle;
    time_t startTime;
    time_t exitTime;
};

class Bill{
    ParkingLot parkingLot;
    Vehicle vehicle;
    int getTotalAmount();
};

class User{
    string firstName;
    string lastName;
    Account accountDetails;
};

class Account{

    int uniqueId;
    string password;
};

class Guard: public User{
    
    ParkingLot parkingLot;
    bool searchParkings(Vehicle v);
    void parkVehicle(Vehicle v);
    void freeParking(Vehicle v);
};

class Admin: public User{

    vector<ParkingInfo> getParkingHistory(Vehicle v);
    void addParkingLot();
    void addParking(ParkingLot);
    vector<ParkingLot> parkingLots;
};