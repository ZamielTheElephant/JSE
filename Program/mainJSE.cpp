#include "mainJSE.h"

int main(int argc, char *argv[])
{
    setRandomSeed();

    ExplorerShip exShip = generateExplorerShip();
    std::cout << exShip.getType() << std::endl;
    std::cout << "The " << exShip.getName() << " launched." << std::endl;
    for(int i = 0; i < atoi(argv[1]); i++)
    {
        std::cout << "Sector " << (i+1) << " Travel" << std::endl;
        resolveSector(exShip, i);

        if(checkDefeatConditions(exShip))
        {
            std::cout << "The Journy Ended in sector number " << i+1 << std::endl;
            break;
        }

        for(int i = 0; i < exShip.getCargoHold().determineAmountOfResources(); i++)
        {
            std::cout << i << std::endl;
            std::cout << exShip.getCargoHold().getResources()[i].getName() << std::endl;
        }

        exShip.repairShip();
        std::cout << "--------------------------------------------" << std::endl;
    }

    std::cout << "Finish" << std::endl;
}
