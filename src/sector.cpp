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

Sector* generateSector(std::vector<std::pair<double, double>> &existingCoordinates, int count)
{
    Sector newSector;
    switch (determineSectorType())
    {
        case 0:
            newSector = generateAnomalySector();
            break;
        case 1:
            newSector = generateEmptySector();
            break;
        case 2:
            newSector = generateTradeSector();
            break;
        case 3:
            newSector = generatePlanetSector(difficultyModifier(count));
            break;
        case 4:
            newSector = generateShipSector(difficultyModifier(count));
            break;
    }

    std::pair<double, double> newCoordinates;

    //Generates 
    bool loop = true;
    while (loop)
    {
        loop = false;
        
        //Generate Sector Coordinates
        newCoordinates = std::make_pair(randomNumGenerator(0.0, 100.0), randomNumGenerator(0.0, 100.0));

        if (std::find(existingCoordinates.begin(), existingCoordinates.end(), newCoordinates) != existingCoordinates.end())
        {
            loop = true;
            break;
        }
    }
    
    newSector.setCoordinates(newCoordinates);
    existingCoordinates.push_back(newCoordinates);

    return &newSector;
}



//SectorMap Functions
SectorList* generateSectorList(int sectorCount)
{
    SectorList* sectorList = new SectorList();

    //Keep track of exisitng sector coordinates so two aren't created in the same location
    std::vector<std::pair<double, double>> existingCoordinates;

    //Loop to generate the specified amount of sectors
    for (int i = 0; i < sectorCount; i++)
    {
        //Generate new sector
        Sector* newSector = generateSector(existingCoordinates, i);
        sectorList->getSectorList().push_back(newSector);
    }

    return sectorList;
}

std::vector<Sector*> SectorList::getSectorList()
{
    return this->sectorList;
}