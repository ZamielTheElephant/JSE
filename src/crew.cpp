#include "mainJSE.h"

//Crew Functions
Crew::Crew(Captain inCaptain, Pilot inPilot, Engineer inEngineer, MiningOfficer inMiningOfficer, WeaponsOfficer inWeaponsOfficer, int inCrewNum)
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
    int officerKilled = randomNumGenerator(1, 5);
    switch (officerKilled)
    {
    case 1:
        //Captain Killed
        std::cout << "The Captain is killed" << std::endl;
        tempCrewDeathRecord += ".\nCaptain: " + this->captain.getTitle() + " " + this->captain.getName() + " was killed.";
        this->captain = Captain(randomNameGenerator(), randomNumGenerator(30, 70), "Captain", std::max(1, this->captain.getSkillLvl().getLevel() - 1));
        this->crewNum--;
        break;
    case 2:
        //Pilot Killed
        std::cout << "The Pilot is killed" << std::endl;
        tempCrewDeathRecord += ".\nPilot: " + this->pilot.getTitle() + " " + this->pilot.getName() + " was killed.";
        this->pilot = Pilot(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", std::max(1, this->pilot.getSkillLvl().getLevel() - 1));
        this->crewNum--;
        break;
    case 3:
        //Engineer Killed
        std::cout << "The Engineer is killed" << std::endl;
        tempCrewDeathRecord += ".\nEngineer: " + this->engineer.getTitle() + " " + this->engineer.getName() + " was killed.";
        this->engineer = Engineer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", std::max(1, this->engineer.getSkillLvl().getLevel() - 1));
        this->crewNum--;
        break;
    case 4:
        //MiningOfficer Killed
        std::cout << "The Mining Officer is killed" << std::endl;
        tempCrewDeathRecord += ".\nMining Officer: " + this->miningOfficer.getTitle() + " " + this->miningOfficer.getName() + " was killed.";
        this->miningOfficer = MiningOfficer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", std::max(1, this->miningOfficer.getSkillLvl().getLevel() - 1));
        this->crewNum--;
        break;
    case 5:
        //WeaponsOfficer Killed
        std::cout << "The Weapons Officer is killed" << std::endl;
        tempCrewDeathRecord += ".\nWeapons Officer: " + this->weaponsOfficer.getTitle() + " " + this->weaponsOfficer.getName() + " was killed.";
        this->weaponsOfficer = WeaponsOfficer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant", std::max(1, this->weaponsOfficer.getSkillLvl().getLevel() - 1));
        this->crewNum--;
        break;
    }

    if (ExplorerShip* exShip = dynamic_cast<ExplorerShip*>(ship))
    {
        (*exShip).getLogBook().addCrewDeathRecord(tempCrewDeathRecord);
    }
}

void Crew::killCrew(int numKilled)
{
    std::cout << numKilled << " crew members killed in the attack." << std::endl;
    crewNum -= numKilled;
    crewNum = std::max(0, crewNum);
    std::cout << "Crew Remaining: " << this->crewNum << std::endl;
}

//Used for Generic Crew !!!NOT EXPLORER CREW!!!
Crew generateGenericCrew(int size, int difficultyModifier)
{
    int max = difficultyModifier + 3;
    int min = difficultyModifier;

    Captain captain(randomNameGenerator(), randomNumGenerator(30, 70), "Captain", randomNumGenerator(min, max));
    Pilot pilot(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant.", randomNumGenerator(min, max));
    Engineer engineer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant.", randomNumGenerator(min, max));
    MiningOfficer miningOfficer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant.", randomNumGenerator(min, max));
    WeaponsOfficer weaponsOfficer(randomNameGenerator(), randomNumGenerator(30, 70), "Lieutenant.", randomNumGenerator(min, max));
    int crewNum = generateCrewNum(size);

    return Crew(captain, pilot, engineer, miningOfficer, weaponsOfficer, crewNum);
}

//Name Generator !! Add More Names
std::string randomNameGenerator()
{
    std::string firstNames[] = { "John", "Aaron", "Fred", "Tom", "Tobius", "Davante", "Jaire", "David", "Mike", "Geronimo",
                            "Ellis", "Beth", "Paige", "Megan", "India", "Kimberly", "Ashley", "Natlia", "Julie", "Lowri" };
    std::string lastNames[] = { "Baker", "Rogers", "Evens", "Fredrickson", "Apple", "Adams", "Alexander", "Bakhtiari", "Daniels", "Allison", "Davis",
                            "O'Moore", "Green", "Reyes", "Woods", "Hopkins", "Middleton", "McCoy", "Bird", "Mullins" };

    std::string fullName = firstNames[randomNumGenerator(0, 19)] + " " + lastNames[randomNumGenerator(0, 19)];
    return fullName;
}