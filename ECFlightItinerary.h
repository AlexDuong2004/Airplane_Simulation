//
//  ECFlightItinerary.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlightItinerary_h
#define ECFlightItinerary_h

#include "ECFlight.h"
#include <vector>
#include <string>

class ECFlight;
class ECAirlineFinancial;

// ****************************************************************************
// Flight itineary: consisting segments of flights so to go from one airport to another airport

class ECFlightItinerary
{
public:
    ECFlightItinerary();
    virtual ~ECFlightItinerary(){}
    // access/edit segments
    // Return the number of segments of the itineary
    int GetNumSegments() const;
    
    // Return a segment
    ECFlight *GetSegment(int segIndex) const;
    
    // Get flight time: from departure to arrival
    double GetFlightTime() const;
    
    // Get segment time: add the time of all segments
    double GetTimeAllSegments() const;
    
    // Get departure time
    double GetDepartTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Price 
    double GetPrice() const;
    
    std::string Dump() const;
    
    void addSegment(ECFlight* flight);
    
    void removeSegment();
    
    
private:
    // your code
    std::vector<ECFlight* > list_segments;
    double price;
//    double departtime;
//    double arrivaltime;
//    double AllSegtime;
//    double Flighttime;
    
};

#endif /* ECFlightItinerary_h */
