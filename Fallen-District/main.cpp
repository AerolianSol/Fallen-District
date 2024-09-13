#include "Batter.h"
#include "Gunslinger.h"
#include "Dancer.h"
#include <iostream>
#include <string>

using namespace std;

//handles the new character creation
Character* newCharCreation(Character* player){
  cout << endl << "Amongst the anarchy of the Fallen District..." << endl;
  cout << "...a voice calls out from the slums." << endl << endl;
  cout << "Select your class." << endl << endl;
  cout << "1.) The Batter - An individual wielding a wooden baseball bat. This archetype excels in delivering destructive strikes and shrugging off damage but is noticably slow to act." << endl;
  cout << "2.) The Gunslinger - An individual wielding a lever-action rifle. This archetype does not particularly excel in any talent nor do they have any noticeable debilitations." << endl;
  cout << "3.) The Dancer - An individual wielding dual katars. This archetype excels in being nimble and debilitating the enemy but is noticably frail in vitality and strength." << endl << endl;

  int input;
  cin >> input;

  while(input < 1 || input > 3)
  {
    cout << "Invalid input. Please input a valid numerical option." << endl;
    cin >> input;
  }

  switch(input){
    case 1:
      player = new Batter();
      cout << endl << "The crack of your wooden bat rings throughout the Fallen District as you fell another bandit." << endl << "Home run." << endl << endl;
      break;
    case 2:
      player = new Gunslinger();
      cout << endl << "A powerful blast alerts everyone nearby that you've claimed your next victim." << endl << "Bullseye." << endl << endl;
      break;
    case 3:
      player = new Dancer();
      cout << endl << "A graceful flip over the bandit spells doom for them as you run your katars through their neck." << endl << "Bravo!" << endl << endl;
      break;
    default:
      cout << "Archetype error" << endl;
      exit(1);
      break;
  }
  
  cout << "As you stare at your fresh kill, you perk your head up at the mention of your name." << endl << "What was your name again?" << endl;
  
  string strInput;
  cin >> strInput;
  player->setName(strInput);

  cout << endl << "It's the barkeep who called out your name. He thanks you for defending his establishment once again and welcomes you in to the Black Lagoon." << endl << "As you settle into a seat, you ponder your next course of action." << endl << endl;

  return player;
}

//handles the save IO file function
void saveCharFile(Character* player){
  cout << endl << "Input a name for your file." << endl;

  string strTemp;
  cin >> strTemp;
  
  ofstream fOutput(strTemp + ".txt");
  int intTemp;
  
  if(!fOutput.is_open()){
    cout << "Error: File failed to open." << endl;
    exit(1);
  }

  strTemp = player->getClass();
  fOutput << strTemp << endl;

  strTemp = player->getName();
  fOutput << strTemp << endl;

  intTemp = player->getLevel();
  fOutput << intTemp << endl;

  intTemp = player->getExp();
  fOutput << intTemp << endl;

  intTemp = player->getMaxHealth();
  fOutput << intTemp << endl;

  intTemp = player->getMaxDef();
  fOutput << intTemp << endl;

  intTemp = player->getMaxStam();
  fOutput << intTemp << endl;

  intTemp = player->getAtk();
  fOutput << intTemp << endl;

  intTemp = player->getSpd();
  fOutput << intTemp;

  fOutput.close();

  cout << endl << "File was successfully saved." << endl << endl;
}

//handles the load IO file function
Character* loadCharFile(Character* player){
  string fileName, strInput;
  int intInput;
  cout << "Input a valid file name. This includes .txt at the end." << endl;
  cin >> fileName;
  
  ifstream fInput(fileName);
  
  if(!fInput.is_open()){
    cout << "Error: File name was invalid." << endl;
    exit(1);
  }
  
  fInput >> strInput;
  if(strInput == "Batter"){
    player = new Batter();
  }
  else if(strInput == "Gunslinger"){
    player = new Gunslinger();
  }
  else if(strInput == "Dancer"){
    player = new Dancer();
  }
  else{
    cout << "Error: Failed to load valid text file." << endl;
    exit(1);
  }

  fInput >> strInput;
  player->setName(strInput);

  fInput >> strInput;
  intInput = stoi(strInput);
  player->setLevel(intInput);

  fInput >> strInput;
  intInput = stoi(strInput);
  player->setExp(intInput);

  fInput >> strInput;
  intInput = stoi(strInput);
  player->setMaxHealth(intInput);
  player->setHealth(intInput);

  fInput >> strInput;
  intInput = stoi(strInput);
  player->setMaxDef(intInput);
  player->setDef(intInput);

  fInput >> strInput;
  intInput = stoi(strInput);
  player->setMaxStam(intInput);
  player->setStam(intInput);

  fInput >> strInput;
  intInput = stoi(strInput);
  player->setAtk(intInput);

  fInput >> strInput;
  intInput = stoi(strInput);
  player->setSpd(intInput);

  fInput.close();
  
  return player;
}

//handles the game loop's main menu
int mainMenu(Character* player){
  int result;

  cout << "====================" << endl << endl;
  
  cout << "Welcome to the Black Lagoon. It's not a place to feel safe but to feel at ease." << endl << endl;
  
  cout << "1.) Look for a duel." << endl;
  cout << "2.) Save." << endl;
  cout << "3.) Load a character file." << endl;
  cout << "4.) Exit the game." << endl << endl;
  
  cout << "====================" << endl << endl;

  cin >> result;

  while(result < 1 || result > 4){
    cout << "Invalid input. Please input a valid numerical option." << endl;
    cin >> result;
    cout << endl;
  }
  
  return result;
}

