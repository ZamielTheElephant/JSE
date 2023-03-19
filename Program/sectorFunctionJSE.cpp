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
    //Nothing
}

AnomalySector::AnomalySector(std::string inName, std::string inType, std::string inEnvironment)
    : Sector(inName, inType, inEnvironment)
{
    //Nothing
}

void AnomalySector::resolveLostSatellite(ExplorerShip& exShip, std::string sectorName, int difficultyModifier)
{
    std::string sectorLog = "---Sector " + sectorName + "---\n";
    std::string tempCrewDeathRecord = "\nSector " + sectorName;
    sectorLog += "Abandoned Satellite Found.\n";
    std::cout << "The " << exShip.getName() << " comes across a abandoned satellite floating in space." << std::endl;
    int storySelection = randomNumGenerator(1,3);

    Resource resource;
    Alien alien;
    Ship alienShip;

    switch(storySelection)
    {
        case 1:
            //Self-Destruct Sequence
            std::cout << "While the crew is investigating the satellite, a self-destruct sequence is activated." << std::endl;
            sectorLog += " Self-destruct sequence activated.\n";
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Deactiveate Sequence
                    std::cout << "The Ships engineer " << exShip.getCrew().getEngineer().getName() << " quickly manages to deactivate the sequence." << std::endl;
                    std::cout << "The " << exShip.getName() << " moves on." << std::endl;
                    sectorLog += "Ships engineer deactivates the sequence.\n";
                    break;
                case 2:
                    //Crew Sacrifice
                    std::cout << "The self-destruct sequence isn't stopped in time. A member of the crew is killed in the blast." << std::endl;
                    tempCrewDeathRecord += ": A satellite self-destructed";
                    exShip.getCrew().killReplaceOfficer(dynamic_cast<Ship*>(&exShip), tempCrewDeathRecord);
                    sectorLog += "The self-destruct sequence completes, crew member is killed in the blast.\n";
                    break;
                case 3:
                    //Ship Massive Damaged
                    std::cout << "The self-destruct sequence isn't stopped in time. The Ship is unable to move away before the blast." << std::endl;
                    exShip.dealAnomalyDamage(100);
                    sectorLog += "The self-destruct sequence completes, ship is heavily damaged in the blast.\n";
                    break;
            }
            break;
        case 2:
            //Mining Information
            std::cout << "The Crew manage to decifer the data on the satellite." << std::endl;
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Diamonds
                    std::cout << "The data contains coordinates to a cache of diamonds nearby." << std::endl;
                    std::cout << "The " << exShip.getName() << " travels to the location and finds the cache." << std::endl;
                    sectorLog += "The Satellite contains location data of a Diamond cache.\n";
    
                    if(exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= 7)
                    {
                        resource = Resource("Diamond", "Metal", 7, 1000, 400, 8);
                        exShip.getCargoHold().addResource(resource);
                        std::cout << "The Diamond is successfully gathered." << std::endl;
                        sectorLog += "The Diamond is successfully gathered.\n";
                    }
                    else
                    {
                        std::cout << "Not enough room to gather the diamond." << std::endl; 
                        sectorLog += "Unsuccessful in gathering the diamond.\n";
                    }
                    break;
                case 2:
                    //Random Resource
                    std::cout << "The data contains coordinates to a cache of a mystery resource." << std::endl;
                    resource = generateResource(generateEmptyPlanetType());
                    std::cout << "The " << exShip.getName() << " travels to the location and finds the cache of " << resource.getName() << "." << std::endl;
                    sectorLog += "The Satellite contains location data of an unknown resource cache.\n";

                    if(exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
                    {
                        exShip.getCargoHold().addResource(resource);
                        std::cout << "The " << resource.getName() << " is successfully gathered." << std::endl;
                        sectorLog += "The " + resource.getName() + " is successfully gathered.\n";
                    }
                    else
                    {
                        std::cout << "Not enough room to gather the " << resource.getName() << "." << std::endl; 
                        sectorLog += "Unsuccessful in gathering the " + resource.getName() + ".\n";
                    }
                    break;
                case 3:
                    //Nothing :(
                    std::cout << "The data contains coordinates to a cache of a mystery resource." << std::endl;
                    sectorLog += "The Satellite contains location data of an unknown resource cache.\n";
                    std::cout << "The " << exShip.getName() << " travels to the location and finds the cache. However there is nothing there." << std::endl;
                    sectorLog += "The cache had nothing in it.\n";
                    break;
            }
            break;
        case 3:
            //Trap Beacon
            std::cout << "As the " << exShip.getName() << " approaches, the satellite activates a beacon.\n";
            sectorLog += "The satellite activates a beacon.\n";
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Bati
                    alien = Alien("Bati", "Warriors", 70, 60, "Looks like a Bati");
                    alienShip = generateNewShip(alien, difficultyModifier);
                    std::cout << "Suddenly a Bati " << alienShip.getType() << " appears and begins to attack." <<std::endl;
                    sectorLog += "A Bati " + alienShip.getType() + " appeared and attacked.\n";
                    if(resolveBattle(exShip, alienShip, sectorLog, sectorName))
                    {
                        std::cout << "\n>>>>>>>>>>> Victory <<<<<<<<<<<\n" << std::endl;
                    }
                    else
                    {
                        std::cout << "\n>>>>>>>>>>> Defeat <<<<<<<<<<<\n" << std::endl;
                    }
                    break;
                case 2:
                    //Drul
                    alien = Alien("Drul", "Hive Mind", 100, 0, "Looks like a Drul");
                    alienShip = generateNewShip(alien, difficultyModifier);
                    std::cout << "Suddenly a Drul " << alienShip.getType() << " appears and begins to attack." <<std::endl;
                    sectorLog += "A Drul " + alienShip.getType() + " appeared and attacked.\n";
                    if(resolveBattle(exShip, alienShip, sectorLog, sectorName))
                    {
                        std::cout << "\n>>>>>>>>>>> Victory <<<<<<<<<<<\n" << std::endl;
                    }
                    else
                    {
                        std::cout << "\n>>>>>>>>>>> Defeat <<<<<<<<<<<\n" << std::endl;
                    }
                    break;
                case 3:
                    //Naaji
                    alien = Alien("Naaji", "Knowledge Seekers", 0, 100, "Looks like a Naaji");
                    alienShip = generateNewShip(alien, difficultyModifier);
                    std::cout << "Suddenly a Naaji " << alienShip.getType() << " appears, they open up communications." << std::endl;
                    std::cout << "They tell you they would like to trade." << std::endl;
                    sectorLog += "A Naaji " + alienShip.getType() + " appeared and offered to trade.\n";
                    resolveTrade(exShip, alienShip, sectorLog);
                    break;
            }
            break;
    }
    exShip.getLogBook().addSectorLog(sectorLog);
}

