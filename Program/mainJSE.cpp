#include "mainJSE.h"

int main(int argc, char *argv[])
{
    setRandomSeed();

    ExplorerShip exShip = generateExplorerShip();

    std::cout << "The " << exShip.getType() << " " << exShip.getName() << " launched." << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    for(int i = 0; i < atoi(argv[1]); i++)
    {
        //Calc Cost of travel and apply to ship
        travelSector(exShip, i);
        std::cout << "Sector " << (i+1) << " Travel" << std::endl;
        resolveSector(exShip, i);

        if(checkDefeatConditions(exShip))
        {
            std::cout << "The Journy Ended in sector number " << i+1 << std::endl;
            break;
        }

        std::cout << "\n---Current Resources---" << std::endl;
        for(int i = 0; i < exShip.getCargoHold().determineAmountOfResources(); i++)
        {
            std::cout << "__" << exShip.getCargoHold().getResources()[i].getName() << "__" << std::endl;
        }
        std::cout << "\nMoney: " << exShip.getCargoHold().getMoney() << " Food: " << exShip.getCargoHold().getFood() << " Fuel: " << exShip.getCargoHold().getFuel() << std::endl;

        //Checking if there is any food or fuel left
        if(exShip.getCargoHold().getFood() <= 0 || exShip.getCargoHold().getFuel() <= 0 )
        {
            std::cout << "Not enough food or fuel to continue" << std::endl;
            std::cout << "The Journy Ended in sector number " << i+1 << std::endl;
            exShip.getLogBook().setFinalState("Out of Resources");
            break;
        }

        exShip.repairShip();
        std::cout << "--------------------------------------------------" << std::endl;
    }
    std::cout << "\n--------------------Final Report----------------------" << std::endl;

    std::cout << "Final Money: " << exShip.getCargoHold().getMoney() << std::endl;
    std::cout << "Final Food: " << exShip.getCargoHold().getFood() << std::endl;
    std::cout << "Final Fuel: " << exShip.getCargoHold().getFuel() << std::endl;
    std::cout << "Total Crew Lost: " << (exShip.getLogBook().getStartCrewNum() - exShip.getCrew().getCrewNum() + 5)  << std::endl;
    std::cout << "Final Ship State: " << exShip.getLogBook().getFinalState() << std::endl;

    std::cout << "--------------------------------------------------\n" << std::endl;
    std::cout << "---------------Officer Death Records---------------" << std::endl;
    for(int i = 0; i < exShip.getLogBook().getCrewDeathRecords().size(); i++)
    {
        std::cout << exShip.getLogBook().getCrewDeathRecords()[i] << std::endl;
    }

    std::cout << "\n-------------------Sector Reports-------------------" << std::endl;
    for(int i = 0; i < exShip.getLogBook().getSectorLogs().size(); i++)
    {
        std::cout << exShip.getLogBook().getSectorLogs()[i];
        std::cout << "--------------------------------------------------" << std::endl;
    }

    std::cout << "End" << std::endl;
}
