#include "product.hpp"
#include "utilities.hpp"

#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>

using namespace std;

ProductManager::ProductManager() : productCount(0) {}

void ProductManager::AddProduct(const string& productName, int categoryID,int threshold, const CategoryManager& categoryManager) {
    // Validate max temporary stroage limitation
    if(productCount >= MAX_PRODUCTS){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add more products. Temporary storage limit reached.");
        return;
    }

    // Validate invalid categoryId
    if(!categoryManager.CategoryExists(categoryID)){
        Utilities::clearScreen();
        string messages = "Category ID " + to_string(categoryID) + " Invalid category ID. Product not added.";
        Utilities::pressAnyKeyToContinue(messages);
        return;
    }

    // Validate empty name
    if(productName.empty() && productName == ""){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot ddd product without name. ");
        return;
    }

    // Validate existing name in lowercase 
    string lowerProductName = productName;
    transform(lowerProductName.begin(), lowerProductName.end(), lowerProductName.begin(), ::tolower);

    for(int i = 0; i < productCount; i++) {
        string lowerExistingName = names[i];
        std::transform(lowerExistingName.begin(), lowerExistingName.end(), lowerExistingName.begin(), ::tolower);
        if(lowerExistingName == lowerProductName) {
            Utilities::clearScreen();
            Utilities::pressAnyKeyToContinue("Product with this name already exists.");
            return;
        }
    }

    ids[productCount] = productCount+1;
    names[productCount] = productName;
    categoryIds[productCount] = categoryID;
    stocks[productCount] = 0;
    thresholds[productCount] = threshold;

    productCount++;
    Utilities::pressAnyKeyToContinue("Product added successfully!");
}

void ProductManager::ViewProducts(int currentPage, int pageSize, CategoryManager& categoryManager) {

    if(productCount == 0){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("No product available.");
        return;
    }
    
    int totalPages = (productCount + pageSize - 1) / pageSize;

    const int idWidth = 5;
    const int nameWidth = 30;
    const int categoryWidth =20;
    const int stockWidth = 10;

    const int tableWidth = idWidth+nameWidth+categoryWidth+stockWidth;
    
    //Print Centered Title
    cout << string(tableWidth, '=') << endl;
    Utilities::printCenteredTitle("Products", tableWidth);
    cout << string(tableWidth, '=') << endl;

    // Print Column Header
    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+"
         << string(categoryWidth, '-') << "+"
         << string(stockWidth, '-') << "+" << endl;

    cout << "| " << setw(idWidth - 1) << left << "ID"
         << "| " << setw(nameWidth -1 ) << left << "Product Name"
         << "| " << setw(categoryWidth - 1) << left << "Category"
         << "| " << setw(stockWidth - 1) << left << "Stock"
         << "|" << endl;

    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+"
         << string(categoryWidth, '-') << "+"
         << string(stockWidth, '-') << "+" << endl;
    

    // Display Product for currentPage
    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < productCount; i++) {
        string categoryName = categoryManager.GetCategoryName(categoryIds[i]);
        cout << "| " << setw(idWidth - 1) << left << ids[i]
             << "| " << setw(nameWidth - 1) << left << names[i]
             << "| " << setw(categoryWidth - 1) << left << categoryName
             << "| " << setw(stockWidth - 1) << left << stocks[i]
             << "|" << endl;
    }

    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+"
         << string(categoryWidth, '-') << "+"
         << string(stockWidth, '-') << "+" << endl;

    cout << "Showing page " << currentPage << " of " << totalPages << "\n";
}

int ProductManager::ViewProductsByCategory(int categoryId, int currentPage, int pageSize, CategoryManager& categoryManager) {
    // Count Filtered products
    int filteredProductCount = 0;
    for(int i=0;i<productCount;i++){
        if(categoryIds[i] == categoryId) {
            filteredProductCount++;
        }
    }

    if (filteredProductCount == 0) {
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("No products found in this category.");
        return 0;
    }

    int totalPages = (filteredProductCount + pageSize - 1) / pageSize;

    const int idWidth = 5;
    const int nameWidth = 30;
    const int stockWidth = 10;

    const int tableWidth = idWidth + nameWidth + stockWidth;

    string categoryName = categoryManager.GetCategoryName(categoryId);

    // Print Title
    cout << string(tableWidth, '=') << endl;
    Utilities::printCenteredTitle("Products in Category "+categoryName, tableWidth);
    cout << string(tableWidth, '=') << endl;

    // Print Column Header
    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+"
         << string(stockWidth, '-') << "+" << endl;

    cout << "| " << setw(idWidth - 1) << left << "ID"
        << "| " << setw(nameWidth - 1) << left << "Product Name"
        << "| " << setw(stockWidth - 1) << left << "Stock"
        << "|" << endl;

    cout << "+" << string(idWidth, '-') << "+"
        << string(nameWidth, '-') << "+"
        << string(stockWidth, '-') << "+" << endl;

    // Display products for the current page
    int productCountOnPage = 0;
    for (int i = 0; i < productCount; i++) {
        if (categoryIds[i] == categoryId) {
            if (productCountOnPage >= (currentPage - 1) * pageSize && productCountOnPage < currentPage * pageSize) {
                cout << "| " << setw(idWidth - 1) << left << ids[i]
                     << "| " << setw(nameWidth - 1) << left << names[i]
                     << "| " << setw(stockWidth - 1) << left << stocks[i]
                     << "|" << endl;
            }
            productCountOnPage++;
        }
    }

    cout << "+" << string(idWidth, '-') << "+"
         << string(nameWidth, '-') << "+"
         << string(stockWidth, '-') << "+" << endl;

    cout << "Showing page " << currentPage << " of " << totalPages << "\n";
    return filteredProductCount;
}

void ProductManager::UpdateStock(int productId, int stockChanges) {
    for(int i=0;i<productCount;i++){
        if(ids[i] == productId) {
            stocks[i] += stockChanges;

            if(stocks[i] < 0){
                Utilities::clearScreen();
                Utilities::pressAnyKeyToContinue("Warning: Stock cannot be negative. Adjusted to 0.");
                stocks[i] = 0;
            }

            if (stocks[i] < thresholds[i]) {
                string message = "Warning: Stock for " + names[i] + " is below the threshold of " + to_string(thresholds[i]) + ". Current stock: " + to_string(stocks[i]);
                Utilities::clearScreen();
                Utilities::pressAnyKeyToContinue(message);
            }

            Utilities::clearScreen();
            string message = "Updated stock for " + names[i] + ": " + to_string(stocks[i]);
            Utilities::pressAnyKeyToContinue(message);
            return;
        }
    }
    Utilities::clearScreen();
    Utilities::pressAnyKeyToContinue("Product ID " + to_string(productId) + " not found!");
}