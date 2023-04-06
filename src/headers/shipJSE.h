#include <vector>
class Alien;
class Ship;

class Weapon
{
    private:
        std::string name;
        int weaponType;
        int hullDamage;
        int shieldDamage;
        int defenceDamage;
        int roundCooldown;
        int lastRoundUsed;
        bool operational;
    public:
        Weapon() {};
        Weapon(std::string name, int weaponType, int hullDamage, int shieldDamage, int defenceDamage, int roundCooldown);
        //Weapon(Weapon* weapon);
        std::string getName() {return name;}
        int getWeaponType() {return weaponType;}
        int getHullDamage() {return hullDamage;}
        int getShieldDamage() {return shieldDamage;}
        int getDefenceDamage() {return defenceDamage;}
        int getRoundCooldown() {return roundCooldown;}
        int getLastRoundUsed() {return lastRoundUsed;}
        bool getOperational() {return operational;}
        void setLastRoundUsed(int currentRound) {lastRoundUsed = currentRound;}
        
};

class Defence
{
    private:
        std::string name;
        int effectiveType;
        int defenceLvl;
        int roundCooldown;
        int lastRoundUsed;
        bool operational;
    public:
        Defence() {};
        Defence(std::string name, int effectiveType, int defenceLvl, int roundCooldown);
        //Defence(Defence* defence);
        std::string getName() {return name;}
        int getEffectiveType() {return effectiveType;}
        int getDefenceLvl() {return defenceLvl;}
        int getRoundCooldown() {return roundCooldown;}
        int getLastRoundUsed() {return lastRoundUsed;}
        bool getOperational() {return operational;}
        void setLastRoundUsed(int currentRound) {lastRoundUsed = currentRound;}
};

class CargoHold
{
    private:
        int capacity;
        int totalCargo;
        int food;
        int fuel;
        int money;
        Resource resources[10];
    public:
        CargoHold() {};
        CargoHold(int capacity, int money);
        //CargoHold(CargoHold* cargoHold);
        int getCapacity() {return capacity;}
        int getTotalCargo() {return totalCargo;}
        int getFood() {return food;}
        int getFuel() {return fuel;}
        int getMoney() {return money;}
        Resource* getResources() {return resources;}
        int determineAmountOfResources();
        void addResource(Resource&);
        void buyResource(int);
        void sellResource(int, int);
        void removeFood(int);
        void buyFood(int);
        void removeFuel(int);
        void buyFuel(int);
};

class SkillLvl
{
    private:
        int level;
        int max;
        int min;
    public:
        SkillLvl() {};
        SkillLvl(int level);
        //SkillLvl(SkillLvl* skillLvl);
        int getLevel() {return level;}
        int getMax() {return max;}
        int getMin() {return min;}
        void setMaxMin();
};

class Officer
{
    private:
        std::string name;
        int age;
        std::string title;
        SkillLvl skillLvl;
    public:
        Officer() {};
        Officer(std::string name, int age, std::string title, SkillLvl skillLvl);
        //Officer(Officer* officer);
        std::string getName() {return name;}
        int getAge() {return age;}
        std::string getTitle() {return title;}
        SkillLvl getSkillLvl() {return skillLvl;}
};

class Captain : public Officer
{
    private:
        int diplomacyLvl;
        int tradingLvl;
        int fortitudeLvl;
    public:
        Captain() {};
        Captain(std::string name, int age, std::string title, SkillLvl skillLvl);
        //Captain(Captain* captain);
        int getDiplomacyLvl() {return diplomacyLvl;}
        int getTradingLvl() {return tradingLvl;}
        int getFortitudeLvl() {return fortitudeLvl;}
};

class Pilot : public Officer
{
    private:
        int travelEfficencyLvl;
        int combatManeuverLvl;
        int conflictEvasionLvl;
    public:
        Pilot() {};
        Pilot(std::string name, int age, std::string title, SkillLvl skillLvl);
        //Pilot(Pilot* pilot);
        int getTravelEfficencyLvl() {return travelEfficencyLvl;}
        int getCombatManeuverLvl() {return combatManeuverLvl;}
        int getConflictEvasionLvl() {return conflictEvasionLvl;}
};

class Engineer : public Officer
{
    private:
        int travelEfficencyLvl;
        int combatManeuverLvl;
        int conflictEvasionLvl;
        int defenceSystemLvl;
        int shipRepairLvl;
    public:
        Engineer() {};
        Engineer(std::string name, int age, std::string title, SkillLvl skillLvl);
        //Engineer(Engineer* engineer);
        int getTravelEfficencyLvl() {return travelEfficencyLvl;}
        int getCombatManeuverLvl() {return combatManeuverLvl;}
        int getConflictEvasionLvl() {return conflictEvasionLvl;}
        int getDefenceSystemLvl() {return defenceSystemLvl;}
        int getShipRepairLvl() {return shipRepairLvl;}
};

