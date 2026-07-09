//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ECAirlineSimulator::ECAirlineSimulator() {
    pAirlineTicket = new ECAirlineTicketing();
//    pAirlineFin = new ECAirlineFinancial();
//    for(int i = 0; i < 4; i++){
//        pref[i] = 0;
//    }
}


void ECAirlineSimulator::AddAirport(const std::string &name, const std::string &code) {
    ECAirportInfo *instance = ECAirportInfo::Instance();
    if (!pAirlineTicket) {
            std::cerr << "ECAirlineTicketing is not initialized!" << std::endl;
            return;
        }
    instance->CreateAirport(name, code);
}


//void ECAirlineSimulator::SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist) {
//    if (!pAirlineTicket) {
//            std::cerr << "ECAirlineTicketing is not initialized!" << std::endl;
//            return;
//        }
//    ECAirportInfo *instance = ECAirportInfo::Instance();
//    instance->SetDistanceBtw(srcAirport, destAirport, dist);
//}

void ECAirlineSimulator::SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist) {
    ECAirportInfo *instance = ECAirportInfo::Instance();
    instance->SetDistanceBtw(srcAirport, destAirport, dist);
}


void ECAirlineSimulator::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate) {
    ECAirportInfo *instance = ECAirportInfo::Instance();
        
        // Check if both airports exist
        if (instance->GetAirport(srcAirport).GetName() == "" || instance->GetAirport(destAirport).GetName() == "") {
            std::cout << "One or both airports do not exist!" << std::endl;
            return;
        }
    pAirlineTicket->addFlight(srcAirport, destAirport, tmDepart, maxPassengers, costOperate);
}

void ECAirlineSimulator::DoneFlightAdding() {
    if (!pAirlineTicket) {
            std::cerr << "ECAirlineTicketing is not initialized!" << std::endl;
            return;
        }
    // Implementation for DoneFlightAdding
    int x = 0;
}

void ECAirlineSimulator::SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const {
    ECAirportInfo* instance = ECAirportInfo::Instance();
    if (instance->GetAirport(src).GetName() == "" || instance->GetAirport(dest).GetName() == "") {
            std::cout << "One or both airports do not exist!" << std::endl;
            return;
        }
    // Implementation for SearchForFlights
    // For example: Perform flight search and populate listItineraries
    listItineraries.clear();
    pAirlineTicket->SearchForFlights(src, dest, listItineraries);
    
    
    }
    
    // sort all at once create 1 function for sorting that recursively calls
    

//std::sort(listItineraries.begin(), listItineraries.end(), [] (const ECFlightItinerary &first, const ECFlightItinerary &second) { return first.GetPrice() < second.GetPrice(); }
//void ECAirlineSimulator :: Book(){
//    
//}
//
//void ECAirlineSimulator :: ClearPreference(){
//    for(int i = 0; i < 4; i++){
//        pref[i] = 0;
//    }
//}
//
//void ECAirlineSimulator :: PreferLowPrice(int n){
//    // indicator is 1
//    pref[n] = 1;
//    
//}
//
//void ECAirlineSimulator :: PreferShortTime(int n){
//    // indicator is 2
//    pref[n] = 2;
//    
//}
//
//void ECAirlineSimulator :: PreferSmallestSegments(int n){
//    // indicator is 3
//    pref[n] = 3;
//}
//
//void ECAirlineSimulator :: PreferEarlyArrival(int n){
//    // indicator is 4
//    pref[n] = 4;
//    
//}

