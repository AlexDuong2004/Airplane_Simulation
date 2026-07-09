//
//  TestProject.cpp
//  3150
//
//  Created by Alex Duong on 4/23/24.
//

#include "ECAirport.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlightItinerary.h"
#include "ECAirlineSimulator.h"
#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUIItem.h"
#include "ECConsoleUITextField.h"
#include "ECFlight.h"
#include "ECConsoleUIButton.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cmath>

//# Format: each row is a record for something, which can contain mutliple fields, seperated by space(s)
//# Ignore any row starting with a #
//# Three types of rows as indicated by the first field of the row
//# 1:  airport info.  Airport Code followed by the full description of the airport
//# 2: airport distance info: origination  destination distance-in-miles
//# 3: flight info: origination desination time length-of-flight cost
//#
//# airport list
//1 ORD Chicago
//1 IAH Houston
//1 SFO San Francisco
//1 EWR New York (Newwark, NJ)
//
//# airport distances
//2 ORD SFO 2000
//2 ORD EWR 1200
//2 IAH SFO 1800
//2 IAH EWR 1500
//
//# flights info
//3 EWR ORD 7.0 5 2000
//3 EWR ORD 14.0 5 2000
//3 ORD SFO 11.0 10 3000
//3 ORD SFO 16.0 10 3000
//3 EWR IAH 8.5 5 2200
//3 EWR IAH 13.0 5 2200
//3 IAH SFO 12.0 10 2800
//3 IAH SFO 18.0 10 2800
//static std::string ORD = "ORD";
//static std::string IAH = "IAH";
//static std::string SFO = "SFO";
//static std::string EWR = "EWR";

//void SetupSimulator(ECAirlineSimulator& sim) {
//    // Add airports
//    sim.AddAirport("Chicago", ORD);
//    sim.AddAirport("Houston", IAH);
//    sim.AddAirport("San Francisco", SFO);
//    sim.AddAirport("New York (Newwark, NJ)", EWR);
//    
//    // Set distances between airports
//    sim.SetDistBtwAirports(ORD, SFO, 2000);
//    sim.SetDistBtwAirports(ORD, EWR, 1200);
//    sim.SetDistBtwAirports(IAH, SFO, 1800);
//    sim.SetDistBtwAirports(IAH, EWR, 1500);
//    
//    // Add flights
//    sim.AddFlight(EWR, ORD, 7.0, 5, 2000);
//    sim.AddFlight(EWR, ORD, 14.0, 5, 2000);
//    sim.AddFlight(ORD, SFO, 11.0, 10, 3000);
//    sim.AddFlight(ORD, SFO, 16.0, 10, 3000);
//    sim.AddFlight(EWR, IAH, 8.5, 5, 2200);
//    sim.AddFlight(EWR, IAH, 13.0, 5, 2200);
//    sim.AddFlight(IAH, SFO, 12.0, 10, 2800);
//    sim.AddFlight(IAH, SFO, 18.0, 10, 2800);
//}

void SetupSimulator(ECAirlineSimulator& sim, std::vector<std::string>& airportcodes, std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') // Skip empty lines or comments
            continue;

        std::istringstream ss(line);
        int type;
        ss >> type;

        if (type == 1) {
            std::string code, desc;
            ss >> code;
            std::getline(ss >> std::ws, desc);
            sim.AddAirport(desc, code);
            airportcodes.push_back(code);
        } else if (type == 2) {
            std::string orig, dest;
            int dist;
            ss >> orig >> dest >> dist;
            sim.SetDistBtwAirports(orig, dest, dist);
        } else if (type == 3) {
            std::string orig, dest;
            double time;
            int length, cost;
            ss >> orig >> dest >> time >> length >> cost;
            sim.AddFlight(orig, dest, time, length, cost);
        }
    }

    file.close();
}

static void Test1(ECConsoleUIView &viewTest, ECAirlineSimulator& sim, std::vector<std::string>& airportcodes){
    // make the text labels
    ECConsoleUITextLabel *pl1 = new ECConsoleUITextLabel(30, 1, "Duong Airliners");
    pl1->SetHighlight(true);
    viewTest.AddUIItem(pl1);
    ECConsoleUITextLabel *pl2 = new ECConsoleUITextLabel(10, 5, "Origination");
    viewTest.AddUIItem(pl2);
    ECConsoleUITextLabel *pl3 = new ECConsoleUITextLabel(40, 5, "Destination");
    viewTest.AddUIItem(pl3);
    std::string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i)
    {
        horizBar += '-';
    }
    ECConsoleUITextLabel *pl4 = new ECConsoleUITextLabel(0, 0, horizBar);
    viewTest.AddUIItem(pl4);
    ECConsoleUITextLabel *pl5 = new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar);
    viewTest.AddUIItem(pl5);
    ECConsoleUITextLabel *flight = new ECConsoleUITextLabel(20, 14, "Flights");
    viewTest.AddUIItem(flight);
    
    // make listboxes
    ECConsoleUIListBox *source = new ECConsoleUIListBox(10, 7, 30, 9 );
    for( auto x : airportcodes){
        source->AddChoice(x);
    }
    source->Choose(0);
    viewTest.AddUIItem(source);
    
    ECConsoleUIListBox *destination = new ECConsoleUIListBox(40, 7, 60, 9 );
    for( auto x : airportcodes){
        destination->AddChoice(x);
    }
    destination->Choose(0);
    viewTest.AddUIItem(destination);
    
    
    ECConsoleUIListBox * flights = new ECConsoleUIListBox( 10, 15, 90, 17);
//    flights->AddChoice("Placeholder");
//    flights->Choose(0);
    viewTest.AddUIItem(flights);
    
    // add the button
    std::string string = "Enter your flights";
    ECConsoleUIButton *button = new ECConsoleUIButton(20, 12, 40, 12, string, source, destination, flights, &sim);
    viewTest.AddUIItem(button);
    
}




int main(int argc, char *argv[])
{
    //setup the airports
    std::vector<std::string> airportcodes;
    ECAirlineSimulator sim;
    SetupSimulator(sim, airportcodes, argv[1]);
//    std::cout << "hi " << std::endl;
//    for (auto x : airportcodes){
//        std::cout << x << std::endl;
//    }
    ECTextViewImp wndTest;

    // add a status bar
    wndTest.AddStatusRow("UI test", "For demo only", true);
    
    // Create a console UI view
    ECConsoleUIView viewUI(&wndTest);
    
    // Add a few UI items
    Test1(viewUI, sim, airportcodes);
    
    // Display it
    viewUI.Refresh();
    
    // Show the window
    try {
        wndTest.Show();
    }
    catch(std::string ex)
    {
        std::cout << "Exception: " << ex << std::endl;
    }
    return 0;
}
