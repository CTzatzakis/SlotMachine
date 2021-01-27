//
// Created by CNXTU on 27/1/2021.
//

#ifndef SLOTMACHINE_SLOTMACHINE_H
#define SLOTMACHINE_SLOTMACHINE_H
#include <iostream>
using namespace std;

class slots
{
private:
    string welcome;
    int wallet;
    int wager;
    int slotOne;
    int slotTwo;
    int slotThree;
    string singles;
    string pair;
    string threeOfAKind;

    void spin();
    void roundOutcome();
    void wagerSetup();
    static string spinSlots(int x);
    void spinOutput();

public:
    slots();
    void run_slots();

};
#endif //SLOTMACHINE_SLOTMACHINE_H
