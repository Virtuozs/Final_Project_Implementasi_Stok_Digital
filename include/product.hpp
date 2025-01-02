#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include "category.hpp"

using namespace std;

class ProductManager {
    public:
        static const int MAX_PRODUCTS = 100;
        int productCount;

        ProductManager();
        void AddProduct(const string& productName, int categoryID,int threshold, const CategoryManager& CategoryManager);
        void ViewProducts(int currentPage, int pageSize, CategoryManager& categoryManager);
        int ViewProductsByCategory(int categoryId, int currentPage, int pageSize, CategoryManager& categoryManager);
        void UpdateStock(int productId, int stockChange);
        bool ProductExists(int productID);
        string GetProductName(int productID);

    private:
        //Add more field
        int ids[MAX_PRODUCTS];
        string names[MAX_PRODUCTS];
        int categoryIds[MAX_PRODUCTS];
        int stocks[MAX_PRODUCTS];
        int thresholds[MAX_PRODUCTS];
};

#endif