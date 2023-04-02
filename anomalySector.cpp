#include "mainJSE.h"

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
    int storySelection = randomNumGenerator(1, 3);

    Resource resource;
    Alien alien;
    Ship alienShip;

    switch (storySelection)
    {
    case 1:
        //Self-Destruct Sequence
        std::cout << "While the crew is investigating the satellite, a self-destruct sequence is activated." << std::endl;
        sectorLog += " Self-destruct sequence activated.\n";
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
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
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Diamonds
            std::cout << "The data contains coordinates to a cache of diamonds nearby." << std::endl;
            std::cout << "The " << exShip.getName() << " travels to the location and finds the cache." << std::endl;
            sectorLog += "The Satellite contains location data of a Diamond cache.\n";

            if (exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= 7)
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

            if (exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
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
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Bati
            alien = Alien("Bati", "Warriors", 70, 60, "Looks like a Bati");
            alienShip = generateNewShip(alien, difficultyModifier);
            std::cout << "Suddenly a Bati " << alienShip.getType() << " appears and begins to attack." << std::endl;
            sectorLog += "A Bati " + alienShip.getType() + " appeared and attacked.\n";
            if (resolveBattle(exShip, alienShip, sectorLog, sectorName))
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
            std::cout << "Suddenly a Drul " << alienShip.getType() << " appears and begins to attack." << std::endl;
            sectorLog += "A Drul " + alienShip.getType() + " appeared and attacked.\n";
            if (resolveBattle(exShip, alienShip, sectorLog, sectorName))
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
    int storySelection = randomNumGenerator(1, 3);
    switch (storySelection)
    {
    case 1:
        //Ancient Temple
        std::cout << "Temple on the surface." << std::endl;
        sectorLog += "Temple is found.\n";
        std::cout << "The Crew Begins to investigate." << std::endl;
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Find Ancient Artifact
            std::cout << "After trawling through meaningless items a crew member finds a valuble Artifact." << std::endl;
            sectorLog += "While searching the Temple an Ancient Artifact is found.\n";
            resource = Resource("Ancient Artifact", "Unique", 1, 2000, 1000, 0);
            if (exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
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
            std::cout << "While searching the Temple, the structure begins to shift and starts to collapse." << std::endl;
            std::cout << "Fortunatly, the search team is able to escape the falling building." << std::endl;
            sectorLog += "While searching the Temple it begins to collapes, the crew is able to escape.\n";
            break;
        case 3:
            //Temple Collapse Loss Crew Member
            std::cout << "While searching the Temple, the structure begins to shift and starts to collapse." << std::endl;
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
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Machine Activates Gain Resource?
            std::cout << "While investigating the Machine, a crew member finds a valuble piece of machinery." << std::endl;
            sectorLog += "While searching the Machine a piece of Ancient Machinery is found.\n";
            resource = Resource("Ancient Machinery", "Unique", 3, 1500, 1000, 0);
            if (exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
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
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Find Powerful Weapon //If Possible?
            std::cout << "While investigating the Ancient Ship, a powerful weapon is found." << std::endl;
            std::cout << "The Ships Engineer " << exShip.getCrew().getEngineer().getName() << " believes they can add it to the ships arsenal." << std::endl;
            sectorLog += "While searching the ship a powerful weapon is found.\n";

            if ((exShip.getAmountOfWeapons()) < 4)
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
    int storySelection = randomNumGenerator(1, 3);

    switch (storySelection)
    {
    case 1:
        //Stone Age
        std::cout << "The aliens here seem to be in a Stone age period in their history.\nThe crew moves to make contact with the aliens" << std::endl;
        sectorLog += "Encountered Stone age aliens and attempted to contact.\n";
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Communicate/Trade
            std::cout << "The crew was able to make peaceful contact with the aliens." << std::endl;
            sectorLog += "The crew made peaceful contact with the primitive aliens.\n";
            resource = generateResource(generateEmptyPlanetType());
            if (exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
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
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Communicate/Trade
            std::cout << "The crew was able to make peaceful contact with the aliens." << std::endl;
            sectorLog += "The crew made peaceful contact with the primitive aliens.\n";
            resource = generateResource(generateEmptyPlanetType());
            if (exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
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
        storySelection = randomNumGenerator(1, 3);
        switch (storySelection)
        {
        case 1:
            //Communicate/Trade
            std::cout << "The crew was able to make peaceful contact with the aliens." << std::endl;
            sectorLog += "The crew made peaceful contact with the primitive aliens.\n";
            resource = generateResource(generateEmptyPlanetType());
            if (exShip.getCargoHold().determineAmountOfResources() < 9 && (exShip.getCargoHold().getCapacity() - exShip.getCargoHold().getTotalCargo()) >= resource.getSize())
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
            std::cout << "The crew attempt to make peaceful contact, but as the crew step off the ship they are peppered by small arms fire." << std::endl;
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

AnomalySector generateAnomalySector()
{
    //Generate Name
    std::string name = generateSectorName();

    //Generate Environment
    std::string environment = generateSectorEnvironment();

    std::string type = "Anomaly Sector";

    return AnomalySector(name, type, environment);
}