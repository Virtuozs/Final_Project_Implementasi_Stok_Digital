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

    int totalPages = Utilities::calculateTotalPages(productCount, pageSize);

    const int columnCount = 4;
    const string headers[columnCount] = {"ID", "Product Name", "Category", "Stock"};
    int columnWidths[columnCount];
    
    Utilities::calculateColumnWidths(headers, columnCount, 10, columnWidths);

    const int tableWidth = Utilities::calculateTableWidths(columnWidths, columnCount);

    string tableTitle = "Products";
    Utilities::printTableTitle(tableTitle, tableWidth, columnCount);

    Utilities::printTableHeader(headers, columnWidths, columnCount);

    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < productCount; i++) {
        const string rowData[columnCount] = {
            to_string(ids[i]),
            names[i],
            categoryManager.GetCategoryName(categoryIds[i]),
            to_string(stocks[i])
        };
        Utilities::printTableRow(rowData, columnWidths, columnCount);
    }

    Utilities::printTableDivider(columnWidths, columnCount);

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

    
    int totalPages = Utilities::calculateTotalPages(filteredProductCount, pageSize);

    const int columnCount = 4;
    const string headers[columnCount] = {"ID", "Product Name", "Category", "Stock"};
    int columnWidths[columnCount];

    Utilities::calculateColumnWidths(headers, columnCount, 10, columnWidths);

    const int tableWidth = Utilities::calculateTableWidths(columnWidths, columnCount);

    string categoryName = categoryManager.GetCategoryName(categoryId);

    string tableTitle = "Products in Category "+categoryName;
    Utilities::printTableTitle(tableTitle, tableWidth, columnCount);

    Utilities::printTableHeader(headers, columnWidths, columnCount);

    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < productCount; i++) {
        if(categoryIds[i] == categoryId){
            const string rowData[columnCount] = {
                to_string(ids[i]),
                names[i],
                categoryManager.GetCategoryName(categoryIds[i]),
                to_string(stocks[i])
            };
            Utilities::printTableRow(rowData, columnWidths, columnCount);
        }
    }

    Utilities::printTableDivider(columnWidths, columnCount);

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

bool ProductManager::ProductExists(int productID){
    for(int i=0;i<productCount;i++){
        if(ids[i] == productID){
            return true;
        }
    }
    return false;
}

string ProductManager::GetProductName(int productID){
    for (int i = 0; i < productCount; ++i) {
        if (ids[i] == productID) {
            return names[i];
        }
    }
    throw std::out_of_range("Category ID is out of range");
}