//
//  ECConsoleUIButton.cpp
//  
//
//

#include "ECConsoleUIButton.h"
#include "ECConsoleUIItem.h"
#include "ECConsoleUIListBox.h"
#include "ECAirlineSimulator.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h"
#include <string>
#include <vector>
#include <iostream>
#include <set>

//*****************************************************************************
// Console UI button: 

// specifiy the portion of the view for this list box
ECConsoleUIButton::ECConsoleUIButton(int xUL, int yUL, int xLR, int yLR, const std::string &textButton, ECConsoleUIListBox *source, ECConsoleUIListBox *destination, ECConsoleUIListBox *flights, ECAirlineSimulator *sim)
    : ECConsoleUIItem(xUL, yUL, xLR, yLR), strButton(textButton), source(source), destination(destination), flights(flights), sim(sim) {}



// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUIButton :: GetTextAtRow(int r) const
{
    // there is only one line
    std::string str;
    int rconv = r - GetYUL();

    if( rconv <0 || /*rconv >= 1 ||*/ rconv >= GetHeight() )
    {
        return str;
    }

    // add a row of '----' right above/below
    if( rconv == 0 || rconv == GetHeight()-1 )
    {
        str += '+';
        for( int i=1 ; i<GetWidth() - 1; ++i)
        {
            str += '-';
        }
        str += '+';
    }
    else
    {
        // begin with a '|'
        //str += '|';

        // align to the center
        if( strButton.size() < GetWidth())
        {
            str += '|';
            for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
        }

        str += strButton;
        for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
            str += '|';

        // end with a '|'
        //str += '|';
    }

    // ensure the str is not too long
    str = str.substr(0, GetWidth());
    return str;
}

// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUIButton :: GetHighlightPosition(int &xLeft, int &xRight) const
{
    return -1;
}

// Handle enter key
void ECConsoleUIButton :: HdlKeyEnter()
{
    // do nohting for now
    // should get the highlights of others and call dfs
    // 3 pointers for each listbox
    // call dfs when you click enter
    // for loop after you do the dfs, put inside listbox
    // clear flights listbox when doing it
    std::vector<ECFlightItinerary> listItineraries;
    std::string src = source->StringAtIndex(source->GetChoice());
    std::string dest = destination->StringAtIndex(destination->GetChoice());
    sim->SearchForFlights(src, dest, listItineraries);
    // get the values into the flights using dump
    if (flights->SizeIndex() > 0){
        flights->DeleteIndex();
    }
    std::set<std::string> duplicate;
    for (int i = 0; i < listItineraries.size(); i++){
        auto it = duplicate.find(listItineraries[i].Dump());
        if (it == duplicate.end()){
            flights->AddChoice(listItineraries[i].Dump());
            duplicate.insert(listItineraries[i].Dump());
        }
    }
}
