#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

const int MAXCHAR = 128;
const int DATACAP = 32;

const int MEGACAP = 432; //to store every possible knife and skin

using namespace std;

//store knives
typedef struct{
  char type[MAXCHAR]; //type of knife (bayonet, karambit, butterfly)
  char skin[MAXCHAR]; //which skin (doppler, fade, vanilla)
  int price; //price of the given skin
}Knife;

//database knives
struct AllKnife{
  Knife knives[MEGACAP];
  int len; //length of mega array
};
//userData (balance, inventory)
struct UserData{
  Knife userInventory[DATACAP]; //make sure user cant own more than 32 knives for printing sake
  int knifeCount; //amount of knives user has for prining
  int balance; //user balance
};

//WELCOME/GOODBYE/MENU/PRINT
void welcome(); //welcome message
void displayMenu(); //displays menu options
void goodbye(); //goodbye message
void printArray(Knife[], int); //prints array nicely
void buyInfo(); //info to teach user to buy
void sellInfo(); //info to teach user to sell
void tradeInfo(); //info to teach user to trade
void printBalance(const UserData);
void printInventory(const UserData);

//CSV FILE STUFF
bool openFile(ifstream&, char[]); //attempts to open csv file
void populateStoreArray(ifstream&, Knife[], int&); //populated my array with csv data
void populateMegaArray(ifstream&, AllKnife&); //populate nested struct with mega data

//USER INPUT
void readMenu(char&, Knife[], int&, bool&, UserData&, char[], char[], AllKnife& ); //very important function that reads menu input and then executes their command
void buy(Knife[], UserData&, int&, char[], char[], AllKnife&); //takes knives store front list and user data (removing from knife list)
void sell(Knife[], UserData&, int&, char[], char[], AllKnife&); //takes knives store front list and user data (adds to knife list and user balance)
void trade(Knife[], UserData&, int&, char[], char[], AllKnife&); //takes knives store front list and user data (swaps user knife for store front knife and adds balance)

//USER INPUT VALIDITY CHECKS
bool charValid(char); //checks that the char is valid true if valid
bool readType(AllKnife&, char[], int&); //read knife type from user and verifies it is valid
bool readSkin(AllKnife&, char[], int&, int); //read skin type from user and verifies it is valid
void validKnife(AllKnife&, char[], char[], int&, int&, int&);

// INSERT AND REMOVE FROM STOREFRONT AND USER INVENTORY
void insertStore(Knife[], int&, AllKnife&, int, UserData&);
void removeStore(Knife[], int&, int);
void insertInventory(UserData&);
void removeInventory(UserData&);
bool checkInventory(UserData&, AllKnife&, int, int&);

#endif
