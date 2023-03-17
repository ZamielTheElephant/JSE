class Alien;

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
        void setMoney(int newMoney) {this->money = newMoney;}
        Resource* getResources() {return resources;}
        int determineAmountOfResources();
        void addResource(Resource&);
        void removeResource(int);
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
        void killReplaceOfficer();
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
        Defence defences[2];
        int hull;
        int shields;
        int combatManeuver;
        CargoHold cargoHold;
    public:
        Ship() {};
        Ship(std::string, std::string, int, Crew, int, int, int, int, CargoHold);
        //Ship(Ship* ship);
        std::string getName() {return name;}
        std::string getType() {return type;}
        int getSize() {return size;}
        int getMiningLvl() {return miningLvl;}
        Crew getCrew() {return crew;}
        Weapon* getWeapons() {return weapons;}
        Defence* getDefences() {return defences;}
        int getHull() {return hull;}
        int getShields() {return shields;}
        CargoHold& getCargoHold() {return cargoHold;}
        void setShields(int damage) {this->shields -= damage;}
        int determineCombatRoll();
        void dealDamage(Weapon&, WeaponsOfficer, Defence&);
        void dealDamage(Weapon&, WeaponsOfficer);
        void damageCrew(int damageDealt);
        Weapon& selectWeapon(int round);
        bool determineDefenceUse();
        int determineAmountOfWeapons();
        int determineAmountOfDefences();
        bool checkFortitude();
        void repairShip();
};

class ExplorerShip : public Ship
{
    private:
        //SectorLog logBook[];
        int date;
    public:
        ExplorerShip() {};
        ExplorerShip(std::string, std::string, int, Crew, int, int, int, int, CargoHold);
        //ExplorerShip(ExplorerShip* explorerShip);
        int getDate() {return date;}
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
Weapon generateWeapon();
int generateMiningLvl(std::string);
Crew generateGenericCrew(int, int);
int generateCrewNum(int);
int generateSize(std::string);
std::string randomNameGenerator();
std::string generateType();
int typeNumber(std::string);
