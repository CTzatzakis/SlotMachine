#include <iostream>
#include <climits>
#include <random>
#include <cmath>
#include "SlotMachine.h"

std::random_device rd; //rd may be used as generator but it is rather a fix result.
std::mt19937 mt(rd()); //
//std::uniform_real_distribution<double> dist(1.0, 100.0);

using namespace std;
slots::slots()
        : welcome("***Slot Me The Money***"), wager(0), wallet(100),slotOne(-1),slotTwo(-1),slotThree(-1)
{}

void slots::wagerSetup()
{
    int wagerAmount;
    bool validWager = false;
    while(!validWager)
    {
        cout << "Total Tokens: " << wallet << endl;
        cout << "Choose Wager Amount: ";
        cin >> wagerAmount;
        if(cin.fail()){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl << "Error: Please enter a number" << endl << endl;
        }
        else if(wagerAmount > wallet)
        {
            cout << endl << "Not enough tokens. Please wager lower." << endl
                 << endl;
        }
        else if(wagerAmount < 1){
            cout << endl << "Invalid amount. Please wager at least 1 token."
                 << endl << endl;
        }
        else
        {
            validWager = true;
        }
    }

    this->wager = wagerAmount;
    //cout << string(50, '\n');
    cout << "Wagering " << wagerAmount << " Token(s). Good Luck!" << endl;
}

void slots::spin()
{
    cout << endl << "Spinning!" << endl << endl;
    const bool winner = ( fmod( mt(), 100.0) ) < 20;
    if (winner)
    {
        this->slotOne = this->slotTwo = this->slotThree = fmod( mt(), 6.0) + 1;
    }
    else
    {
        do
        {
            this->slotOne = fmod( mt(), 6.0) + 1;
            this->slotTwo = fmod( mt(), 6.0) + 1;
            this->slotThree = fmod( mt(), 6.0) + 1;
        } while ( slotOne == slotTwo && slotTwo == slotThree );
    }
    this->singles = spinSlots(this->slotOne);
    this->pair = spinSlots(this->slotTwo);
    this->threeOfAKind = spinSlots(this->slotThree);
}


string slots::spinSlots(int currentSlot)
{
    string fruits [] = {"apple", "orange", "cherry", "strawberry", "lemon", "banana"};
    return fruits[currentSlot - 1];
}

void slots::spinOutput()
{
    string one = "?", two = "?", three = "?";
    for(int i = 3; i >= 0; --i)
    {
        cout << "----------------------------------------" << endl;
        cout.width(15); cout << left << one;
        cout.width(15); cout << left << two;
        cout.width(15); cout << left << three << endl;
        cout << "----------------------------------------" << endl;
        //usleep(2000000);
        if(i == 3)
            one = singles;
        else if(i == 2)
            two = pair;
        else if(i == 1)
            three = threeOfAKind;
    }
    roundOutcome();
}

void slots::roundOutcome()
{
    if(slotOne == slotTwo && slotOne == slotThree)
    {
        cout << "Winner! Congratulations!" << endl;
        this->wallet += 2 * wager;
        cout << "New Token Balance: " << wallet << endl;
    }
    else
    {
        cout << "Aww. Better luck next time." << endl;
        this->wallet -= wager;
        cout << "Tokens Remaining: " << wallet << endl;
    }
}

void slots::run_slots()
{
    char gameplay = 'Y';
    bool winner = true;

    while(gameplay != 'n' && gameplay != 'N')
    {
        cout << welcome << endl;
        wagerSetup();
        spin();
        spinOutput();
        if(wallet > 0)
        {
            cout << "Continue Playing? (Y or N): ";
            cin >> gameplay;
            cout << endl;
            while(gameplay != 'n' && gameplay != 'N' && gameplay != 'Y' && gameplay != 'y'){
                cout << "Invalid Option. Continue Playing? (Y or N): ";
                cin >> gameplay;
                cout << endl;
            }
        }
        else
        {
            winner = false;
            break;
        }
    }
    if(winner)
        cout << "Thanks for playing!" << endl << "You ended with " << wallet << " tokens!" << endl;
    else
        cout << "No tokens remaining. You Lose." << endl;
}

int main()
{
    slots play;
    play.run_slots();
    return 0;
}