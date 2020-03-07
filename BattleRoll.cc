#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Prototypes
string getNextAttack(vector<string> *attacks);
void display(int hp, int atkRoll, int enemyBlock, string msg1, string msg2);
void displayRolls(int atkRoll, int enemyBlock, string msg);
void displayHp(int hp, string msg);


int main()
{
    srand(time(0));
    string attack;
    int hp = 100;
    int atk = 5;
    int dmg = atk;
    int atkRoll, enemyBlock;
    string msg1, msg2;

    vector<string> attacks = { "punch", "kick", "grab" };

    while(hp > 0) {
        dmg = atk;
        atkRoll = 1 + (rand() % 20);
        attack = getNextAttack(&attacks);
        enemyBlock = 1 + (rand() % 20);

        if(atkRoll <= 5) {
            dmg = 0;
            msg1 = "";
            msg2 = "I didn't even have to move for that one. Is that the best you can do?";
        } else if(enemyBlock < atkRoll) {
            if(atkRoll <= 10) {
                msg1 = "You landed a hit!";
                msg2 = "Even a broken clock is right twice a day.";
            } else if(atkRoll <= 15) {
                dmg += 5;
                msg1 = "You landed a strong hit! Extra damage!";
                msg2 = "I'll give you that one, kid.";
            } else {
                dmg += 10;
                msg1 = "Critical hit! The enemy is reeling!";
                msg2 = "Argh! I'll make you pay for this!";
            }
        } else if(enemyBlock == atkRoll) {
            dmg -= 4;
            msg1 = "The enemy blocked your attack! They take reduced damage!";
            msg2 = "Not bad, but you're going to have to try harder than that.";
        } else {
            dmg = 0;
            msg1 = "";
            msg2 = "I am like water.";
        }

        hp -= dmg;
        display(hp, atkRoll, enemyBlock, msg1, msg2);
    }
    
    return 0;
}

//Collect next attack input.
string getNextAttack(vector<string> *attacks) {
    string prompt = "Type ";
    vector<string> atkOpts = *attacks;
    int i = atkOpts.size();
    for(string option : (*attacks)) {
        if(i > 1) {
            prompt += option + ", ";
        } else {
            prompt += "or " + option + ": ";
        }
        i--;
    }

    string selAtk;
    vector<string>::iterator it;
    //Eventually they will type in a valid attack, right????
    while (true) {
        cout << prompt;
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
//Displays results of an attack.
void display(int hp, int atkRoll, int enemyBlock, string msg1, string msg2) {
    displayRolls(atkRoll, enemyBlock, msg1);
    displayHp(hp, msg2);
    cout << endl;
}

//Display attack roll and optionally displays dodge rolls and message if present.
void displayRolls(int atkRoll, int enemyBlock, string msg) {
        cout << "Attack Roll: " << atkRoll << "." << endl;
        if(enemyBlock > 0) 
            cout << "Dodge Roll: " << enemyBlock << "." << endl;
        
        if(msg != "")
            cout << msg << endl;
}

//Displays current HP
void displayHp(int hp, string msg) {
    cout << "EnemyName[HP: " << hp << "] " << msg << endl;   
}