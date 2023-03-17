#include <string>
#include <iostream>
#include "resource.h"
#include "shipJSE.h"
#include "sectorJSE.h"

void resolveSector(ExplorerShip&, int);
int difficultyModifier(int);
int determineSectorType();
void resolveShipSector(ExplorerShip&, int);
bool resolveBattle(ExplorerShip&, Ship&);
void fireWeapon(Weapon&, WeaponsOfficer, Ship&, int);
bool checkHit(Ship&);
bool checkDefeatConditions(Ship&);
bool tradeTalksCheck(ExplorerShip&, ShipSector&);
bool diplomacyCheck(ExplorerShip&, ShipSector&);
void resolvePlanetSector(ExplorerShip&, int);
void resolveTrade(ExplorerShip&, Planet&)
bool diplomacyCheck(ExplorerShip&, PlanetSector&);
bool tradeTalksCheck(ExplorerShip&, PlanetSector&);
void resolvePlanetMine(ExplorerShip&, Planet&);
void resolveTradeSector(ExplorerShip&);
void resolveEmptySector(ExplorerShip&);
void resolveAnomalySector(ExplorerShip&);
void setRandomSeed();
int randomNumGenerator(int,int);
