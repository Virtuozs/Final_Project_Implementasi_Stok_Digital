#include "category.hpp"
#include "product.hpp"
#include "utilities.hpp"
#include <iostream>
#include <limits>

using namespace std;

void DisplayAdminMenu(CategoryManager &categoryManager, ProductManager &productManager);
void DisplayStaffMenu(CategoryManager &categoryManager, ProductManager &productManager);

int main() {
    CategoryManager categoryManager;
    ProductManager productManager;

    bool running = true;

    while (running)
    {
        Utilities::clearScreen();
        char choice;
        cout << "1. Admin Menu" << endl ;
        cout << "2. Staff Menu" << endl ;
        cout << "3. Exit" << endl ;
        cout << "Choose function: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            Utilities::clearScreen();
            DisplayAdminMenu(categoryManager, productManager);
            break;
        case '2':
            Utilities::clearScreen();
            DisplayStaffMenu(categoryManager, productManager);
            break;
        case '3':
            Utilities::clearScreen();
            running=false;
            break;
        default:
            Utilities::pressAnyKeyToContinue("Invalid choice. Try again");
            break;
        }
    }
    return 0;
}

void DisplayAdminMenu(CategoryManager &categoryManager, ProductManager &productManager) {
    int pageSize=5;
    int currentProductPage=1;
    int currentCategoryPage=1;
    bool running = true;

    while (running) {
        char choice;
        //Print Centered Title
        Utilities::printCenteredTitle("Admin Menu", 20);
        cout << "1. Add Category" <<endl;
        cout << "2. View Categories" << endl;
        cout << "3. Add Product" << endl;
        cout << "4. View Products" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose function: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            Utilities::clearScreen();
            
            //Print Centered Title
            Utilities::printCenteredTitle("Adding Category", 30);

            string categoryName;
            cout << "Enter category name: ";
            cin.ignore();
            getline(cin, categoryName);
            categoryManager.AddCategory(categoryName);
            Utilities::clearScreen();
            break;
        }
        case '2': {
            do {
                Utilities::clearScreen();

                if(categoryManager.categoryCount == 0){
                    Utilities::pressAnyKeyToContinue("No categories available to display.");
                    break;
                }

                categoryManager.ViewCategories(currentCategoryPage, pageSize);

                cout << "Navigate (n: next, p: previous, q: quit): ";
                cin >> choice;

                if (choice == 'n') {
                    if (currentCategoryPage < (categoryManager.categoryCount + pageSize - 1) / pageSize) {
                        currentCategoryPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentCategoryPage > 1) {
                        currentCategoryPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                }
            } while (choice != 'q');
            currentCategoryPage =1;
            Utilities::clearScreen();
            break;
        }
        case '3': {
            Utilities::clearScreen();
            string productName;
            int categoryId;
            int stockThreshold;
            
            Utilities::printCenteredTitle("Adding Product", 40);
            cout << "\nEnter product name: ";
            cin.ignore();
            getline(cin, productName);
            cout << "Enter category ID for this product: ";
            cin >> categoryId;
            cout << "Enter Stock Threshold for this product: ";
            cin >> stockThreshold;
            productManager.AddProduct(productName, categoryId,stockThreshold, categoryManager);
            Utilities::clearScreen();
            break;
        }
        case '4': {
            do {
                Utilities::clearScreen();

                if(productManager.productCount == 0){
                    Utilities::pressAnyKeyToContinue("No products available to display.");
                    break;
                }

                productManager.ViewProducts(currentProductPage, pageSize, categoryManager);

                cout << "Navigate (n: next, p: previous, q: quit): ";
                cin >> choice;

                if (choice == 'n') {
                    if (currentProductPage < (productManager.productCount + pageSize - 1) / pageSize) {
                        currentProductPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentProductPage > 1) {
                        currentProductPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                }
            } while (choice != 'q');
            currentProductPage =1;
            Utilities::clearScreen();
            break;
        }
        case '5':
            Utilities::clearScreen();
            running = false;
            break;
        default:
            Utilities::clearScreen();
            Utilities::pressAnyKeyToContinue("Invalid choice. Try again.");
            break;
        }
    }
}

