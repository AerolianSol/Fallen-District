#include "Gunslinger.h"

using namespace std;

//handles Gunslinger creation
Gunslinger::Gunslinger() : Character(){
  //playstyle: balanced and neutral stats
  
  setMaxHealth(15);
  setHealth(getMaxHealth());
  setMaxDef(5);
  setDef(getMaxDef());
  setAtk(6);
  setMaxStam(100);
  setStam(getMaxStam());
  setSpd(5);
  setLevel(1);
  setExp(0);
}

//handles enemy Gunslinger creation that scales to player level
Gunslinger::Gunslinger(int _level) : Character(){
  setLevel(_level);
  setName("Gunslinger");
  setMaxHealth(12 + (_level * 3));
  setHealth(getMaxHealth());
  setMaxDef(5);
  setDef(getMaxDef());
  setAtk(4 + (_level * 2));
  setMaxStam(99 + _level);
  setStam(getMaxStam());
  setSpd(3 + (_level * 2));
  
  setExp(0);
}

//level up for Gunslinger gives balanced attribute increase compared to other RPG classes
void Gunslinger::levelUp(int _exp){
  setExp(getExp() + _exp);
  
  if(getExp() > 50 + (50 * getLevel())){
    cout << "You feel your potential grow.." << endl << "Level up!" << endl << endl;
  
    setLevel(getLevel() + 1);
    setMaxHealth(getMaxHealth() + 3);
    setHealth(getMaxHealth());
    setDef(getMaxDef());
    setAtk(getAtk() + 2);
    setMaxStam(getMaxStam() + 1);
    setStam(getMaxStam());
    setSpd(getSpd() + 2);
  
    setExp(0);
  }
}

//displays Gunslinger specific text when choosing basic attack
void Gunslinger::attackTarget(Character* target){
  if(target->getDef() > 0){
    target->setDef(target->getDef() - 2);
    target->setStam(target->getStam() - 16);
    if(target->getStam() > 0){  
      cout << getName() << " fires at " << target->getName() << " twice but their defense withstood the shots." << endl << endl;
    }
    else{
      target->setStamBroken(true);
      cout << "STAMINA BREAK!" << endl;
      cout << getName() << " fires at " << target->getName() << ", sneaking a shot at their ankles and stunning them!" << endl << endl;
    }
  }
  else if(target->getStamBroken()){
    target->setHealth(target->getHealth() - (getAtk() * 2));
    cout << "BANG! BANG! BANG!" << endl;
    cout << getName() << " fires point blank at " << target->getName() << "'s head, dealing " << getAtk() << " damage!" << endl << endl;
  }
  else{
    target->setHealth(target->getHealth() - getAtk());
    cout << getName() << " shoots true into " << target->getName() << "'s gut, dealing " << getAtk() << " damage!" << endl << endl; 
  }
}

////displays Gunslinger specific skills
void Gunslinger::displaySkills(){
  //if Batter does not have 26 STAM or higher, do not let them use skills
  
  cout << "You reload your revolver..." << endl << endl;
  
  cout << "====================" << endl << endl;
  
  cout << "1.) Flashbang (30 STAM) - Reach into your belt and lob a flashbang at your target, dealing 40 STAM DMG." << endl;
  cout << "2.) Pistol Whip (20 STAM) - Feint a shot and sprint towards the target into a pistol whip, dealing " << (int) (getAtk() * 0.5) << " DMG and 15 STAM DMG. This pierces through target's DEF." << endl;
  cout << "3.) Double Tap (35 STAM) - Fire twice at the target for " << getAtk() * 2 << " DMG and 30 STAM DMG. Blocked by target's DEF and does not lower target's DEF." << endl;
  cout << "4.) Full Chamber (55 STAM) - Shoot 6 rounds into the target, dealing " << (int)(getAtk() * 0.5) << " DMG each for " << getAtk() * 3 << " total DMG. Blocked by target's available DEF and doesn't lower DEF." << endl << endl;
  
  cout << "====================" << endl << endl;
}

//handles Gunslinger specific skills if stam > 
void Gunslinger::performSkill(int skill, Character* target){
  switch(skill){
    case 1:
      setStam(getStam() - 30);
      target->setStam(target->getStam() - 40);
      if(target->getStam() <= 0){
        target->setStamBroken(true);
        cout << "STAMINA BREAK!" << endl;
        cout << getName() << " lobs a Flashbang at " << target->getName() << ", stunning them for 30 STAM DMG!" << endl << endl;
      }
      else{
        cout << getName() << " chucks a Flashbang, dealing 40 STAM DMG to " << target->getName() << "!" << endl << endl;
      }
      break;
    case 2:
      setStam(getStam() - 20);
      target->setHealth(target->getHealth() - (int) (getAtk() * 0.5));
      target->setStam(target->getStam() - 15);
      if(target->getStam() <= 0){
        target->setStamBroken(true);
        cout << "STAMINA BREAK!" << endl;
      }
      cout << getName() << " readies a shot but ducks and then pistol whips " << target->getName() << "'s face, dealing " << (int) (getAtk() * 0.5) << " DMG and 15 STAM DMG!" << endl << endl;
      break;
    case 3:
      setStam(getStam() - 35);
      if(target->getDef() <= 0){  
        target->setHealth(target->getHealth() - (getAtk() * 2));
        target->setStam(target->getStam() - 35);
        if(target->getStam() <= 0){
          target->setStamBroken(true);
          cout << "STAMINA BREAK!" << endl;
        }
        cout << getName() << " fires twice, dealing " << getAtk() * 2 << " DMG and 35 STAM DMG to " << target->getName() << "!" << endl << endl;
      }
      else{
        cout << getName() << " goes for a Double Tap but " << target->getName() << " zipped out of the way!" << endl << endl;
      }
      break;
    case 4:
      setStam(getStam() - 55);
      if(target->getDef() <= 0){
        target->setHealth(target->getHealth() - ((int) (getAtk() * 3)));
        cout << "BANG BANG BANG!" << endl;
        cout << getName() << " catches " << target->getName() << " off guard and empties their revolver's entire chamber into them for " << (int) (getAtk() * 3) << " DMG!" << endl << endl;
      }
      else{
        cout << getName() << " empties their revolver's entire chamber into " << target->getName() << " but anticipated the attack and dodged!" << endl << endl;
      }
      break;
    default:
      cout << "Error: invalid option selected" << endl;
      exit(1);
  }
}

//handles player action if playing Gunslinger
void Gunslinger::playerAction(Character* enemy){
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

  if(intInput == 2 && getStam() <= 20){
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

//handles enemy AI Gunslinger behavior
void Gunslinger::enemyAction(Character* player){
  int randNum;

  cout << "Enemy " << getClass() << "'s turn!" << endl << endl;

  if(((rand() % 100 + 1) >= 25 && player->getDef() <= 0)){
    if(((rand() % 100 + 1) >= 50) && getStam() > 35){
      performSkill(3, player);
    }
    else if((rand() % 100 + 1) >= 25 && getStam() > 55){
      performSkill(4, player);
    }
    else if((rand() % 100 + 1) >= 65 && getStam() > 30){
      performSkill(1, player);
    }
    else{
      attackTarget(player);
    }
  }
  else{
    if((rand() % 100 + 1) >= 55 && getStam() > 30){
      performSkill(1, player);
    }
    else if((rand() % 100 + 1) >= 75 && getStam() > 20){
      performSkill(2, player);
    }
    else{
      attackTarget(player);
    }
  }
}

//returns RPG class name
string Gunslinger::getClass(){
  return "Gunslinger";
}