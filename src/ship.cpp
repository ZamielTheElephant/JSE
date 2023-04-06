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
    if (shields > 0)
    {
        //Deal shield damage with defence mitigation, min damage is 10
        shields -= std::max((weapon.getShieldDamage() + weaponsOfficer.getWeaponsLvl()) - defenceMitigation, 10);

        if (shields <= 0)
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
        if (damageDealt >= 100)
            damageAmount = "massive";
        else if (damageDealt >= 50 && damageDealt < 100)
            damageAmount = "moderate";
        else
            damageAmount = "low";

        if (hull <= 0)
            std::cout << "The hull takes catastrophic damage." << std::endl;
        else
            std::cout << "The hull takes " << damageAmount << " damage." << std::endl;

        damageCrew((weapon.getHullDamage() + weaponsOfficer.getWeaponsLvl()) - defenceMitigation, tempCrewDeathRecord);
    }
}

void Ship::dealDamage(Weapon& weapon, WeaponsOfficer weaponsOfficer, std::string tempCrewDeathRecord)
{
    if (shields > 0)
    {
        shields -= weapon.getShieldDamage() + weaponsOfficer.getWeaponsLvl();

        if (shields <= 0)
            std::cout << "The shields loss power leaving the hull exposed." << std::endl;
        else
            std::cout << "The shields take a hit, but continue to function." << std::endl;
    }
    else
    {
        int damageDealt = weapon.getHullDamage() + weaponsOfficer.getWeaponsLvl();
        hull -= damageDealt;

        std::string damageAmount;
        if (damageDealt >= 100)
            damageAmount = "massive";
        else if (damageDealt >= 50 && damageDealt < 100)
            damageAmount = "moderate";
        else
            damageAmount = "low";

        if (hull <= 0)
            std::cout << "The hull takes catastrophic damage." << std::endl;
        else
            std::cout << "The hull takes " << damageAmount << " damage." << std::endl;

        damageCrew(weapon.getHullDamage() + weaponsOfficer.getWeaponsLvl(), tempCrewDeathRecord);
    }
}

void Ship::dealAnomalyDamage(int damageDealt)
{
    if (this->hull <= 0)
        std::cout << "The hull takes catastrophic damage." << std::endl;
    else
        std::cout << "The hull takes massive damage." << std::endl;

    this->hull -= damageDealt;
}


bool Ship::checkFortitude()
{
    int fortitudeCheck = randomNumGenerator(0, 200);

    if (this->crew.getCaptain().getFortitudeLvl() > (fortitudeCheck - this->hull))
        return true;
    else
        return false;
}

