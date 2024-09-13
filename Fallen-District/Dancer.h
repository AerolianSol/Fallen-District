#ifndef DANCER.C++
#define DANCER.C++

#include "Character.h"

using namespace std;

class Dancer : public Character{
  private:
    
  public:
    Dancer();
    Dancer(int _level); //used to create an enemy of player's level
	  void levelUp(int _exp);
	  void attackTarget(Character* target);
	  void displaySkills();
	  void performSkill(int skill, Character* target);
    string getClass();
    void playerAction(Character* player);
    void enemyAction(Character* player);
};

#endif