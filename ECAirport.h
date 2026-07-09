//
//  ECAirport.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECAirport_h
#define ECAirport_h

#include <string>
#include <set>
#include <map>

class ECAirport {
public:
    ECAirport();
    ECAirport(const std::string &nameAP, const std::string &codeIATA);
    ECAirport(const ECAirport &rhs);
    
    std::string GetName() const;
    std::string GetCode() const;
    
    bool IsOperating() const;
    void SetOperating(bool f);
    
private:
    std::string nameAP;
    std::string codeIATA;
    bool operating;
};

class ECAirportInfo {
public:
    virtual ~ECAirportInfo() {}
    
    void CreateAirport(const std::string &name, const std::string &code);
    const ECAirport& GetAirport(const std::string &code);
    
    void SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist);
    int GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code);
    
    static ECAirportInfo* Instance();
    
    std::map<std::string, std::map<std::string, int>> GetMap2(){
            return map2;
        }
    
protected:
    ECAirportInfo();
    
private:
    std::map<std::string, ECAirport> map1;
    std::map<std::string, std::map<std::string, int>> map2;
    static ECAirportInfo* _instance;
};

#endif /* ECAirport_h */

