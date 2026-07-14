//
//  ECFlight.cpp
//  
//
//

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

ECFlight :: ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn) : srcIn(srcIn), destIn(destIn), tmDepartIn(tmDepartIn), maxPassengersIn(maxPassengersIn) {}

void ECFlight :: SetMaxNumPassengers(int m){
    maxPassengersIn = m;
}

std::string ECFlight :: GetSource() const{
    return srcIn;
}

std::string ECFlight :: GetDest() const{
    return destIn;
}

double ECFlight :: GetDepartureTime() const{
    return tmDepartIn;
}

double ECFlight :: GetArrivalTime() const{
    double res = 0.0;
    std::string src = GetSource();
    std::string dest = GetDest();
    
    ECAirportInfo* instance = ECAirportInfo::Instance();
    int dist = instance->GetDistanceBtw(src, dest);
    
    if (dist > 0) {  // Check if distance is valid
        const double speed = 500.0;  // Speed in miles per hour
        res = static_cast<double>(dist) / speed;
    } else {
        std::cout << "Invalid distance between " << src << " and " << dest << std::endl;
        // Handle this case appropriately
    }
    
    double departtime = GetDepartureTime();
    res += departtime;
    return res;
}
 // dist from a to b / 500  then + depart time

