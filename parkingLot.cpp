#include<bits/stdc++.h>
#include<ctime>
using namespace std;

enum VehicleType{Bike,Car,Heavy};

class ParkingInfo{
    public:
        int parkingLotId;
        tm *startTime;
        tm *exitTime;
        int amountPaid;
};

class Vehicle{
    public:
        string vehicleId;
        VehicleType type;
        ParkingInfo currentInfo;
        vector<ParkingInfo> parkingHistory;
        bool inCarParking;

        // Vehicle();

        // Vehicle(string id,VehicleType vtype){
        //     type = vtype;
        //     vehicleId = id;
        //     inCarParking = false;
        // }
};

class RateChart{
    public:
        int perHourBike;
        int perHourCar;
        int perHourHeavy;

        // RateChart();

        // RateChart(int rateBike,int rateCar,int rateHeavy){
        //     perHourBike = rateBike;
        //     perHourCar = rateCar;
        //     perHourHeavy = rateHeavy;
        // }
};

class ParkingLot{

    public:
        int parkingLotId;
        int carCapacity;
        int bikeCapacity;
        bool sharedBikeParked;
    // vector<Parking> parkingSlots;
        
        RateChart ratechart;

        ParkingLot(int id,int car_capacity,int bike_capacity,RateChart rc){
            parkingLotId = id;
            carCapacity = car_capacity;
            bikeCapacity = bike_capacity;
            ratechart = rc;
            sharedBikeParked = false;
        }
};

class Account{
    public:
        int uniqueId;
        string password;
};

class User{
    public:
        string firstName;
        string lastName;
        Account accountDetails;
};

class Admin{
    public:
        vector<ParkingLot> parkingLots;
        vector<Vehicle> vehicleList;
    
        bool searchParkings(Vehicle v){
            ParkingLot parkingLot = parkingLots[parkingLots.size() - 1];
            if(v.type == Bike){
                if(parkingLot.bikeCapacity > 0) return true;
                else if(parkingLot.carCapacity > 0) return true;
                else return false;
            }

            else if(parkingLot.carCapacity == 0) return false;
            else return true;
        };
        void parkVehicle(Vehicle v){
            ParkingLot parkingLot = parkingLots[parkingLots.size() - 1];
            cout<<"Activated Parking: "<<parkingLot.parkingLotId<<endl;;
            if(!searchParkings(v)){
                cout<<"No Parking slots empty!"<<endl;
                return;
            }
            else cout<<"\nVehicle Parked!"<<endl;
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
            vehicleList.push_back(v);
            time_t t_time = time(0);
            tm *local_time = localtime(&t_time);
            v.currentInfo.startTime = local_time;
            v.currentInfo.parkingLotId = parkingLot.parkingLotId;
        };
        void freeParking(string vehicle_id){
            ParkingLot parkingLot = parkingLots[parkingLots.size() - 1];
            Vehicle v;
            for(auto i: vehicleList){
                if(i.vehicleId == vehicle_id) v = i;
            }
            time_t t_time = time(0);
            tm *local_time = localtime(&t_time);
            v.currentInfo.exitTime = local_time;
            int hours = v.currentInfo.exitTime->tm_hour - v.currentInfo.startTime->tm_hour + 1;
            if(v.type == Bike) v.currentInfo.amountPaid = hours*parkingLot.ratechart.perHourBike;
            else if(v.type == Car) v.currentInfo.amountPaid = hours*parkingLot.ratechart.perHourCar;
            else v.currentInfo.amountPaid = hours*parkingLot.ratechart.perHourHeavy;
            cout<<"Your amount to be paid is "<<v.currentInfo.amountPaid<<endl;

            v.parkingHistory.push_back(v.currentInfo);
            if(v.type == Bike && !v.inCarParking) parkingLot.bikeCapacity++;
            else if(v.type == Bike && v.inCarParking) parkingLot.carCapacity++;
            else parkingLot.carCapacity++;
        };

        void addParkingLot(int carCapacity,int bikeCapacity,RateChart rc){
            int id = rand();
            ParkingLot p1(id,carCapacity,bikeCapacity,rc);
            parkingLots.push_back(p1);
            cout<<"\nParking Lot created with id "<<id<<endl;
        };

        vector<ParkingInfo> getParkingHistory(string vehicle_id){
            
            Vehicle v;
            for(auto i: vehicleList){
                if(i.vehicleId == vehicle_id) v = i;
            }
            for(auto i: v.parkingHistory){
                    cout<<"Parking Lot ID -> "<<i.parkingLotId<<endl;
                    cout<<"Parking Start -> "<<i.startTime<<endl;
                    cout<<"Parking Ends -> "<<i.exitTime<<endl;
                    cout<<"Total Amount -> "<<i.amountPaid<<"\n\n\n";
            }
            return v.parkingHistory;
        };
};

int main(){
    int x;
    Admin a;
    do{
        
        cout<<"\n...Parking Lot Menu...\n"<<endl;
        cout<<"1. Add a new Parking Lot"<<endl;
        cout<<"2. Park a vehicle"<<endl;
        cout<<"3. Remove a vehicle"<<endl;
        cout<<"4. Get parking history"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Chose the action: ";
        cin>>x;

        switch (x)
        {
        case 1:
            {    int carCap,bikeCap,bikeRate,carRate,heavyRate;
                cout<<"Enter car capacity for this Parking: ";
                cin>>carCap;
                cout<<"Enter bike capacity for this Parking: ";
                cin>>bikeCap;
                
                cout<<"Enter rate for bike per hour: ";
                cin>>bikeRate;
                cout<<"Enter rate for car per hour: ";
                cin>>carRate;
                cout<<"Enter rate for heavy vehicles per hour: ";
                cin>>heavyRate;
                RateChart rc;
                rc.perHourBike = bikeRate;
                rc.perHourCar =  carRate;
                rc.perHourHeavy = heavyRate;
                a.addParkingLot(carCap,bikeCap,rc);
            break;}

        case 2:
            {    string VehicleNum;
                VehicleType vtype;
                int t;
                cout<<"Enter vehicle number (Avoid spaces): ";
                cin>>VehicleNum;
                cout<<"Chose the type of the vehicle"<<endl;
                cout<<"1.Bike  2.Car  3.Heavy"<<endl;
                cout<<"Enter number: ";
                cin>>t;
                if(t==1) vtype = Bike;
                else if(t==2) vtype = Car;
                else if(t==3) vtype = Heavy;
                Vehicle v;
                v.vehicleId = VehicleNum;
                v.inCarParking = false;
                v.type = vtype;
                a.parkVehicle(v);
            break;}

        case 3:
            {    string VehicleNum;
                cout<<"Enter vehicle number (Avoid spaces): ";
                cin>>VehicleNum;
                a.freeParking(VehicleNum);
            break;}

        case 4:
            {    string VehicleNum;
                cout<<"Enter vehicle number (Avoid spaces): ";
                cin>>VehicleNum;
                vector<ParkingInfo> history = a.getParkingHistory(VehicleNum);
                for(auto i: history){
                    cout<<"Parking Lot ID -> "<<i.parkingLotId<<endl;
                    cout<<"Parking Start -> "<<i.startTime<<endl;
                    cout<<"Parking Ends -> "<<i.exitTime<<endl;
                    cout<<"Total Amount -> "<<i.amountPaid<<"\n\n\n";
                }
            break;}
        case 5:
            {break;}
        default:
                cout<<"Invalid Input! Please try again."<<endl;;
            break;
        }

    }while(x != 5);
}