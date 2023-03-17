#include "mainJSE.h"

//Sector Functions
Sector::Sector(std::string inName, std::string inType, std::string inEnvironment)
{
    this->name = inName;
    this->type = inType;
    this->environment = inEnvironment;
}

//ShipSector Functions
ShipSector::ShipSector(std::string inName, std::string inType, std::string inEnvironment, Ship inAlienShip, Alien inAlien)
    : Sector(inName, inType, inEnvironment)
{
    this->alienShip = inAlienShip;
    this->alien = inAlien;
}

//PlanetSector Functions
PlanetSector::PlanetSector(std::string inName, std::string inType, std::string inEnvironment, Planet inPlanet, Alien inAlien)
    : Sector(inName, inType, inEnvironment)
{
    this->planet = inPlanet;
    this->alien = inAlien;
}

//TradeSector Functions
TradeSector::TradeSector(std::string inName, std::string inType, std::string inEnvironment, TradeStation inTradeStation)
    : Sector(inName, inType, inEnvironment)
{
    this->tradeStation = inTradeStation;
}

//EmptySector Functions
EmptySector::EmptySector(std::string inName, std::string inType, std::string inEnvironment)
    : Sector(inName, inType, inEnvironment)
{

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

//TradeStation Functions
TradeStation::TradeStation(std::string inName, int inFuelGoods, int inFoodGoods, int inBarteringLvl)
{
    this->name = inName;
    this->fuelGoods = inFuelGoods;
    this->foodGoods = inFoodGoods;
    this->barteringLvl = inBarteringLvl;
}

//Resource Functions
Resource::Resource(std::string inName, std::string inType, int inSize, int inValue, int inMiningDiffuculty)
{
    this->name = inName;
    this->type = inType;
    this->size = inSize;
    this->value = inValue;
    this->miningDifficulty = inMiningDiffuculty;
}

//Alien Functions
Alien::Alien(std::string inName, std::string inType, int inHostility, int inIntellegence, std::string inDescription)
{
    this->name = inName;
    this->type = inType;
    this->hostility = inHostility;
    this->intellegence = inIntellegence;
    this->description = inDescription;
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

TradeSector generateTradeSector()
{
    //Generate Name
    std::string name = generateSectorName();

    //Generate Environment
    std::string environment = generateSectorEnvironment();

    std::string type = "Trade Sector";

    //Generate TradeStation
    TradeStation tradeStation = generateTradeStation();

    return TradeSector(name, type, environment, tradeStation);
}

TradeStation generateTradeStation()
{
    std::string tradeStationNames[] = {"Food Station", "Fuel Station", "Pawn Station"};
    std::string name = tradeStationNames[randomNumGenerator(0,2)];
    
    int fuelGoods;
    int foodGoods;
    int barteringLvl;

    if(name == "Food Station")
    {
        fuelGoods = randomNumGenerator(0,20);
        foodGoods = randomNumGenerator(30,60);
        barteringLvl = randomNumGenerator(10,60);
    }
    else if(name == "Fuel Station")
    {
        fuelGoods = randomNumGenerator(30,60);
        foodGoods = randomNumGenerator(0,20);
        barteringLvl = randomNumGenerator(10,60);
    }
    else
    {
        fuelGoods = randomNumGenerator(0,20);
        foodGoods = randomNumGenerator(0,20);
        barteringLvl = randomNumGenerator(50,80);
    }

    return TradeStation(name, fuelGoods, foodGoods, barteringLvl);
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

    if(randomNumGenerator(1,100) <= 40)
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
    int size = randomNumGenerator(1,5);
    int population = 0;
    Ship ship;
    Resource resource = generateResource(type);

    return Planet(name, type, size, population, ship, resource);
}

Resource generateResource(std::string planetType)
{
    std::string name = generateResourceName(planetType);

    std::string type = generateResourceType(name);

    int size = generateResourceSize(type);

    int value = generateResourceValue(name);

    int miningDifficulty = generateResourceMiningDifficulty(type);

    return Resource(name, type, size, value, miningDifficulty);
}

int generateResourceMiningDifficulty(std::string type)
{
    if(type == "Metal")
        return 8;
    else if(type == "Animal")
        return 6;
    else if(type == "Mineral")
        return 5;
    else
        return 4;
}

int generateResourceValue(std::string name)
{
    if(name == "Iron" || name == "Salt")
        return randomNumGenerator(50,100);
    else if(name == "Diamond")
        return randomNumGenerator(500,1000);
    else if(name == "Sand" || name == "Flint" || name == "Seaweed")
        return randomNumGenerator(10,30);
    else if(name == "Fish" || name == "Mushrooms" || name == "Fruit")
        return randomNumGenerator(30,50);
    else if(name == "Logs" || name == "Cactus")
        return randomNumGenerator(50,70);
    else 
        return randomNumGenerator(100,150);
}

int generateResourceSize(std::string type)
{
    if(type == "Metal")
        return randomNumGenerator(7,10);
    else if(type == "Mineral")
        return randomNumGenerator(5,7);
    else if(type == "Plant")
        return randomNumGenerator(2,5);
    else
        return randomNumGenerator(1,4);
}

std::string generateResourceType(std::string name)
{
    if(name == "Iron" || name == "Diamond" || name == "Lava Gem")
        return "Metal";
    else if(name == "salt" || name == "Flint" || name == "Sand")
        return "Mineral";
    else if(name == "Fish" || name == "Scorpion Venom")
        return "Animal Produce";
    else
        return "Plant Produce";
}

std::string generateResourceName(std::string type)
{
    std::string barrenNames[] = {"Iron", "Salt", "Flint"};
    std::string forestNames[] = {"Logs", "Mushrooms", "Fruit"};
    std::string desertNames[] = {"Sand", "Cactus", "Scorpion Venom"};
    std::string oceanNames[] = {"Fish", "Salt", "Seaweed"};
    std::string volcanoNames[] = {"Diamond", "Iron", "Lava Gem"};

    if(type == "Barren World")
        return barrenNames[randomNumGenerator(0,2)];
    else if(type == "Forest World")
        return forestNames[randomNumGenerator(0,2)];
    else if(type == "Desert World")
        return desertNames[randomNumGenerator(0,2)];
    else if(type == "Ocean World")
        return oceanNames[randomNumGenerator(0,2)];
    else
        return volcanoNames[randomNumGenerator(0,2)];
}

std::string generateEmptyPlanetType()
{
    std::string types[] = {"Barren World", "Forest World", "Desert World", "Ocean World", "Volcano World"};

    return types[randomNumGenerator(0,4)];
}

std::string generateEmptyPlanetName()
{
    std::string names[] = {"PNAME"}; //Make up Empty planet names

    return names[randomNumGenerator(0,0)]; //Change when more names!!!
}

//Alien Planet Generation
Planet generateAlienPlanet(Alien alien, int difficultyModifier)
{
    std::string type = generateAlienPlanetType(alien.getType());
    std::string name = generateAlienPlanetName(type);
    int size = randomNumGenerator(1,5);
    int population = generatePlanetPopulation(type);
    Ship ship = generateNewShip(alien, difficultyModifier);
    Resource resource; //Generate Resource

    return Planet(name, type, size, population, ship, resource);
}

int generatePlanetPopulation(std::string type)
{
    if(type == "Crusader World")
        return randomNumGenerator(1,3); //Billion approx.
    else if(type == "Factory World")
        return randomNumGenerator(10,15); //Billion approx.
    else if(type == "Hive World")
        return randomNumGenerator(30,50);
    else if(type == "Gret Archive World")
        return randomNumGenerator(1,2);
    else
        return randomNumGenerator(3,7);
}

std::string generateAlienPlanetName(std::string type) //Edits Required
{
    std::string planetNames[] = {""};

    return planetNames[randomNumGenerator(0,0)];
}

std::string generateAlienPlanetType(std::string alienType)
{
    if(alienType == "Warriors")
        return "Crusader World";
    else if(alienType == "Traders")
        return "Factory World";
    else if(alienType == "Hive Mind")
        return "Hive World";
    else if(alienType == "Knowledge Seekers")
        return "Great Archive World";
    else
        return "City World";
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

Alien generateAlien() //Edits required
{
    std::string name = generateAlienName();
    std::string type;
    int hostility;
    int intellegence;
    std::string description;

    if(name == "Bati")
    {
        type = "Warriors";
        hostility = randomNumGenerator(50,70);
        intellegence = randomNumGenerator(40,60);
        description = "Looks Like an A"; //Make up description
    }
    else if(name == "Caladri")
    {
        type = "Traders";
        hostility = randomNumGenerator(10,30);
        intellegence = randomNumGenerator(30,80);
        description = "Looks like a B"; //Make up description
    }
    else if(name == "Drul")
    {
        type = "Hive Mind";
        hostility = 100;
        intellegence = 0;
        description = "Looks like a C"; //Make up description
    }
    else if(name == "Naaji")
    {
        type = "Knowledge Seekers";
        hostility = randomNumGenerator(0,20);
        intellegence = randomNumGenerator(80,100);
        description = "Looks like a D"; //Make up description
    }
    else
    {
        type = "Timid Nomads";
        hostility = randomNumGenerator(10,30);
        intellegence = randomNumGenerator(10,30);
        description = "Looks like an E"; //Make up description
    }

    return Alien(name, type, hostility, intellegence, description);
}

std::string generateAlienName()
{
    std::string names[] = {"Bati","Caladri","Drul","Naaji","Juradoo"}; //Make up good names!!!
    return names[randomNumGenerator(0,4)];
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
