#include "utilities.hpp"
#include <iostream>

using namespace std;

void Utilities::clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Utilities::printCenteredTitle(const string& title, int width){
    int padding = (width - title.size()) / 2;
    cout << string(padding, ' ') << title << string(padding, ' ') << endl;    
    cout << endl;
}

void Utilities::pressAnyKeyToContinue(const string& customMessage){
    if(customMessage.empty()){
        cout << "Press any key to continue...";
    }else{
        cout << customMessage;
    }
    cin.ignore();
    cin.get();
}