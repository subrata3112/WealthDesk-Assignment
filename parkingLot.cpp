#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class ParkingLot{

    int parkingLotId;
    Location location;
    vector<Parking> parkingSlots;
};

class Location{
    string City;
    string State;
    int Pincode;
};

class Parking{

    int parkingId;
    ParkingStatus status;
    vector<Vehicle> ParkedVehicles;
};

enum ParkingStatus{Alloted,Free,UnderMantainance,BikeOnly};

class Vehicle{
    string vehicleId;
    VehicleType type;
    vector<ParkingInfo> parkingHistory;
};

enum VehicleType{Bike,Car};

class ParkingInfo{

    Vehicle vehicle;
    time_t startTime;
    time_t exitTime;
};