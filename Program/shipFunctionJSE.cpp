#include "mainJSE.h"

//Ship Functions
Ship::Ship(std::string inName, std::string inType, int inSize, Crew inCrew, int inAmountOfWeapons, int inMiningLvl, int inHull, int inShields, int inCombatManeuver, CargoHold inCargoHold)
{
    name = inName;
    type = inType;
    size = inSize;
    crew = inCrew;
    miningLvl = inMiningLvl;
    populateWeapons(type, weapons);
    amountOfWeapons = inAmountOfWeapons;
    populateDefences(type, defences);
    hull = inHull;
    shields = inShields;
    combatManeuver = inCombatManeuver;
    cargoHold = inCargoHold;
}

int Ship::determineCombatRoll()
{
    //Average of Pilot and Engineers CombatManeuverLvl
    int skillAverage = (crew.getPilot().getCombatManeuverLvl() + crew.getEngineer().getCombatManeuverLvl() + this->combatManeuver) / 3;
    return randomNumGenerator(skillAverage - 10, skillAverage);
}

void Ship::dealDamage(Weapon& weapon, WeaponsOfficer weaponsOfficer, Defence& defence, std::string tempCrewDeathRecord)
{
    int defenceMitigation = defence.getDefenceLvl() + ((this->crew.getWeaponsOfficer().getDefenceLvl() + this->crew.getEngineer().getDefenceSystemLvl()) / 2);
    if(shields > 0)
    {   
        //Deal shield damage with defence mitigation, min damage is 10
        shields -= std::max((weapon.getShieldDamage() + weaponsOfficer.getWeaponsLvl()) - defenceMitigation, 10);

        if(shields <= 0)
            std::cout << "The shields loss power leaving the hull exposed." << std::endl;
        else    
            std::cout << "The shields take a hit, but continue to function." << std::endl;
    }
    else
    {
        //Deal hull damage with defence mitigation, min damage is 10
        int damageDealt = std::max(weapon.getHullDamage() - defenceMitigation, 10);
        hull -= damageDealt;

        std::string damageAmount;
        if(damageDealt >= 100)
            damageAmount = "massive";
        else if(damageDealt >= 50  && damageDealt < 100)  
            damageAmount = "moderate";
        else
            damageAmount = "low";  

        if(hull <= 0)
            std::cout << "The hull takes catastrophic damage." << std::endl;
        else
            std::cout << "The hull takes " << damageAmount << " damage." << std::endl;

        damageCrew((weapon.getHullDamage() + weaponsOfficer.getWeaponsLvl()) - defenceMitigation, tempCrewDeathRecord);
    }
}

void Ship::dealDamage(Weapon& weapon, WeaponsOfficer weaponsOfficer, std::string tempCrewDeathRecord)
{
    if(shields > 0)
    {
        shields -= weapon.getShieldDamage() + weaponsOfficer.getWeaponsLvl();

        if(shields <= 0)
            std::cout << "The shields loss power leaving the hull exposed." << std::endl;
        else    
            std::cout << "The shields take a hit, but continue to function." << std::endl;
    }
    else
    {
        int damageDealt = weapon.getHullDamage() + weaponsOfficer.getWeaponsLvl();
        hull -= damageDealt;

        std::string damageAmount;
        if(damageDealt >= 100)
            damageAmount = "massive";
        else if(damageDealt >= 50  && damageDealt < 100)  
            damageAmount = "moderate";
        else
            damageAmount = "low";

        if(hull <= 0)
            std::cout << "The hull takes catastrophic damage." << std::endl;
        else
            std::cout << "The hull takes " << damageAmount << " damage." << std::endl;

        damageCrew(weapon.getHullDamage() + weaponsOfficer.getWeaponsLvl(), tempCrewDeathRecord);
    }
}

void Ship::dealAnomalyDamage(int damageDealt)
{
    if(this->hull <= 0)
            std::cout << "The hull takes catastrophic damage." << std::endl;
        else
            std::cout << "The hull takes massive damage." << std::endl;

    this->hull -= damageDealt;
}


bool Ship::checkFortitude()
{
    int fortitudeCheck = randomNumGenerator(0, 200);
    
    if(this->crew.getCaptain().getFortitudeLvl() > (fortitudeCheck - this->hull))
        return true;
    else
        return false;
}

