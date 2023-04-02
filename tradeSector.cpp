#include "mainJSE.h"

//TradeSector Functions
TradeSector::TradeSector(std::string inName, std::string inType, std::string inEnvironment, TradeStation inTradeStation)
    : Sector(inName, inType, inEnvironment)
{
    this->tradeStation = inTradeStation;
}

//TradeStation Functions
TradeStation::TradeStation(std::string inName, int inFuelGoods, int inFoodGoods, int inBarteringLvl)
{
    this->name = inName;
    this->fuelGoods = inFuelGoods;
    this->foodGoods = inFoodGoods;
    this->barteringLvl = inBarteringLvl;
}

void TradeStation::removeFoodGoods(int foodRemoved)
{
    this->foodGoods -= foodRemoved;
}

void TradeStation::removeFuelGoods(int fuelRemoved)
{
    this->fuelGoods -= fuelRemoved;
}

TradeSector generateTradeSector()
{
    //Generate Name
    std::string name = generateSectorName();

    //Generate Environment
    std::string environment = generateSectorEnvironment();

    std::string type = "Trade Sector";

    //Generate TradeStation
    TradeStation tradeStation = generateTradeStation();

    return TradeSector(name, type, environment, tradeStation);
}

TradeStation generateTradeStation()
{
    std::string tradeStationNames[] = { "Food Station", "Fuel Station", "Pawn Station" };
    std::string name = tradeStationNames[randomNumGenerator(0, 2)];

    int fuelGoods;
    int foodGoods;
    int barteringLvl;

    if (name == "Food Station")
    {
        fuelGoods = randomNumGenerator(10, 20);
        foodGoods = randomNumGenerator(40, 60);
        barteringLvl = randomNumGenerator(10, 60);
    }
    else if (name == "Fuel Station")
    {
        fuelGoods = randomNumGenerator(40, 60);
        foodGoods = randomNumGenerator(10, 20);
        barteringLvl = randomNumGenerator(10, 60);
    }
    else
    {
        fuelGoods = randomNumGenerator(10, 20);
        foodGoods = randomNumGenerator(10, 20);
        barteringLvl = randomNumGenerator(50, 80);
    }

    return TradeStation(name, fuelGoods, foodGoods, barteringLvl);
}