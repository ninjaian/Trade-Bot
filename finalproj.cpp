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
  char type[MAXCHAR] = {0}; //type of knife (bayonet, karambit, butterfly)
  char skin[MAXCHAR] = {0}; //which skin (doppler, fade, vanilla)
  int price = 0; //price of the given skin
}Knife;

//database knives
struct AllKnife{
  Knife knives[MEGACAP];
  int len = 0; //length of mega array
};
//userData (balance, inventory)
struct UserData{
  Knife userInventory[DATACAP]; //make sure user cant own more than 32 knives for printing sake
  int knifeCount = 0; //amount of knives user has for prining
  int balance = 0; //user balance
};

//WELCOME/GOODBYE/MENU/PRINT
void welcome(); //welcome message
void displayMenu(); //displays menu options
void goodbye(); //goodbye message
void printArray(Knife knives[], int size); //prints array nicely
void buyInfo(); //info to teach user to buy
void sellInfo(); //info to teach user to sell
void tradeInfo(); //info to teach user to trade

//CSV FILE STUFF
bool openFile(ifstream& ifile, char ifileName[]); //attempts to open csv file
void populateStoreArray(ifstream& ifile, Knife knives[], int& size); //populated my array with csv data
void populateMegaArray(ifstream& datafile, AllKnife& allKnives); //populate nested struct with mega data

//USER INPUT
void readMenu(char& userChar, Knife knives[], int& size, bool& quit, UserData& ud); //very important function that reads menu input and then executes their command
void buy(Knife knives[], UserData& ud); //takes knives store front list and user data (removing from knife list)
void sell(Knife knives[], UserData& ud); //takes knives store front list and user data (adds to knife list and user balance)
void trade(Knife knives[], UserData& ud); //takes knives store front list and user data (swaps user knife for store front knife and adds balance)

//USER INPUT VALIDITY CHECKS
bool charValid(char userChar); //checks that the char is valid true if valid
bool readType(AllKnife& allKnives, char userType[]); //read knife type from user and verifies it is valid
bool readSkin(AllKnife& allKnives, char userSkin[]); //read skin type from user and verifies it is valid

// INSERT AND REMOVE FROM STOREFRONT AND USER INVENTORY
void insertStore(Knife knives[], int size);
void removeStore(Knife knives[], int size);
void insertInventory(UserData& ud);
void removeInventory(UserData& ud);

int main(){
  //STRUCT INITIALIZERS------------------------------------------------
  Knife knives[DATACAP]; //STOREFRONT ARRAY 
  AllKnife allKnives; //creates allKnives that has nested Knife knives and contains mega array
  UserData ud; //creates user data struct
  int size = 0; //size of storefront array!
  //--------------------------------------------------------------------

  //CIN VARIABLES--------------------------------------------------------
  char userChar = ' ';
  char userType[MAXCHAR] = " "; //users cin for knife type
  char userSkin[MAXCHAR] = " "; //users cin for knife skin
  bool quit = false;
  //----------------------------------------------------------------------


  //OPENING FILE-------------------------------------------------------------
  //store page file
  ifstream ifile;
  char ifileName[MAXCHAR]= "finalstore.csv";
  if(!openFile(ifile, ifileName)){
    cout << "error opening " << ifileName << "! terminating program.." << endl;
    return 1;
  }
  populateStoreArray(ifile, knives, size); //populates store front array
  //database file
  ifstream datafile;
  char datafileName[MAXCHAR]= "finaldata.csv";
  if(!openFile(datafile, datafileName)){
    cout << "error opening " << datafileName << "! terminating program.." << endl;
    return 1;
  }
  populateMegaArray(datafile, allKnives); //populate mega array with all possible csgo knives
  datafile.close();
  //----------------------------------------------------------------------
  
  
  welcome();

  while(!quit){
    readMenu(userChar, knives, size, quit, ud);
  }
  
  ifile.close();
}
void buy(Knife knives[], UserData& ud){
  buyInfo();
  //create function for user to buy knife with balance
}
void sell(Knife knives[], UserData& ud){
  sellInfo();
  //create function for user to sell knife for balance
}
void trade(Knife knives[], UserData& ud){
  tradeInfo();
  //create function for user to trade knife and get left over balance
}
bool readSkin(AllKnife& allKnives, char userSkin[]){
  for(int i = 0; i>allKnives.len; i++){
    if(strcmp(allKnives.knives[i].skin, userSkin) == 0){
      return true;
    }
  }
  return false;
}
bool readType(AllKnife& allKnives, char userType[]){
  for(int i = 0; i<allKnives.len; i++){
    if(strcmp(allKnives.knives[i].type, userType) == 0){
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

void readMenu(char& userChar, Knife knives[], int& size, bool& quit, UserData& ud){
  displayMenu();
  cin >> userChar;
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
    trade(knives, ud);
  }
  if (userChar == 'b' || userChar == 'B'){ //BUY
    printArray(knives, size);
    buy(knives, ud);
  }
  if (userChar == 's' || userChar == 'S'){ //SELL
    sell(knives, ud);
  }
  if (userChar == 'p' || userChar == 'P'){ //PRINT KNIVES
    printArray(knives, size);
  }
  if (userChar == 'w' || userChar == 'W'){ //print wallet
    //printBal(balance);
  }
  if (userChar == 'i' || userChar == 'I'){ //print user inventory
    //printInventory();
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

    if(ifile.eof()){
      endFound = true;
    }
  }
  if(endFound){
    size--;
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
  cout << "Please type the name of the knife you would like to buy from the storefront!" << endl;
  cout << "ex. Karambit Fade" << endl;
  cout << "If you have sufficient balance to buy it then the knife will transfer to your inventory." << endl;
}
void sellInfo(){
  cout << endl;
  cout << "Please type the name of the knife you would like to sell to us!" << endl;
  cout << "ex. Butterfly Vanilla" << endl;
  cout << "If the knife is valid then we will send you balance for it which you can then use to buy something else." << endl;
}
void tradeInfo(){
  cout << endl;
  cout << "Please type the name of the knife you would like to trade for from the storefront" << endl;
  cout << "ex. Talon Doppler" << endl;
  cout << "You will then be prompted to type the name of the knife you want to trade for it" << endl;
  cout << "ex. Flip Tiger Tooth" << endl;
  cout << "If the price of your knife is equivalent or greater, the trade will go through and you will get the left over balance" << endl;
}
