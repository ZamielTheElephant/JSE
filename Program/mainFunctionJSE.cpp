#include "mainJSE.h"
#include <random>

static std::default_random_engine randEng;

void resolveSector(ExplorerShip& exShip, int sectorNum)
{
    switch(determineSectorType())
        {
            case 0:
                resolveAnomalySector(exShip, difficultyModifier(sectorNum));
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
        }
}

int difficultyModifier(int sectorNum)
{
    if(sectorNum <= 20)
        return 2;
    else if(sectorNum > 20 && sectorNum <= 30)
        return 5;
    else
        return 7;
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
    std::string sectorLog;
    ShipSector sector = generateShipSector(difficultyModifier);
    std::cout << sector.getType() << std::endl;
    Ship alienShip = sector.getAlienShip();
    sectorLog = "---Sector " + sector.getName() + "---\n";
    std::cout << "The " << exShip.getName() << " arrives in Sector: " << sector.getName() << std::endl;
    sectorLog += "Encounted a " + sector.getAlien().getName() + " " + sector.getAlienShip().getType() + "\n";
    
    if(sector.getAlien().getName() != "Drul")
        std::cout << "A " << sector.getAlien().getName() << " " << sector.getAlienShip().getType() << " opens communications." << std::endl;
    else
        std::cout << "A " << sector.getAlien().getName() << " " << sector.getAlienShip().getType() << " begins to approach." << std::endl;
    
    //Determine if battle will take place
    if(diplomacyCheck(exShip, sector))
    {
        sectorLog += "Situation De-escalated ... Commenced Trade Negotiation.\n";
        std::cout << "Trade Negotiations Commence." << std::endl;
        //Determine if trade occurs
        if(tradeTalksCheck(exShip, sector))
        {
            //Trade
            sectorLog += "Negotiation was Successful\n";
            std::cout << "The Negotiations were Successful." << std::endl;
            resolveTrade(exShip,alienShip,sectorLog);
        }
        else
        {
            sectorLog += "Negotiation was Unsuccessful\n";
            std::cout << "The Negotiations were Unsuccessful" << std::endl;
        }
    }
    else
    {
        if(sector.getAlien().getName() == "Drul")
        {
            std::cout << "The Drul " << sector.getAlienShip().getType() << " immediately attacks when in range." << std::endl;
            sectorLog += "Battle broke out immediately\n";
        }
        else
        {
            std::cout << "The situation escalates. Both Ships move to attack." << std::endl;
            sectorLog += "Situation Escalated ... Battle Commenced.\n";
        }

        if(resolveBattle(exShip, alienShip, sectorLog, sector.getName()))
        {
            std::cout << "\n>>>>>>>>>>> Victory <<<<<<<<<<<\n" << std::endl;
        }
        else
        {
            std::cout << "\n>>>>>>>>>>> Defeat <<<<<<<<<<<\n" << std::endl;
        }
    }

    //Add the sector Log to the LogBook
    exShip.getLogBook().addSectorLog(sectorLog);
}

