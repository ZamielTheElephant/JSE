#include "mainJSE.h"

//EmptySector Functions
EmptySector::EmptySector(std::string inName, std::string inType, std::string inEnvironment)
    : Sector(inName, inType, inEnvironment)
{
    //Nothing
}

//EmptySector Generation
EmptySector generateEmptySector()
{
    //Generate Name
    std::string name = generateSectorName();

    //Generate Environment
    std::string environment = generateSectorEnvironment();

    std::string type = "Empty Sector";

    return EmptySector(name, type, environment);
}