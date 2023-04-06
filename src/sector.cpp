#include "mainJSE.h"

//Sector Functions
Sector::Sector(std::string inName, std::string inType, std::string inEnvironment)
{
    this->name = inName;
    this->type = inType;
    this->environment = inEnvironment;
}

std::string generateSectorEnvironment()
{
    std::string environments[] = {"Outer Space", "Nebula", "Asteroid Field", "Star"};

    return environments[randomNumGenerator(0,3)];
}

std::string generateSectorName()
{
    std::string letter[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    
    return letter[randomNumGenerator(0,25)] + std::to_string(randomNumGenerator(1,99));
}

int sectorTypeNumber(std::string type)
{
    if(type.compare("Empty Sector") == 0)
        return 0;
    else if(type.compare("Ship Sector") == 0)
        return 1;
    else if(type.compare("Planet Sector") == 0)
        return 2;
    else if(type.compare("Trade Sector") == 0)
        return 3;
    else
        return 4;
}
