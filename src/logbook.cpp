#include "mainJSE.h"

//LogBook Functions
LogBook::LogBook(int inStartMoney, int inStartFood, int inStartFuel, int inStartCrewNum)
{
    this->startMoney = inStartMoney;
    this->startFood = inStartFood;
    this->startFuel = inStartFuel;
    this->startCrewNum = inStartCrewNum;
}

void LogBook::addSectorLog(std::string sectorLog)
{
    sectorLogs.push_back(sectorLog);
}

void LogBook::addCrewDeathRecord(std::string crewDeathRecord)
{
    this->crewDeathRecords.push_back(crewDeathRecord);
}
