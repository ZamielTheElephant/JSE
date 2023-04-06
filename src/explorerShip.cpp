#include "mainJSE.h"

//ExplorerShip Functions
ExplorerShip::ExplorerShip(std::string inName, std::string inType, int inSize, Crew inCrew, int inAmountOfWeapons, int inMiningLvl, int inHull, int inShields, int inCombatManeuver, CargoHold inCargoHold, LogBook inLogBook)
    : Ship(inName, inType, inSize, inCrew, inAmountOfWeapons, inMiningLvl, inHull, inShields, inCombatManeuver, inCargoHold)
{
    this->logBook = inLogBook;
}

void ExplorerShip::takeSpoils(int liberatedFood, int liberatedFuel)
{
    while (getCargoHold().getCapacity() - getCargoHold().getTotalCargo() > 0 && (liberatedFood != 0 || liberatedFuel != 0))
    {
        if (liberatedFood > 0 && getCargoHold().getCapacity() - getCargoHold().getTotalCargo() > 0)
        {
            getCargoHold().buyFood(0);
            liberatedFood--;
        }

        if (liberatedFuel > 0 && getCargoHold().getCapacity() - getCargoHold().getTotalCargo() > 0)
        {
            getCargoHold().buyFuel(0);
            liberatedFuel--;
        }
    }
}

//Explorer Ship Generator Functions
ExplorerShip generateExplorerShip()
{
    //Generate Ship Name
    std::string name = generateExplorerShipName();

    //Generate Type
    std::string type = generateType();

    //Generate Size
    int size = generateSize(type);

    //Generate ExShip Crew
    Crew crew = generateExplorerShipCrew(size);

    //Generate Amount of Weapons
    int amountOfWeapons = generateAmountOfWeapons(type);

    //Generate Mininglvl
    int miningLvl = generateMiningLvl(type);

    //Generate Hull
    int hull = generateHull(type);

    //Generate Shields
    int shield = generateShield(type);

    //Generate combatManeuver
    int combatManeuver = generateCombatManeuver(size);

    //Generate ExplorerShip CargoHold
    CargoHold cargoHold = generateExplorerShipCargoHold(type);

    LogBook logBook(cargoHold.getMoney(), cargoHold.getFood(), cargoHold.getFuel(), crew.getCrewNum() + 5);

    return ExplorerShip(name, type, size, crew, amountOfWeapons, miningLvl, hull, shield, combatManeuver, cargoHold, logBook);
}

CargoHold generateExplorerShipCargoHold(std::string type)
{
    int capacity;
    int money;

    switch (typeNumber(type))
    {
    case 0:
        capacity = randomNumGenerator(7, 8) * 30;//Mining
        money = 100;
    case 1:
        capacity = randomNumGenerator(9, 10) * 30;//Trade
        money = 200;
    case 2:
        capacity = randomNumGenerator(3, 4) * 30;//Corvette
        money = 100;
    case 3:
        capacity = randomNumGenerator(4, 5) * 30;//Frigate
        money = 100;
    case 4:
        capacity = randomNumGenerator(6, 7) * 30;//Destroyer
        money = 100;
    case 5:
        capacity = randomNumGenerator(6, 7) * 30;//Battlecruiser
        money = 100;
    }

    return CargoHold(capacity, money);

}

std::string generateExplorerShipName()
{
    std::string shipNames[] = { "Ulysses", "Fenrir", "Illithid", "Behemoth", "Midgardsormr", "Hraesvelgr", "Nidhogg", "Elendil", "Gil-galad", "Theseus", "Marathon" };//Add more names maybe??

    return "JSE " + shipNames[randomNumGenerator(0, 10)];
}

//Used for Explorer Crew!!! Not Generic
Crew generateExplorerShipCrew(int size)
{
    Captain captain(randomNameGenerator(), randomNumGenerator(30, 70), "Captain", 10);
    Pilot pilot(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", 10);
    Engineer engineer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", 10);
    MiningOfficer miningOfficer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", 10);
    WeaponsOfficer weaponsOfficer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", 10);
    int crewNum = generateCrewNum(size);

    return Crew(captain, pilot, engineer, miningOfficer, weaponsOfficer, crewNum);
}