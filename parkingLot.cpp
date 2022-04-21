#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class ParkingLot{

    public:
        int parkingLotId;
        int carCapacity;
        int bikeCapacity;
        bool sharedBikeParked;
    // vector<Parking> parkingSlots;
        vector<Vehicle> vehiclesList;
        RateChart ratechart;

        ParkingLot(int id,int car_capacity,int bike_capacity){
            parkingLotId = id;
            carCapacity = car_capacity;
            bikeCapacity = bike_capacity;
        }
};

class RateChart{
    public:
        int perHourBike;
        int perHourCar;
        int perHourHeavy;
};

class Vehicle{
    public:
        string vehicleId;
        VehicleType type;
        ParkingInfo currentInfo;
        vector<ParkingInfo> parkingHistory;
        bool inCarParking;
};

enum VehicleType{Bike,Car,Heavy};

class ParkingInfo{
    public:
        int parkingLotId;
        tm *startTime;
        tm *exitTime;
        int amountPaid;
};

class User{
    public:
        string firstName;
        string lastName;
        Account accountDetails;
};

class Account{
    public:
        int uniqueId;
        string password;
};

class Guard: public User{
    public:
        ParkingLot parkingLot;
        bool searchParkings(Vehicle v){
            if(v.type == Bike){
                if(parkingLot.bikeCapacity > 0) return true;
                else if(parkingLot.carCapacity > 0) return true;
                else return false;
            }

            else if(parkingLot.carCapacity == 0) return false;
        };
        void parkVehicle(Vehicle v){
            if(v.type == Bike){
                if(parkingLot.bikeCapacity > 0) parkingLot.bikeCapacity--;
                else if(parkingLot.carCapacity > 0  && parkingLot.sharedBikeParked == false){
                    parkingLot.carCapacity--;
                    parkingLot.sharedBikeParked = true;
                    v.inCarParking = true;
                }
                else {
                    parkingLot.sharedBikeParked = false;
                    v.inCarParking = true;
                }
            }
            else parkingLot.carCapacity--;
            parkingLot.vehiclesList.push_back(v);
            time_t t_time = time(0);
            tm *local_time = localtime(&t_time);
            v.currentInfo.startTime = local_time;
        };
        void freeParking(Vehicle v){
            time_t t_time = time(0);
            tm *local_time = localtime(&t_time);
            v.currentInfo.exitTime = local_time;
            int hours = v.currentInfo.exitTime->tm_hour - v.currentInfo.startTime->tm_hour + 1;
            if(v.type == Bike) v.currentInfo.amountPaid = hours*parkingLot.ratechart.perHourBike;
            else if(v.type == Car) v.currentInfo.amountPaid = hours*parkingLot.ratechart.perHourCar;
            else v.currentInfo.amountPaid = hours*parkingLot.ratechart.perHourHeavy;

            v.parkingHistory.push_back(v.currentInfo);
            if(v.type == Bike && !v.inCarParking) parkingLot.bikeCapacity++;
            else if(v.type == Bike && v.inCarParking) parkingLot.carCapacity++;
            else parkingLot.carCapacity++;
        };
};

class Admin: public User{
    public:
        vector<ParkingLot> parkingLots;
        void addParkingLot(int carCapacity,int bikeCapacity){
            ParkingLot p1(123,carCapacity,bikeCapacity);
            parkingLots.push_back(p1);
        };
        vector<ParkingInfo> getParkingHistory(string vehicle_id){
            ParkingLot p = parkingLots[parkingLots.size() - 1];
            Vehicle v;
            for(auto i: p.vehiclesList){
                if(i.vehicleId == vehicle_id) v = i;
            }
            return v.parkingHistory;
        };
};