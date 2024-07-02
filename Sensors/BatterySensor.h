#pragma once

class BatterySensor {
    int& battery;



public:
    BatterySensor(int& battery); // Constructor
    int getBattery() const;
    void setBattery(int newBattery);

};