//Determines the result of Battle
bool resolveBattle(ExplorerShip& exShip, Ship& alienShip, std::string& sectorLog, std::string sectorName)
{
    std::string tempCrewDeathRecord;
    int currentRound = 0;
    Ship* ships[2];

    int exShipCombatRoll = randomNumGenerator(0, exShip.determineCombatRoll());
    int alienShipCombatRoll = randomNumGenerator(0, alienShip.determineCombatRoll());

    //Determine Turn order
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

    //Continue battle till one of the ships is destroyed
    while(exShip.getHull() != 0 && alienShip.getHull() != 0)
    { 
        std::cout << "\n############ " <<  (*ships[0]).getName() << " ############" << std::endl;
        //Select first ships weapon
        Weapon shipAWeapon = (*ships[0]).selectWeapon();
        
        //Fire selected weapon
        std::cout << "The " << (*ships[0]).getName();
        tempCrewDeathRecord = "\nSector " + sectorName + ": during a battle with a " + (*ships[0]).getName();
        fireWeapon(shipAWeapon, (*ships[0]).getCrew().getWeaponsOfficer(), *ships[1], currentRound, tempCrewDeathRecord);

        //Check if ship has been destroyed
        if((*ships[1]).getHull() <= 0)
        {
            std::cout << "\n" << (*ships[1]).getName() << " has been destroyed." << std::endl;
            if(&(*ships[1]) == &exShip)
            {
                sectorLog += "The " + exShip.getName() + " was destroyed in the battle.\n";
                exShip.getLogBook().setFinalState("Destoryed");
                return false;
            }
            else if(&(*ships[1]) == &alienShip)
            {
                sectorLog += "The " + alienShip.getName() + " was destroyed in the battle.\n";
                exShip.takeSpoils((alienShip.getCargoHold().getFood()/4), (alienShip.getCargoHold().getFuel()/4));
                return true;
            }
        }

        //Check if any crew remain
        if((*ships[1]).getCrew().getCrewNum() <= 0)
        {
            std::cout << "\nNot enough crew to operate. Remaining crew surrender." << std::endl;
            if(&(*ships[1]) == &exShip)
            {
                sectorLog += "The " + exShip.getName() + " surrendered, due to overwhelming crew casualties.\n";
                exShip.getLogBook().setFinalState("Surrendered");
                return false;
            }
            else if(&(*ships[1]) == &alienShip)
            {
                sectorLog += "The " + alienShip.getName() + " surrendered, due to overwhelming crew casualties.\n";
                exShip.takeSpoils((alienShip.getCargoHold().getFood()/2), (alienShip.getCargoHold().getFuel()/2));
                return true;
            }
        }

        //Check to see if ship flees
        if(!(*ships[1]).checkFortitude())
        {
            std::cout << "\nThe " + (*ships[1]).getName() + " flees the battle." << std::endl;
            sectorLog += "The " + (*ships[1]).getName() + " fled the battle.\n";

            //Check which ship fled
            if(&(*ships[1]) == &exShip)
                return false;
            else if(&(*ships[1]) == &alienShip)
                return true;
        }    
    
        std::cout << "\n############ " <<  (*ships[1]).getName() << " ############" << std::endl;
        //Select second ships weapon
        Weapon shipBWeapon = (*ships[1]).selectWeapon();

        //Fire selected weapon
        std::cout << "The " << (*ships[1]).getName();
        tempCrewDeathRecord = "\nSector " + sectorName + ": during a battle with a " + (*ships[1]).getName();
        fireWeapon(shipBWeapon, (*ships[1]).getCrew().getWeaponsOfficer(), *ships[0], currentRound, tempCrewDeathRecord);

        //Check if ship has been destroyed
        if((*ships[0]).getHull() <= 0)
        {
            std::cout << "\n" << (*ships[0]).getName() << " has been destroyed." << std::endl;
            if(&(*ships[0]) == &exShip)
            {
                sectorLog += "The " + exShip.getName() + " was destroyed in the battle.\n";
                exShip.getLogBook().setFinalState("Destoryed");
                return false;
            }
            else if(&(*ships[0]) == &alienShip)
            {
                sectorLog += "The " + alienShip.getName() + " was destroyed in the battle.\n";
                exShip.takeSpoils((alienShip.getCargoHold().getFood()/4), (alienShip.getCargoHold().getFuel()/4));
                return true;
            }
        }
        
        //Checks if any crew remain
        if((*ships[0]).getCrew().getCrewNum() <= 0)
        {
            std::cout << "\nNot enough crew to operate. Remaining crew surrender." << std::endl;
            if(&(*ships[0]) == &exShip)
            {
                sectorLog += "The " + exShip.getName() + " surrendered, due to overwhelming crew casualties.\n";
                exShip.getLogBook().setFinalState("Surrendered");
                //ExplorerShip defeated
                return false;
            }
            else if(&(*ships[0]) == &alienShip)
            {
                sectorLog += "The " + alienShip.getName() + " surrendered, due to overwhelming crew casualties.\n";
                exShip.takeSpoils((alienShip.getCargoHold().getFood()/2), (alienShip.getCargoHold().getFuel()/2));
                //Alien Ship defeated
                return true;
            }
        }

        if(!(*ships[0]).checkFortitude())
        {
            std::cout << "\nThe " + (*ships[0]).getName() + " flees the battle." << std::endl;
            sectorLog += "The " + (*ships[0]).getName() + " fled the battle.\n";

            //Check which ship fled
            if(&(*ships[0]) == &exShip)
                return false;
            else if(&(*ships[0]) == &alienShip)
                return true;
        }

        currentRound++;
    }
}

