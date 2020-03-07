#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Prototypes
string getNextAttack(vector<string> *attacks);
void displayRolls(int atkRoll, int enemyBlock, string msg);
void displayHp(int hp, string msg);

int main()
{
    srand(time(0));
    string attack;
    int hp = 100;
    int atk = 5;
    int atkRoll;
    int enemyBlock;
    int heroHP = 100;
    int eatk = 5;
    vector<string> attacks = { "punch", "kick", "grab" };

    while(hp > 0) {
        attack = getNextAttack(&attacks);
        atkRoll = 1 + (rand() % 20);
        if(atkRoll <= 5) {
            displayRolls(atkRoll, 0, "");
            displayHp(hp, "I didn't even have to move for that one. Is that the best you can do?");
        }

        enemyBlock = 1 + (rand() % 20);

        if(enemyBlock < atkRoll) {
            if(atkRoll > 6 && atkRoll <= 10) {
                hp -= atk;
                displayRolls(atkRoll, enemyBlock, "You landed a hit!");
                displayHp(hp, "Even a broken clock is right twice a day.");
            } if(atkRoll > 10 && atkRoll <= 15) {
                hp -=  (atk + 5);
                displayRolls(atkRoll, enemyBlock, "You landed a strong hit! Extra damage!");
                displayHp(hp, "I'll give you that one, kid.");
            } if(atkRoll > 15) {
                hp -= (atk + 10);
                displayRolls(atkRoll, enemyBlock, "Critical hit! The enemy is reeling!");
                displayHp(hp, "Argh! I'll make you pay for this!");
            }
        }

        if(enemyBlock == atkRoll) {
            hp -= (atk - 4);
            displayRolls(atkRoll, enemyBlock, "The enemy blocked your attack! They take reduced damage!");
            displayHp(hp, "Not bad, but you're going to have to try harder than that.");
        } if(enemyBlock > atkRoll) {
            displayRolls(atkRoll, enemyBlock, "");
            displayHp(hp, "I am like water.");
        }
    }
    
    return 0;
}

string getNextAttack(vector<string> *attacks) {
    vector<string> atkOpts = *attacks;

    //Generate prompt for attack input
    string prompt = "Type ";
    int i = atkOpts.size();
    for(string option : atkOpts) {
        if(i > 1) {
            prompt += option + ", ";
        } else {
            prompt += "or " + option;
        }
        i--;
    }
    
    string selAtk;
    vector<string>::iterator it;
    while (true) {
        cout << prompt << endl;
        cin >> selAtk;

        it = find(atkOpts.begin(), atkOpts.end(), selAtk);
        //We found a valid attack.
        if(it != atkOpts.end()) {
            return *it;
        } else {
            cout << "Thats not an attack you fool!" << endl;
        }
    }
}

void displayRolls(int atkRoll, int enemyBlock, string msg) {
        cout << "Attack Roll: " << atkRoll << "." << endl;
        if(enemyBlock > 0) 
            cout << "Dodge Roll: " << enemyBlock << "." << endl;
        
        if(msg != "")
            cout << msg << endl;
}

void displayHp(int hp, string msg) {
    cout << "EnemyName[HP: " << hp << "]" << msg << endl;   
}