void Ship::damageCrew(int damageDealt, std::string tempCrewDeathRecord)
{
    if(damageDealt > 10)
    {
        crew.killCrew(randomNumGenerator(0,damageDealt/10));
        if(damageDealt > 25)
            crew.killReplaceOfficer(this, tempCrewDeathRecord);
    }
}

void Ship::addWeapon(Weapon newWeapon)
{
    int arraySlot = amountOfWeapons + 1;
    amountOfWeapons++;
    this->weapons[arraySlot] = newWeapon;
}

Weapon& Ship::selectWeapon()
{
    int weaponSelect = randomNumGenerator(0,amountOfWeapons);
    return this->weapons[weaponSelect];
}

bool Ship::determineDefenceUse()
{
    if(this->crew.getWeaponsOfficer().getDefenceLvl() > randomNumGenerator(0,100))
        return true;
    else
        return false;
}

int Ship::determineAmountOfCurrentWeapons()
{
    for(int i = 0; i < 5; i++)
    {
        if(this->weapons[i].getName() == "")
        {
            return i;
        }
    }
    return 0;
}

int Ship::determineAmountOfWeapons()
{
    switch(typeNumber(type))
    {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return 3;
        case 5:
            return 4;
    }
}

int Ship::determineAmountOfDefences()
{
    switch(typeNumber(type))
    {
        case 0:
            return 1;
        case 1:
            return 1;
        case 2:
            return 1;
        case 3:
            return 1;
        case 4:
            return 2;
        case 5:
            return 2;
    }
}

void Ship::repairShip()
{
    int repair = getHull();
    switch(typeNumber(this->type))
    {
        case 0:
            repair += this->crew.getEngineer().getShipRepairLvl();
            this->hull = std::min(600, repair);
            std::cout << "Hull repaired: " << std::min(600, repair) << std::endl;
            this->shields = 60;
            break;
        case 1:
            repair += this->crew.getEngineer().getShipRepairLvl();
            this->hull = std::min(700, repair);
            std::cout << "Hull repaired: " << std::min(700, repair) << std::endl;
            this->shields = 70;
            break;
        case 2:
            repair += this->crew.getEngineer().getShipRepairLvl();
            this->hull = std::min(500, repair);
            std::cout << "Hull repaired: " << std::min(500, repair) << std::endl;
            this->shields = 50;
            break;
        case 3:
            repair += this->crew.getEngineer().getShipRepairLvl();
            this->hull = std::min(600, repair);
            std::cout << "Hull repaired: " << std::min(600, repair) << std::endl;
            this->shields = 60;
            break;
        case 4:
            repair += this->crew.getEngineer().getShipRepairLvl();
            this->hull = std::min(800, repair);
            std::cout << "Hull repaired: " << std::min(800, repair) << std::endl;
            this->shields = 80;
            break;
        case 5:
            repair += this->crew.getEngineer().getShipRepairLvl();
            this->hull = std::min(1000, repair);
            std::cout << "Hull repaired: " << std::min(1000, repair) << std::endl;
            this->shields = 100;
            break;
    }
}

//ExplorerShip Functions
ExplorerShip::ExplorerShip(std::string inName, std::string inType, int inSize, Crew inCrew, int inAmountOfWeapons, int inMiningLvl, int inHull, int inShields, int inCombatManeuver, CargoHold inCargoHold, LogBook inLogBook) 
    : Ship(inName, inType, inSize, inCrew, inAmountOfWeapons, inMiningLvl, inHull, inShields, inCombatManeuver, inCargoHold)
{
    this->logBook = inLogBook;
}

void ExplorerShip::takeSpoils(int liberatedFood, int liberatedFuel)
{
    while(getCargoHold().getCapacity() - getCargoHold().getTotalCargo() > 0 && (liberatedFood != 0 || liberatedFuel != 0))
    {
        if(liberatedFood > 0 && getCargoHold().getCapacity() - getCargoHold().getTotalCargo() > 0)
        {
            getCargoHold().buyFood(0);
            liberatedFood--;
        }
        
        if(liberatedFuel > 0 && getCargoHold().getCapacity() - getCargoHold().getTotalCargo() > 0)
        {
            getCargoHold().buyFuel(0);
            liberatedFuel--;
        }
    }
}

