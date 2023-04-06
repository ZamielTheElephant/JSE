#include "mainJSE.h"

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

Weapon generateWeapon()
{
    int weaponSelect = randomNumGenerator(0, 4);

    switch (weaponSelect)
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
