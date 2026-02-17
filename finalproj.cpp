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
struct allKnife{
  Knife knives[MEGACAP];
  int len = 0; //length of mega array
};
//userData (balance, inventory)
struct userData{
  Knife knives[DATACAP]; //make sure user cant own more than 32 knives for printing sake
  int knifeCount = 0; //amount of knives user has for prining
  int balance = 0;
};

//WELCOME/GOODBYE/MENU/PRINT
void welcome();
void displayMenu();
void goodbye();
void printArray(Knife knives[], int size); //prints array nicely

//CSV FILE STUFF
bool openFile(ifstream& ifile, char ifileName[]); //attempts to open csv file
void populateStructArray(ifstream& ifile, Knife knives[], int& size); //populated my array with csv data

//************** GET DATABASE FROM AXEL SO I CAN VERIFY KNIVES AND SKINS

//USER INPUT
void readMenu(char& userChar, Knife knives[], int& size); //reads user menu character (Q, T, S, B);
bool charValid(char userChar); //checks that the char is valid true if valid
void readType(char userType[]); //read knife type
void readSkin(char userSkin[]); //read skin type


int main(){
  Knife knives[DATACAP]; //STOREFRONT ARRAY 
  int size = 0; //size of array

  //CIN VARIABLES--------------------------------------------------------
  char userChar = ' ';
  char userType[MAXCHAR] = " "; //users cin for knife type
  char userSkin[MAXCHAR] = " "; //users cin for knife skin
  //----------------------------------------------------------------------

  //OPENING FILE-------------------------------------------------------------
  //store page file
  ifstream ifile;
  char ifileName[MAXCHAR]= "finalstore.csv";
  if(!openFile(ifile, ifileName)){
    cout << "error opening " << ifileName << "! terminating program.." << endl;
    return 1;
  }

  //database file
  ifstream datafile;
  char datafileName[MAXCHAR]= "finaldata.csv";
  if(!openFile(datafile, datafileName)){
    cout << "error opening " << datafileName << "! terminating program.." << endl;
    return 1;
  }
  //----------------------------------------------------------------------
  
  //POPULATING STRUCT KNIVES ARRAY WITH CSV FILE DATA----------------------
  populateStructArray(ifile, knives, size);
  //----------------------------------------------------------------------
  welcome();
  readMenu(userChar, knives, size);

  ifile.close();
}
void readMenu(char& userChar, Knife knives[], int& size){
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
    exit(1);
  }
  if (userChar == 't' || userChar == 'T'){ //TRADE
    //trade();
  }
  if (userChar == 'b' || 'B'){ //BUY
    //buy();
  }
  if (userChar == 's' || userChar == 'S'){ //SELL
    //sell();
  }
  if (userChar == 'p' || userChar == 'P'){ //PRINT KNIVES
    printArray(knives, size);
  }
  if (userChar == 'w' || userChar == 'W'){ //print wallet
    //printBal(balance);
  }
  if (userChar == 'i' || userChar == 'I'){
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
void populateStructArray(ifstream& ifile, Knife knives[], int& size){
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
}
void goodbye(){ 
  cout << "Thanks for using my program! We confiscated all your items and balance ;)" << endl;
}
void displayMenu(){
  cout << setw(45) << "Buy! Sell! Trade!" << endl << endl;
  cout << "Pick an option from below:" << endl <<endl;
  cout << "(B)UY KNIFE" << endl;
  cout << "(S)ELL KNIFE" << endl;
  cout << "(T)RADE KNIFE" << endl;
  cout << "(W)ALLET BALANCE" << endl;
  cout << "(I)NVENTORY PRINT" << endl;
  cout << "(P)RINT STOREFRONT" << endl;
  cout << "(Q)UIT PROGRAM" << endl << endl;
}