//LogBook Functions
LogBook::LogBook(int inStartMoney, int inStartFood, int inStartFuel, int inStartCrewNum)
{
    this->startMoney = inStartMoney;
    this->startFood = inStartFood;
    this->startFuel = inStartFuel;
    this->startCrewNum = inStartCrewNum;
}

void LogBook::addSectorLog(std::string sectorLog)
{
    sectorLogs.push_back(sectorLog);
}

void LogBook::addCrewDeathRecord(std::string crewDeathRecord)
{
    this->crewDeathRecords.push_back(crewDeathRecord);
}

//Weapon Functions
Weapon::Weapon(std::string inName, int inWeaponType, int inHullDamage, int inShieldDamage, int inDefenceDamage, int inRoundCooldown)
{
    this->name = inName;
    this->weaponType = inWeaponType; // 0 = Energy | 1 = Physical
    this->hullDamage = inHullDamage;
    this->shieldDamage = inShieldDamage;
    this->defenceDamage = inDefenceDamage;
    this->roundCooldown = inRoundCooldown;
    this->lastRoundUsed = 0;
    this->operational = true;
}

//Defence Functions
Defence::Defence(std::string inName, int inEffectiveType, int inDefenceLvl, int inRoundCooldown)
{
    this->name = inName;
    this->effectiveType = inEffectiveType;
    this->defenceLvl = inDefenceLvl;
    this->roundCooldown = inRoundCooldown;
    this->lastRoundUsed = 0;
    this->operational = true;
}

//CargoHold Functions
CargoHold::CargoHold(int inCapacity, int inMoney)
{
    this->capacity = inCapacity;
    this->totalCargo = 60;
    this->food = 30;
    this->fuel = 30;
    this->money = inMoney;
}

void CargoHold::addResource(Resource& newResource)
{
    int arraySlot = determineAmountOfResources();
    this->resources[arraySlot] = newResource;
    this->totalCargo += newResource.getSize();
}

//This is just used to change money for Alien Ships
void CargoHold::buyResource(int cost)
{
    this->money -= cost;
}

void CargoHold::sellResource(int arraySlot, int profit)
{
    this->totalCargo -= this->resources[arraySlot].getSize();
    this->resources[arraySlot] = Resource();
    std::cout << "Money: " << this->money << " -> ";
    this->money += profit;
    std::cout << this->money << std::endl;
}

void CargoHold::removeFood(int foodRemoved)
{
    this->food -= foodRemoved;
    this->totalCargo -= foodRemoved;
}

void CargoHold::buyFood(int foodCost)
{
    this->food++;
    this->totalCargo++;
    this->money -= foodCost;
}

void CargoHold::removeFuel(int fuelRemoved)
{
    this->fuel -= fuelRemoved;
    this->totalCargo -= fuelRemoved;
}

void CargoHold::buyFuel(int fuelCost)
{
    this->fuel++;
    this->totalCargo++;
    this->money -= fuelCost;
}

int CargoHold::determineAmountOfResources()
{
    for(int i = 0; i < 10; i++)
    {
        if(this->resources[i].getName() == "")
        {
            return i;
        }
    }
    return 0;
}

//Crew Functions
Crew::Crew(Captain inCaptain, Pilot inPilot, Engineer inEngineer, MiningOfficer inMiningOfficer, WeaponsOfficer inWeaponsOfficer,  int inCrewNum)
{
    this->captain = inCaptain;
    this->pilot = inPilot;
    this->engineer = inEngineer;
    this->miningOfficer = inMiningOfficer;
    this->weaponsOfficer = inWeaponsOfficer;
    this->crewNum = inCrewNum;
}

