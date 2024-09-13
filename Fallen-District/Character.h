#ifndef CHARACTER.C++
#define CHARACTER.C++

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Character{
  public:
    Character(); //initializes private variables
    int getHealth(); //gets health 
    void setHealth(int _health); //sets health 
    int getMaxHealth(); //gets maxHealth 
    void setMaxHealth(int _maxHealth); //sets maxHealth 
    int getDef(); //gets def 
    void setDef(int _def); //sets def 
    int getMaxDef(); //gets maxDef 
    void setMaxDef(int _maxDef); //sets maxDef
    int getStam(); //gets stam 
    void setStam(int _stam); //sets stam 
    int getMaxStam(); //gets maxStam 
    void setMaxStam(int _maxStam); //sets maxStam 
    string getName(); //gets name 
    void setName(string _name); //sets name 
    int getLevel(); //gets level 
    void setLevel(int _level); //sets level 
    int getExp(); //gets exp 
    void setExp(int _exp); //sets exp 
    int getAtk(); //gets atk 
    void setAtk(int _atk); //sets atk 
    int getSpd(); //gets spd 
    void setSpd(int _spd); //sets spd

    void setStamBroken(bool stamBroken);
    bool getStamBroken();

    void setFighting(bool con);
    bool getFighting();

    //all virtual functions for inherited classes to handle
    virtual string getClass() = 0;
    virtual void levelUp(int _exp) = 0;
	  virtual void attackTarget(Character* target) = 0;
    virtual void displaySkills() = 0;
    virtual void playerAction(Character* enemy) = 0;
    virtual void enemyAction(Character* player) = 0;

  private:
    string name; //identifier for player
    bool isStamBroken; //if getStam() >= 0, set true, setDef(0), skip turn 
    bool isFighting; //checks to see if player is fleeing during combat
    int health; //if 0, lose
    int maxHealth;
    int atk; //determines damage output
    int spd; //determines turn order; if doubles the target's spd, take two turns
    int def; //def indicates amount of atks nullified and reduces by 1 for each atk blocked
    int maxDef; //use multi-hit attacks to break def
    int stam; //used for skill moves
    int maxStam; //if stam reaches 0, isStamBroken = true
    int level; //player uses level to determine maxExp; enemy uses level to scale stats to player
    int exp; //determines if player levels up    
};

#endif