#include "mainJSE.h"
#include <random>

static std::default_random_engine randEng;

void resolveSector(ExplorerShip& exShip, int sectorNum)
{
    //TESTING SHIP SECTOR
    resolvePlanetSector(exShip, difficultyModifier(sectorNum));
    /*switch(determineSectorType())
        {
            case 0:
                resolveAnomalySector(exShip);
                break;
            case 1:
                resolveEmptySector(exShip);
                break;
            case 2:
                resolveTradeSector(exShip);
                break;
            case 3:
                resolvePlanetSector(exShip, difficultyModifier(sectorNum));
                break;
            case 4:
                resolveShipSector(exShip, difficultyModifier(sectorNum));
                break;
        }*/
}

int difficultyModifier(int sectorNum)
{
    if(sectorNum <= 20)
        return 5;
    else if(sectorNum > 20 && sectorNum <= 30)
        return 10;
    else
        return 15;
}

int determineSectorType()
{
    int typeRandomiser = randomNumGenerator(1,100);

    if(typeRandomiser <= 10)
        return 0; //Anomaly
    else if(typeRandomiser > 10 && typeRandomiser <= 25)
        return 1; //Empty
    else if(typeRandomiser > 25 && typeRandomiser <= 40)
        return 2; //Trade
    else if(typeRandomiser > 40 && typeRandomiser <= 65)
        return 3; //Planet
    else
        return 4; //Ship
}

//Ship Sector Functions
void resolveShipSector(ExplorerShip& exShip, int difficultyModifier)
{
    ShipSector sector = generateShipSector(difficultyModifier);
    std::cout << "The " << exShip.getName() << " arrives in Sector: " << sector.getName() << std::endl;
    std::cout << "A " << sector.getAlien().getName() << " " << sector.getAlienShip().getType() << " opens communications." << std::endl;
    //Diplomacy check
    if(diplomacyCheck(exShip, sector))
    {
        std::cout << "Trade Talks" << std::endl;
        if(tradeTalksCheck(exShip, sector))
        {
            //Trade
            //resolveTrade(exShip);
        }
        else
        {
            std::cout << "No Trade" << std::endl;
        }
    }
    else
    {
        std::cout << "Battle" << std::endl;
        Ship alienShip = sector.getAlienShip();

        if(resolveBattle(exShip, alienShip))
        {
            std::cout << "Victory" << std::endl;
        }
        else
        {
            std::cout << "Defeat" << std::endl;
        }
    }

    //report and end
}

bool resolveBattle(ExplorerShip& exShip, Ship& alienShip)
{
    int currentRound = 0;
    Ship* ships[2];

    int exShipCombatRoll = randomNumGenerator(0, exShip.determineCombatRoll());
    int alienShipCombatRoll = randomNumGenerator(0, alienShip.determineCombatRoll());

    if(exShipCombatRoll >= alienShipCombatRoll)
    {
        ships[0] = &exShip;
        ships[1] = &alienShip;
    }
    else
    {
        ships[0] = &alienShip;
        ships[1] = &exShip;
    }

    while(exShip.getHull() != 0 && alienShip.getHull() != 0)
    {
        std::cout << "The " << (*ships[0]).getName() << " attacks" << std::endl;//Test
        
        //Select first ships weapon
        Weapon shipAWeapon = (*ships[0]).selectWeapon(currentRound);
        std::cout << "Selected Weapon -> " << shipAWeapon.getName() << std::endl;
        
        //Fire selected weapon
        std::cout << "Fire" << std::endl;
        fireWeapon(shipAWeapon, (*ships[0]).getCrew().getWeaponsOfficer(), *ships[1], currentRound);

        //Check if ship has been destroyed
        if((*ships[1]).getHull() <= 0)
        {
            std::cout << (*ships[1]).getName() << " has been destroyed." << std::endl;
            if(&(*ships[1]) == &exShip)
                return false;
            else if(&(*ships[1]) == &alienShip)
                return true;
        }

        //Check if any crew remain
        if((*ships[1]).getCrew().getCrewNum() <= 0)
        {
            std::cout << "Not enough crew to operate. Remaining crew surrender." << std::endl;
            if(&(*ships[1]) == &exShip)
                return false;
            else if(&(*ships[1]) == &alienShip)
                return true;
        }

        //Check to see if ship flees
        if(!(*ships[1]).checkFortitude())
        {
            std::cout << "Ship 2 Ran away" << std::endl;
            //Check which ship fled
            if(&(*ships[1]) == &exShip)
                return false;
            else if(&(*ships[1]) == &alienShip)
                return true;
        }
            
        std::cout << "The " << (*ships[1]).getName() << " attacks" << std::endl;//Test

        //Select second ships weapon
        Weapon shipBWeapon = (*ships[1]).selectWeapon(currentRound);
        std::cout << "Selected Weapon -> " << shipBWeapon.getName() << std::endl;

        //Fire selected weapon
        std::cout << "Fire" << std::endl;
        fireWeapon(shipBWeapon, (*ships[1]).getCrew().getWeaponsOfficer(), *ships[0], currentRound);

        //Check if ship has been destroyed
        if((*ships[0]).getHull() <= 0)
        {
            std::cout << (*ships[0]).getName() << " has been destroyed." << std::endl;
            if(&(*ships[0]) == &exShip)
                return false;
            else if(&(*ships[0]) == &alienShip)
                return true;
        }
        
        //Checks if any crew remain
        if((*ships[0]).getCrew().getCrewNum() <= 0)
        {
            std::cout << "Not enough crew to operate. Remaining crew surrender." << std::endl;
            if(&(*ships[0]) == &exShip)
                return false;
            else if(&(*ships[0]) == &alienShip)
                return true;
        }

        if(!(*ships[0]).checkFortitude())
        {
            //Check which ship fled
            std::cout << "Ship 1 Ran away" << std::endl;
            if(&(*ships[0]) == &exShip)
                return false;
            else if(&(*ships[0]) == &alienShip)
                return true;
        }

        currentRound++;
    }
}

