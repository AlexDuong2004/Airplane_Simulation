//
//  ECAirlineFinancial.h
//
//
//

#ifndef ECAirlineFinancial_h
#define ECAirlineFinancial_h

#include <vector>

class ECFlightItinerary;
class ECAirlineOperation;
class ECPassenger;
class ECFlight;


// ****************************************************************************
// Airline finanical: budgetting, pricing and money bookkeeping
class ECAirlineSimulator;

class ECAirlineFinancial
{
public:
    ECAirlineFinancial(){}
    ECAirlineFinancial(ECAirlineOperation *pOperateIn);
    virtual ~ECAirlineFinancial();
    
    // Register a passenger
    // this is useful for things like flight updates
    // for the moment, you just need to maintain a list of passengers
    void RegisterPassenger(ECPassenger *pPassenger);
    
    // Get the number of registered passingers
    int GetNumPassengers() const { return listPassengers.size(); }
    
    // Get the passenger that is added in the k-th position
    ECPassenger *GetPassenger(int k) const { return listPassengers[k]; }
    
    // pricing the itinerary
    double Quote(const ECFlightItinerary &itin) const;
    
    // get revenue
    double GetRevenue() const { return balance; }

    // Balance query = revnue - cost
    double GetBalance() const;
    
    // Paid by $amt
    void Paid(double amt);
    
    // Charged by $amt
    void Charged(double amt);
    
    // the following functions are not required...
    // Pricing settings
    // Use flight distance
    //void PricingByFlightTime();

    // Use number of segments
    //void PricingBySegments();
    
    // Analysis
    // Estimate revenue genearted by a flight
    //double EstimateRevenueByFlight(const ECFlight *pFlight) const;
    
    // Dump out
    void Dump() const;
    
private:
    // Operating
    ECAirlineOperation *pOperate;
    
    // balance: how much money the airline has?
    double balance;
    
    // list of registered passengers
    std::vector<ECPassenger *> listPassengers;
};

#endif /* ECAirlineFinancial_h */