void AnomalySector::resolveAncientPlace(ExplorerShip& exShip, std::string sectorName)
{
    std::string sectorLog = "---Sector " + sectorName + "---\n";
    std::string tempCrewDeathRecord = "\nSector " + sectorName;
    std::cout << "The " << exShip.getName() << " comes across a planet that has what looks like an Ancient ";
    sectorLog += "An Ancient ";

    Resource resource;
    int storySelection = randomNumGenerator(1,3);
    switch(storySelection)
    {
        case 1:
            //Ancient Temple
            std::cout << "Temple on the surface." << std::endl;
            sectorLog += "Temple is found.\n";
            std::cout << "The Crew Begins to investigate." << std::endl;
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Find Ancient Artifact
                    std::cout << "After trawling through meaningless items a crew member finds a valuble Artifact." << std::endl;
                    sectorLog += "While searching the Temple an Ancient Artifact is found.\n";
                    resource = Resource("Ancient Artifact", "Unique", 1, 2000, 1000, 0);
                    if(exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
                    {
                        exShip.getCargoHold().addResource(resource);
                        std::cout << "The " << resource.getName() << " is stored into the cargo hold." << std::endl;
                        sectorLog += "The " + resource.getName() + " is successfully collected.\n";
                    }
                    else
                    {
                        std::cout << "Not enough room to store the " << resource.getName() << "." << std::endl; 
                        sectorLog += "Unsuccessful in collecting the " + resource.getName() + ".\n";
                    }
                    break;
                case 2:
                    //Temple Collapse No Gain
                    std::cout << "While searching the Temple, the structure begins to shift and starts to collapse." <<std::endl;
                    std::cout << "Fortunatly, the search team is able to escape the falling building." << std::endl;
                    sectorLog += "While searching the Temple it begins to collapes, the crew is able to escape.\n";
                    break;
                case 3:
                    //Temple Collapse Loss Crew Member
                    std::cout << "While searching the Temple, the structure begins to shift and starts to collapse." <<std::endl;
                    std::cout << "The search team begins to flee the, however not everyone is able to escape." << std::endl;
                    sectorLog += "While searching the Temple it begins to collapes, one of the officers is killed.\n";
                    tempCrewDeathRecord += ": A temple collapse while the crew searches for artifacts";
                    exShip.getCrew().killReplaceOfficer(dynamic_cast<Ship*>(&exShip), tempCrewDeathRecord);
                    break;
            }
            break;
        case 2:
            //Ancient Machine Building
            std::cout << "Machine on the surface." << std::endl;
            sectorLog += "Machine is found.\n";
            std::cout << "The Crew Begins to investigate." << std::endl;
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Machine Activates Gain Resource?
                    std::cout << "While investigating the Machine, a crew member finds a valuble piece of machinery." << std::endl;
                    sectorLog += "While searching the Machine a piece of Ancient Machinery is found.\n";
                    resource = Resource("Ancient Machinery", "Unique", 3, 1500, 1000, 0);
                    if(exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
                    {
                        exShip.getCargoHold().addResource(resource);
                        std::cout << "The " << resource.getName() << " is stored into the cargo hold." << std::endl;
                        sectorLog += "The " + resource.getName() + " is successfully collected.\n";
                    }
                    else
                    {
                        std::cout << "Not enough room to store the " << resource.getName() << "." << std::endl; 
                        sectorLog += "Unsuccessful in collecting the " + resource.getName() + ".\n";
                    }
                    break;
                case 2:
                    //Machine Non functional
                    std::cout << "The Ships engineer " << exShip.getCrew().getEngineer().getName() << " investigates the Machine, but finds it to be non-functional." << std::endl;
                    sectorLog += "The Machine was non-functional.\n";
                    break;
                case 3:
                    //Machine Activates Loss Crew Member
                    std::cout << "As the crew search the Machine it begins to start up." << std::endl;
                    std::cout << "The crew begin to flee from the Mechanical Monstrosity, but not everyone escapes." << std::endl;
                    sectorLog += "While investigating the Machine it begins to start up, one of the officers is killed in the chaos.\n";
                    tempCrewDeathRecord += ": A deadly machine activates while the crew searches it for artifacts";
                    exShip.getCrew().killReplaceOfficer(dynamic_cast<Ship*>(&exShip), tempCrewDeathRecord);
                    break;
            }
            break;
        case 3:
            //Ancient Ship Ruins
            std::cout << "Ship Ruin on the surface." << std::endl;
            sectorLog += "Ships Ruin is found.\n";
            std::cout << "The Crew Begins to investigate." << std::endl;
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Find Powerful Weapon //If Possible?
                    std::cout << "While investigating the Ancient Ship, a powerful weapon is found." << std::endl;
                    std::cout << "The Ships Engineer " << exShip.getCrew().getEngineer().getName() << " believes they can add it to the ships arsenal." << std::endl;
                    sectorLog += "While searching the ship a powerful weapon is found.\n";

                    if((exShip.getAmountOfWeapons()) < 4)
                    {
                        exShip.addWeapon(Weapon("Ancient Cannon", 3, 100, 80, 50, 5));
                        std::cout << "The Ancient Cannon is fitted onto the ship." << std::endl;
                        sectorLog += "The Weapon was fitted to the ship.\n";
                    }
                    else
                    {
                        std::cout << "There was not enough room to fit the weapon to the ship." << std::endl;
                        sectorLog += "The Weapon was NOT fitted to the ship.\n";
                    }
                    break;
                case 2:
                    //Nothing Found
                    std::cout << "The crew searches the ruins, but find nothing except ash and twisted metal." << std::endl;
                    sectorLog += "The crew found nothing in the ruins.\n";
                    break;
                case 3:
                    //Explosion Loss Crew Member
                    std::cout << "While searching the ruins, an ancient munitions cache is triggered." << std::endl;
                    std::cout << "An officer is killed in the blast." << std::endl;
                    sectorLog += "While searching the ruins, an old munitions cache exploded, killing an officer.\n";
                    tempCrewDeathRecord += ": A set of ancient munitions explodes";
                    exShip.getCrew().killReplaceOfficer(dynamic_cast<Ship*>(&exShip), tempCrewDeathRecord);
                    break;
            }
            break;
    }
    exShip.getLogBook().addSectorLog(sectorLog);
}