class MiningOfficer : public Officer
{
    private:
        int miningAbilityLvl;
    public:
        MiningOfficer() {};
        MiningOfficer(std::string name, int age, std::string title, SkillLvl skillLvl);
        int getMiningAbilityLvl() {return miningAbilityLvl;}
};

class WeaponsOfficer : public Officer
{
    private:
        int weaponsLvl;
        int defencesLvl;
    public:
        WeaponsOfficer() {};
        WeaponsOfficer(std::string name, int age, std::string title, SkillLvl skillLvl);
        int getWeaponsLvl() {return weaponsLvl;}
        int getDefenceLvl() {return defencesLvl;}
};

class Crew
{
    private:
        Captain captain;
        Pilot pilot;
        Engineer engineer;
        MiningOfficer miningOfficer;
        WeaponsOfficer weaponsOfficer;
        int crewNum;
    public:
        Crew(){};
        Crew(Captain, Pilot, Engineer, MiningOfficer, WeaponsOfficer, int);
        //Crew(Crew* crew);
        Captain getCaptain() {return captain;}
        Pilot getPilot() {return pilot;}
        Engineer getEngineer() {return engineer;}
        MiningOfficer getMiningOfficer() {return miningOfficer;}
        WeaponsOfficer getWeaponsOfficer() {return weaponsOfficer;}
        int getCrewNum() {return crewNum;}
        void killReplaceOfficer(Ship*, std::string);
        void killCrew(int numKilled);
};

class Ship
{
    private:
        std::string name;
        std::string type;
        int size;
        Crew crew;
        int miningLvl;
        Weapon weapons[5];
        int amountOfWeapons;
        Defence defences[2];
        int hull;
        int shields;
        int combatManeuver;
        CargoHold cargoHold;
    public:
        Ship() {};
        Ship(std::string, std::string, int, Crew, int, int, int, int, int, CargoHold);
        //Ship(Ship* ship);
        virtual std::string getName() {return name;}
        virtual std::string getType() {return type;}
        int getSize() {return size;}
        int getMiningLvl() {return miningLvl;}
        Crew getCrew() {return crew;}
        Weapon* getWeapons() {return weapons;}
        int getAmountOfWeapons() {return amountOfWeapons;}
        Defence* getDefences() {return defences;}
        int getHull() {return hull;}
        int getShields() {return shields;}
        CargoHold& getCargoHold() {return cargoHold;}
        int determineCombatRoll();
        void dealDamage(Weapon&, WeaponsOfficer, Defence&, std::string);
        void dealDamage(Weapon&, WeaponsOfficer, std::string);
        void dealAnomalyDamage(int);
        void damageCrew(int, std::string);
        Weapon& selectWeapon();
        bool determineDefenceUse();
        void addWeapon(Weapon);
        int determineAmountOfCurrentWeapons();
        int determineAmountOfWeapons();
        int determineAmountOfDefences();
        bool checkFortitude();
        void repairShip();
};

class LogBook
{
    private:
        std::vector<std::string> sectorLogs;
        std::vector<std::string> crewDeathRecords;
        int startMoney;
        int startFood;
        int startFuel;
        int startCrewNum;
        std::string finalState = "Survived";
    public:
        LogBook() {};
        LogBook(int,int,int,int);
        std::vector<std::string> getSectorLogs() {return sectorLogs;}
        std::vector<std::string> getCrewDeathRecords() {return crewDeathRecords;}
        int getStartCrewNum() {return startCrewNum;}
        std::string getFinalState() {return finalState;}
        void setFinalState(std::string newFinalState) {finalState = newFinalState;}
        void addSectorLog(std::string sectorLog);
        void editTempCrewDeathRecord(std::string);
        void addCrewDeathRecord(std::string);
};

class ExplorerShip : public Ship
{
    private:
        LogBook logBook;
    public:
        ExplorerShip() {};
        ExplorerShip(std::string, std::string, int, Crew, int, int, int, int, int, CargoHold, LogBook);
        //ExplorerShip(ExplorerShip* explorerShip);
        LogBook& getLogBook() {return logBook;}
        void takeSpoils(int,int);
};

//Explorer Ship Generator Functions
ExplorerShip generateExplorerShip();
CargoHold generateExplorerShipCargoHold(std::string);
std::string generateExplorerShipName();
Crew generateExplorerShipCrew(int);

//Ship Generator Functions
Ship generateNewShip(Alien&,int);
CargoHold generateCargoHold(std::string);
int generateCombatManeuver(int);
int generateShield(std::string);
int generateHull(std::string);
void populateDefences(std::string, Defence[]);
Defence generateDefence();
void populateWeapons(std::string, Weapon[]);
int generateAmountOfWeapons(std::string);
Weapon generateWeapon();
int generateMiningLvl(std::string);
Crew generateGenericCrew(int, int);
int generateCrewNum(int);
int generateSize(std::string);
std::string randomNameGenerator();
std::string generateType();
int typeNumber(std::string);
