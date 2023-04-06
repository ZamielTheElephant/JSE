#include "mainJSE.h"

//Alien Functions
Alien::Alien(std::string inName, std::string inType, int inHostility, int inIntellegence, std::string inDescription)
{
    this->name = inName;
    this->type = inType;
    this->hostility = inHostility;
    this->intellegence = inIntellegence;
    this->description = inDescription;
}

Alien generateAlien() //Edits required
{
    std::string name = generateAlienName();
    std::string type;
    int hostility;
    int intellegence;
    std::string description;

    if (name == "Bati")
    {
        type = "Warriors";
        hostility = randomNumGenerator(50, 70);
        intellegence = randomNumGenerator(40, 60);
        description = "Looks Like an A"; //Make up description
    }
    else if (name == "Caladri")
    {
        type = "Traders";
        hostility = randomNumGenerator(10, 30);
        intellegence = randomNumGenerator(30, 80);
        description = "Looks like a B"; //Make up description
    }
    else if (name == "Drul")
    {
        type = "Hive Mind";
        hostility = 100;
        intellegence = 0;
        description = "Looks like a C"; //Make up description
    }
    else if (name == "Naaji")
    {
        type = "Knowledge Seekers";
        hostility = randomNumGenerator(0, 20);
        intellegence = randomNumGenerator(80, 100);
        description = "Looks like a D"; //Make up description
    }
    else
    {
        type = "Timid Nomads";
        hostility = randomNumGenerator(10, 30);
        intellegence = randomNumGenerator(10, 30);
        description = "Looks like an E"; //Make up description
    }

    return Alien(name, type, hostility, intellegence, description);
}

std::string generateAlienName()
{
    std::string names[] = { "Bati","Caladri","Drul","Naaji","Juradoo" }; //Make up good names!!!
    return names[randomNumGenerator(0, 4)];
}