void AnomalySector::resolvePrimitiveCivilisation(ExplorerShip& exShip, std::string sectorName)
{
    std::string sectorLog = "---Sector " + sectorName + "---\n";
    std::string tempCrewDeathRecord = "\nSector " + sectorName;
    std::cout << "The " << exShip.getName() << " comes across a populated Planet. The people here seem quite primitive." << std::endl;
    sectorLog += "The Ship comes landed on a Planet with a primitive population.\n";

    Resource resource;
    int storySelection = randomNumGenerator(1,3);

    switch(storySelection)
    {
        case 1:
            //Stone Age
            std::cout << "The aliens here seem to be in a Stone age period in their history.\nThe crew moves to make contact with the aliens" << std::endl;
            sectorLog += "Encountered Stone age aliens and attempted to contact.\n";
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Communicate/Trade
                    std::cout << "The crew was able to make peaceful contact with the aliens." << std::endl;
                    sectorLog += "The crew made peaceful contact with the primitive aliens.\n";
                    resource = generateResource(generateEmptyPlanetType());
                    if(exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
                    {
                        exShip.getCargoHold().addResource(resource);
                        std::cout << "The aliens offer to trade with the crew." << std::endl;
                        std::cout << "The aliens trade some " << resource.getName() << " to the crew." << std::endl; 
                        sectorLog += "The aliens traded some " + resource.getName() + ".\n";
                    }
                    else
                    {
                        std::cout << "The aliens offer to trade but the Ship couldn't carry anymore cargo." << std::endl; 
                        sectorLog += "The aliens offered to trade but there was not enought room in the ship.\n";
                    }
                    break;
                case 2:
                    //Aggressive/Escape
                    std::cout << "The crew attempt to make peaceful contact, but are meet with spears and arrows.\nThe crew is forced to return to the ship empty handed." << std::endl;
                    sectorLog += "The crew attempted to make peaceful contact, but were driven away.\n";
                    break;
                case 3:
                    //Aggressive/Loss Crew Member
                    std::cout << "The crew attempt to make peaceful contact, but the aliens attack.\nBefore the crew can get back to the ship an officer is killed." << std::endl;
                    sectorLog += "The crew attempted to make peaceful contact, but were attacked.\nAn officer was killed in the fighting.\n";
                    tempCrewDeathRecord += ": The crew was attacked when trying to make contact with primitive aliens.";
                    exShip.getCrew().killReplaceOfficer(dynamic_cast<Ship*>(&exShip), tempCrewDeathRecord);
                    break;
            }
            break;
        case 2:
            //Medieval Era
            std::cout << "The aliens here seem to be in a Medieval period in their history.\nThe crew moves to make contact with the aliens" << std::endl;
            sectorLog += "Encountered Medieval aliens and attempted to contact.\n";
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Communicate/Trade
                    std::cout << "The crew was able to make peaceful contact with the aliens." << std::endl;
                    sectorLog += "The crew made peaceful contact with the primitive aliens.\n";
                    resource = generateResource(generateEmptyPlanetType());
                    if(exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
                    {
                        exShip.getCargoHold().addResource(resource);
                        std::cout << "The aliens offer to trade with the crew." << std::endl;
                        std::cout << "The aliens trade some " << resource.getName() << " to the crew." << std::endl; 
                        sectorLog += "The aliens traded some " + resource.getName() + ".\n";
                    }
                    else
                    {
                        std::cout << "The aliens offer to trade but the Ship couldn't carry anymore cargo." << std::endl; 
                        sectorLog += "The aliens offered to trade but there was not enought room in the ship.\n";
                    }
                    break;
                case 2:
                    //Aggressive/Escape
                    std::cout << "The crew attempt to make peaceful contact, but are ambushed by sword wielding aliens.\nThe crew is forced to return to the ship wounded but alive." << std::endl;
                    sectorLog += "The crew attempted to make peaceful contact, but were forced to return to the ship.\n";
                    break;
                case 3:
                    //Aggressive/Loss Crew Member
                    std::cout << "The crew attempt to make peaceful contact, the aliens draw their swords as they approach.\nAs the crew flee to the ship, an officer is cut down by an alien." << std::endl;
                    sectorLog += "The crew attempted to make peaceful contact, but were attacked.\nAn officer was killed while fleeing to the ship in the fighting.\n";
                    tempCrewDeathRecord += ": The crew was attacked when trying to make contact with primitive aliens.";
                    exShip.getCrew().killReplaceOfficer(dynamic_cast<Ship*>(&exShip), tempCrewDeathRecord);
                    break;
            }
            break;
        case 3:
            //Modern Era
            std::cout << "The aliens here seem to be in a Modern period in their history.\nThe crew moves to make contact with the aliens" << std::endl;
            sectorLog += "Encountered Modern period aliens and attempted to contact.\n";
            storySelection = randomNumGenerator(1,3);
            switch(storySelection)
            {
                case 1:
                    //Communicate/Trade
                    std::cout << "The crew was able to make peaceful contact with the aliens." << std::endl;
                    sectorLog += "The crew made peaceful contact with the primitive aliens.\n";
                    resource = generateResource(generateEmptyPlanetType());
                    if(exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
                    {
                        exShip.getCargoHold().addResource(resource);
                        std::cout << "The aliens are interested in the crews advanced technology and offer to trade." << std::endl;
                        std::cout << "The aliens trade some " << resource.getName() << " to the crew." << std::endl; 
                        sectorLog += "The aliens traded some " + resource.getName() + ".\n";
                    }
                    else
                    {
                        std::cout << "The aliens offer to trade but the Ship couldn't carry anymore cargo." << std::endl; 
                        sectorLog += "The aliens offered to trade but there was not enought room in the ship.\n";
                    }
                    break;
                case 2:
                    //Aggressive/Escape
                    std::cout << "The crew attempt to make peaceful contact, but as the crew step off the ship they are peppered by small arms fire."<< std::endl;
                    std::cout << "The crew return fire as they reboard the ship." << std::endl;
                    sectorLog += "The crew attempted to make peaceful contact, but were attacked by small arms fire.\n";
                    break;
                case 3:
                    //Aggressive/Loss Crew Member
                    std::cout << "The crew attempt to make peaceful contact, but the aliens open fire as they approach.\nAs the crew retreats to the ship, an officer is fatally shot." << std::endl;
                    sectorLog += "The crew attempted to make peaceful contact, but were shot at.\nAn officer was killed in the firefight.\n";
                    tempCrewDeathRecord += ": The crew was attacked when trying to make contact with primitive aliens.";
                    exShip.getCrew().killReplaceOfficer(dynamic_cast<Ship*>(&exShip), tempCrewDeathRecord);
                    break;
            }
            break;
    }
    exShip.getLogBook().addSectorLog(sectorLog);
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

void TradeStation::removeFoodGoods(int foodRemoved)
{
    this->foodGoods -= foodRemoved;
}

void TradeStation::removeFuelGoods(int fuelRemoved)
{
    this->fuelGoods -= fuelRemoved;
}

//Resource Functions
Resource::Resource(std::string inName, std::string inType, int inSize, int inValue, int inMinValue, int inMiningDiffuculty)
{
    this->name = inName;
    this->type = inType;
    this->size = inSize;
    this->value = inValue;
    this->minValue = inMinValue;
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

AnomalySector generateAnomalySector()
{
    //Generate Name
    std::string name = generateSectorName();

    //Generate Environment
    std::string environment = generateSectorEnvironment();

    std::string type = "Anomaly Sector";

    return AnomalySector(name, type, environment);
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
        fuelGoods = randomNumGenerator(10,20);
        foodGoods = randomNumGenerator(40,60);
        barteringLvl = randomNumGenerator(10,60);
    }
    else if(name == "Fuel Station")
    {
        fuelGoods = randomNumGenerator(40,60);
        foodGoods = randomNumGenerator(10,20);
        barteringLvl = randomNumGenerator(10,60);
    }
    else
    {
        fuelGoods = randomNumGenerator(10,20);
        foodGoods = randomNumGenerator(10,20);
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

    int minValue = generateResourceMinValue(name);

    int miningDifficulty = generateResourceMiningDifficulty(type);

    return Resource(name, type, size, value, minValue, miningDifficulty);
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
        return randomNumGenerator(20,40);
    else if(name == "Fish" || name == "Mushrooms" || name == "Fruit")
        return randomNumGenerator(30,50);
    else if(name == "Logs" || name == "Cactus")
        return randomNumGenerator(50,70);
    else 
        return randomNumGenerator(100,150);
}

int generateResourceMinValue(std::string name)
{
    if(name == "Iron" || name == "Salt")
        return 40;
    else if(name == "Diamond")
        return 400;
    else if(name == "Sand" || name == "Flint" || name == "Seaweed")
        return 10;
    else if(name == "Fish" || name == "Mushrooms" || name == "Fruit")
        return 20;
    else if(name == "Logs" || name == "Cactus")
        return 40;
    else 
        return 70;
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
    std::string firstHalf[] = {"Hu", "Am", "Mo", "Cho", "Br", "Ve", "Ba", "Tha", "Li", "Gr", "Cu", "Za", "Cro", "Del", "In"};
    std::string secondHalf[] = {"ron", "iea", "des", "mia", "lea", "on", "nus", "gantu", "shan", "dus", "dore", "tune", "rilia", "karth", "ade"};

    std::string emptyPlanetName = firstHalf[randomNumGenerator(0,14)] + secondHalf[randomNumGenerator(0,14)] + " " + std::to_string(randomNumGenerator(100,999));

    return emptyPlanetName;
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
    std::string firstHalf[] = {"Hu", "Am", "Mo", "Cho", "Br", "Ve", "Ba", "Tha", "Li", "Gra", "Cu", "Za", "Cro", "Del", "In", "Ce", "Dr", "Thu", "Mor", "Cha"};
    std::string secondHalf[] = {"ron", "iea", "des", "mia", "lea", "on", "nus", "gantu", "shan", "dus", "dore", "tune", "rilia", "karth", "ade", "rth", "ion", "liv", "tron", "clite"};

    std::string planetName = firstHalf[randomNumGenerator(0,19)] + secondHalf[randomNumGenerator(0,19)];

    return planetName;
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