void fireWeapon(Weapon &weapon, WeaponsOfficer weaponsOfficer, Ship &ship, int currentRound, std::string& tempCrewDeathRecord)
{
    if(checkHit(ship))
    {
        if(weapon.getName() == "Fighters")
        {
            tempCrewDeathRecord += " the " + ship.getName() + " was hit by a fighter run";
            std::cout << " sends Fighters for a strafing run on the " << ship.getName() << "." << std::endl;
        }
        else if(weapon.getName() == "Bombers")
        {
            tempCrewDeathRecord += " the " + ship.getName() + " was hit by a bomber run";
            std::cout << " sends Bombers for a bombing run on the " << ship.getName() << "." << std::endl;
        }
        else
        {
            tempCrewDeathRecord += " the " + ship.getName() + " was hit by a " + weapon.getName();
            std::cout << " fires a " << weapon.getName() << " on the " << ship.getName() << "." << std::endl;
        }

        if(ship.determineDefenceUse())
        {
            Defence defence = ship.getDefences()[randomNumGenerator(0,ship.determineAmountOfDefences()-1)];
            if(weapon.getWeaponType() == defence.getEffectiveType())
            {
                //Use Defences
                std::cout << "The " << ship.getName() << " activates its " << defence.getName() << "." << std::endl;
                ship.dealDamage(weapon, weaponsOfficer, defence, tempCrewDeathRecord);
                return;
            }
        }
        //Don't use defences
        ship.dealDamage(weapon, weaponsOfficer, tempCrewDeathRecord);
    }
    else
    {
        if(weapon.getName() == "Fighters" || weapon.getName() == "Bombers")
            std::cout << " sends " << weapon.getName() << ", but they miss their target." << std::endl;
        else
            std::cout << " fires a " << weapon.getName() << ", but it misses the target." << std::endl;
    }
}

bool checkHit(Ship &ship)
{
    int shipCombatManeuver = ship.determineCombatRoll();

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
    int captainDiplomacyRoll = randomNumGenerator(0,100) - randomNumGenerator(0,exShip.getCrew().getCaptain().getDiplomacyLvl());
    int alienIntellegence = sector.getAlien().getIntellegence();

    if(captainDiplomacyRoll < alienIntellegence)
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
    std::string sectorLog;
    PlanetSector sector = generatePlanetSector(difficultyModifier);
    Ship alienShip = sector.getPlanet().getShip();
    std::cout << sector.getType() << std::endl;

    sectorLog = "---Sector " + sector.getName() + "---\n";
    std::cout << "The " << exShip.getName() << " arrives in Sector: " << sector.getName() << std::endl;
    sectorLog += "Arrived at the " + sector.getPlanet().getType() + " " + sector.getPlanet().getName() + ".\n";

    //Check if the Planet is populated
    if(sector.getAlien().getName() != "")
    {
        std::cout << sector.getAlien().getName() << " Planet: " << sector.getPlanet().getName() << std::endl;
        sectorLog += "A Ship was sent from the planet.\n";
        std::cout << "A Ship is detected approaching from the surface." << std::endl;

        if(sector.getAlien().getName() != "Drul")
            std::cout << "The " << sector.getAlien().getName() << " " << sector.getPlanet().getShip().getType() << " opened communications." << std::endl;

        if(diplomacyCheck(exShip, sector))
        {
            sectorLog += "Situation De-escalated ... Commenced Trade Negotiation.\n";
            std::cout << "Trade Negotiations Commence." << std::endl;
            if(tradeTalksCheck(exShip, sector))
            {
                //Trade
                std::cout << "The Negotiations were Successful." << std::endl;
                sectorLog += "Trade Negotiation was Successful\n";
                resolveTrade(exShip,alienShip,sectorLog);
            }
            else
            {
                sectorLog += "Negotiation was Unsuccessful\n";
                std::cout << "The Negotiations were Unsuccessful" << std::endl;
            }
        }
        else
        {
            if(sector.getAlien().getName() == "Drul")
            {
                std::cout << "The Drul " << sector.getPlanet().getShip().getType() << " immediately attacks when in range." << std::endl;
                sectorLog += "Battle broke out immediately\n";
            }
            else
            {
                std::cout << "The situation escalates. Both Ships move to attack." << std::endl;
                sectorLog += "Situation Escalated ... Battle Commenced.\n";
            }
            
            if(resolveBattle(exShip, alienShip, sectorLog, sector.getName()))
            {
                std::cout << "\n>>>>>>>>>>> Victory <<<<<<<<<<<\n" << std::endl;
            }
            else
            {
                std::cout << "\n>>>>>>>>>>> Defeat <<<<<<<<<<<\n" << std::endl;
            }
        }
    }
    else
    {
        //Go to Planet and mine
        std::cout << "Planet: " << sector.getPlanet().getName() << std::endl;
        std::cout << "No civilized life detected on the Planet." << std::endl;
        sectorLog += "No civilized life was detected on Planet\n";
        Planet planet = sector.getPlanet();
        resolvePlanetMine(exShip, planet, sectorLog);
    }

    //Report and end
    exShip.getLogBook().addSectorLog(sectorLog);
}

