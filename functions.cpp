#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "functions.h"

using namespace std;

void buy(Knife knives[], UserData& ud, int& size, char userType[], char userSkin[], AllKnife& allKnives){
  buyInfo();
  int typeIndex = 0;
  int skinIndex = 0;
  int index = 0;
  int targetIndex = 0;
  bool found = false;
  validKnife(allKnives, userType, userSkin, typeIndex, skinIndex, index); 
  for(int i = 0; i<size; i++){
    if(strcmp(knives[i].type, userType) == 0 && strcmp(knives[i].skin, userSkin) == 0){
      found = true;
      targetIndex = i;
      cout << endl << endl;
      //cout << "Located knife in storefront." << endl;
      cout << knives[i].type << " " << knives[i].skin << " $" << knives[i].price << endl;
      if(ud.balance >= knives[i].price){ 
        ud.balance -= knives[i].price;
        ud.userInventory[ud.knifeCount] = knives[i];
        cout << ud.userInventory[ud.knifeCount].type << " " << ud.userInventory[ud.knifeCount].skin << " in your inventory" << endl; 
        ud.knifeCount++;
        cout << "Your remaining balance is: $" << ud.balance << endl;
        removeStore(knives, size, targetIndex);
      } else {
        cout << "Insufficient balance! You have $" << ud.balance << " in balance." << endl; 
      }
    }
  }
  if(!found){
    cout << " Could not locate knife in storefront..." << endl;
  }
}

void sell(Knife knives[], UserData& ud, int& size, char userType[], char userSkin[], AllKnife& allKnives){
  sellInfo();
  int skinIndex = 0;
  int typeIndex = 0;
  int index = 0;
  int target = 0;
  validKnife(allKnives, userType, userSkin, typeIndex, skinIndex, index);
  insertStore(knives, size, allKnives, index, ud);
  ud.balance = allKnives.knives[index].price;
  bool inInventory = checkInventory(ud, allKnives, index, target);
  if(inInventory){
    for(int i = target; i<ud.knifeCount-1; i++){
        ud.userInventory[i] = ud.userInventory[i+1];
    }
    cout << "Removing from inventory.." << endl;
    ud.knifeCount--;
  }
}

bool checkInventory(UserData& ud, AllKnife& allKnives, int index, int& target){
  for(int i = 0; i<ud.knifeCount; i++){
    if(strcmp(allKnives.knives[index].type, ud.userInventory[i].type) == 0 && 
        strcmp(allKnives.knives[index].skin, ud.userInventory[i].skin) == 0){
      target = i;
      return true;
    }
  }
  return false;
}

void trade(Knife knives[], UserData& ud, int& size, char userType[], char userSkin[], AllKnife& allKnives){
  tradeInfo();
  int skinIndex = 0;
  int typeIndex = 0;
  int index = 0;
  char userTypeTrade[MAXCHAR] = {0};
  char userSkinTrade[MAXCHAR] = {0};
  bool found = false;
  int targetIndex = 0;
  cout << "Enter the type of knife from the storefront : ";
  cin.getline(userTypeTrade, MAXCHAR);
  cout << "Enter the skin of the knife from the storefront : ";
  cin.getline(userSkinTrade, MAXCHAR);
  for(int i = 0; i<size; i++){
    if(strcmp(knives[i].type, userTypeTrade) == 0 && strcmp(knives[i].skin, userSkinTrade) == 0){
      cout << endl << endl;
      cout << "Located knife in storefront." << endl;
      cout << knives[i].type << " " << knives[i].skin << " $" << knives[i].price << endl;
      found = true;
    }
    if(found){
      targetIndex = i;
      cout << endl <<"Please enter the name of the knife you wish to trade for it." << endl;
      validKnife(allKnives, userType, userSkin, typeIndex, skinIndex, index);
      if(allKnives.knives[index].price >= knives[i].price){
        int target = 0;
        bool inInventory = checkInventory(ud, allKnives, index, target);
        if(inInventory){
          for(int i = target; i<ud.knifeCount-1; i++){
            ud.userInventory[i] = ud.userInventory[i+1];
          }
          cout << "Removing from inventory.." << endl;
          ud.knifeCount--;
        }
        ud.balance += (allKnives.knives[index].price - knives[i].price);
        ud.userInventory[ud.knifeCount] = knives[i];
        cout << ud.userInventory[ud.knifeCount].type << " " << ud.userInventory[ud.knifeCount].skin << " in your inventory" << endl;  
        ud.knifeCount++;
        insertStore(knives, size, allKnives, index, ud);
        removeStore(knives, size, targetIndex);
      }
      i = size;
    }
  }
  if(!found){
    cout << "Could not find knife in storefront!" << endl;
  }
}