void fireWeapon(Weapon &weapon, WeaponsOfficer weaponsOfficer, Ship &ship, int currentRound)
{
    if(checkHit(ship))
    {
        std::cout << "Attack from " << weapon.getName() << " hits." << std::endl;
        if(ship.determineDefenceUse())
        {
            std::cout << "Defence... Test" << std::endl;
            Defence defence = ship.getDefences()[randomNumGenerator(0,ship.determineAmountOfDefences()-1)];
            if(weapon.getWeaponType() == defence.getEffectiveType())
            {
                //Use Defence
                std::cout << "Defence Used" << std::endl;
                ship.dealDamage(weapon, weaponsOfficer, defence);
                return;
            }
        }

        std::cout << "No Defence" << std::endl;
        //Don't use defences
        ship.dealDamage(weapon, weaponsOfficer);
    }
    else
    {
        std::cout << "Attack from " << weapon.getName() << " missed." << std::endl;
    }
}

bool checkHit(Ship &ship)
{
    int shipCombatManeuver = ship.determineCombatRoll();
    std::cout << "Test... CombatManeuver: " << shipCombatManeuver << std::endl;

    if(shipCombatManeuver < randomNumGenerator(0, 100))
    {
        //Attack Hits
        return true;
    }
    else
    {
        //Attack Misses
        return false;
    }

}

bool checkDefeatConditions(Ship &ship)
{
    if(ship.getHull() <= 0 || ship.getCrew().getCrewNum() <= 0)
        return true;
    else
        return false;
}

bool tradeTalksCheck(ExplorerShip &exShip, ShipSector &sector)
{
    int captainDiplomacyRoll = randomNumGenerator(0,exShip.getCrew().getCaptain().getDiplomacyLvl());
    int alienIntellegence = sector.getAlien().getIntellegence();

    if(captainDiplomacyRoll > alienIntellegence)
        return true;
    else  
        return false;
    
}

bool diplomacyCheck(ExplorerShip &exShip, ShipSector &sector)
{
    int captainDiplomacyRoll = randomNumGenerator(0,exShip.getCrew().getCaptain().getDiplomacyLvl());
    int alienHostility = sector.getAlien().getHostility();

    if(captainDiplomacyRoll > alienHostility)
        return true;
    else
        return false;
}

//Planet Sector Functions
void resolvePlanetSector(ExplorerShip& exShip, int difficultyModifier)
{
    PlanetSector sector = generatePlanetSector(difficultyModifier);
    std::cout << sector.getType() << std::endl;

    //Check if the Planet is populated
    if(sector.getAlien().getName() != "")
    {
        if(diplomacyCheck(exShip, sector))
        {
            std::cout << "Trade Talks" << std::endl;
            if(tradeTalksCheck(exShip, sector))
            {
                //Trade
                resolveTrade(exShip);
            }
            else
            {
                std::cout << "No Trade" << std::endl;
            }
        }
        else
        {
            std::cout << "Battle" << std::endl;
            Ship alienShip = sector.getPlanet().getShip();
            if(resolveBattle(exShip, alienShip))
            {
                std::cout << "Victory" << std::endl;
            }
            else
            {
                std::cout << "Defeat" << std::endl;
            }
        }
    }
    else
    {
        //Go to Planet and mine
        Planet planet = sector.getPlanet();
        resolvePlanetMine(exShip, planet);
    }

    //Report and end
}