void Ship::damageCrew(int damageDealt, std::string tempCrewDeathRecord)
{
    if (damageDealt > 10)
    {
        crew.killCrew(randomNumGenerator(0, damageDealt / 10));
        if (damageDealt > 25)
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
    int weaponSelect = randomNumGenerator(0, amountOfWeapons);
    return this->weapons[weaponSelect];
}

bool Ship::determineDefenceUse()
{
    if (this->crew.getWeaponsOfficer().getDefenceLvl() > randomNumGenerator(0, 100))
        return true;
    else
        return false;
}

int Ship::determineAmountOfCurrentWeapons()
{
    for (int i = 0; i < 5; i++)
    {
        if (this->weapons[i].getName() == "")
        {
            return i;
        }
    }
    return 0;
}

int Ship::determineAmountOfWeapons()
{
    switch (typeNumber(type))
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
    switch (typeNumber(type))
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
    switch (typeNumber(this->type))
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

//Ship Generator Functions
Ship generateNewShip(Alien& alien, int difficultyModifier)
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

int generateCombatManeuver(int size)
{
    switch (size)
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
    switch (typeNumber(type))
    {
    case 0:
        return randomNumGenerator(5, 6) * 10;//Mining
    case 1:
        return randomNumGenerator(5, 7) * 10;//Trade
    case 2:
        return randomNumGenerator(3, 5) * 10;//Corvette
    case 3:
        return randomNumGenerator(5, 6) * 10;//Frigate
    case 4:
        return randomNumGenerator(7, 8) * 10;//Destroyer
    case 5:
        return randomNumGenerator(9, 10) * 10;//Battlecruiser
    }
}

int generateHull(std::string type)
{
    switch (typeNumber(type))
    {
    case 0:
        return randomNumGenerator(5, 6) * 100;//Mining
    case 1:
        return randomNumGenerator(5, 7) * 100;//Trade
    case 2:
        return randomNumGenerator(3, 5) * 100;//Corvette
    case 3:
        return randomNumGenerator(5, 6) * 100;//Frigate
    case 4:
        return randomNumGenerator(7, 8) * 100;//Destroyer
    case 5:
        return randomNumGenerator(9, 10) * 100;//Battlecruiser
    }
}

void populateDefences(std::string type, Defence defences[])
{
    switch (typeNumber(type))
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
        for (int defence = 0; defence < 2; defence++)
        {
            defences[defence] = generateDefence();
        }
    case 5:
        for (int defence = 0; defence < 2; defence++)
        {
            defences[defence] = generateDefence();
        }
    }
}

void populateWeapons(std::string type, Weapon weapons[])
{
    switch (typeNumber(type))
    {
    case 0:
        weapons[0] = generateWeapon();
    case 1:
        for (int weapon = 0; weapon < 2; weapon++)
        {
            weapons[weapon] = generateWeapon();
        }
    case 2:
        for (int weapon = 0; weapon < 2; weapon++)
        {
            weapons[weapon] = generateWeapon();
        }
    case 3:
        for (int weapon = 0; weapon < 3; weapon++)
        {
            weapons[weapon] = generateWeapon();
        }
    case 4:
        for (int weapon = 0; weapon < 4; weapon++)
        {
            weapons[weapon] = generateWeapon();
        }
    case 5:
        for (int weapon = 0; weapon < 5; weapon++)
        {
            weapons[weapon] = generateWeapon();
        }
    }
}

int generateAmountOfWeapons(std::string type)
{
    switch (typeNumber(type))
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

//Generate Mining Lvl based on type
int generateMiningLvl(std::string type)
{
    switch (typeNumber(type))
    {
    case 0:
        return randomNumGenerator(80, 100);
    case 1:
        return randomNumGenerator(60, 80);
    case 2:
        return randomNumGenerator(10, 30);
    case 3:
        return randomNumGenerator(20, 40);
    case 4:
        return randomNumGenerator(30, 50);
    case 5:
        return randomNumGenerator(30, 50);
    }
}

int generateCrewNum(int size)
{
    switch (size)
    {
    case 1:
        return randomNumGenerator(10, 20);
    case 2:
        return randomNumGenerator(20, 30);
    case 3:
        return randomNumGenerator(30, 40);
    case 4:
        return randomNumGenerator(50, 60);
    case 5:
        return randomNumGenerator(60, 70);
    case 6:
        return randomNumGenerator(70, 80);
    case 7:
        return randomNumGenerator(80, 90);
    case 8:
        return randomNumGenerator(90, 100);
    case 9:
        return randomNumGenerator(100, 110);
    case 10:
        return randomNumGenerator(110, 120);
    }
}

int generateSize(std::string type)
{
    switch (typeNumber(type))
    {
    case 0:
        return randomNumGenerator(4, 8);//Mining
    case 1:
        return randomNumGenerator(2, 6);//Trade
    case 2:
        return randomNumGenerator(1, 4);//Corvette
    case 3:
        return randomNumGenerator(3, 5);//Frigate
    case 4:
        return randomNumGenerator(5, 7);//Destroyer
    case 5:
        return randomNumGenerator(7, 10);//Battlecruiser
    }
}

//Generates a random ship type
std::string generateType()
{
    std::string types[] = { "Trading Ship", "Corvette", "Frigate", "Destroyer", "Battlecruiser", "Mining Ship" };
    int shipSelect = randomNumGenerator(0, 5);

    return types[shipSelect];
}

//Retrives the ships type as a number to be used in Switch
int typeNumber(std::string type)
{
    if (type.compare("Mining Ship") == 0)
        return 0;
    else if (type.compare("Trading Ship") == 0)
        return 1;
    else if (type.compare("Corvette") == 0)
        return 2;
    else if (type.compare("Frigate") == 0)
        return 3;
    else if (type.compare("Destroyer") == 0)
        return 4;
    else
        return 5;
}