void insertStore(Knife knives[], int& size, AllKnife& allKnives, int index, UserData& ud){
  if(size+1 < DATACAP){
    strcpy(knives[size].type, allKnives.knives[index].type); //NEED TO FIX THIS
    strcpy(knives[size].skin, allKnives.knives[index].skin);
    knives[size].price = allKnives.knives[index].price;
    cout << "Adding " << knives[size].type << " | " << knives[size].skin << " To the store" << endl;
    //ud.balance += knives[size].price;
    //cout << "Added $" << knives[size].price << " to your balance. Your current balance is now $" << ud.balance << endl;
    size++;
  }
}

void removeStore(Knife knives[], int& size, int targetIndex){
  for(int i = targetIndex; i<size-1; i++){
    knives[i] = knives[i+1];
  }
  size--;
}

void validKnife(AllKnife& allKnives, char userType[], char userSkin[], int& typeIndex, int& skinIndex, int& index){
  bool valid = false;
  while(!valid){ //make sure valid knife
    cin.clear();
    cout << "Enter the knife type : ";
    cin.getline(userType, MAXCHAR);
    cout << "Enter the knife skin : ";
    cin.getline(userSkin, MAXCHAR);
    cout << endl;
    if(readType(allKnives, userType, typeIndex)){
        if(readSkin(allKnives, userSkin, skinIndex, typeIndex)){
          index = skinIndex;
          cout << userSkin << " " << userType << " is a valid knife. Price: $" << allKnives.knives[index].price << endl;
          valid = true;
        }
    }else {
      cout << "...Invalid Knife" << endl;
    }
  }
}

bool readSkin(AllKnife& allKnives, char userSkin[], int& skinIndex, int typeIndex){
  for(int i = typeIndex -1; i<allKnives.len; i++){
    if(strcmp(allKnives.knives[i].skin, userSkin) == 0){
      skinIndex = i;
      return true;
    }
  }
  return false;
}

bool readType(AllKnife& allKnives, char userType[], int& typeIndex){
  for(int i = 0; i<allKnives.len; i++){
    if(strcmp(allKnives.knives[i].type, userType) == 0){
      typeIndex = i;
      return true;
    }
  }
  return false;
}

void populateMegaArray(ifstream& datafile, AllKnife& allKnives){
  datafile.ignore(1024, '\n');
  while(!datafile.eof() && allKnives.len < 431){
    datafile.getline(allKnives.knives[allKnives.len].type, MAXCHAR, ',');
    datafile.getline(allKnives.knives[allKnives.len].skin, MAXCHAR, ',');

    datafile >> allKnives.knives[allKnives.len].price;

    datafile.ignore(1024, '\n');

    allKnives.len++;
  }
  allKnives.len--;
}

void readMenu(char& userChar, Knife knives[], int& size, bool& quit, UserData& ud, char userType[], char userSkin[], AllKnife& allKnives){
  displayMenu();
  cin >> userChar;
  cin.clear();
  cin.ignore(100, '\n');
  while(!charValid(userChar)){
    cout << "Please enter a valid character!" << endl;
    displayMenu();
    cin.clear();
    cin.ignore(100, '\n');
    cin >> userChar;
  }

  if(userChar == 'q' || userChar == 'Q'){ //QUIT
    goodbye();
    quit = true; // i know i know
    exit(1); //cheeky sorry :P
  }
  if (userChar == 't' || userChar == 'T'){ //TRADE
    printArray(knives, size);
    trade(knives, ud, size, userType, userSkin, allKnives);
  }
  if (userChar == 'b' || userChar == 'B'){ //BUY
    printArray(knives, size);
    buy(knives, ud, size, userType, userSkin, allKnives);
  }
  if (userChar == 's' || userChar == 'S'){ //SELL
    sell(knives, ud, size, userType, userSkin, allKnives);
  }
  if (userChar == 'p' || userChar == 'P'){ //PRINT KNIVES
    printArray(knives, size);
  }
  if (userChar == 'w' || userChar == 'W'){ //print wallet
    printBalance(ud);
  }
  if (userChar == 'i' || userChar == 'I'){ //print user inventory
    printInventory(ud);
  }
}

