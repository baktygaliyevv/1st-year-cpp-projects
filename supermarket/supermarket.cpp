/**
  * File:    supermarket.cpp
  *
  * Author:  Nuraly Baktygaliyev (nuraly2.baktygaliyev@live.uwe.ac.uk)
  * Date:     01/03/2023
  * Partner:  I worked alone 
  * Course:   UWEBIC IY469 Programming in C/C++
  *
  * Summary of File:
  *
  * This code is a C++ console application for managing items of a store. 
  * It includes functions to load and save items from/to a text file, add/remove/edit items, 
  * print low stock and expired items, search items, and exit the application. 
  * The program has a menu-driven interface that allows users to perform these 
  * operations until they choose to exit. 
  *
  */

//I confirm that this assignment is my own work. Where I have referred to academic sources, I have provided in-text citations and included the sources in the final reference list.


#include <algorithm> 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>


//Define the structurte of an item in the text file 
struct Item {
  std::string name;
  std::string best_before;
  int quantity;
  double price;
  std::string type;
};


/*
void load_items(std::vector<Item> &items)

Summary of the load_items function:
  The load_items function reads data from a text file "items.txt" and stores it in a vector of type 'Item'

Parameters : items: a reference to a vector of type 'Item'

Return Value : Nothing -- Note: Modifies the vector "in place".

Description:
  This function reads data from a text file "items.txt" line by line using the standard getline function.
  Each line is then stored in a stringstream, which is used to extract the different values for each item,
  such as the name, best before date, quantity, price and type.
  These values are then stored in a temporary 'Item' object.
  Finally, the 'Item' object is added to the end of the vector of type 'Item'.
  Note, the vector is modified in place.
*/
void load_items(std::vector<Item> &items) {
  std::ifstream file("items.txt");
  std::string line;
  while (std::getline(file, line)) {
    Item item;
    std::stringstream ss(line);
    std::getline(ss, item.name, ',');
    std::getline(ss, item.best_before, ',');
    std::string q;
    std::getline(ss, q, ',');
    std::string p;
    std::getline(ss, p, ',');
    item.quantity = atoi(q.c_str());
    item.price = atof(p.c_str());
    std::getline(ss, item.type);
    items.push_back(item);
  }
}


/*
void save_items(std::vector<Item> &items)

Summary of the save_items function: 
  The save_items function, writes the contents of the input vector "items" to a file named "items.txt"

Parameters : items: a vector of Item objects

Return Value : Nothing

Description:
  This function takes a vector of Item objects as input and writes its contents to a file named "items.txt".
  The data is written in the format: item.name,item.best_before,item.quantity,item.price,item.type. Each item is separated by a new line character.
*/
void save_items(std::vector<Item> &items) {
  std::ofstream out_file("items.txt");
  for (const auto &item : items) {
      out_file << item.name << "," << item.best_before << "," << item.quantity << "," << item.price << "," << item.type << "\n";
  }
}


/*
void list_items(std::vector<Item> &items)

Summary of the list_items function:
  The list_items function, displays the contents of the given
  vector of items in a formatted manner.

Parameters : items: a vector of Item objects

Return Value : Nothing

Description:
  This function prints the contents of the given vector of Item objects
  with proper formatting. The contents of the Item objects are displayed
  as follows: "Name", "Best Before", "Quantity", "Price", and "Type".
*/
void list_items(std::vector<Item> &items) {
  std::cout << "\n" << std::left << std::setw(15) << "Name" << std::setw(15) << "Best Before" << std::setw(15) << "Quantity" << std::setw(15) << "Price" << "Type" << "\n";
  for (const auto &item : items) {
    std::cout << std::left << std::setw(15) << item.name << std::setw(15) << item.best_before << std::setw(15) << item.quantity << std::setw(15) << item.price << item.type << "\n";
  }
}


