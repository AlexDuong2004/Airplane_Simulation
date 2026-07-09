    //
    //  ECConsoleUIListBox.cpp
    //
    //
    //  Created by Yufeng Wu on 5/23/23.
    //

    #include "ECConsoleUIListBox.h"
    #include "ECConsoleUIItem.h"
    #include <string>
    #include <vector>
#include <iostream>

    ECConsoleUIListBox :: ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR) : ECConsoleUIItem(xUL, yUL, xLR, yLR), indexChoice(0), index(), VisibleRows(yLR - yUL + 1), firstVisible(0) {}
    void ECConsoleUIListBox :: AddChoice(const std::string &text){
        // puts the choice into the vector
        index.push_back(text);
    }

    void ECConsoleUIListBox :: Choose(int rIndex){
        if (rIndex >= 0 && rIndex < index.size()){
            indexChoice = rIndex;
        }
    }

std::string ECConsoleUIListBox::GetTextAtRow(int r) const {
    std::string strOut;
    if(index.size() == 0){
        return strOut;
    }
    int add = r - GetYUL();
    if( r >= GetYUL() && r <= GetYLR() )
    {
        return index[add + firstVisible];
    }
    return strOut;
}

    int ECConsoleUIListBox :: GetHighlightPosition(int &xLeft, int &xRight) const
    {
        if (indexChoice >= firstVisible && indexChoice < firstVisible + VisibleRows) {
                int relativeIndex = indexChoice - firstVisible;
                xLeft = 0;
                xRight = GetWidth();
                return relativeIndex;
            } else {
                // No highlight outside the visible range
                return -1;
            }
    }


    void ECConsoleUIListBox::HdlKeyUp() {
        if (GetChoice() == 0) {
            return;
        }
        Choose(GetChoice() - 1);
        if (GetChoice() == firstVisible) {
            ScrollUp();
        }
    }

    void ECConsoleUIListBox :: HdlKeyDown(){
        if (GetChoice() == index.size()){
            return;
        }
        Choose(GetChoice() + 1);
        if (GetChoice() == firstVisible + VisibleRows){
            ScrollDown();
        }
        
    }

    void ECConsoleUIListBox :: ScrollUp(){
        if (firstVisible > 0) {
            firstVisible--;
        }
    }

    void ECConsoleUIListBox :: ScrollDown() {
        if (firstVisible < index.size() - VisibleRows)
        firstVisible++;
    }

    void ECConsoleUIListBox :: DeleteIndex(){
        index.clear();
}

    int ECConsoleUIListBox :: SizeIndex(){
        return index.size();
}