void Crew::killReplaceOfficer(Ship* ship, std::string tempCrewDeathRecord)
{
    int officerKilled = randomNumGenerator(1,5);
    switch(officerKilled)
    {
        case 1:
            //Captain Killed
            std::cout << "The Captain is killed" << std::endl;
            tempCrewDeathRecord += ".\nCaptain: " + this->captain.getTitle() + " " + this->captain.getName() + " was killed.";
            this->captain = Captain(randomNameGenerator(), randomNumGenerator(30,70), "Captain", std::max(1,this->captain.getSkillLvl().getLevel() - 1));
            this->crewNum--;
            break;
        case 2:
            //Pilot Killed
            std::cout << "The Pilot is killed" << std::endl;
            tempCrewDeathRecord += ".\nPilot: " + this->pilot.getTitle() + " " + this->pilot.getName() + " was killed.";
            this->pilot = Pilot(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", std::max(1,this->pilot.getSkillLvl().getLevel() - 1));
            this->crewNum--;
            break;
        case 3:
            //Engineer Killed
            std::cout << "The Engineer is killed" << std::endl;
            tempCrewDeathRecord += ".\nEngineer: " + this->engineer.getTitle() + " " + this->engineer.getName() + " was killed.";
            this->engineer = Engineer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", std::max(1,this->engineer.getSkillLvl().getLevel() - 1));
            this->crewNum--;
            break;
        case 4:
            //MiningOfficer Killed
            std::cout << "The Mining Officer is killed" << std::endl;
            tempCrewDeathRecord += ".\nMining Officer: " + this->miningOfficer.getTitle() + " " + this->miningOfficer.getName() + " was killed.";
            this->miningOfficer = MiningOfficer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", std::max(1,this->miningOfficer.getSkillLvl().getLevel() - 1));
            this->crewNum--;
            break;
        case 5:
            //WeaponsOfficer Killed
            std::cout << "The Weapons Officer is killed" << std::endl;
            tempCrewDeathRecord += ".\nWeapons Officer: " + this->weaponsOfficer.getTitle() + " " + this->weaponsOfficer.getName() + " was killed.";
            this->weaponsOfficer = WeaponsOfficer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", std::max(1,this->weaponsOfficer.getSkillLvl().getLevel() - 1));
            this->crewNum--;
            break;
    }

    if(ExplorerShip* exShip = dynamic_cast<ExplorerShip*>(ship))
    {
        (*exShip).getLogBook().addCrewDeathRecord(tempCrewDeathRecord);
    }
}

void Crew::killCrew(int numKilled)
{
    std::cout << numKilled << " crew members killed in the attack." << std::endl;
    crewNum -= numKilled;
    crewNum = std::max(0,crewNum);
    std::cout << "Crew Remaining: " << this->crewNum << std::endl;
}

//Officer Functions
Officer::Officer(std::string inName, int inAge, std::string inTitle, SkillLvl inSkillLvl)
{
    this->name = inName;
    this->age = inAge;
    this->title = inTitle;
    this->skillLvl = inSkillLvl;
}

//SkillLvl Functions
SkillLvl::SkillLvl(int inLevel)
{
    this->level = inLevel;
    this->setMaxMin();
}

void SkillLvl::setMaxMin()
{
    switch(this->level)
    {
        case 10: this->max = 100, this->min = 80;
            break;
        case 9: this->max = 90, this->min = 70;
            break;
        case 8: this->max = 80, this->min = 60;
            break;
        case 7: this->max = 70, this->min = 50;
            break;
        case 6: this->max = 60, this->min = 40;
            break;
        case 5: this->max = 50, this->min = 30;
            break;
        case 4: this->max = 40, this->min = 20;
            break;
        case 3: this->max = 30, this->min = 10;
            break;
        case 2: this->max = 20, this->min = 5;
            break;
        case 1: this->max = 10, this->min = 0;
            break;
    }
}

//Captain Functions
Captain::Captain(std::string inName, int inAge, std::string inTitle, SkillLvl inSkillLvl)
    : Officer(inName, inAge, inTitle, inSkillLvl)
{
    this->diplomacyLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax()); //Change all these to use function!!!
    this->tradingLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->fortitudeLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
}

//Pilot Functions
Pilot::Pilot(std::string inName, int inAge, std::string inTitle, SkillLvl inSkillLvl)
    : Officer(inName, inAge, inTitle, inSkillLvl)
{
    this->travelEfficencyLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->combatManeuverLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->conflictEvasionLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
}

//Engineer Functions
Engineer::Engineer(std::string inName, int inAge, std::string inTitle, SkillLvl inSkillLvl)
    : Officer(inName, inAge, inTitle, inSkillLvl)
{
    this->travelEfficencyLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->combatManeuverLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->conflictEvasionLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->defenceSystemLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->shipRepairLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
}

