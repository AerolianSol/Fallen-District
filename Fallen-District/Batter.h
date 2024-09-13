#ifndef BATTER.C++
#define BATTER.C++

#include "Character.h"

using namespace std;

class Batter : public Character{
  private:
    
  public:
    Batter();
    Batter(int _level);
	  void levelUp(int _exp);
	  void attackTarget(Character* target);
	  void displaySkills();
    void performSkill(int skill, Character* target);
    string getClass();
    void playerAction(Character* player);
    void enemyAction(Character* player);
};

#endif