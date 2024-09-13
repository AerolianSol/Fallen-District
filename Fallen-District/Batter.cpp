#include "Batter.h"

using namespace std;

//handles Batter creation
Batter::Batter() : Character(){
  //playstyle: health tanky, single hard-hitter but slow and low def
  
  setMaxHealth(25);
  setHealth(getMaxHealth());
  setMaxDef(5);
  setDef(getMaxDef());
  setAtk(8);
  setMaxStam(100);
  setStam(getMaxStam());
  setSpd(3);
  setLevel(1);
  setExp(0);
}

//handles enemy Batter creation scaled to the player's level
Batter::Batter(int _level) : Character(){
  setLevel(_level);
  setName("Batter");
  setMaxHealth(20 + (_level * 5));
  setHealth(getMaxHealth());
  setMaxDef(5);
  setDef(getMaxDef());
  setAtk(5 + (_level * 3));
  setMaxStam(99 + _level);
  setStam(getMaxStam());
  setSpd(2 + _level);
  
  setExp(0);
}

//level up gives Batter more maxHealth and ATK than other RPG classes
void Batter::levelUp(int _exp){
  //Batter gets more max health and ATK than other classes
  setExp(getExp() + _exp);
  
  if(getExp() > 50 + (50 * getLevel())){
    cout << "You feel your potential grow.." << endl << "Level up!" << endl << endl;
  
    setLevel(getLevel() + 1);
    setMaxHealth(getMaxHealth() + 5);
    setHealth(getMaxHealth());
    setDef(getMaxDef());
    setAtk(getAtk() + 3);
    setMaxStam(getMaxStam() + 1);
    setStam(getMaxStam());
    setSpd(getSpd() + 1);
  
    setExp(0);
  }
}

//displays Batter specific text when choosing basic attack
void Batter::attackTarget(Character* target){
  if(target->getDef() > 0){
    target->setDef(target->getDef() - 1);
    target->setStam(target->getStam() - 12);
    if(target->getStam() > 0){  
      cout << getName() << " swings their wooden bat at " << target->getName() << " but their defense held strong." << endl << endl;
    }
    else{
      target->setStamBroken(true);
      cout << "STAMINA BREAK!" << endl;
      cout << getName() << " swings their wooden bat at " << target->getName() << " and stuns them!" << endl << endl;
    }
  }
  else if(target->getStamBroken()){
    target->setHealth(target->getHealth() - (getAtk() * 2));
    cout << "SMAAAASH!" << endl;
    cout << getName() << " drives their wooden bat into " << target->getName() << "'s skull, dealing " << getAtk() << " damage!" << endl << endl;
  }
  else{
    target->setHealth(target->getHealth() - getAtk());
    cout << getName() << " swings their wooden bat into " << target->getName() << "'s gut, dealing " << getAtk() << " damage!" << endl << endl; 
  }
}

//displays Batter specific skills
void Batter::displaySkills(){
  //if Batter does not have 26 STAM or higher, do not let them use skills
  
  cout << "You wind up your baseball bat..." << endl << endl;
  
  cout << "====================" << endl << endl;
  
  cout << "1.) Brainbuster (70 STAM) - Wait for your target's guard to drop and then overhead swing onto their head, destroying all their DEF and dealing " << (int) (getAtk() * 0.5)  << " DMG." << endl;
  cout << "2.) Slide Tackle (30 STAM) - Holster your baseball bat and then go for a slide tackle, dealing " << (int) (getAtk() * 0.5) << " DMG and 40 STAM DMG. Blocked by target's available DEF and doesn't lower DEF." << endl;
  cout << "3.) Strike Out (25 STAM) - Feint a baseball bat swing and instead pitch a high-speed baseball for " << getAtk() << " DMG. This pierces through target's DEF but does not lower target's DEF or STAM." << endl;
  cout << "4.) HOME RUN! (35 STAM) - Swing a devastating blow that deals " << (int) (getAtk() * 3) << " DMG. Blocked by target's available DEF and doesn't lower DEF." << endl << endl;
  
  cout << "====================" << endl << endl;
}