bool charValid(char userChar){ //NEED TO ADD ONE TO CHECK BALANCE and INVENTORY (Wallet, Inventory)
  if(userChar == 't' || userChar == 'T' || userChar == 's' || userChar == 'S' 
      || userChar == 'b' || userChar == 'B' || userChar == 'q' || userChar == 'Q'
      || userChar == 'p' || userChar == 'P' || userChar == 'w' || userChar == 'W'
      || userChar == 'i' || userChar == 'I'){
    return true;
  }
  return false;
}

void populateStoreArray(ifstream& ifile, Knife knives[], int& size){
  bool endFound = false;
  ifile.ignore(1024, '\n');
  while(!ifile.eof() && size < 32){

    ifile.getline(knives[size].type, MAXCHAR, ',');
    ifile.getline(knives[size].skin, MAXCHAR, ',');

    ifile >> knives[size].price;
    ifile.ignore(MAXCHAR, '\n');
    size++;

  }
}

void printArray(Knife knives[], int size){
    cout << endl;
    cout << setw(60) << "*****CURRENT KNIVES FOR SALE: *****" << endl;
    cout << endl;
    cout << left << setw(30) << "Knife Type" << setw(30) << "Knife Skin" << setw(15) << "Knife Price" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    for(int i = 0; i<size; i++){
      cout << left<< setw(30) << knives[i].type << setw(30) << knives[i].skin << setw(15) << knives[i].price << endl;
    }
    cout << "----------------------------------------------------------------------------------------------" << endl;
}

bool openFile(ifstream& ifile, char ifileName[]){
  ifile.open(ifileName);
  return ifile.is_open();
}

void welcome(){
  cout << "Welcome to my cutting edge virtual trading environment!" << endl;
  cout << "We will buy any knife, but we only have a limited supply for sale." << endl << endl;
  cout << endl;
  cout << setw(45) << "Buy! Sell! Trade!" << endl << endl;
  cout << "Pick an option from below:" << endl <<endl;
}

void goodbye(){
  cout << endl;
  cout << "Thanks for using my program! We confiscated all your items and balance ;)" << endl;
}

void displayMenu(){
  
  cout << endl;
  cout << "(B)UY KNIFE" << endl;
  cout << "(S)ELL KNIFE" << endl;
  cout << "(T)RADE KNIFE" << endl;
  cout << "(W)ALLET BALANCE" << endl;
  cout << "(I)NVENTORY PRINT" << endl;
  cout << "(P)RINT STOREFRONT" << endl;
  cout << "(Q)UIT PROGRAM" << endl << endl;
}

void buyInfo(){
  cout << endl;
  cout << "Please enter the type and skin of the knife you would like to buy from the storefront! You must have balance to use this feature!" << endl;
  cout << "ex." << endl;
  cout << "Karambit" << endl;
  cout << "Fade" << endl;
  cout << "If you have sufficient balance to buy it then the knife will transfer to your inventory." << endl << endl;
}

void sellInfo(){
  cout << endl;
  cout << "Please enter the type and skin of the knife you would like to sell to us!" << endl;
  cout << "ex." << endl;
  cout << "Butterfly" << endl;
  cout << "Vanilla" << endl;
  cout << "If the knife is valid then we will send you balance for it which you can then use to buy something else." << endl << endl;
}

void tradeInfo(){
  cout << endl;
  cout << "Please enter the type and skin of the knife you want to trade for from the storefront" << endl;
  cout << "ex." << endl;
  cout << "Talon Doppler" << endl;
  cout << "You will then be prompted to enter the type and skin of the knife you would like to trade for it" << endl;
  cout << "ex." << endl;
  cout << "Flip" << endl;
  cout << "Tiger Tooth" << endl;
  cout << "If the price of your knife is equivalent or greater, the trade will go through and you will get the left over balance" << endl << endl;
}

void printBalance(const UserData ud){
  cout << endl;
  cout << "Your current balance is: $" << ud.balance << endl;
}

void printInventory(const UserData ud){
  cout << endl;
  if(ud.knifeCount > 0){
    cout << "Knives in inventory: " << endl;
    for(int i = 0; i<ud.knifeCount; i++){
      cout << ud.userInventory[i].type << " | " << ud.userInventory[i].skin << " | $" << ud.userInventory[i].price << endl;
    }
  } else {
    cout << "Your inventory is empty!" << endl;
  }
}
