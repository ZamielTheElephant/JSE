#include "mainJSE.h"

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

Defence generateDefence()
{
    int weaponSelect = randomNumGenerator(0, 1);

    switch (weaponSelect)
    {
    case 0: //Energy Defence
        return Defence("Energy Defence", 0, 70, 2);
    case 1: //Physical Defence
        return Defence("Defence Missiles", 1, 70, 2);
    }
}