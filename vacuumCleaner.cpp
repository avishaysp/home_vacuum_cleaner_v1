#pragma once
#include <string>
#include <iostream>
#include "VacuumCleaner.h"
#include "Algorithm.h"
#include "Sensors/WallSensor.h"
#include "Sensors/DirtSensor.h"
#include "Sensors/BatterySensor.h"

/*VacuumCleaner*/
VacuumCleaner::VacuumCleaner(int maxSteps, int batterySize, House& house) 
    : maxSteps(maxSteps), batterySize(batterySize), house(house), currentLocation(house.docStation), historyPath() {
        this->Wal
    }

void cleanHouse() {
    WallSensor wallSensor;
    DirtSensor dirtSensor;
    BatterySensor batterySensor;
    Algorithm* algo = new Algorithm(wallSensor, dirtSensor, batterySensor);
    for (int i = 0; i < 10; ++i) {
        algo->nextStep()
        Direction = algo.nextStep();
    
    }

    


 
}
        
    
