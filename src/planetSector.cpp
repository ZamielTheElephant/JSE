#include "mainJSE.h"

//PlanetSector Functions
PlanetSector::PlanetSector(std::string inName, std::string inType, std::string inEnvironment, Planet inPlanet, Alien inAlien)
    : Sector(inName, inType, inEnvironment)
{
    this->planet = inPlanet;
    this->alien = inAlien;
}

//Planet Functions
Planet::Planet(std::string inName, std::string inType, int inSize, int inPopulation, Ship inShip, Resource inResource)
{
    this->name = inName;
    this->type = inType;
    this->size = inSize;
    this->population = inPopulation;
    this->ship = inShip;
    this->resource = inResource;
}

//Planet Sector Generation
PlanetSector generatePlanetSector(int difficultyModifier)
{
    //Generate Name
    std::string name = generateSectorName();

    //Generate Environment
    std::string environment = generateSectorEnvironment();

    std::string type = "Planet Sector";

    Planet planet;
    Alien alien;

    if (randomNumGenerator(1, 100) <= 40)
    {
        planet = generateEmptyPlanet();
    }
    else
    {
        alien = generateAlien();
        planet = generateAlienPlanet(alien, difficultyModifier);
    }

    return PlanetSector(name, type, environment, planet, alien);
}

//Empty Planet Generation
Planet generateEmptyPlanet()
{
    std::string name = generateEmptyPlanetName();
    std::string type = generateEmptyPlanetType();
    int size = randomNumGenerator(1, 5);
    int population = 0;
    Ship ship;
    Resource resource = generateResource(type);

    return Planet(name, type, size, population, ship, resource);
}

std::string generateEmptyPlanetType()
{
    std::string types[] = { "Barren World", "Forest World", "Desert World", "Ocean World", "Volcano World" };

    return types[randomNumGenerator(0, 4)];
}

std::string generateEmptyPlanetName()
{
    std::string firstHalf[] = { "Hu", "Am", "Mo", "Cho", "Br", "Ve", "Ba", "Tha", "Li", "Gr", "Cu", "Za", "Cro", "Del", "In" };
    std::string secondHalf[] = { "ron", "iea", "des", "mia", "lea", "on", "nus", "gantu", "shan", "dus", "dore", "tune", "rilia", "karth", "ade" };

    std::string emptyPlanetName = firstHalf[randomNumGenerator(0, 14)] + secondHalf[randomNumGenerator(0, 14)] + " " + std::to_string(randomNumGenerator(100, 999));

    return emptyPlanetName;
}

//Alien Planet Generation
Planet generateAlienPlanet(Alien alien, int difficultyModifier)
{
    std::string type = generateAlienPlanetType(alien.getType());
    std::string name = generateAlienPlanetName(type);
    int size = randomNumGenerator(1, 5);
    int population = generatePlanetPopulation(type);
    Ship ship = generateNewShip(alien, difficultyModifier);
    Resource resource; //Generate Resource

    return Planet(name, type, size, population, ship, resource);
}

int generatePlanetPopulation(std::string type)
{
    if (type == "Crusader World")
        return randomNumGenerator(1, 3); //Billion approx.
    else if (type == "Factory World")
        return randomNumGenerator(10, 15); //Billion approx.
    else if (type == "Hive World")
        return randomNumGenerator(30, 50);
    else if (type == "Gret Archive World")
        return randomNumGenerator(1, 2);
    else
        return randomNumGenerator(3, 7);
}

std::string generateAlienPlanetName(std::string type) //Edits Required
{
    std::string firstHalf[] = { "Hu", "Am", "Mo", "Cho", "Br", "Ve", "Ba", "Tha", "Li", "Gra", "Cu", "Za", "Cro", "Del", "In", "Ce", "Dr", "Thu", "Mor", "Cha" };
    std::string secondHalf[] = { "ron", "iea", "des", "mia", "lea", "on", "nus", "gantu", "shan", "dus", "dore", "tune", "rilia", "karth", "ade", "rth", "ion", "liv", "tron", "clite" };

    std::string planetName = firstHalf[randomNumGenerator(0, 19)] + secondHalf[randomNumGenerator(0, 19)];

    return planetName;
}

std::string generateAlienPlanetType(std::string alienType)
{
    if (alienType == "Warriors")
        return "Crusader World";
    else if (alienType == "Traders")
        return "Factory World";
    else if (alienType == "Hive Mind")
        return "Hive World";
    else if (alienType == "Knowledge Seekers")
        return "Great Archive World";
    else
        return "City World";
}