void DisplayStaffMenu(CategoryManager &categoryManager, ProductManager &productManager){
    int pageSize=5;
    int currentProductPage=1;
    int currentCategoryPage=1;
    bool running = true;

    while (running)
    {
        char choice;
        Utilities::printCenteredTitle("Staff Menu", 30);
        cout << "1. Monitor Inventory (Per Product)" << endl;
        cout << "2. Monitor Inventory (Per Category)" << endl;
        cout << "3. Record Stock In" << endl;
        cout << "4. Record Stock Out" << endl;
        cout << "5. Bulk Update Products" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose function: ";

        cin >> choice;

        switch (choice)
        {
        case '1': {
            do {
                Utilities::clearScreen();

                if (productManager.productCount==0){
                    Utilities::pressAnyKeyToContinue("No Products available to display.");
                    break;
                }

                productManager.ViewProducts(currentProductPage, pageSize, categoryManager);

                cout << "Navigate (n: next, p: previous, q: quit): ";
                cin >> choice;

                if (choice == 'n') {
                    if (currentProductPage < (productManager.productCount + pageSize - 1) / pageSize) {
                        currentProductPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentProductPage > 1) {
                        currentProductPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                }
            } while (choice != 'q');
            currentProductPage =1;
            Utilities::clearScreen();
            break;
        }
        case '2': {
            int categoryId;
            do {
                Utilities::clearScreen();
                if (categoryManager.categoryCount == 0){
                    Utilities::pressAnyKeyToContinue("No categories available to display.");
                    break;
                }
                categoryManager.ViewCategories(currentCategoryPage, pageSize);

                cout << "Navigate (n: next, p: previous, q: quit)" << endl;
                cout << "Select a Category ID to view products: ";
                cin >> choice;

                if (choice == 'n') {
                    if (currentCategoryPage < (categoryManager.categoryCount + pageSize - 1) / pageSize) {
                        currentCategoryPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentCategoryPage > 1) {
                        currentCategoryPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                } else if (choice == 'q') {
                    break;
                } else {
                    cin.putback(choice);  // Put the character back to the input stream
                    cin >> categoryId;  
                    if(cin.fail()) {
                        // Handle invalid input if cin fails
                        cin.clear(); // Clear the error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        Utilities::pressAnyKeyToContinue("Invalid Category ID. Try again.");
                        continue;  // Skip the rest of the loop and ask again
                    }
                    break;      
                }
            } while (true);
            
            do {
                Utilities::clearScreen();
                int filteredProductCount = productManager.ViewProductsByCategory(categoryId, currentProductPage, pageSize, categoryManager);

                if(filteredProductCount == 0){
                    break;
                }

                cout << "Navigate (n: next, p: previous, q: quit): ";
                cin >> choice;

                if (choice == 'n') {
                    if (currentProductPage < (filteredProductCount + pageSize - 1) / pageSize) {
                        currentProductPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentProductPage > 1) {
                        currentProductPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                }
            } while (choice != 'q');

            currentProductPage=1;
            Utilities::clearScreen();
            break;
        }
        case '3': {
            cout << "\nRecord Stock In:\n";
            int productId, stockChange;

            do {
                Utilities::clearScreen();
                productManager.ViewProducts(currentProductPage, pageSize, categoryManager);

                cout << "Navigate (n: next, p: previous, q: quit)" << endl;
                cout << "Select a product ID to Record Stock In: ";
                cin >> choice;

                if (choice == 'n') {
                    if (currentProductPage < (productManager.productCount + pageSize - 1) / pageSize) {
                        currentProductPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentProductPage > 1) {
                        currentProductPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                } else if (choice == 'q') {
                    break;
                } else {
                    cin.putback(choice);
                    cin >> productId;  
                    if(cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        Utilities::pressAnyKeyToContinue("Invalid Category ID. Try again.");
                        continue;
                    }
                    break;      
                }
            } while (true);
            Utilities::clearScreen();
            cout << "Updating " << productManager.GetProductName(productId) << endl;
            cout << "Enter quantity to add: ";
            cin >> stockChange;
            productManager.UpdateStock(productId, stockChange);
            break;
        }
        case '4': {
            cout << "\nRecord Stock Out:\n";
            int productId, stockChange;

            do {
                Utilities::clearScreen();
                productManager.ViewProducts(currentProductPage, pageSize, categoryManager);

                cout << "Navigate (n: next, p: previous, q: quit)" << endl;
                cout << "Select a product ID to Record Stock In: ";
                cin >> choice;

                if (choice == 'n') {
                    if (currentProductPage < (productManager.productCount + pageSize - 1) / pageSize) {
                        currentProductPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentProductPage > 1) {
                        currentProductPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                } else if (choice == 'q') {
                    break;
                } else {
                    if (!isdigit(choice)) {
                        Utilities::pressAnyKeyToContinue("Invalid input. Please enter a valid number.");
                        continue;
                    }
                    cin.putback(choice);
                    cin >> productId;  
                    if(cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        Utilities::pressAnyKeyToContinue("Invalid Category ID. Try again.");
                        continue;
                    }
                    break;      
                }
            } while (true);
            cout << "Enter quantity to subtract: ";
            cin >> stockChange;
            productManager.UpdateStock(productId, -stockChange);
            break;
        }
        case '5': {
            int productIDs[productManager.MAX_PRODUCTS];
            //int stockChanges[productManager.MAX_PRODUCTS];
            int productIDCount = 0;
            //int stockChangeCount = 1;
            bool noInputYet = true;
            bool updateState = false;
            do{
                Utilities::clearScreen();
                productManager.ViewProducts(currentProductPage, pageSize, categoryManager);

                cout << "Navigate (n: next, p: previous, q: quit, u: update)" << endl;
                cout << "Below is the product update queue: " << endl;
                for(int i=0;i<productIDCount;i++){
                    if (noInputYet) {
                        cout << " ";
                    } else {
                        cout << i+1 << ". "<< productManager.GetProductName(productIDs[i]) << endl;
                    }
                }
                cout << "\nSelect a product ID to include in update queue: ";
                cin >> choice;
                if (choice == 'n') {
                    if (currentProductPage < (productManager.productCount + pageSize - 1) / pageSize) {
                        currentProductPage++;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the last page.");
                    }
                } else if (choice == 'p') {
                    if (currentProductPage > 1) {
                        currentProductPage--;
                    } else {
                        Utilities::pressAnyKeyToContinue("You are already on the first page.");
                    }
                } else if (choice == 'q') {
                    break;
                } else if (choice == 'u') {
                    if(productIDCount<1){
                        Utilities::pressAnyKeyToContinue("There are no product inside update queue");
                        continue;
                    }else{
                        updateState=true;
                        break;
                    }
                }
                else{
                    cin.putback(choice);
                    int temporaryProductID;
                    cin >> temporaryProductID;

                    bool isExist = productManager.ProductExists(temporaryProductID);
                    bool isDuplicate = false;

                    if (!noInputYet) {
                        for (int i = 0; i < productIDCount; i++) {
                            if (productIDs[i] == temporaryProductID) {
                                isDuplicate = true;
                                break;
                            }
                        }
                    }

                    if (isDuplicate) {
                        Utilities::pressAnyKeyToContinue("Product already exists in Update Queue.");
                        continue;
                    }

                    if(isExist){
                        productIDs[productIDCount] = temporaryProductID;
                        noInputYet=false;
                    } 
                    else{
                        // handling invalid user input string or char
                        if(cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            Utilities::pressAnyKeyToContinue("Invalid Product ID. Try again.");
                            continue;
                        }else{
                            Utilities::pressAnyKeyToContinue("Invalid Product ID. Try again.");
                            continue;
                        }
                    }
                    if(!noInputYet){
                        productIDCount++;
                    }
                }
            }while (true);
            if(updateState){
                for(int i=0;i<productIDCount;i++){
                    Utilities::clearScreen();
                    string productName = productManager.GetProductName(productIDs[i]);
                    Utilities::printCenteredTitle("Updating product "+productName+" in queue", 40);

                    int updateType;
                    while (true) {
                        cout << "1. Stock In" << endl;
                        cout << "2. Stock Out" << endl;
                        cout << "Choose the update type: ";
                        cin >> updateType;

                        if (cin.fail() || (updateType != 1 && updateType != 2)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter 1 for Stock In or 2 for Stock Out." << endl;
                        } else {
                            break;
                        }
                    }

                    int stockChange;
                    while (true) {
                        if (updateType == 1) {
                            cout << "Enter quantity to add: ";
                        } else {
                            cout << "Enter quantity to subtract: ";
                        }
                        cin >> stockChange;

                        if (cin.fail() || stockChange <= 0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a positive integer." << endl;
                        } else {
                            break;
                        }
                    }

                    if(updateType==1){
                        productManager.UpdateStock(productIDs[i],stockChange);
                    }else{
                        productManager.UpdateStock(productIDs[i],-stockChange);
                    }
                }
            }
            Utilities::clearScreen();
            break;
        }
        case '6': {
            Utilities::clearScreen();
            running = false;
            break;
        }
        default:
            Utilities::clearScreen();
            Utilities::pressAnyKeyToContinue("Invalid choice. Try again.");
            break;
        }
    }
    
}