//handles the game loop's combat
void initiateCombat(Character* player){
  Character* enemy;
  int num = (rand() % 3) + 1;

  cout << "You get off your seat and head out into the land of the Fallen District." << endl << endl;
  cout << "After an hour of trekking, you come across a " << endl;
  
  switch(num){
    case 1:
      enemy = new Batter(player->getLevel());
      cout << "Batter wielding a wooden baseball bat. They don't look particularly friendly to your intrusion." << endl << endl;
      break;
    case 2:
      enemy = new Gunslinger(player->getLevel());
      cout << "Gunslinger drawing a steel revolver. The spin of the chamber suggests hostile intent." << endl << endl;
      break;
    case 3:
      enemy = new Dancer(player->getLevel());
      cout << "Dancer scraping their dual katars against each other. Their omnious giggle unnerves you." << endl << endl;
      break;
    default:
      cout << "Error: Failed to load enemy." << endl;
      exit(1);
  }

  cout << "You prepare yourself for a battle." << endl << endl;
  
  while(player->getHealth() > 0 && enemy->getHealth() > 0 && player->getFighting()){
    int speedAdvantage;

    if(player->getSpd() >= enemy->getSpd() || enemy->getStamBroken()){
      speedAdvantage = player->getSpd() / enemy->getSpd();

      if(!player->getStamBroken()){
        for(int i = 1; i <= speedAdvantage; i++){
        //provide choices for player
        player->playerAction(enemy);
        player->setStam(player->getStam() + 10);
        }
      }
      else{
        player->setStam(player->getMaxStam());
        player->setStamBroken(false);
      }
      
      if(!enemy->getStamBroken() && enemy->getHealth() > 0){
        enemy->enemyAction(player);
        enemy->setStam(enemy->getStam() + 10);
      }
      else{
        enemy->setStam(enemy->getMaxStam());
        enemy->setStamBroken(false);
      }
    }
    else if(player->getSpd() < enemy->getSpd() || player->getStamBroken()){
      speedAdvantage = enemy->getSpd() / player->getSpd();

      if(!enemy->getStamBroken()){
        for(int i = 1; i <= speedAdvantage; i++){
          enemy->enemyAction(player);
          enemy->setStam(enemy->getStam() + 10);
        }
      }
      else{
        enemy->setStam(enemy->getMaxStam());
        enemy->setStamBroken(false);
      }
      
      //provide choices for player
      if(!player->getStamBroken() && player->getHealth() > 0){
        player->playerAction(enemy);
        player->setStam(player->getStam() + 10);
      }
      else{
        player->setStam(player->getMaxStam());
        player->setStamBroken(false);
      }
    }
  }

  if(enemy->getHealth() <= 0){
    cout << "The " << enemy->getName() << " stumbles onto their knees, body swaying in the air before collapsing onto the ground without a word." << endl;
    cout << "You sigh and holster your weapon, turning to head back to the Black Lagoon." << endl;
    cout << "About an hour of walking later, you settle back into a seat at the Black Lagoon." << endl << endl;

    player->levelUp(50 + (enemy->getLevel() * 25));
    player->setHealth(player->getMaxHealth());
    player->setDef(player->getMaxDef());
    player->setStam(player->getMaxStam());
  }
  else if(player->getHealth() <= 0){
    delete enemy;
    cout << "You stumble onto your knees, feeling the world spin around you." << endl;
    cout << "Your opponent walks up to you, pity in their eyes." << endl;
    cout << "Then, the world around you goes dark." << endl << endl;
    cout << "GAME OVER." << endl;
    exit(0);
  }
  else{
    cout << "You cut your losses and begin to run..." << endl;
    cout << "After thirty minutes of running, you safely make it back to the Black Lagoon." << endl << endl;

    player->setHealth(player->getMaxHealth());
    player->setDef(player->getMaxDef());
    player->setStam(player->getMaxStam());
    player->setFighting(true);
  }

  delete enemy;
}

//run on start up
int main() {
  cout << "====================" << endl << endl;
  
  cout << "FALLEN DISTRICT" << endl << endl;
  
  cout << "1.) Create a new character." << endl;
  cout << "2.) Load an existing save file." << endl;
  cout << "3.) Exit the game." << endl << endl;
  
  cout << "====================" << endl << endl;

  int numInput;
  cin >> numInput;
  cout << endl;
  
  while(numInput < 1 || numInput > 3){
    cout << "Invalid input. Please input a valid numerical option." << endl;
    cin >> numInput;
    cout << endl;
  }

  Character* player;

  switch(numInput){
    case 1:
      player = newCharCreation(player);
      break;
    case 2:
      player = loadCharFile(player);
      cout << endl << player->getName() << " was successfully loaded." << endl << endl;
      cout << "You wake up from your nap, pondering your next move." << endl << endl;
      break;
    case 3:
      cout << "Exiting game..." << endl;
      exit(0);
    default:
      cout << "Menu error" << endl;
      exit(1);
  }

  bool gameLoop = true;
  while(gameLoop){
    numInput = mainMenu(player);
    
    switch(numInput){
      case 1:
        initiateCombat(player);
        break;
      case 2:
        saveCharFile(player);
        break;
      case 3:
        player = loadCharFile(player);
        cout << endl << player->getName() << " was successfully loaded." << endl;
        break;
      case 4:
        cout << endl << "You rest your head on the table, dreaming of a better tomorrow..." << endl << endl;
        gameLoop = false;
        break;
      default:
        cout << "Main menu error" << endl;
        exit(1);
    }
  }

  cout << "Exiting game..." << endl;
  delete player;
  
  return 0;
}