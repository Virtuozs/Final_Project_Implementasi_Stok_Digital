
# 📦 Stok Digital - Simple Inventory Management System

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [User Roles and Functionalities](#user-roles-and-functionalities)
  - [Admin](#admin)
  - [Staff](#staff)
- [System Requirements](#system-requirements)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)

---

## 📖 Introduction
**Stok Digital** is a simple inventory management system designed to streamline product and stock management processes. This project allows **Admins** to manage product categories and inventory, while **Staff** can monitor and update stock levels. It serves as a comprehensive yet straightforward solution for small-scale inventory management.

This project is developed as part of **Kelompok 6 Algo 05**'s final assignment for (Algoritma dan Pemrograman) and is implemented in **C++** for its efficiency and versatility in handling structured data.

**Kelompok 6 Algo05**
1. Taufiqurrahman (24130500005)
2. Febri Andri Yanto (24130300002)
3. Zaki Khairi Ziwar (24130500009)

---

## ✨Features
### Admin Features
1. **Category Management**
   - Add new categories for product grouping.
   - View a list of all categories.
2. **Product Management**
   - Add new products with details such as code, name, and category.
   - View a list of all products in inventory.

### Staff Features
1. **Stock Monitoring**
   - View stock availability per product.
   - View stock availability per category.
2. **Stock Movement**
   - Record incoming stock to update inventory.
   - Record outgoing stock to manage depletion of inventory.

---

## 👤 User Roles and Functionalities

### Admin
- **Category Management:**
  - Add categories to classify products efficiently.
  - Monitor and review existing categories for better organization.
- **Product Management:**
  - Add products to inventory with essential details like name, category, and code.
  - View a comprehensive list of products in the system.

### Staff
- **Stock Monitoring:**
  - Check stock levels for individual products to ensure availability.
  - Monitor stock levels within specific categories for better inventory control.
- **Stock Mo    vement:**
  - Record and update stock inflows (incoming stock).
  - Record and update stock outflows (outgoing stock).

---

## 🛠 System Requirements
- **Programming Language:** C++
- **Compiler:** Any C++ compiler that supports C++11 or higher (e.g., GCC, Clang, MSVC)
- **Operating System:** Windows, macOS, or Linux

---

## ⚙️ Setup and Installation
1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/Virtuozs/Final_Project_Implementasi_Stok_Digital.git
   cd Final_Project_Implementasi_Stok_Digital
2. Compile the source code using your preferred C++ compiler. For example:
   ``` bash
   g++ -std=c++17 -Wall -Wextra -Werror -I./include -o build/Stock_Digital src/main.cpp src/category.cpp src/product.cpp src/utilities.cpp
2. Run the compiled program
   ``` bash
   ./StokDigital

---

## 🚀 Usage
-   Launch the program and log in as either **Admin** or **Staff**.
-   Follow the interactive menu options to perform tasks based on your role:
    -   **Admins** can manage categories and products.
    -   **Staff** can monitor and update stock levels.
-   Use the corresponding menu options to input, view, and manage inventory data.