//Mining Officer Functions
MiningOfficer::MiningOfficer(std::string inName, int inAge, std::string inTitle, SkillLvl inSkillLvl)
    : Officer(inName, inAge, inTitle, inSkillLvl)
{
    this->miningAbilityLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
}

WeaponsOfficer::WeaponsOfficer(std::string inName, int inAge, std::string inTitle, SkillLvl inSkillLvl)
    : Officer(inName, inAge, inTitle, inSkillLvl)
{
    this->weaponsLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
    this->defencesLvl = randomNumGenerator(inSkillLvl.getMin(), inSkillLvl.getMax());
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

    LogBook logBook(cargoHold.getMoney(), cargoHold.getFood(), cargoHold.getFuel(), crew.getCrewNum()+5);

    return ExplorerShip(name, type, size, crew, amountOfWeapons, miningLvl, hull, shield, combatManeuver, cargoHold, logBook);
}

CargoHold generateExplorerShipCargoHold(std::string type)
{
    int capacity;
    int money;

    switch(typeNumber(type))
    {
        case 0:
            capacity = randomNumGenerator(7,8) * 30;//Mining
            money = 100;
        case 1:
            capacity = randomNumGenerator(9,10) * 30;//Trade
            money = 200;
        case 2:
            capacity = randomNumGenerator(3,4) * 30;//Corvette
            money = 100;
        case 3:
            capacity = randomNumGenerator(4,5) * 30;//Frigate
            money = 100;
        case 4:
            capacity = randomNumGenerator(6,7) * 30;//Destroyer
            money = 100;
        case 5:
            capacity = randomNumGenerator(6,7) * 30;//Battlecruiser
            money = 100;
    }

    return CargoHold(capacity, money);

}

std::string generateExplorerShipName()
{
    std::string shipNames[] = {"Ulysses", "Fenrir", "Illithid", "Behemoth", "Midgardsormr", "Hraesvelgr", "Nidhogg", "Elendil", "Gil-galad", "Theseus", "Marathon"};//Add more names maybe??

    return "JSE " + shipNames[randomNumGenerator(0,10)];
}

