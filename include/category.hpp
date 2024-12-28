#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <string>

class CategoryManager {
    public:
        static const int MAX_CATGORIES = 20;
        int categoryCount;

        CategoryManager();
        void AddCategory(const std::string& categoryName);
        void ViewCategories(int currentPage, int pageSize);
        bool CategoryExists(int CategoryID) const;
        std::string GetCategoryName(int categoryID) const;

    private:
        int ids[MAX_CATGORIES];
        std::string names[MAX_CATGORIES];
};


#endif