//performs Batter specific skills if stam > 25
void Batter::performSkill(int skill, Character* target){
  switch(skill){
    case 1:
      setStam(getStam() - 70);
      target->setDef(0);
      cout << getName() << " finds an opening and overhead swings into " << target->getName() << "'s head for a Brainbuster, destroying all their DEF and dealing "; 
      if(target->getStamBroken()){
        cout << (int) (getAtk() * 0.5) << " DMG!" << endl << endl;
        target->setHealth(target->getHealth() - ((int) (getAtk() * 0.5)));
      }
      else{
        cout << getAtk() << " DMG!" << endl << endl;
        target->setHealth(target->getHealth() - getAtk());
      }
      break;
    
    case 2:
      setStam(getStam() - 30);
      if(target->getDef() <= 0){  
        target->setStam(target->getStam() - 40);
        if(target->getStam() <= 0){
          target->setStamBroken(true);
          cout << "STAMINA BREAK!" << endl;
        }
        cout << getName() << " goes for a Slide Tackle dealing "; 
        if(target->getStamBroken()){
          target->setHealth(target->getHealth() - getAtk());
          cout << getAtk() << " DMG and 40 STAM DMG to " << target->getName() << "!" << endl << endl;
        }
        else{
          target->setHealth(target->getHealth() - ((int) (getAtk() * 0.5)));
          cout << (int) (getAtk() * 0.5) << " DMG and 40 STAM DMG to " << target->getName() << "!" << endl << endl;
        }
      }
      else{
        cout << getName() << " goes for a Slide Tackle but " << target->getName() << " was not fazed!" << endl << endl;
      }
      break;
    
    case 3:
      setStam(getStam() - 25);
      cout << getName() << " goes for a Strike Out, tossing a literal curveball at " << target->getName() << "'s face and dealing "; 
      if(!target->getStamBroken()){
        target->setHealth(target->getHealth() - getAtk());
        cout << getAtk() << " DMG!" << endl << endl;
      }
      else{
        target->setHealth(target->getHealth() - (getAtk() * 2));
        cout << (getAtk() * 2) << " DMG!" << endl << endl;
      }
      break;
    
    case 4:
      setStam(getStam() - 35);
      if(target->getDef() <= 0){
        cout << "SMAAAAASH!" << endl;
        cout << getName() << " finds the perfect angle and launches " << target->getName() << " across an entire baseball field's length for "; 
        if(target->getStamBroken()){  
          target->setHealth(target->getHealth() - ((int)(getAtk() * 6)));
          cout << (int)(getAtk() * 6) << " DMG! HOME RUN!" << endl << endl;
        }
        else{
          target->setHealth(target->getHealth() - ((int)(getAtk() * 3)));
          cout << (int)(getAtk() * 3) << " DMG! HOME RUN!" << endl << endl;
        }
      }
      else{
        cout << getName() << " finds the perfect angle for a HOME RUN but " << target->getName() << " anticipated the attack and dodged!" << endl << endl;
      }
      break;
    
    default:
      cout << "Error: invalid option selected" << endl;
      exit(1);
  }
}

//handles player selection if playing Batter
void Batter::playerAction(Character* enemy){
  cout << getName() << "'s turn!" << endl << endl;

  cout << "====================" << endl << endl;

  cout << getName() << endl;
  cout << "HP: " << getHealth() << "/" << getMaxHealth() << endl;
  cout << "DEF: " << getDef() << "/" << getMaxDef() << endl;
  cout << "STAM: " << getStam() << "/" << getMaxStam() << endl << endl;

  cout << "Enemy " << enemy->getName() << endl;
  cout << "HP: " << enemy->getHealth() << "/" << enemy->getMaxHealth() << endl;
  cout << "DEF: " << enemy->getDef() << "/" << enemy->getMaxDef() << endl;
  cout << "STAM: " << enemy->getStam() << "/" << enemy->getMaxStam() << endl << endl;
  
  cout << "1.) Basic Attack" << endl;
  cout << "2.) Perform a skill (26 STAM required)" << endl;
  cout << "3.) Flee" << endl;
  
  cout << "====================" << endl << endl;

  int intInput;
  cin >> intInput;

  if(intInput == 2 && getStam() <= 25){
    while(intInput == 2){
      cout << endl << "Insufficient STAM!" << endl << endl;
      cin >> intInput;
    }
  }

  switch(intInput){
    case 1:
      attackTarget(enemy);
      break;
    case 2:
      int skillInput;
      displaySkills();
      cin >> skillInput;
      performSkill(skillInput, enemy); //hoping the player doesn't input an invalid num
      break;
    case 3:
      setFighting(false);
      break;
    default:
      cout << "Error: invalid player action option" << endl;
      exit(1);
  }
}

//handles enemy Batter AI behavior
void Batter::enemyAction(Character* player){
  int randNum;

  cout << "Enemy " << getClass() << "'s turn!" << endl << endl;
  
  if(((rand() % 100 + 1) >= 25 && player->getDef() <= 0)){
    if(((rand() % 100 + 1) >= 25) && getStam() > 35){
      performSkill(4, player);
    }
    else if((rand() % 100 + 1) >= 50 && getStam() > 30){
      performSkill(2, player);
    }
    else{
      attackTarget(player);
    }
  }
  else{
    if((rand() % 100 + 1) >= 50 && getStam() > 25){
      performSkill(3, player);
    }
    else if((rand() % 100 + 1) >= 25 && getStam() > 70){
      performSkill(1, player);
    }
    else{
      attackTarget(player);
    }
  }
}

//returns RPG class name
string Batter::getClass(){
  return "Batter";
}
