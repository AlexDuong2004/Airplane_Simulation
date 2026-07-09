//
//  ECFlightItinerary.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

ECFlightItinerary::ECFlightItinerary() {}

int ECFlightItinerary :: GetNumSegments() const{
    return list_segments.size();
}

ECFlight* ECFlightItinerary :: GetSegment(int segIndex) const{
    if (segIndex < 0 || segIndex >= GetNumSegments()){
        throw std::out_of_range("segment out of range");
    }
    if (segIndex < list_segments.size()) {
        return list_segments[segIndex];
    }
    return nullptr;
}
//GetTimeAllSegments are flipped
//GetFlightTime
double ECFlightItinerary :: GetTimeAllSegments() const{
    // get the arrival time of the last flight
    // get the depart of the first flight
    double departtime = GetDepartTime();
    double arrivaltime = GetArrivalTime();
    return arrivaltime - departtime;
}

double ECFlightItinerary :: GetFlightTime() const{
    // go through each segment do arrival - depart
    double res = 0.0;
    for(int i = 0; i < GetNumSegments(); i++){
        res += GetSegment(i)->GetArrivalTime() - GetSegment(i)->GetDepartureTime();
    }
    return res;
}

double ECFlightItinerary :: GetDepartTime() const{
   auto first_flight = GetSegment(0);
    return first_flight->GetDepartureTime();
}

double ECFlightItinerary :: GetArrivalTime() const{
    auto last_flight = GetSegment(GetNumSegments() - 1);
    return last_flight->GetArrivalTime();
    
}

double ECFlightItinerary :: GetPrice() const{
    // 120 * flight time
    return 120 * GetFlightTime();
}

std::string ECFlightItinerary :: Dump() const
{

    std::string finalString = list_segments[0]->GetSource();
    for (int i = 0; i < GetNumSegments(); i++){
        finalString += " -> " + list_segments[i]->GetDest();
    }
    double deptime = GetDepartTime();
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << deptime;
    std::string deptimefinal = ss.str();
    finalString += " Departure time: " + deptimefinal;
    double arrtime = GetFlightTime();
    std::stringstream sss;
    sss << std::fixed << std::setprecision(1) << arrtime;
    std::string arrtimefinal = sss.str();
    finalString += " Flight time: " + arrtimefinal;
    double price = GetPrice();
    std::stringstream ssss;
    ssss << std::fixed << std::setprecision(1) << price;
    std::string pricefinal = ssss.str();
    finalString += " Price: " + pricefinal;
    return finalString;
}

void ECFlightItinerary :: addSegment(ECFlight* flight){
    list_segments.push_back(flight);
}

void ECFlightItinerary :: removeSegment() {
       if (!list_segments.empty()) {
           list_segments.pop_back();
       }
   }