//Used for Explorer Crew!!! Not Generic
Crew generateExplorerShipCrew(int size)
{
    Captain captain(randomNameGenerator(), randomNumGenerator(30,70), "Captain", 10);
    Pilot pilot(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", 10);
    Engineer engineer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", 10);
    MiningOfficer miningOfficer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", 10);
    WeaponsOfficer weaponsOfficer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant", 10);
    int crewNum = generateCrewNum(size);

    return Crew(captain, pilot, engineer, miningOfficer, weaponsOfficer, crewNum);
} 

//Ship Generator Functions
Ship generateNewShip(Alien &alien, int difficultyModifier)
{
    //Used for alien ships
    std::string name = alien.getName() + " Ship";

    //Generate Type
    std::string type = generateType();

    //Generate Size (Based on Type)
    int size = generateSize(type);

    //Generate Crew (Crew number based on size)
    Crew crew = generateGenericCrew(size, difficultyModifier);

    //Generate Amount of Weapons
    int amountOfWeapons = generateAmountOfWeapons(type);

    //Generate miningLvl (Based on type)
    int miningLvl = generateMiningLvl(type);

    //Generate Hull (Based on type)
    int hull = generateHull(type);

    //Generate Shield (Based on type)
    int shield = generateShield(type);

    //Generate combatManeuver
    int combatManeuver = generateCombatManeuver(size);

    //Generate CargoHold (Based on type)
    CargoHold cargoHold = generateCargoHold(type);

    return Ship(name, type, size, crew, amountOfWeapons, miningLvl, hull, shield, combatManeuver, cargoHold);
}

CargoHold generateCargoHold(std::string type)
{
    int capacity;
    int money;

    switch(typeNumber(type))
    {
        case 0:
            capacity = randomNumGenerator(7,8) * 10;//Mining
            money = randomNumGenerator(1,5) * 100;
        case 1:
            capacity = randomNumGenerator(9,10) * 10;//Trade
            money = randomNumGenerator(5,10) * 100;
        case 2:
            capacity = randomNumGenerator(3,4) * 10;//Corvette
            money = randomNumGenerator(1,3) * 100;
        case 3:
            capacity = randomNumGenerator(4,5) * 10;//Frigate
            money = randomNumGenerator(1,4) * 100;
        case 4:
            capacity = randomNumGenerator(6,7) * 10;//Destroyer
            money = randomNumGenerator(1,5) * 100;
        case 5:
            capacity = randomNumGenerator(6,7) * 10;//Battlecruiser
            money = randomNumGenerator(1,6) * 100;
    }

    return CargoHold(capacity, money);

}

int generateCombatManeuver(int size)
{
    switch(size)
    {
        case 1:
            return 90;
        case 2:
            return 80;
        case 3:
            return 70;
        case 4:
            return 60;
        case 5:
            return 50;
        case 6:
            return 40;
        case 7:
            return 30;
        case 8:
            return 20;
        case 9:
            return 10;
        case 10:
            return 0;
    }
}

int generateShield(std::string type)
{
    switch(typeNumber(type))
    {
        case 0:
            return randomNumGenerator(5,6) * 10;//Mining
        case 1:
            return randomNumGenerator(5,7) * 10;//Trade
        case 2:
            return randomNumGenerator(3,5) * 10;//Corvette
        case 3:
            return randomNumGenerator(5,6) * 10;//Frigate
        case 4:
            return randomNumGenerator(7,8) * 10;//Destroyer
        case 5:
            return randomNumGenerator(9,10) * 10;//Battlecruiser
    }
}

int generateHull(std::string type)
{
    switch(typeNumber(type))
    {
        case 0:
            return randomNumGenerator(5,6) * 100;//Mining
        case 1:
            return randomNumGenerator(5,7) * 100;//Trade
        case 2:
            return randomNumGenerator(3,5) * 100;//Corvette
        case 3:
            return randomNumGenerator(5,6) * 100;//Frigate
        case 4:
            return randomNumGenerator(7,8) * 100;//Destroyer
        case 5:
            return randomNumGenerator(9,10) * 100;//Battlecruiser
    }
}

void populateDefences(std::string type, Defence defences[])
{
    switch(typeNumber(type))
    {
        case 0:
            defences[0] = generateDefence();
        case 1:
            defences[0] = generateDefence();
        case 2:
            defences[0] = generateDefence();
        case 3:
            defences[0] = generateDefence();
        case 4:
            for(int defence = 0; defence < 2; defence++)
            {
                defences[defence] = generateDefence();
            }
        case 5:
            for(int defence = 0; defence < 2; defence++)
            {
                defences[defence] = generateDefence();
            }
    }
}

Defence generateDefence()
{
    int weaponSelect = randomNumGenerator(0,1);

    switch(weaponSelect)
    {
        case 0: //Energy Defence
            return Defence("Energy Defence", 0, 70, 2);
        case 1: //Physical Defence
            return Defence("Defence Missiles", 1, 70, 2);
    }
}

void populateWeapons(std::string type, Weapon weapons[])
{
    switch(typeNumber(type))
    {
        case 0:
            weapons[0] = generateWeapon();
        case 1:
            for(int weapon = 0; weapon < 2; weapon++)
            {
                weapons[weapon] = generateWeapon();
            }
        case 2:
            for(int weapon = 0; weapon < 2; weapon++)
            {
                weapons[weapon] = generateWeapon();
            }
        case 3:
            for(int weapon = 0; weapon < 3; weapon++)
            {
                weapons[weapon] = generateWeapon();
            }
        case 4:
            for(int weapon = 0; weapon < 4; weapon++)
            {
                weapons[weapon] = generateWeapon();
            }
        case 5:
            for(int weapon = 0; weapon < 5; weapon++)
            {
                weapons[weapon] = generateWeapon();
            }
    }
}

int generateAmountOfWeapons(std::string type)
{
    switch(typeNumber(type))
    {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return 3;
        case 5:
            return 4;
    }
}

Weapon generateWeapon()
{
    int weaponSelect = randomNumGenerator(0,4);

    switch(weaponSelect)
    {
        case 0: //Laser
            return Weapon("Laser", 0, 30, 60, 20, 1);
        case 1: //Missiles
            return Weapon("Missile", 1, 70, 30, 20, 2);
        case 2: //EMP
            return Weapon("EMP", 0, 30, 80, 60, 3);
        case 3: //Fighters
            return Weapon("Fighters", 1, 50, 50, 70, 2);
        case 4: //Bombers
            return Weapon("Bombers", 1, 70, 30, 30, 2);
    }
}

//Generate Mining Lvl based on type
int generateMiningLvl(std::string type)
{
    switch(typeNumber(type))
    {
        case 0:
            return randomNumGenerator(80,100);
        case 1:
            return randomNumGenerator(60,80);
        case 2:
            return randomNumGenerator(10,30);
        case 3:
            return randomNumGenerator(20,40);
        case 4:
            return randomNumGenerator(30,50);
        case 5:
            return randomNumGenerator(30,50);
    }
}

//Used for Generic Crew !!!NOT EXPLORER CREW!!!
Crew generateGenericCrew(int size, int difficultyModifier)
{
    int max = difficultyModifier + 3;
    int min = difficultyModifier;

    Captain captain(randomNameGenerator(), randomNumGenerator(30,70), "Captain", randomNumGenerator(min,max));
    Pilot pilot(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant.", randomNumGenerator(min,max));
    Engineer engineer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant.", randomNumGenerator(min,max));
    MiningOfficer miningOfficer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant.", randomNumGenerator(min,max));
    WeaponsOfficer weaponsOfficer(randomNameGenerator(), randomNumGenerator(30,70), "Lieutenant.", randomNumGenerator(min,max));
    int crewNum = generateCrewNum(size);

    return Crew(captain, pilot, engineer, miningOfficer, weaponsOfficer, crewNum);
}

int generateCrewNum(int size)
{
    switch(size)
    {
        case 1:
            return randomNumGenerator(10,20);
        case 2:
            return randomNumGenerator(20,30);
        case 3:
            return randomNumGenerator(30,40);
        case 4:
            return randomNumGenerator(50,60);
        case 5:
            return randomNumGenerator(60,70);
        case 6:
            return randomNumGenerator(70,80);
        case 7:
            return randomNumGenerator(80,90);
        case 8:
            return randomNumGenerator(90,100);
        case 9:
            return randomNumGenerator(100,110);
        case 10:
            return randomNumGenerator(110,120);
    }
}

int generateSize(std::string type)
{
    switch(typeNumber(type))
    {
        case 0:
            return randomNumGenerator(4,8);//Mining
        case 1:
            return randomNumGenerator(2,6);//Trade
        case 2:
            return randomNumGenerator(1,4);//Corvette
        case 3:
            return randomNumGenerator(3,5);//Frigate
        case 4:
            return randomNumGenerator(5,7);//Destroyer
        case 5:
            return randomNumGenerator(7,10);//Battlecruiser
    }
}

//Name Generator !! Add More Names
std::string randomNameGenerator()
{
    std::string firstNames[] = {"John", "Aaron", "Fred", "Tom", "Tobius", "Davante", "Jaire", "David", "Mike", "Geronimo", 
                            "Ellis", "Beth", "Paige", "Megan", "India", "Kimberly", "Ashley", "Natlia", "Julie", "Lowri"};
    std::string lastNames[] = {"Baker", "Rogers", "Evens", "Fredrickson", "Apple", "Adams", "Alexander", "Bakhtiari", "Daniels", "Allison", "Davis", 
                            "O'Moore", "Green", "Reyes", "Woods", "Hopkins", "Middleton", "McCoy", "Bird", "Mullins"};

    std::string fullName = firstNames[randomNumGenerator(0,19)] + " " + lastNames[randomNumGenerator(0,19)];
    return fullName;
}

//Generates a random ship type
std::string generateType()
{
    std::string types[] = {"Trading Ship", "Corvette", "Frigate", "Destroyer", "Battlecruiser", "Mining Ship"};
    int shipSelect = randomNumGenerator(0,5);

    return types[shipSelect];
}

//Retrives the ships type as a number to be used in Switch
int typeNumber(std::string type)
{
    if(type.compare("Mining Ship") == 0)
        return 0;
    else if(type.compare("Trading Ship") == 0)
        return 1;
    else if(type.compare("Corvette") == 0)
        return 2;
    else if(type.compare("Frigate") == 0)
        return 3;
    else if(type.compare("Destroyer") == 0)
        return 4;
    else
        return 5;
}
