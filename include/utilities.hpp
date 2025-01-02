#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#include <iostream>

using namespace std;

class Utilities {
    public:
        static void clearScreen();
        static void printCenteredTitle(const string& title, int width);
        static void pressAnyKeyToContinue(const string& customMessage);
        
        // Table Utilities 
        // TODO Maybe create separate helper class for table
        static void printTableTitle(const string& title, const int tableWidth, const int columnCount);
        static void printTableHeader(const string headers[], const int columnWidths[], int columnCount);
        static void printTableRow(const string rowData[], const int columnWidths[], int columnCount);
        static void printTableDivider(const int columnWidths[], int columnCount);
        static int calculateTotalPages(const int itemCount, const int pageSize);
        static void calculateColumnWidths(const string headers[], int headerCount, int padding, int columnWidths[]);
        static int calculateTableWidths(const int columnWidths[], const int columnCount);

        //static void createTable(const string tableTitle,const string headers[], const int columnCount, int columnWidths[], const int itemCount, int currentPage,  int pageSize);
};

#endif