#include <string>
#include <iostream>
#include "resource.h"
#include "shipJSE.h"
#include "sectorJSE.h"

void resolveSector(ExplorerShip&, int);
int difficultyModifier(int);
int determineSectorType();
void resolveShipSector(ExplorerShip&, int);
bool resolveBattle(ExplorerShip&, Ship&, std::string&, std::string);
void fireWeapon(Weapon&, WeaponsOfficer, Ship&, int, std::string&);
bool checkHit(Ship&);
bool checkDefeatConditions(Ship&);
bool tradeTalksCheck(ExplorerShip&, ShipSector&);
bool diplomacyCheck(ExplorerShip&, ShipSector&);
void resolvePlanetSector(ExplorerShip&, int);
void resolveTrade(ExplorerShip&, Ship&, std::string&);
bool diplomacyCheck(ExplorerShip&, PlanetSector&);
bool tradeTalksCheck(ExplorerShip&, PlanetSector&);
void resolvePlanetMine(ExplorerShip&, Planet&, std::string&);
void resolveTradeSector(ExplorerShip&);
void resolveTrade(ExplorerShip&, TradeStation&, std::string&);
void resolveEmptySector(ExplorerShip&);
void describeEmptySector(EmptySector);
void resolveAnomalySector(ExplorerShip&, int);
void travelSector(ExplorerShip&, int);
void setRandomSeed();
int randomNumGenerator(int, int);
int selectSectorFromList(SectorList*, int);
