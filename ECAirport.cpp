//
//  ECAirport.cpp
//  
//
//

#include "ECAirport.h"
#include <iostream>
#include <map>

ECAirport::ECAirport() {}

ECAirport  ::  ECAirport(const std::string &nameAP, const std::string &codeIATA)
    : nameAP(nameAP), codeIATA(codeIATA) {}

ECAirport :: ECAirport(const ECAirport &rhs) : nameAP(rhs.nameAP), codeIATA(rhs.codeIATA) {}

std::string ECAirport :: GetName() const{
    return nameAP;
}

std::string ECAirport :: GetCode() const{
    return codeIATA;
}


void ECAirportInfo :: CreateAirport(const std::string &name, const std::string &code){
    map1[code] = ECAirport(name, code);
}

const ECAirport& ECAirportInfo :: GetAirport(const std::string &code){
    // throw exception if it doesn't exist
    if (map1.find(code) == map1.end()) {
        std::cout << "not a valid airport" << std::endl;
        throw std::runtime_error("Airport not found");
    }
    return map1[code];
}

void ECAirportInfo :: SetDistanceBtw(const std::string &ap1Code,const std::string &ap2Code, int dist){
    //map2[ap1Code].insert(std::make_pair(ap2Code, dist));
    map2[ap1Code][ap2Code] = dist;
    map2[ap2Code][ap1Code] = dist;
}

int ECAirportInfo :: GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code){
    return map2[ap1Code][ap2Code];
}

ECAirportInfo* ECAirportInfo::_instance = nullptr;

ECAirportInfo* ECAirportInfo::Instance() {
    if (_instance == nullptr) {
        _instance = new ECAirportInfo;
    }
    return _instance;
}

ECAirportInfo::ECAirportInfo() {}







