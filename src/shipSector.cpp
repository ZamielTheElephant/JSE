#include "mainJSE.h"

//ShipSector Functions
ShipSector::ShipSector(std::string inName, std::string inType, std::string inEnvironment, Ship inAlienShip, Alien inAlien)
    : Sector(inName, inType, inEnvironment)
{
    this->alienShip = inAlienShip;
    this->alien = inAlien;
}

//Ship Sector Generation
ShipSector generateShipSector(int difficultyModifier)
{
    //Generate Name
    std::string name = generateSectorName();

    //Generate Environment
    std::string environment = generateSectorEnvironment();

    std::string type = "Ship Sector";

    Alien alien = generateAlien();

    Ship alienShip = generateNewShip(alien, difficultyModifier);

    return ShipSector(name, type, environment, alienShip, alien);
}