void resolveTrade(ExplorerShip &exShip, Planet &planet)
{
    int tradingModifier = exShip.getCrew().getCaptain().getTradingLvl() - planet.getAlienShip().getCrew().getCaptain().getTradingLvl();

    if(exShip.getCargoHold().determineAmountOfResources() >= 0)
    {
        //Sell Resources
        for(int i = exShip.getCargoHold().determineAmountOfResources(); i >= 0; i--)
        {
            int resourceSellValue = (*(exShip.getCargoHold().getResources() + i)).getValue() + tradingModifier;
            if(planet.getAlienShip().getCargoHold().getMoney() < resourceSellValue)
            {
                //Alien can afford it
                planet.getAlienShip().getCargoHold().setMoney(planet.getAlienShip().getCargoHold().getMoney() - resourceSellValue);
                exShip.getCargoHold().removeResource(i);
            }
            else
            {
                //Aliens cannot afford it
                std::cout << "Alien can not afford the resource" << std::endl;
                break;
            }

        }
    }
    
    //Flip tradeModifier for selling 
    tradingModifier = planet.getAlienShip().getCrew().getCaptain().getTradingLvl() - exShip.getCrew().getCaptain().getTradingLvl();
    int cargoSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();

    if(exShip.getCargoHold().getMoney() > 0 && cargoSpaceRemaining > 0)
    {
        if(exShip.getCargoHold().getFood() < exShip.getCargoHold().getFuel())
        {
            //Find Food cost
            int foodCost = std::max(5,tradingModifier);
            while(exShip.getCargoHold().getMoney() > foodCost && planet.getAlienShip().getCargoHold().getFood() > 0 && exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo() > 0)
            {
                //Buy Food until no more money, no more food to buy or no more space
                exShip.getCargoHold().buyFood(foodCost);
                planet.getAlienShip().removeFood(1);
            }
        }
        else
        {
            //Find Fuel cost
            int fuelCost = std::max(10,tradingModifier);
            while(exShip.getCargoHold().getMoney() > fuelCost && planet.getAlienShip().getCargoHold().getFuel() > 0 && exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo() > 0)
            {
                //Buy Fuel until no more money, no more fuel to buy or no more space
                exShip.getCargoHold().buyFuel(fuelCost);
                planet.getAlienShip().removeFuel(1);
            }
        }
    }
    else
    {
        //Nothing to buy or sell
        std::cout << "Cant Buy Food or Fuel" << std::endl;
    }
}

bool diplomacyCheck(ExplorerShip &exShip, PlanetSector &sector)
{
    int captainDiplomacyRoll = randomNumGenerator(0,exShip.getCrew().getCaptain().getDiplomacyLvl());
    int alienHostility = sector.getAlien().getHostility();

    if(captainDiplomacyRoll > alienHostility)
        return true;
    else
        return false;
}

bool tradeTalksCheck(ExplorerShip &exShip, PlanetSector &sector)
{
    int captainDiplomacyRoll = randomNumGenerator(0,exShip.getCrew().getCaptain().getDiplomacyLvl());
    int alienIntellegence = sector.getAlien().getIntellegence();

    if(captainDiplomacyRoll > alienIntellegence)
        return true;
    else  
        return false;
    
}

void resolvePlanetMine(ExplorerShip &exShip, Planet &planet)
{
    Resource resource = planet.getResource();
    std::cout << resource.getName() << std::endl;
    int cargoSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();
    std::cout << cargoSpaceRemaining << std::endl;
    if(cargoSpaceRemaining > 0 && cargoSpaceRemaining >= resource.getSize() && exShip.getCargoHold().determineAmountOfResources() < 10)
    {
        if(exShip.getCrew().getMiningOfficer().getMiningAbilityLvl() > randomNumGenerator(0,resource.getMiningDifficulty() * 10))
        {
            //Mining Successfull
            exShip.getCargoHold().addResource(resource);
        }
        else
        {
            //Mining Failed
            std::cout << "Mining of " << resource.getName() << " was unsuccessful." << std::endl;
        }
    }
}

void resolveTradeSector(ExplorerShip& exShip)
{
    TradeSector sector = generateTradeSector();
    std::cout << sector.getType() << std::endl;

    //Resolve trade
}

void resolveEmptySector(ExplorerShip& exShip)
{
    EmptySector sector = generateEmptySector();
    std::cout << sector.getType() << std::endl;

    //Describe the emptiness of space???
}

void resolveAnomalySector(ExplorerShip& exShip)
{
    std::cout << "Anomaly" << std::endl;
    //TBD
}

void setRandomSeed()
{
    std::random_device randomDevice;
    randEng.seed(randomDevice());
}

int randomNumGenerator(int min, int max)
{
    std::uniform_int_distribution<unsigned> uniform(min,max);

    return uniform(randEng);
}