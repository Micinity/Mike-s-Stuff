#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Prototypes
string getNextAttack(vector<string> *attacks);

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
    vector<string> attacks = {"punch", "kick", "grab"};

    while(hp > 0) {
        attack = getNextAttack(&attacks);
        atkRoll = 1 + (rand() % 20);
        if(atkRoll <= 5) {
            cout << "Attack Roll: " << atkRoll << "." << endl;
            cout << "Your attack was too slow!" << endl;
            cout << "EnemyName[HP: " << hp << "] I didn't even have to move for that one. Is that the best you can do?" << endl;
        }

        enemyBlock = 1 + (rand() % 20);

        if(enemyBlock < atkRoll) {
            if(atkRoll > 6 && atkRoll <= 10) {
                hp = hp - atk;
                cout << "Attack Roll: " << atkRoll << "." << endl;
                cout << "Dodge Roll: " << enemyBlock << "." << endl;
                cout << "You landed a hit!" << endl;
                cout << "EnemyName[HP: " << hp << "] Even a broken clock is right twice a day." << endl;
            } if(atkRoll > 10 && atkRoll <= 15) {
                hp = hp - (atk + 5);
                cout << "Attack Roll: " << atkRoll << "." << endl;
                cout << "Dodge Roll: " << enemyBlock << "." << endl;
                cout << "You landed a strong hit! Extra damage!" << endl;
                cout << "EnemyName[HP: " << hp << "] I'll give you that one, kid." << endl;
            } if(atkRoll > 15) {
                hp = hp - (atk + 10);
                cout << "Attack Roll: " << atkRoll << "." << endl;
                cout << "Dodge Roll: " << enemyBlock << "." << endl;
                cout << "Critical hit! The enemy is reeling!" << endl;
                cout << "EnemyName[HP: " << hp << "] Argh! I'll make you pay for this!" << endl;
            }

        }
        
        if(enemyBlock == atkRoll) {
            cout << "Attack Roll: " << atkRoll << "." << endl;
            cout << "Dodge Roll: " << enemyBlock << "." << endl;
            cout << "The enemy blocked your attack! They take reduced damage!" << endl;
            hp = hp - (atk - 4);
            cout << "EnemyName[HP: " << hp << "] Not bad, but you're going to have to try harder than that." << endl;
        } if(enemyBlock > atkRoll) {
            cout << "Attack Roll: " << atkRoll << "." << endl;
            cout << "Dodge Roll: " << enemyBlock << "." << endl;
            cout << "EnemyName[HP: " << hp << "] I am like water." << endl;
        }
    }
    return 0;
}

string getNextAttack(vector<string> *attacks) {
    string attack;
    vector<string> atks = *attacks;
    vector<string>::iterator it;
    
    //Generate prompt for attack input
    string prompt = "Type ";
    int lenAtks = atks.size();
    int i = 0;
    for(string atk : atks) {
        if(i < (lenAtks - 1)) {
            prompt += atk + ", ";
        } else {
            prompt += "or " + atk;
        }
        i++;
    }

    while (true) {
        cout << prompt << endl;
        cin >> attack;

        it = find(atks.begin(), atks.end(), attack);
        //We found a valid attack.
        if(it != atks.end()) {
            return *it;
        }
    }
}