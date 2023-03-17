
class Alien
{
    private:
        std::string name;
        std::string type;
        int hostility;
        int intellegence;
        std::string description;
    public:
        Alien() {};
        Alien(std::string, std::string, int, int, std::string);
        //Alien(Alien*);
        std::string getName() {return name;}
        std::string getType() {return type;}
        int getHostility() {return hostility;}
        int getIntellegence() {return intellegence;}
        std::string getDescription() {return description;}
};

class TradeStation
{
    private:
        std::string name;
        int fuelGoods;
        int foodGoods;
        int barteringLvl;
    public:
        TradeStation() {};
        TradeStation(std::string, int, int, int);
        //TradeStation(TradeStation*);
        std::string getName() {return name;}
        int getFuelGoods() {return fuelGoods;}
        int getFoodGoods() {return foodGoods;}
        int getBarteringLvl() {return barteringLvl;}
};

class Planet
{
    private:
        std::string name;
        std::string type;
        int size;
        int population;
        Ship ship;
        Resource resource;
    public:
        Planet() {};
        Planet(std::string, std::string, int, int, Ship, Resource);
        //Planet(Planet*);
        std::string getName() {return name;}
        std::string getType() {return type;}
        int getSize() {return size;}
        int getPopulation() {return population;}
        Ship getShip() {return ship;}
        Resource& getResource() {return resource;}
};

class Sector
{
    private:
        std::string name;
        std::string type;
        std::string environment;
    public:
        Sector() {};
        Sector(std::string, std::string, std::string);
        //Sector(Sector*);
        std::string getType() {return type;}
        std::string getName() {return name;}
        std::string getEnvironment() {return environment;}
};

class ShipSector : public Sector
{
    private:
        Ship alienShip;
        Alien alien;
    public:
        ShipSector() {};
        ShipSector(std::string, std::string, std::string, Ship, Alien);
        //ShipSector(ShipSector*);
        Ship getAlienShip() {return alienShip;}
        Alien getAlien() {return alien;}
};

class PlanetSector : public Sector
{
    private:
        Planet planet;
        Alien alien;
    public:
        PlanetSector() {};
        PlanetSector(std::string, std::string, std::string, Planet, Alien);
        //PlanetSector(PlanetSector*);
        Planet getPlanet() {return planet;}
        Alien getAlien() {return alien;}
};

class TradeSector : public Sector
{
    private:
        TradeStation tradeStation;
    public:
        TradeSector() {};
        TradeSector(std::string, std::string, std::string, TradeStation);
        //TradeSector(TradeSector*);
        TradeStation getTradeStation() {return tradeStation;}
};

class EmptySector : public Sector
{
    public:
        EmptySector() {};
        EmptySector(std::string, std::string, std::string);
        //EmptySector(EmptySector*);
};

class AnomalySector : public Sector
{
    //TBD
};

EmptySector generateEmptySector();
TradeSector generateTradeSector();
TradeStation generateTradeStation();
PlanetSector generatePlanetSector(int);
Planet generateEmptyPlanet();
Resource generateResource(std::string);
int generateResourceMiningDifficulty(std::string);
int generateResourceValue(std::string);
int generateResourceSize(std::string);
std::string generateResourceType(std::string);
std::string generateResourceName(std::string);
std::string generateEmptyPlanetType();
std::string generateEmptyPlanetName();
Planet generateAlienPlanet(Alien, int);
int generatePlanetPopulation(std::string);
std::string generateAlienPlanetName(std::string);
std::string generateAlienPlanetType(std::string);
ShipSector generateShipSector(int);
Alien generateAlien();
std::string generateAlienName();
std::string generateSectorEnvironment();
std::string generateSectorName();
int sectorTypeNumber(std::string);
