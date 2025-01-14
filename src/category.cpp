#include "category.hpp"
#include "utilities.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

CategoryManager::CategoryManager() : categoryCount(0) {}

void CategoryManager::AddCategory(const string& categoryName){
    if(categoryCount >= MAX_CATGORIES){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add more categories. Temporary storage limit reached.");
        return;
    }
    if (categoryName.empty() && categoryName == ""){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add category without name.");
        return;
    }
    
    // Validate existing name
    string lowerCategoryName = categoryName;
    transform(lowerCategoryName.begin(), lowerCategoryName.end(), lowerCategoryName.begin(), ::tolower);

    for(int i = 0; i < categoryCount; i++) {
        string lowerExistingName = names[i];
        transform(lowerExistingName.begin(), lowerExistingName.end(), lowerExistingName.begin(), ::tolower);
        if(lowerExistingName == lowerCategoryName) {
            Utilities::clearScreen();
            Utilities::pressAnyKeyToContinue("Category with this name already exists.");
            return;
        }
    }
    
    ids[categoryCount] = categoryCount+1;
    names[categoryCount] = categoryName;

    categoryCount++;
    Utilities::pressAnyKeyToContinue("Category added successfully...");
 }

 void CategoryManager::ViewCategories(int currentPage, int pageSize) {
    if(categoryCount == 0) {
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("No categories available");
        return;
    }

    int totalPages = (categoryCount + pageSize - 1) / pageSize;

    const int idWidth = 5;
    const int nameWidth = 30;

    const int tableWidth = idWidth+nameWidth;

        //Print Centered Title
    cout << string(tableWidth+3, '=') << endl;
    Utilities::printCenteredTitle("Categories", tableWidth+3);
    cout << string(tableWidth+3, '=') << endl;

    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+" << endl;

    cout << "| " << setw(idWidth - 1) << left << "ID"
         << "| " << setw(nameWidth -1 ) << left << "Product Name"
         << "|" << endl;

    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+" << endl;

    // Display Product for currentPage
    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < categoryCount; i++) {
        cout << "| " << setw(idWidth - 1) << left << ids[i]
             << "| " << setw(nameWidth - 1) << left << names[i]
             << "|" << endl;
    }

    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+" << endl;

    cout << "Showing page " << currentPage << " of " << totalPages << "\n";
 }

 bool CategoryManager::CategoryExists(int categoryID) const {
    for(int i=0;i<categoryCount;i++){
        if(ids[i] == categoryID){
            return true;
        }
    }
    return false;
 }

std::string CategoryManager::GetCategoryName(int categoryID) const {
    // Search for the categoryID in the ids array
    for (int i = 0; i < categoryCount; ++i) {
        if (ids[i] == categoryID) {
            return names[i];
        }
    }
    // If not found, throw an exception
    throw std::out_of_range("Category ID is out of range");
}