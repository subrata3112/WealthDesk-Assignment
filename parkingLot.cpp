#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class ParkingLot{

    int parkingLotId;
    Location location;
    int carCapacity;
    int bikeCapacity;
    vector<Parking> parkingSlots;
    RateChart ratechart;
};

class Location{
    string City;
    string State;
    int Pincode;
};

class Parking{
    int parkingId;
    ParkingStatus status;
    vector<Vehicle> parkedVehicles;
};

enum ParkingStatus{Alloted,Free,UnderMantainance,BikeOnly};

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
    vector<Parking> searchParkings(Vehicle);
    void parkVehicle(Parking,Vehicle);
    void freeParking(Parking);
};

class Admin: public User{

    vector<ParkingInfo> getParkingHistory(Vehicle v);
    void addParkingLot();
    void addParking(ParkingLot);
};