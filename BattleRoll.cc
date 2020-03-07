#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

//Prototypes
string getNextAttack(vector<string> *attacks);
void display(int hp, int atkRoll, int enemyBlock, string msg1, string msg2);
void displayRolls(int atkRoll, int enemyBlock, string msg);

class Game {

    vector<Player> players;
    vector<Player>::iterator playerIT;

    public:
        
        Game(vector<Player> players) {
            this->players = player;
        }

        bool isOver() {
            for(Player player : players) {
                if(player.getHp() <= 0) //If there is a player no HP The game is over.
                    return true;
            }
            return false;
        }

        Player getNextPlayer() {
            next(playerIT);
            if(playerIT == players.end()) {
                playerIT = players.begin();
            }
            return *playerIT;
        }
}

class Player {
    int hp = 100;
    int atkPower = 5;
    string name;
    bool isHuman;

    public:
        Player (string name, bool isHuman) {
            this->name = name;
            this->isHuman = isHuman;
        }

        Player(int hp, int atkPower, string name, bool isHuman) {
            this->hp = hp;
            this->atkPower = atkPower;
            this->name = name;
            this->isHuman = isHuman;
        }

        bool isHuman() {
            return this->isHuman;
        }

        int getHp() {
            return this->hp;
        }

        //Displays current HP
        void displayHp() {
            this->displayHp("");
        }
        
        void displayHp(string msg) {
            cout << this-> name << " - [HP: " << this->hp << "] " << msg << endl;   
        }
};

class AttackType {
    string name;
    int atkPower;

    public:
        AttackType(string name, int atkPower) {
            this.name = name;
            this.atkPower = atkPower;
        }

        string getName() {
            return this->name;
        }

        int getAtkPower() {
            return this->atkPower;
        }
};

class AttackSelector {
    vector<AttackType> atkOpts;

    public:
        void setAttackOptions(vector<AttackType> atkOpts) {
            this->atkOpts = atkOpts;
        }

        AttackType selectAttack() {
            string prompt = "Type ";
    
            int i = this->atkOpts.size();
            for(AttackType option : this->atkOpts) {
                if(i > 1) {
                    prompt += option.getName() + ", ";
                } else {
                    prompt += "or " + option.getName() + ": ";
                }
                i--;
            }

            string selAtk;
            vector<string>::iterator it;
            //Eventually they will type in a valid attack, right????
            while (true) {
                cout << prompt;
                cin >> selAtk;    
                it = find(this->atkOpts.begin(), this->atkOpts.end(), selAtk);
                //We found a valid attack.
                if(it != this->atkOpts.end()) {
                    return *it;
                } else {
                    cout << "Thats not an attack option you fool!" << endl;
                }
            }
        }
};

class QuipGenerator {
    string dodgeQuoip = "I am like water." ;
    string blockQuip = "Not bad, but you're going to have to try harder than that.";
    string whiffQuip = "I didn't even have to move for that one. Is that the best you can do?";
    string hitQuip = "Even a broken clock is right twice a day.";
    string strongQuip = "I'll give you that one, kid.";
    string critQuip = "Argh! I'll make you pay for this!";

    public:
        string generateQuip(int atkRoll, int blockRoll) {
            if(atkRoll <= 5) {
                return whiffQuip;
            } else if(blockRoll < atkRoll) {
                if(atkRoll <= 10) {
                    return hitQuip;
                } else if(atkRoll <= 15) {
                    return strongQuip;
                } else {
                    return critQuip;
                }
            } else if(blockRoll == atkRoll) {
                return blockQuip;
            } else {
                return dodgeQuoip;
            }
        }

};

int main()
{
    srand(time(0));
    string attack;
    int hp = 100;
    int atk = 5;
    int dmg = atk;
    int atkRoll, enemyBlock;
    string msg1, msg2;
    

    cout << "Enter your name: ";
    string name;
    cin >> name;

    Player p1(name, true);
    Player p2("Bruce Lee", false);
    
    QuipGenerator quips;

    AttackType punch("punch", 10);
    AttackType kick("kick", 20);
    AttackType grab("grab", 30);

    vector<AttackType> atacks { punch, kick, grab };
    AttackSelector atkSelector(attacks);

    vector<Player> players = { p1, p2 }
    Game game(players);
    Player currPlayer;
    
    while(!game.isOver()) {
        currPlayer = game.getNextPlayer();
        dmg = currPlayer.atkPower;
        atkRoll = 1 + (rand() % 20);
        
        enemyBlock = 1 + (rand() % 20);

        if(atkRoll <= 5) {
            dmg = 0;
            msg1 = "";
        } else if(enemyBlock < atkRoll) {
            if(atkRoll <= 10) {
                msg1 = "You landed a hit!";
            } else if(atkRoll <= 15) {
                dmg += 5;
                msg1 = "You landed a strong hit! Extra damage!";
            } else {
                dmg += 10;
                msg1 = "Critical hit! The enemy is reeling!";
            }
        } else if(enemyBlock == atkRoll) {
            dmg -= 4;
            msg1 = "The enemy blocked your attack! They take reduced damage!";
        } else {
            dmg = 0;
            msg1 = "";
        }
        
        hp -= dmg;

        msg2 = quips.generateQuip(atkRoll, enemyBlock);
        msg1 = quips.generateSysMsg(atkRoll, )
        display(hp, atkRoll, enemyBlock, msg1, msg2);
    }
    
    return 0;
}

//Collect next attack input.

//Displays results of an attack.
void display(int hp, int atkRoll, int enemyBlock, string msg1, string msg2) {
    displayRolls(atkRoll, enemyBlock, msg1);
    //displayHp(hp, msg2);
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



