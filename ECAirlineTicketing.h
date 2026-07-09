#ifndef ECAirlineTicketing_h
#define ECAirlineTicketing_h

#include "ECAirport.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h" // Include for full definition
#include <vector>
#include <string>

// Forward declaration of ECAirlineSimulator if needed
class ECAirlineSimulator;

class ECAirlineTicketing {
public:
    virtual ~ECAirlineTicketing();

    void addFlight(const std::string& srcAirport, const std::string& destAirport, double tmDepart, int maxPassengers, double costOperate);

    void SearchForFlights(const std::string& src, const std::string& dest, std::vector<ECFlightItinerary>& listItineraries);

//    void DFS(const std::string& src, const std::string& dest, std::vector<ECFlightItinerary>& listItineraries, std::vector<std::string>& visited, double currenttime);
    
    void DFS(const std::string& src, const std::string& dest, std::vector<ECFlightItinerary>& listItineraries, std::vector<std::string>& visited, double currenttime, ECFlightItinerary& currentItinerary);

    
private:
    std::vector<ECFlight*> listFlights;
    //std::vector<ECFlightItinerary*> listItineraries;
};

#endif /* ECAirlineTicketing_h */

