#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "functions.h"

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
  datafile.close(); //close the data file
  //----------------------------------------------------------------------
  
  
  welcome();//print welcome menu

  while(!quit){
    readMenu(userChar, knives, size, quit, ud, userType, userSkin, allKnives); //begin program to read user input 
    
  }
  
  ifile.close(); //close storefront file at program termination
}

