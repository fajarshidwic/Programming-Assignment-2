#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>

using std::cout;
using std::string;
using std::vector;
using std::cin;
using std::endl;
using std::getline;
using std::ifstream;


void printMainMenu();

void useLinkedList();

bool loadItem(char **argv, LinkedList& vendingMachine);
void splitString(string s, vector<string>& tokens, string delimiter);
string readInput();
string strip(std::string& s);
bool isInt(const std::string& input);

bool addFoodItem(LinkedList& vendingMachine);
bool removeFoodItem(LinkedList& vendingMachine);

void purchaseItem(LinkedList& LinkedList);

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
    
    string choice = "-1";
    bool exit = false;

    while (!std::cin.eof() && !exit && allowedArgs) {
        // useLinkedList();
        // vendingMachine.printItems();
        printMainMenu();
        choice = readInput();

        if (!std::cin.eof()) {
            bool isInt = true;
            // Menu Block
            if (isInt && choice != "") {

                if (std::stoi(choice) == 1) {
                    // Display Items
                    vendingMachine.printItems();
                    cout << endl;

                } else if (std::stoi(choice) == 2) {
                    // Purchase Items
                    purchaseItem(vendingMachine);
                    std::cout << "2" << std::endl;
                    cin.clear();

                } else if (std::stoi(choice) == 3) {
                    // Save & Exit
                    exit = true;
                    std::cout << "Save and Exit" << std::endl;
                    // saveItem(outFileName, vendingMachine);
                    // saveCoin(coinFile, vendingMachine);

                } else if (std::stoi(choice) == 4) {
                    // Add Item
                    addFoodItem(vendingMachine);
                    std::cout << "4" << std::endl;
                    std::cin.clear();

                } else if (std::stoi(choice) == 5) {
                    // Remove Item
                    removeFoodItem(vendingMachine);
                    std::cout << "5" << std::endl;
                    cin.clear();

                } else if (std::stoi(choice) == 6) {
                    // Displayt Coins
                    // displayCoin(vendingMachine);
                    std::cout << "6" << std::endl;

                } else if (std::stoi(choice) == 7) {
                    // Abort Program
                    exit = true;
                } else if (!std::cin.eof()) {
                    // Invalid Input Number
                    std::cout << "Error: menu item selected is not valid." << std::endl;

                }
            }
        } else {
            std::cout << "Error: input was not a number. Please try again." << std::endl;
            std::cin.clear();
        }
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
            // food_price = foodTokens[3];

            // // convert the food_price into token based on delimeter '.' and create new Price object

            // std::vector<std::string> priceTokens;
            // string priceDelimiter = ".";
            // splitString(food_price, priceTokens, priceDelimiter);

            // unsigned int dollars = atoi(priceTokens[0].c_str());
            // unsigned int cents = atoi(priceTokens[1].c_str());

            // Price foodPrice = Price{dollars, cents};
            food_price = std::stod(foodTokens[3]);
            food_stock = std::stoi(foodTokens[4]);

            cout << "Creating FoodItem:" << endl;
            cout << "food_id: " << food_id << endl;
            cout << "food_name: " << food_name << endl;
            cout << "food_desc: " << food_desc << endl;
            cout << "food_price: " << food_price << endl;
            cout << "food_stock: " << food_stock << endl;
            cout << endl;

            // Create node
            FoodItem* item = new FoodItem(food_id, food_name, food_desc, food_price, food_stock);
            // Append node to end of linked list
            vendingMachine.addBack(item);

            // Debug specific properties
            cout << "FoodItem properties:" << endl;
            cout << "ID: " << item->id << endl;
            cout << "Name: " << item->name << endl;
            cout << "Description: " << item->description << endl;
            cout << "Price: " << item->price.dollars << "." << item->price.cents << endl;
            cout << "Stock: " << item->on_hand << endl;
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

string readInput()
{
    string input;
    std::getline(std::cin, input);

    return input;
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

bool addFoodItem(LinkedList& vendingMachine) {
    bool success = false;

    string itemID, itemName, itemDescription;
    double itemPrice;
    int itemStock = DEFAULT_FOOD_STOCK_LEVEL;

    Node* node = vendingMachine.getBack();
    itemID = node->data->id;

    // itemID = getNextItemID(itemID);

    cout << "Enter the item name: ";
    getline(cin, itemName);

    cout << "Enter the item description: ";
    getline(cin, itemDescription);

    cout << "Enter the price for this item (in cents): ";
    cin >> itemPrice;

    FoodItem* item = new FoodItem(itemID, itemName, itemDescription, itemPrice, itemStock);
    vendingMachine.addBack(item);

    return success;

}

bool removeFoodItem(LinkedList& vendingMachine) {
    string itemID;

    cout << "Enter the food id of the food to remove from the menu: ";
    cin >> itemID;

    // TODO
    bool success = false;
    return success;
}


// std::string getNextItemID(std::string& currentID) {
//     std::string prefix = currentID.substr(0, 1);

//     std::string numericPart = currentID.substr(1);

//     int num = std::stoi(numericPart);
//     num++;

//     std::ostringstream oss;
//     oss << std::setw(numericPart.length()) << std::setfill('0') << num;

//     return prefix + oss.str();
// }

void purchaseItem(LinkedList& LinkedList) {

    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase:";

    std::string itemId;
    bool quit = false;
    while (!quit) {
        std::getline(std::cin, itemId);
        strip(itemId);

        if (itemId.length() > IDLEN) {
            std::cout << "Error: line entered was too long. Please try again.\n"
                    << "Error inputting ID of the product. Please try again.\n" 
                    << "Please enter the id of the item you wish to purchase:";
        } else {
            quit = true;
        }
    }

    if ((!cin.eof())) {
        // Check if the itemID exists
        if (LinkedList.get(itemId) == 0) {
            cout << "Invalid Input" << endl;
            cout << endl;
        } else {

            FoodItem* item = LinkedList.get(itemId);

            if (item->on_hand > 0) {

                // Printing the item
                cout << "You have selected \"";
                cout << item->name;
                cout << " - ";
                cout << item->description;
                cout << "\". This will cost you $ ";

                // Set local variables.
                int dollar = item->price.dollars;
                int cent = item->price.cents;
                string money = std::to_string(dollar) + "." + std::to_string(cent);

                // Continuation
                cout << money << "." << endl;
                cout << "Please hand over the money - type in the value of each note/coin in cents.\nPress enter or ctrl-d on a new line to cancel this purchase:\n";

                // Initialise more Variables
                bool paidFor = false;
                int remainingCost = (dollar * 100) + cent;
                vector<int> coinsToAdd;
                string moneyIn;

                // Loop until the item has been paidFor or the user has terminated the loop
                while (paidFor == false) {
                    dollar = remainingCost / 100;
                    cent = remainingCost % 100;

                    cout << "Remaining Cost: $" << dollar << "." << cent << ": ";
                    moneyIn = readInput();
                    strip(moneyIn);
                    
                    // This is to check for empty values
                    if ((cin.eof()) || (moneyIn == "")) {
                        // User cancels purchase
                        cout << "Pressed ctrl-D or enter" << endl;
                        paidFor = true;
                        clearerr(stdin);
                    } 

                    else if (isInt(moneyIn)) {
                        // Initialise and set variables
                        int coinDenoms[8] = {5, 10, 20, 50, 100, 200, 500, 1000};
                        int denomSize = sizeof(coinDenoms) / sizeof(coinDenoms[0]);
                        bool validDenomination = false;
    
                        // Check if the input is a valid denomination
                        for (int idx = 0; idx < denomSize; idx++) {
                            if (stoi(moneyIn) == coinDenoms[idx]) {
                                validDenomination = true;
                            }
                        } 
                        
                        if (validDenomination == false) {
                            // Invalid Denomination
                            cout << "That is not a valid denomination" << endl;
                        } else {
                            // Valid Input
                            remainingCost -= stoi(moneyIn);
    
                            // Add input to sumVector
                            coinsToAdd.push_back(stoi(moneyIn));
                            
                            // Paid for item
                            if (remainingCost <= 0) {
                                // User has paid for the item
                                paidFor = true;
                                int change = abs(remainingCost);
                                
                                cout << "Here is your " << item->name << " and your change of $" << change / 100 << "." << change % 100 << ": ";
                                // if (printChange(change, LinkedList)) {
                                //     // if failed to give change
                                //     cout << "Sorry, we don't have enough coins to give you change" << endl;
                                //     cout << "Try again with more exact coins" << endl;
                                // } else {
                                //     // if successfully gave change
                                //     cout << "Please come again soon.\n";
    
                                //     // removing stock
                                //     item->on_hand -= 1;

                                //     // removing coins from purse
                                //     int sizeAdd = coinsToAdd.size();
                                //     for (int idx = 0; idx < sizeAdd; idx++) {
                                //         int denomIdx = 0;
                                //         for (int jdx = 0; jdx < 8; jdx++) {
                                //             if (coinsToAdd[idx] == coinDenoms[jdx]) {
                                //                 denomIdx = jdx;
                                //             }
                                //         }
                                //         LinkedList.purse[denomIdx].count++;
                                //     }
                                // }
                                // if successfully gave change
                                    cout << "Please come again soon.\n";
    
                                    // removing stock
                                    item->on_hand -= 1;

                                    // removing coins from purse
                                    int sizeAdd = coinsToAdd.size();
                                    for (int idx = 0; idx < sizeAdd; idx++) {
                                        int denomIdx = 0;
                                        for (int jdx = 0; jdx < 8; jdx++) {
                                            if (coinsToAdd[idx] == coinDenoms[jdx]) {
                                                denomIdx = jdx;
                                            }
                                        }
                                        LinkedList.purse[denomIdx].count++;
                                    }
                            }
                        }
                    } else {
                        cout << "Enter a valid denomination" << endl;
                    }
                }
            }
            else {
                cout << "Item not in machine" << endl;
            }
        }
    } else {
        clearerr(stdin);
        cout << endl;
    }
}

string strip(std::string& s) {
    int i = 0;
    while (std::isspace(s[i])) {
        // Remove the character at index i
        s.erase(i, 1);
    }
    // Count for new index for end point here.
    int lastIndex = s.length() - 1;
    while (std::isspace(s[lastIndex])) {
        // Remove the character at index i
        s.erase(lastIndex, 1);
        // Count for new index for end point here.
        lastIndex = s.length() - 1;
    }
    return s;
}

bool isInt(const std::string& input) {
    bool retVal = true;
    int inputLen = input.length();
    for (int i = 0; i < inputLen; ++i){
        if (!isdigit(input[i])){
            retVal = false;
        }
    }

    // Added this because "nothing" should not be an int
    if (input.length() == 0) {
        retVal = false;
    }
    return retVal;
}

// delete this function in the final code
// void useLinkedList() {
//     FoodItem* item1 = new FoodItem("I0001", "Burger", "A cheese burger", 12.99, 10);
//     FoodItem* item2 = new FoodItem("I0002", "Pizza", "A big pizza", 15.99, 10);
//     FoodItem* item3 = new FoodItem("I0003", "Tea", "Black tea", 6.75, 10);
//     FoodItem* item4 = new FoodItem("I0004", "Fruit", "any fruit", 0.95, 10);
//     FoodItem* item5 = new FoodItem("I0005", "Apple Pie", "description", 1.5, 100);

//     LinkedList list;

//     list.addFront(item1);
//     list.addBack(item2);
//     list.addFront(item3);
//     list.addBack(item4);
//     list.addAt(item5, 2);
//     list.addFront(new FoodItem("I0006", "Lemon Tart", "description", 3.75)); 
//     list.printItems();

//     list.removeBack();
//     list.removeFront();
//     list.removeAt(2);
   
//     list.printItems();
// }