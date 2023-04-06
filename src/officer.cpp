#include "mainJSE.h"

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
    switch (this->level)
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
