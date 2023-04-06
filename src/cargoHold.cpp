#include "mainJSE.h"

//CargoHold Functions
CargoHold::CargoHold(int inCapacity, int inMoney)
{
    this->capacity = inCapacity;
    this->totalCargo = 60;
    this->food = 30;
    this->fuel = 30;
    this->money = inMoney;
}

void CargoHold::addResource(Resource& newResource)
{
    int arraySlot = determineAmountOfResources();
    this->resources[arraySlot] = newResource;
    this->totalCargo += newResource.getSize();
}

//This is just used to change money for Alien Ships
void CargoHold::buyResource(int cost)
{
    this->money -= cost;
}

void CargoHold::sellResource(int arraySlot, int profit)
{
    this->totalCargo -= this->resources[arraySlot].getSize();
    this->resources[arraySlot] = Resource();
    std::cout << "Money: " << this->money << " -> ";
    this->money += profit;
    std::cout << this->money << std::endl;
}

void CargoHold::removeFood(int foodRemoved)
{
    this->food -= foodRemoved;
    this->totalCargo -= foodRemoved;
}

void CargoHold::buyFood(int foodCost)
{
    this->food++;
    this->totalCargo++;
    this->money -= foodCost;
}

void CargoHold::removeFuel(int fuelRemoved)
{
    this->fuel -= fuelRemoved;
    this->totalCargo -= fuelRemoved;
}

void CargoHold::buyFuel(int fuelCost)
{
    this->fuel++;
    this->totalCargo++;
    this->money -= fuelCost;
}

int CargoHold::determineAmountOfResources()
{
    for (int i = 0; i < 10; i++)
    {
        if (this->resources[i].getName() == "")
        {
            return i;
        }
    }
    return 0;
}

CargoHold generateCargoHold(std::string type)
{
    int capacity;
    int money;

    switch (typeNumber(type))
    {
    case 0:
        capacity = randomNumGenerator(7, 8) * 10;//Mining
        money = randomNumGenerator(1, 5) * 100;
    case 1:
        capacity = randomNumGenerator(9, 10) * 10;//Trade
        money = randomNumGenerator(5, 10) * 100;
    case 2:
        capacity = randomNumGenerator(3, 4) * 10;//Corvette
        money = randomNumGenerator(1, 3) * 100;
    case 3:
        capacity = randomNumGenerator(4, 5) * 10;//Frigate
        money = randomNumGenerator(1, 4) * 100;
    case 4:
        capacity = randomNumGenerator(6, 7) * 10;//Destroyer
        money = randomNumGenerator(1, 5) * 100;
    case 5:
        capacity = randomNumGenerator(6, 7) * 10;//Battlecruiser
        money = randomNumGenerator(1, 6) * 100;
    }

    return CargoHold(capacity, money);

}