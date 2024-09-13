#include "Dancer.h"

using namespace std;

//handles Dancer creation
Dancer::Dancer() : Character(){
  //playstyle: fast, take as many turns as possible but frail and low ATK
  
  setMaxHealth(10);
  setHealth(getMaxHealth());
  setMaxDef(8);
  setDef(getMaxDef());
  setAtk(4);
  setMaxStam(100);
  setStam(getMaxStam());
  setSpd(7);
  setLevel(1);
  setExp(0);
}

//handles enemy Dancer creation that scales to player level
Dancer::Dancer(int _level) : Character(){
  setLevel(_level);
  setName("Dancer");
  setMaxHealth(9 + _level);
  setHealth(getMaxHealth());
  setMaxDef(8);
  setDef(getMaxDef());
  setAtk(3 + _level);
  setMaxStam(99 + _level);
  setStam(getMaxStam());
  setSpd(4 + (_level * 3));
  
  setExp(0);
}

//level up gives Dancer more spd than other RPG classes
void Dancer::levelUp(int _exp){
  setExp(getExp() + _exp);
  
  if(getExp() > 50 + (50 * getLevel())){
    cout << "You feel your potential grow.." << endl << "Level up!" << endl << endl;
  
    setLevel(getLevel() + 1);
    setMaxHealth(getMaxHealth() + 1);
    setHealth(getMaxHealth());
    setDef(getMaxDef());
    setAtk(getAtk() + 1);
    setMaxStam(getMaxStam() + 1);
    setStam(getMaxStam());
    setSpd(getSpd() + 3);
  
    setExp(0);
  }
}

//displays Dancer specific text when choosing basic attack
void Dancer::attackTarget(Character* target){
  if(target->getDef() > 0){
    target->setDef(target->getDef() - 1);
    target->setStam(target->getStam() - 20);
    if(target->getStam() > 0){  
      cout << getName() << " slashes their dual katars at " << target->getName() << " but their defense withstood the laceration." << endl << endl;
    }
    else{
      target->setStamBroken(true);
      cout << "STAMINA BREAK!" << endl;
      cout << getName() << " swings their dual katars at " << target->getName() << " and catches them off guard!" << endl << endl;
    }
  }
  else if(target->getStamBroken()){
    target->setHealth(target->getHealth() - (getAtk() * 2));
    cout << "SLASH!!!" << endl;
    cout << getName() << " drives a katar deep into " << target->getName() << "'s neck, dealing " << getAtk() << " damage!" << endl << endl;
  }
  else{
    target->setHealth(target->getHealth() - getAtk());
    cout << getName() << " drives their dual katars into " << target->getName() << "'s gut, dealing " << getAtk() << " damage!" << endl << endl; 
  }
}

//displays Dancer specific skills
void Dancer::displaySkills(){
  //if Dancer does not have 30 STAM, do not let them use skills
  
  cout << "You crouch low to the ground..." << endl << endl;
  
  cout << "====================" << endl << endl;
  
  cout << "1.) Encore (" << (int)(getMaxHealth() * 0.10) << "HP) - Strike a pose and motivate yourself to continue bladedancing, regenerating " << (int) (getMaxStam() * 0.50)  << "% of your Max STAM. This cannot set you to 0 HP or over your max STAM." << endl;
  cout << "2.) Flourish (40 STAM) - Swipe your dual katars 2 times dealing " << (int)(getAtk() * 0.7) << " DMG and 12 STAM DMG each time for a total of " << (int)(getAtk() * 1.4) << " DMG and 24 STAM DMG. Attacks target's DEF and STAM instead if they have any." << endl;
  cout << "3.) Updraft (30 STAM) - Produce an updraft of wind with your blades that knock your target off their feet, dealing 40 STAM DMG. This pierces through target's DEF." << endl;
  cout << "4.) Blade Dance (75 STAM) - Spin into a bladed whirlwind, slashing your target 3 times and dealing " << (int) (getAtk() * 3) << " total DMG. Attacks target's DEF instead if they have any." << endl << endl;
  
  cout << "====================" << endl << endl;
}