/*
void add_item(std::vector<Item> &items)

Summary of the add_item function:
The add_item function allows the user to add a new item to the supermarket inventory.

Parameters : items: a vector containing instances of the Item structure

Return Value : Nothing

Description:
  This function prompts the user to enter the details of the new item to be added to the inventory, including name, best before date, 
  quantity in stock, price, and type. The function validates the user input and ensures that only valid data is added to the inventory. 
  The new item is then added to the items vector and saved to the items.txt file.
*/
void add_item(std::vector<Item> &items) {
  Item item;

  do {
    std::cout << "Enter name: ";
    std::cin >> item.name;
    if (!std::cin || !isalpha(item.name[0])) {
      std::cout << "Invalid input. Please enter a text" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } while (!std::cin || !isalpha(item.name[0]));
  
  while(true) {
    std::cout << "Enter best before date(dd/mm/yyyy): ";
    std::cin >> item.best_before;
    std::tm t = {};
    std::istringstream ss(item.best_before);
    if (ss >> std::get_time(&t, "%d/%m/%Y")) {
      break;
    }
  std::cout << "Invalid input. Ensure that you have entered the date in the correct format (dd/mm/yyyy).\n";
  }
  
  do {
    std::cout << "Enter quantity in stock: ";
    std::cin >> item.quantity;
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else if (item.quantity <= 0) {
    std::cout << "Invalid input. Please enter a positive value" << std::endl;
    }
  } while (std::cin.fail() || item.quantity <= 0);
  
  do {
    std::cout << "Enter price: ";
    std::cin >> item.price;
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else if (item.price <= 0) {
      std::cout << "Invalid input. Please enter a positive value" << std::endl;
    }
  } while (std::cin.fail() || item.price <= 0);
  
  std::string itemType;
  while (true) {
    std::cout << "Enter item type: ";
    std::cin >> itemType;
    if (std::all_of(itemType.begin(), itemType.end(), ::isalpha)) {
      item.type = itemType;
      break;
    } else {
      std::cout << "Invalid input. Please enter a text" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  items.push_back(item);
  save_items(items);
  std::cout << "Item added successfully" << std::endl;
}


/*
void remove_item(std::vector<Item> &items)

Summary of the remove_item function:
  The remove_item function allows the user to remove an item from the
  inventory by specifying its name. If multiple items are found with the
  same name, the user will be prompted to specify which item they want to
  remove.
Parameters : items: a vector containing the items in the inventory

Return Value : Nothing -- Note: Modifies the inventory stored in the items vector.

Description:
  This function prompts the user to enter the name of the item they want
  to remove. It searches the items vector for items with a name containing
  the specified name. If multiple items are found, it prompts the user to
  specify which item they want to remove. If only one item is found, it
  removes the item from the items vector and saves the updated inventory
  to the items.txt file.
*/
void remove_item(std::vector<Item> &items) {
  std::string name;
  while (true) {
    std::cout << "Enter name of item you want to find(start with the capital letter): ";
    std::cin >> name;
    std::vector<Item> items_to_remove;
    for (const auto &item : items) {
      if (item.name.find(name) != std::string::npos) {
        items_to_remove.push_back(item);
      }
    }
    if (items_to_remove.empty()) {
      std::cout << "No items found with name containing: " << name << std::endl;
    } 
    else if (items_to_remove.size() > 1) {
      std::cout << "Multiple items found, please specify:\n";
      for (const auto &item : items_to_remove) {
        std::cout << item.name << "\n";
      }
    } 
    else {
      auto it = std::remove_if(items.begin(), items.end(), [&](const Item &item) { return item.name == items_to_remove[0].name; });
      items.erase(it, items.end());
      save_items(items);
      std::cout << "Item removed successfully" << std::endl;
      break;
    }
  }
}


/*
void edit_item(std::vector<Item> &items)

Summary of the edit_item function:
  The edit_item function allows the user to modify the existing item information in the items vector.
Parameters : items: vector containing Item objects

Return Value : Nothing -- Note: Modifies the items vector "in place".

Description:
  This function takes in the items vector and prompts the user to input the name of the item they want to edit.
  If the item is found, the user is then asked to input the updated information for the best before date,
  quantity, price, and type of the item. The updated information is then saved to the items vector and the
  items are saved to the "items.txt" file.
*/
void edit_item(std::vector<Item> &items) {
  std::string name;
  auto it = items.end();
  while (it == items.end()) {
    std::cout << "Enter name: ";
    std::cin >> name;
    it = std::find_if(items.begin(), items.end(), [&](const Item &item) { return item.name == name; });
    if (it == items.end()) {
      std::cout << "Item not found. Please enter the name again." << std::endl;
    }
  }
  while (true) {
    std::cout << "Enter best before date (dd/mm/yyyy): ";
    std::string bestBefore;
    std::cin >> bestBefore;
    std::tm t = {};
    std::istringstream ss(bestBefore);
    if (ss >> std::get_time(&t, "%d/%m/%Y")) {
      it->best_before = bestBefore;
      break;
    }
    std::cout << "Invalid input. Ensure that you have entered the date in the correct format (dd/mm/yyyy).\n";
  }
  do {
    std::cout << "Enter quantity in stock: ";
    std::cin >> it->quantity;
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else if (it->quantity <= 0) {
      std::cout << "Invalid input. Please enter a positive value" << std::endl;
    }
  } while (std::cin.fail() || it->quantity <= 0);
  do {
    std::cout << "Enter price: ";
    std::cin >> it->price;
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else if (it->price <= 0) {
      std::cout << "Invalid input. Please enter a positive value" << std::endl;
    }
  } while (std::cin.fail() || it->price <= 0);
  while (true) {
    std::string type;
    std::cout << "Enter item type: ";
    std::cin >> it->type;
    if (std::all_of(it->type.begin(), it->type.end(), ::isalpha)) {
      type = it->type;
      break;
    } 
    else {
      std::cout << "Invalid input. Please enter a text" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  save_items(items);
  std::cout << "Item edited successfully" << std::endl;
}


/*
void print_low_stock(std::vector<Item> &items)

Summary of the print_low_stock function:
  The print_low_stock function prints out the items in the inventory that have a quantity
  less than a specified threshold value.

Parameters : items: A vector containing the items in the inventory

Return Value : Nothing

Description:
  This function prompts the user to enter a threshold value for the quantity of items.
  It then iterates through the items in the inventory and prints out the items that have
  a quantity less than the specified threshold value.
*/
void print_low_stock(std::vector<Item> &items) {
  int idkhowtocallthat;
  bool check = false;
  while (!check) { 
    std::cout << "Enter the number less than which will be considered that the item in the low stock: ";
    std::cin >> idkhowtocallthat;
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } 
    else {
      check = true;
    }
  }
  std::cout << "\nLow stock items:\n";
  std::cout << "\n" << std::left << std::setw(15) << "Name" << std::setw(15) << "Best Before" << std::setw(15) << "Quantity" << std::setw(15) << "Price" << "Type" << "\n";
  for (const auto &item : items) {
    if (item.quantity < idkhowtocallthat)
      std::cout << std::left << std::setw(15) << item.name << std::setw(15) << item.best_before << std::setw(15) << item.quantity << std::setw(15) << item.price << item.type << "\n";
  }
}


/*
void print_expired(std::vector<Item> &items)

Summary of the print_expired function:
  The print_expired function prints out the items in the inventory that have an expiration date
  within a specified number of days from the current date.

Parameters: items: A vector containing the items in the inventory

Return Value: Nothing
 
Description:   
  This function prompts the user to enter the number of days before expiration date.
  It then iterates through the items in the inventory and prints out the items that have
  an expiration date within the specified number of days from the current date.
*/
void print_expired(std::vector<Item> &items) {
  int days_before_expiration;
  bool check = false;
  while (!check) {
    std::cout << "Enter the number of days before expiration date: ";
    std::cin >> days_before_expiration;
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
      check = true;
    }
  }
  std::cout << "\nItems about to expire (or already expired):\n";
  std::cout << "\n" << std::left << std::setw(15) << "Name" << std::setw(15) << "Best Before" << std::setw(15) << "Quantity" << std::setw(15) << "Price" << "Type" << "\n";
  for (const auto &item : items) {
    std::tm t = {};
    std::istringstream ss(item.best_before);
    ss >> std::get_time(&t, "%d/%m/%Y");
    auto best_before = std::chrono::system_clock::from_time_t(std::mktime(&t));
    auto now = std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::hours>(best_before - now).count() <= 24 * days_before_expiration) {
      std::cout << std::left << std::setw(15) << item.name << std::setw(15) << item.best_before
                << std::setw(15) << item.quantity << std::setw(15) << item.price << item.type
                << "\n";
    }
  }
}


//Function to search items in the vector
void search_items(std::vector<Item> &items) {
  bool found = false;
  while (true) {
    std::cout << "Enter the name or type of item you want to find (start with the capital letter): ";
    std::string term;
    std::cin >> term;
    for (const auto &item : items) {
      if (item.name.find(term) != std::string::npos || item.type.find(term) != std::string::npos) {
        if (!found) {
          std::cout << "\n" << std::left << std::setw(15) << "Name" << std::setw(15) << "Best Before" << std::setw(15) << "Quantity" << std::setw(15) << "Price" << "Type" << "\n";
          found = true;
        }
        std::cout << std::left << std::setw(15) << item.name << std::setw(15) << item.best_before << std::setw(15) << item.quantity << std::setw(15) << item.price << item.type << "\n";
      }
    }
    if (!found) {
      std::cout << "Item not found. Would you like to try again? (1 - yes / 0 - no): ";
      int again;
      while (true) {
        std::cin >> again;
        if (std::cin.fail()) {
          std::cout << "Invalid input. Please enter a number: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } 
        else if (again == 0 || again == 1) {
          break;
        } 
        else {
          std::cout << "\nInvalid input. Please enter number between 1(yes) and 2(no): ";
        }
      }
      if (again == 0) {
        break;
      }
    } 
    else {
      break;
    }
  }
}


/*
void exit()

Summary of the exit function: The exit function closes the application and terminates the program

Parameters : None

Return Value : Nothing

Description:
  This function outputs a message indicating that the application has been closed and
  then terminates the program using the std::exit function with a status code of 0.
*/
void exit() {
  std::cout << "Application is closed\n";
  std::exit(0);
}


/*
void print_menu()

Summary of the print_menu function:
  This function prints the main menu of the application, listing the available options
  for the user to interact with the inventory.

Parameters: None

Return Value: Nothing

Description:
  This function prints the main menu of the application, listing the options for the user to
  list items, add items, remove items, edit items, print low stock items, print expired items, 
  search items and exit the application.
*/
void print_menu() {
  std::cout << "\n------MENU------\n";
  std::cout << "1. List items\n";
  std::cout << "2. Add item\n";
  std::cout << "3. Remove item\n";
  std::cout << "4. Edit item\n";
  std::cout << "5. Print low stock items\n";
  std::cout << "6. Print expired items\n";
  std::cout << "7. Search items\n";
  std::cout << "8. Exit\n";
  std::cout << "Enter the option: ";
}


/*
void execute(int choice, std::vector<Item> &items)
 
Summary of the execute function:
  The execute function takes a user choice and a reference to a vector of items as input,
  and performs the corresponding action based on the user's choice.

Parameters: 
  choice: An integer representing the user's choice from the menu
  items: A vector containing the items in the inventory

Return Value : Nothing

Description:
  This function takes a user choice and a reference to a vector of items as input.
  It then performs the corresponding action based on the user's choice.
  The options available are:
    1. List items
    2. Add item
    3. Remove item
    4. Edit item
    5. Print low stock items
    6. Print expired items
    7. Search items
    8. Exit
*/
void execute(int choice, std::vector<Item> &items){
  do {
    std::cin >> choice;
    if (std::cin.fail() || choice < 1 || choice > 8) {
      std::cout << "Invalid choice. Please enter a number between 1 and 8: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } while (std::cin.fail() || choice < 1 || choice > 8);
  switch (choice) {
    case 1:
      list_items(items);
      break;
    case 2:
      add_item(items);
      break;
    case 3:
      remove_item(items);
      break;
    case 4:
      edit_item(items);
      break;
    case 5:
      print_low_stock(items);
      break;
    case 6:
      print_expired(items);
      break;
    case 7:
      search_items(items);
      break;
    case 8:
      exit();
      break;
  }
}


/*
int main()

Summary of the main function:
  The main function is the entry point of the program. It initializes an empty
  vector of items, loads items from a file, and then repeatedly displays a menu
  and executes the selected operation until the user chooses to exit.

Parameters : None

Return Value : int, 0 indicating successful execution.

Description:
  The main function initializes an empty vector of items and then calls the
  load_items function to load the items from a file. It then enters a loop
  where it repeatedly displays a menu of options, gets the user's choice,
  and calls the execute function to perform the selected operation.
  The loop continues until the user chooses to exit.
*/
int main() {
  std::vector<Item> items;
  load_items(items);
  int choice;
  while (true) {
    print_menu();
    execute(choice,items);
  }
  return 0;
}