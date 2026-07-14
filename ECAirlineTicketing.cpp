//
//  ECAirlineTicketing.cpp
//  
//
//

#include "ECAirlineTicketing.h"
#include "ECAirport.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h"
#include "ECAirlineSimulator.h"
#include <vector>
#include <string>
#include <algorithm>

ECAirlineTicketing::~ECAirlineTicketing() {
    for (auto flight : listFlights) {
        delete flight;
    }
}


void ECAirlineTicketing :: addFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate){
    listFlights.push_back( new ECFlight(srcAirport, destAirport, tmDepart, maxPassengers));
}


void ECAirlineTicketing :: SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries){
    std::vector<std::string> visited;
    ECFlightItinerary currentItinerary;
    double time = 0;
    DFS(src, dest, listItineraries, visited, time, currentItinerary);
}



void ECAirlineTicketing::DFS(const std::string& src, const std::string& dest, std::vector<ECFlightItinerary>& listItineraries, std::vector<std::string>& visited, double currenttime, ECFlightItinerary& currentItinerary) {
    ECAirportInfo* instance = ECAirportInfo::Instance();
    visited.push_back(src);

    // Check if source airport exists in the map
    const auto& map2 = instance->GetMap2();
    if (map2.find(src) == map2.end()) {
        visited.pop_back();  // Backtrack
        return;
    }

    const std::map<std::string, int>& adj = map2.at(src);
    
    for (const auto& adjacent : adj) {
        const std::string& nextAirport = adjacent.first;

        // Check if next airport has been visited
        if (std::find(visited.begin(), visited.end(), nextAirport) != visited.end()) {
            continue;
        }

        // Check if there's a flight from src to nextAirport departing after the current time
        for (const auto& flight : listFlights) {
            if (flight->GetSource() == src && flight->GetDest() == nextAirport && flight->GetDepartureTime() >= currenttime) {
                
                // Update current time to the arrival time of the flight
                double newTime = flight->GetArrivalTime();
                
                // Add the current flight to the itinerary
                currentItinerary.addSegment(flight);
                
                if (nextAirport == dest) {
                    // We found a valid itinerary, add it to the listItineraries
                    listItineraries.push_back(currentItinerary);
                } else {
                    // Recursive call with updated current time and current itinerary
                    DFS(nextAirport, dest, listItineraries, visited, newTime, currentItinerary);
                }
                
                // Remove the flight from the current itinerary for backtracking
                currentItinerary.removeSegment();
            }
        }
    }

    visited.pop_back();  // Backtrack
}