//handles Dancer specific skills if stam > 30
void Dancer::performSkill(int skill, Character* target){
  switch(skill){
    case 1:
      setHealth(getHealth() - (getMaxHealth() * 0.1));
      if(getHealth() <= 0){
        setHealth(1);
      }
      setStam(getStam() + (getMaxStam()*0.5));
      if(getStam() > getMaxStam()){
        setStam(getMaxStam());
      }
      cout << getName() << " strikes a pose and pushes their body even further beyond, regenerating " << getMaxStam() * 0.5 << " STAM!" << endl << endl;
      break;
    case 2:
      setStam(getStam() - 40);
      for(int i = 0; i < 2; i++){
        if(target->getDef() <= 0){
          if(target->getStamBroken()){
            target->setHealth(target->getHealth() - (getAtk()*1.4));
            cout << "SHLK!" << endl;
            cout << getName() << " Flourishes a katar deep into " << target->getName() << "'s open wound for " << (int) (getAtk()*1.4) << " DMG!" << endl;
          }
          else{
            target->setHealth(target->getHealth() - (getAtk()*0.7));
            target->setStam(target->getStam() - 12);

            if(target->getStam() <= 0){
              target->setStamBroken(true);
              cout << "STAMINA BREAK!" << endl;
            }

            cout << getName() << " activates Flourish and slices a katar across " << target->getName() << "'s chest for " << (int)(getAtk()*0.7) << " DMG and 12 STAM DMG!" << endl;
          }
        }
        else{
          target->setDef(target->getDef() - 1);
          target->setStam(target->getStam() - 12);

          if(target->getStam() <= 0){
            target->setStamBroken(true);
            cout << "STAMINA BREAK!" << endl;
            cout << target->getName() << " tried to withstand " << getName() << "'s Flourish but was knocked down!" << endl;
          }
          else{
            cout << getName() << " swiped a Flourish at " << target->getName() << " but they withstood the blow." << endl;
          }
        }
      }
      break;
    case 3:
      setStam(getStam() - 30);
      target->setStam(target->getStam() - 40);
      if(target->getStam() <= 0){
        cout << "STAMINA BREAK!" << endl;
        cout << getName() << " produces an Updraft of wind, tossing " << target->getName() << " up into the air for 40 STAM DMG!" << endl << endl;
      }
      else{
        cout << getName() << " produces an Updraft of air, dealing 40 STAM DMG to " << target->getName() << "!" << endl << endl;
      }
      break;
    case 4:
      setStam(getStam() - 75);
      for(int i = 0; i < 3; i++){
        if(target->getDef() <= 0){
          if(target->getStamBroken()){
            target->setHealth(target->getHealth() - (getAtk()*2));
            cout << "SHLK!" << endl;
            cout << getName() << " drives a bladed katar deep into " << target->getName() << "'s heart for " << getAtk()*2 << " DMG!" << endl;
          }
          else{
            target->setHealth(target->getHealth() - getAtk());

            cout << getName() << " spins a blade into " << target->getName() << "'s chest for " << getAtk() << " DMG!" << endl;
          }
        }
        else{
          target->setDef(target->getDef() - 1);
          cout << getName() << " spun a blade at " << target->getName() << " but they withstood the Blade Dance." << endl;
        }
      }
      break;
    default:
      cout << "Error: invalid option selected" << endl;
      exit(1);
  }
}

//handles player action if playing Dancer
void Dancer::playerAction(Character* enemy){
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
  cout << "2.) Perform a skill" << endl;
  cout << "3.) Flee" << endl;
  
  cout << "====================" << endl << endl;

  int intInput;
  cin >> intInput;
  
  if(intInput == 2 && getStam() <= 30){
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

//handles enemy AI Dancer behavior
void Dancer::enemyAction(Character* player){
  int randNum;

  cout << "Enemy " << getClass() << "'s turn!" << endl << endl;

  if((rand() % 100 + 1) >= 25 && player->getDef() <= 0 && getStam() > 75){
    performSkill(4, player);
  }
  else if((rand() % 100 + 1) >= 55 && getStam() <= 30 && getHealth() > (getMaxHealth() * 0.25)){
    performSkill(1, player);
  }
  else{
    if((rand() % 100 + 1) >= 50 && getStam() > 40){
      performSkill(2, player);
    }
    else if((rand() % 100 + 1) >= 25 && getStam() > 30 && !player->getStamBroken()){
      performSkill(3, player);
    }
    else{
      attackTarget(player);
    }
  }
}

//returns RPG class name
string Dancer::getClass(){
  return "Dancer";
}