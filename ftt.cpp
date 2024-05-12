#include <iostream>
#include "LinkedList.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

void printMainMenu();

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

    return EXIT_SUCCESS;
}


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

