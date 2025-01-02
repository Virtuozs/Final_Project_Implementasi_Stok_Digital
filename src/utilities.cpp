#include "utilities.hpp"
#include <iomanip>
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
    cout << string(width, '=') << endl;
    int padding = (width - title.size()) / 2;       
    cout << string(padding, ' ') << " " <<title << " " <<string(padding, ' ') << endl;    
    cout << string(width, '=') << endl;
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

void Utilities::printTableDivider(const int columnWidths[], int columnCount){
    for(int i = 0;i<columnCount;++i){
        cout << "+" << string(columnWidths[i], '-');
    }
    cout << "+" << endl;
}

void Utilities::printTableHeader(const string headers[], const int columnWidths[], int columnCount){
    printTableDivider(columnWidths, columnCount);

    for (int i = 0; i < columnCount; ++i) {
        cout << "| " << setw(columnWidths[i] - 1) << left << headers[i];
    }
    cout << "|" << endl;

    printTableDivider(columnWidths, columnCount);
}

void Utilities::printTableRow(const string rowData[], const int columnWidths[], int columnCount) {
    for (int i = 0; i < columnCount; ++i) {
        cout << "| " << setw(columnWidths[i] - 1) << left << rowData[i];
    }
    cout << "|" << endl;
}

int Utilities::calculateTotalPages(const int itemCount, const int pageSize){
    return (itemCount + pageSize - 1) / pageSize;
}

void Utilities::calculateColumnWidths(const string headers[], int headerCount, int padding, int columnWidths[]) {
    for (int i = 0; i < headerCount; ++i) {
        columnWidths[i] = static_cast<int>(headers[i].length()) + padding;
    }
}

int Utilities::calculateTableWidths(const int columnWidths[], const int columnCount){
    int tableWidth = 0;
    for (int i = 0; i < columnCount; ++i) {
        tableWidth += columnWidths[i];
    }
    return tableWidth;
}

void Utilities::printTableTitle(const string& title, const int tableWidth, const int columnCount){
    printCenteredTitle(title, tableWidth+columnCount+1);
}

