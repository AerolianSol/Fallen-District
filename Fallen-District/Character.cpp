#include "Character.h"

using namespace std;

//default Character creation that initializes private variables
Character::Character(){
  name = "";
  level = 0;
  exp = 0;
  maxHealth = 0;
  maxDef = 0;
  maxStam = 0;
  atk = 0;
  spd = 0;

  health = 0;
  def = 0;
  stam = 0;

  isStamBroken = false;
  isFighting = true;
}

//returns health
int Character::getHealth(){
  return health;
}

//sets health to _health
void Character::setHealth(int _health){
  health = _health;    
}

//returns maxHealth
int Character::getMaxHealth(){
  return maxHealth;
}

//sets maxHealth to _maxHealth
void Character::setMaxHealth(int _maxHealth){
  maxHealth = _maxHealth;
}

//returns def
int Character::getDef(){
  return def;
}

//sets def to _def
void Character::setDef(int _def){
  def = _def;
} 

//returns maxDef
int Character::getMaxDef(){
  return maxDef;
} 

//sets maxDef to _maxDef
void Character::setMaxDef(int _maxDef){
  maxDef = _maxDef;
}

//returns stam
int Character::getStam(){
  return stam;
} 

//sets stam to _stam
void Character::setStam(int _stam){
  stam = _stam;
} 

//returns maxStam
int Character::getMaxStam(){
  return maxStam;
} 

//sets maxStam to _maxStam
void Character::setMaxStam(int _maxStam){
  maxStam = _maxStam;
} 

//returns name
string Character::getName(){
  return name;
} 

//sets name to _name
void Character::setName(string _name){
  name = _name;
} 

//returns level
int Character::getLevel(){
  return level;
} 

//sets level to _level
void Character::setLevel(int _level){
  level = _level;
} 

//returns exp
int Character::getExp(){
  return exp;
} 

//sets exp to _exp
void Character::setExp(int _exp){
  exp = _exp;
} 

//returns atk
int Character::getAtk(){
  return atk;
} 

//sets atk to _atk
void Character::setAtk(int _atk){
  atk = _atk;
} 

//returns spd
int Character::getSpd(){
  return spd;
} 

//sets spd to _spd
void Character::setSpd(int _spd){
  spd = _spd;
}

//sets isStamBroken to stamBroken
void Character::setStamBroken(bool stamBroken){
  isStamBroken = stamBroken;

  if(stamBroken){
    setDef(0);
  }
  else{
    setStam(getMaxStam());
  }
}

//returns isStamBroken
bool Character::getStamBroken(){
  return isStamBroken;
}

//sets isFighting to con
void Character::setFighting(bool con){
  isFighting = con;
}

//returns isFighting
bool Character::getFighting(){
  return isFighting;
}