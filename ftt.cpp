#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

void printMainMenu();

void useLinkedList();

bool loadItem(char **argv, LinkedList& vendingMachine);
void splitString(string s, vector<string>& tokens, string delimiter);

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO

    // initialize 
    LinkedList vendingMachine;
    bool allowedArgs = true;
    std::string foodsFile;
    std::string coinsFile;


    // input validation
    if (argc != 3) {
        cout << "you entered the wrong arguments." << endl;
        allowedArgs = false;
    }
    else {
        foodsFile = argv[1];
        coinsFile = argv[2];
        allowedArgs = loadItem(argv, vendingMachine);
    }
    
    bool exit = false;

    while (!std::cin.eof() && !exit && allowedArgs) {
        // useLinkedList();
        vendingMachine.printItems();
        exit = true;
    }

    return EXIT_SUCCESS;
}

bool loadItem(char **argv, LinkedList& vendingMachine){
   // Reading the data inserted.
   bool allowedArgs = true;
   string foodsDat = argv[1];
   string coinsDat = argv[2];
   // Reading files
   string foodLine;
   // Save the food file as a linked list.
   ifstream myfile(foodsDat);
   if (myfile.is_open()) {
      while (getline(myfile, foodLine)) {
            // Local variables
            string food_id, food_name, food_desc;
            double food_price;
            int food_stock;
            // Split string function by delimter.
            std::vector<std::string> foodTokens;
            string delimiter = "|";
            splitString(foodLine,foodTokens,delimiter);
            // Giving values
            food_id = foodTokens[0];
            food_name = foodTokens[1];
            food_desc = foodTokens[2];
            food_price = std::stod(foodTokens[3]);
            food_stock = std::stoi(foodTokens[4]);

            // Create node
            FoodItem* item = new FoodItem(food_id, food_name, food_desc, food_price, food_stock);
            // Append node to end of linked list
            vendingMachine.addBack(item);
      }
      // Failed to open
      myfile.close();
   }
   else {
      allowedArgs = false;
      cout << "Unable to open stock file" << endl;
   }
   string coinLine;
   // Save the coin file as array since fixed array size of eight.
   ifstream coinFile(coinsDat);
   if (coinFile.is_open()) {
        int count = 0;
        while (getline(coinFile, coinLine)) {
                std::vector<std::string> coinToken;
                string delimiter = ",";
                splitString(coinLine,coinToken,delimiter);
                // Check if the coins file is a correct input.
                vendingMachine.purse[count].count = std::stoi(coinToken[1]);

                // TODO: Unable to handle non valid files.
                vendingMachine.purse[count].denom = vendingMachine.purse->string_to_denomination(coinToken[0]);
                count += 1;
        }
        coinFile.close();
        //Sort the coin array.
        vendingMachine.purse->sortCoins(vendingMachine.purse);
   }
   else {
      allowedArgs = false;
      cout << "Unable to open coin file" << endl;
   }

   cout << "loaded" << endl;
   return allowedArgs;
}

void splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

/**
 * Prints the main menu of the vending machine
**/
void printMainMenu() {

    cout << "Main Menu:" << endl;

    cout << "\t1. Display Meal Options" << endl;
    cout << "\t2. Purchase Meal" << endl;
    cout << "\t3. Save and Exit" << endl;

    cout << "Administrator-Only Menu:" << endl;
    cout << "\t4. Add Food" << endl;
    cout << "\t5. Remove Food" << endl;
    cout << "\t6. Display Balance" << endl;
    cout << "\t7. Abort Program" << endl;

    cout << "Select your option (1-7) :" << endl;

}

// delete this function in the final code
void useLinkedList() {
    FoodItem* item1 = new FoodItem("I0001", "Burger", "A cheese burger", 12.99, 10);
    FoodItem* item2 = new FoodItem("I0002", "Pizza", "A big pizza", 15.99, 10);
    FoodItem* item3 = new FoodItem("I0003", "Tea", "Black tea", 6.75, 10);
    FoodItem* item4 = new FoodItem("I0004", "Fruit", "any fruit", 0.95, 10);
    FoodItem* item5 = new FoodItem("I0005", "Apple Pie", "description", 1.5, 100);

    LinkedList list;

    list.addFront(item1);
    list.addBack(item2);
    list.addFront(item3);
    list.addBack(item4);
    list.addAt(item5, 2);
    list.addFront(new FoodItem("I0006", "Lemon Tart", "description", 3.75)); 
    list.printItems();

    list.removeBack();
    list.removeFront();
    list.removeAt(2);
   
    list.printItems();
}