void resolveTrade(ExplorerShip &exShip, Ship &alienShip, std::string& sectorLog)
{
    int tradingModifier = exShip.getCrew().getCaptain().getTradingLvl() - alienShip.getCrew().getCaptain().getTradingLvl();

    if((*exShip.getCargoHold().getResources()).getName() != "")
    {
        int resourcesSold = 0;
        //Sell Resources
        for(int i = exShip.getCargoHold().determineAmountOfResources() - 1; i >= 0; i--)
        {
            Resource sellResource = exShip.getCargoHold().getResources()[i];
            int resourceSellValue = std::max(sellResource.getMinValue(), sellResource.getValue() + tradingModifier);
            if(alienShip.getCargoHold().getMoney() > resourceSellValue)
            {
                //Alien can afford it
                std::cout << "Ship purchased -> " << sellResource.getName() << std::endl;
                alienShip.getCargoHold().buyResource(resourceSellValue);
                exShip.getCargoHold().sellResource(i, resourceSellValue);
                resourcesSold++;
            }
            else
            {
                //Aliens cannot afford it
                std::cout << "Alien can not afford the resource" << std::endl;
                break;
            }
        }

        if(resourcesSold > 0)
            sectorLog += "Sold " + std::to_string(resourcesSold) + " mined resources to the " + alienShip.getName() + ".\n";
        else
            sectorLog += "Unable to sell mined resources\n";
    }
    else
    {
        sectorLog += "No mined resources to sell\n";
        std::cout << "No resources to Sell" << std::endl;
    }
    
    //Flip tradeModifier for selling 
    tradingModifier = alienShip.getCrew().getCaptain().getTradingLvl() - exShip.getCrew().getCaptain().getTradingLvl();
    int cargoSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();

    if(exShip.getCargoHold().getMoney() >= 5 && cargoSpaceRemaining > 0)
    {
        sectorLog += "Purchased supplies\n";
        std::cout << "Purchasing Supplies" << std::endl;
        //Find Food and Fuel cost
        int resourceCost = std::max(5,tradingModifier);
        int exShipSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();
        while(exShip.getCargoHold().getMoney() >= resourceCost && exShipSpaceRemaining > 0 && (alienShip.getCargoHold().getFood() >= 5 || alienShip.getCargoHold().getFuel() >= 5))
        {

            if(exShip.getCargoHold().getMoney() >= resourceCost && alienShip.getCargoHold().getFood() >= 5 && exShipSpaceRemaining > 0)
            {
                //Buy Food until no more money, no more food to buy or no more space
                exShip.getCargoHold().buyFood(resourceCost);
                alienShip.getCargoHold().removeFood(1);
            }
            
            //Update the space remaining
            exShipSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();

            if(exShip.getCargoHold().getMoney() >= resourceCost && alienShip.getCargoHold().getFuel() >= 5 && exShipSpaceRemaining > 0)
            {
                //Buy Fuel until no more money, no more fuel to buy or no more space
                exShip.getCargoHold().buyFuel(resourceCost);
                alienShip.getCargoHold().removeFuel(1);
            }

            //Update the space remaining
            exShipSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();
        }
    }
    else
    {
        //Nothing to buy or sell
        sectorLog += "Did not purchase supplies.\n";
        std::cout << "Can't Buy Food or Fuel" << std::endl;
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

void resolvePlanetMine(ExplorerShip &exShip, Planet &planet, std::string& sectorLog)
{
    Resource resource = planet.getResource();
    std::cout << "Scans show an abundance of " << resource.getName() << "." << std::endl;
    sectorLog += "Commenced mining operation.\n";
    int cargoSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();
    if(cargoSpaceRemaining > 0 && cargoSpaceRemaining >= resource.getSize() && exShip.getCargoHold().determineAmountOfResources() < 10)
    {
        int miningChance = (exShip.getCrew().getMiningOfficer().getMiningAbilityLvl() + exShip.getMiningLvl()) / 2;
        if(miningChance > randomNumGenerator(0,resource.getMiningDifficulty() * 10))
        {
            //Mining Successfull
            sectorLog += "Mining of " + resource.getName() + " was successful.\n";
            std::cout << "Mining of " << resource.getName() << " was successful." << std::endl;
            exShip.getCargoHold().addResource(resource);
        }
        else
        {
            //Mining Failed
            sectorLog += "Mining of " + resource.getName() + " was unsuccessful.\n";
            std::cout << "Mining of " << resource.getName() << " was unsuccessful." << std::endl;
        }
    }
}

//Trade Sector Functions
void resolveTradeSector(ExplorerShip& exShip)
{
    std::string sectorLog;
    TradeSector sector = generateTradeSector();
    TradeStation tradeStation = sector.getTradeStation();
    std::cout << sector.getType() << std::endl;
    sectorLog = "---Sector " + sector.getName() + "---\n";
    std::cout << "The " << exShip.getName() << " arrives in Sector: " << sector.getName() << std::endl;
    sectorLog += "Arrived at a " + tradeStation.getName() + ".\n";

    //Resolve trade
    resolveTrade(exShip, tradeStation, sectorLog);

    //Log Report
    exShip.getLogBook().addSectorLog(sectorLog);
}

void resolveTrade(ExplorerShip& exShip, TradeStation& tradeStation, std::string& sectorLog)
{
    int tradingModifier = exShip.getCrew().getCaptain().getTradingLvl() - tradeStation.getBarteringLvl();
    std::cout << "The " << exShip.getName() << " arrives at a " << tradeStation.getName() << "." << std::endl;

    if((*exShip.getCargoHold().getResources()).getName() != "")
    {
        sectorLog += "Sold all mined resources.\n";
        //Sell Resources
        for(int i = exShip.getCargoHold().determineAmountOfResources() - 1; i >= 0; i--)
        {
            Resource sellResource = exShip.getCargoHold().getResources()[i];
            //TradeStation buy at reduced rates
            int resourceSellValue = std::max(sellResource.getMinValue(),(sellResource.getValue() - 20) + tradingModifier);
            std::cout << "Trade Station purchased -> " << sellResource.getName() << std::endl;
            
            //TradeStation's have alway got enough money
            exShip.getCargoHold().sellResource(i, resourceSellValue);
        }
    }
    else
    {
        sectorLog += "No mined resources to sell\n";
        std::cout << "No resources to Sell" << std::endl;
    }

    //Flip tradeModifier for selling 
    tradingModifier = tradeStation.getBarteringLvl() - exShip.getCrew().getCaptain().getTradingLvl();
    int cargoSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();

    if(exShip.getCargoHold().getMoney() > 0 && cargoSpaceRemaining > 0)
    {
        sectorLog += "Purchased supplies\n";
        std::cout << "Purchasing Supplies" << std::endl;
        int resourceCost = std::max(5,tradingModifier);
        int exShipSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();
        while(exShip.getCargoHold().getMoney() >= resourceCost && exShipSpaceRemaining > 0 && (tradeStation.getFoodGoods() >= 5 || tradeStation.getFuelGoods() >= 5))
        {
            if(exShip.getCargoHold().getMoney() >= resourceCost && tradeStation.getFoodGoods() >= 5 && exShipSpaceRemaining > 0)
            {
                //Buy Food until no more money, no more food to buy or no more space
                exShip.getCargoHold().buyFood(resourceCost);
                tradeStation.removeFoodGoods(1);
            }
            
            //Update the space remaining
            exShipSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();

            if(exShip.getCargoHold().getMoney() >= resourceCost && tradeStation.getFuelGoods() >= 5 && exShipSpaceRemaining > 0)
            {
                //Buy Fuel until no more money, no more fuel to buy or no more space
                exShip.getCargoHold().buyFuel(resourceCost);
                tradeStation.removeFuelGoods(1);
            }

            //Update the space remaining
            exShipSpaceRemaining = exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo();
        }
    }
    else
    {
        //Nothing to buy or sell
        sectorLog += "Did not purchase supplies.\n";
        std::cout << "Can't Buy Food or Fuel" << std::endl;
    }
}

void resolveEmptySector(ExplorerShip& exShip)
{
    std::string sectorLog;
    EmptySector sector = generateEmptySector();
    std::cout << sector.getType() << std::endl;

    //Describe the emptiness of space???
    sectorLog = "---Sector " + sector.getName() + "---\n";
    sectorLog += "Arrived at an empty sector.\n";

    std::cout << "The " << exShip.getName() << " arrives in Sector: " << sector.getName() << std::endl;
    describeEmptySector(sector);
    exShip.getLogBook().addSectorLog(sectorLog);
}

void describeEmptySector(EmptySector sector)
{
    int selection;
    if(sector.getEnvironment() == "Outer Space")
    {
        //Describe OuterSpace
        selection = randomNumGenerator(1,3);
        switch(selection)
        {
            case 1:
                std::cout << "Nothing but some loose ship parts from ancient battles." << std::endl;
                break;
            case 2:
                std::cout << "Small rocks fizzle in the Ships shields, but thats about it." << std::endl;
                break;
            case 3:
                std::cout << "The Ship is suddenly surrounded by... nothing." << std::endl;
        }
    }
    else if(sector.getEnvironment() == "Nebula")
    {
        //Describe a Nebula
        selection = randomNumGenerator(1,3);
        switch(selection)
        {
            case 1:
                std::cout << "The Ship moves slowly through a Nebulas cloud." << std::endl;
                break;
            case 2:
                std::cout << "Ionized gases swirl around the Ship." << std::endl;
                break;
            case 3:
                std::cout << "A cloud of dust towers over the Ship, beautiful but not much else." << std::endl;
        }

    }
    else if(sector.getEnvironment() == "Asteroid Field")
    {
        //Describe Asteroid Field
        selection = randomNumGenerator(1,3);
        switch(selection)
        {
            case 1:
                std::cout << "The Ship navigates an asteroid field looking for resources, to no avail." << std::endl;
                break;
            case 2:
                std::cout << "Asteroids slam into the Ship while the crew works to keep the shields up." << std::endl;
                break;
            case 3:
                std::cout << "The Ship lands on a large asteroid and waits, while the Captain plots the next course." << std::endl;
        }
    }
    else
    {
        //Describe Star
        selection = randomNumGenerator(1,3);
        switch(selection)
        {
            case 1:
                std::cout << "The firey blue glow of a Star cascades through the Ships portholes." << std::endl;
                break;
            case 2:
                std::cout << "A Red Giant star keeps the Ships radiation shielding busy while the Ship makes it's way to the next sector." << std::endl;
                break;
            case 3:
                std::cout << "A Star burns gently as the Ship pulled into its orbit." << std::endl;
        }
    }
}

void resolveAnomalySector(ExplorerShip& exShip, int difficultyModifier)
{
    //Anomaly Sector
    AnomalySector sector = generateAnomalySector();
    std::cout << "The " << exShip.getName() << " arrives in Sector: " << sector.getName() << std::endl;
    std::cout << sector.getType() << std::endl;
    int anomalySelection = randomNumGenerator(1,3);

    switch(anomalySelection)
    {
        case 1:
            //Lost satellite
            sector.resolveLostSatellite(exShip, sector.getName(), difficultyModifier);
            break;
        case 2:
            //Ancient Place
            sector.resolveAncientPlace(exShip, sector.getName());
            break;
        case 3:
            //Primative Civilization
            sector.resolvePrimitiveCivilisation(exShip, sector.getName());
            break;
    }
}

void travelSector(ExplorerShip &exShip, int sectorNum)
{
    int requiredRecource;
    if(sectorNum <= 10)
        requiredRecource = 1;
    else if(sectorNum > 10 && sectorNum <= 20)
        requiredRecource = 2;
    else if(sectorNum > 20 && sectorNum <= 30)
        requiredRecource = 3;
    else if(sectorNum > 30 && sectorNum <= 40)
        requiredRecource = 4;
    else
        requiredRecource = 5;

    if(exShip.getCargoHold().getFood() < requiredRecource)
    {
        std::cout << "Not enough food to get to next sector, travelled to furthest sector possible." << std::endl;
        exShip.getCargoHold().removeFood(exShip.getCargoHold().getFood());
        exShip.getCargoHold().removeFuel(exShip.getCargoHold().getFood());
    }
    else if(exShip.getCargoHold().getFuel() < requiredRecource)
    {
        std::cout << "Not enough fuel to get to next sector, travelled to furthest sector possible." << std::endl;
        exShip.getCargoHold().removeFuel(exShip.getCargoHold().getFuel());
        exShip.getCargoHold().removeFood(exShip.getCargoHold().getFuel());
    }
    else
    {
        std::cout << "Travelled to next sector." << std::endl;
        exShip.getCargoHold().removeFuel(requiredRecource);
        exShip.getCargoHold().removeFood(requiredRecource);
    }
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