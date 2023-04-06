#include "mainJSE.h"

//Resource Functions
Resource::Resource(std::string inName, std::string inType, int inSize, int inValue, int inMinValue, int inMiningDiffuculty)
{
    this->name = inName;
    this->type = inType;
    this->size = inSize;
    this->value = inValue;
    this->minValue = inMinValue;
    this->miningDifficulty = inMiningDiffuculty;
}

Resource generateResource(std::string planetType)
{
    std::string name = generateResourceName(planetType);

    std::string type = generateResourceType(name);

    int size = generateResourceSize(type);

    int value = generateResourceValue(name);

    int minValue = generateResourceMinValue(name);

    int miningDifficulty = generateResourceMiningDifficulty(type);

    return Resource(name, type, size, value, minValue, miningDifficulty);
}

int generateResourceMiningDifficulty(std::string type)
{
    if (type == "Metal")
        return 8;
    else if (type == "Animal")
        return 6;
    else if (type == "Mineral")
        return 5;
    else
        return 4;
}

int generateResourceValue(std::string name)
{
    if (name == "Iron" || name == "Salt")
        return randomNumGenerator(50, 100);
    else if (name == "Diamond")
        return randomNumGenerator(500, 1000);
    else if (name == "Sand" || name == "Flint" || name == "Seaweed")
        return randomNumGenerator(20, 40);
    else if (name == "Fish" || name == "Mushrooms" || name == "Fruit")
        return randomNumGenerator(30, 50);
    else if (name == "Logs" || name == "Cactus")
        return randomNumGenerator(50, 70);
    else
        return randomNumGenerator(100, 150);
}

int generateResourceMinValue(std::string name)
{
    if (name == "Iron" || name == "Salt")
        return 40;
    else if (name == "Diamond")
        return 400;
    else if (name == "Sand" || name == "Flint" || name == "Seaweed")
        return 10;
    else if (name == "Fish" || name == "Mushrooms" || name == "Fruit")
        return 20;
    else if (name == "Logs" || name == "Cactus")
        return 40;
    else
        return 70;
}

int generateResourceSize(std::string type)
{
    if (type == "Metal")
        return randomNumGenerator(7, 10);
    else if (type == "Mineral")
        return randomNumGenerator(5, 7);
    else if (type == "Plant")
        return randomNumGenerator(2, 5);
    else
        return randomNumGenerator(1, 4);
}

std::string generateResourceType(std::string name)
{
    if (name == "Iron" || name == "Diamond" || name == "Lava Gem")
        return "Metal";
    else if (name == "salt" || name == "Flint" || name == "Sand")
        return "Mineral";
    else if (name == "Fish" || name == "Scorpion Venom")
        return "Animal Produce";
    else
        return "Plant Produce";
}

std::string generateResourceName(std::string type)
{
    std::string barrenNames[] = { "Iron", "Salt", "Flint" };
    std::string forestNames[] = { "Logs", "Mushrooms", "Fruit" };
    std::string desertNames[] = { "Sand", "Cactus", "Scorpion Venom" };
    std::string oceanNames[] = { "Fish", "Salt", "Seaweed" };
    std::string volcanoNames[] = { "Diamond", "Iron", "Lava Gem" };

    if (type == "Barren World")
        return barrenNames[randomNumGenerator(0, 2)];
    else if (type == "Forest World")
        return forestNames[randomNumGenerator(0, 2)];
    else if (type == "Desert World")
        return desertNames[randomNumGenerator(0, 2)];
    else if (type == "Ocean World")
        return oceanNames[randomNumGenerator(0, 2)];
    else
        return volcanoNames[randomNumGenerator(0, 2)];
}