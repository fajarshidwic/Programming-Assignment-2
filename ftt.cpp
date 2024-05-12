#include <iostream>
#include "LinkedList.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

void printMainMenu();

void useLinkedList();

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO

    cout << "Just a test, nothing implemented yet!" << endl;
    useLinkedList();

    return EXIT_SUCCESS;
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