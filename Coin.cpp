#include "Coin.h"
#include <string>
 
 // implement functions for managing coins; this may depend on your design.

void Coin::sortCoins(Coin* purse) {
    int n = 10;
    Coin* arr = purse;
    // Bubble sort since only 8 items.
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].denom > arr[j + 1].denom) {
                Coin temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    purse = arr;
}

Denomination Coin::string_to_denomination(std::string& str) {
    Denomination value;
    if (str == "5") {
        value = FIVE_CENTS;
    } else if (str == "10") {
        value = TEN_CENTS;
    } else if (str == "20") {
        value = TWENTY_CENTS;
    } else if (str == "50") {
        value = FIFTY_CENTS;
    } else if (str == "100") {
        value = ONE_DOLLAR;
    } else if (str == "200") {
        value = TWO_DOLLARS;
    } else if (str == "500") {
        value = FIVE_DOLLARS;
    } else if (str == "1000") {
        value = TEN_DOLLARS;
    } else if (str == "2000") {
        value = TWENTY_DOLLARS;
    } else if (str == "5000") {
        value = FIFTY_DOLLARS;
    } else {
         // handle error
        value = ERROR;
    }
    return value;
}

std::string Coin::denomination_to_string(Denomination denom) {
    std::string s;
    if (denom == FIVE_CENTS) {
        s = "5";
    } else if (denom == TEN_CENTS) {
        s = "10";
    } else if (denom == TWENTY_CENTS) {
        s = "20";
    } else if (denom == FIFTY_CENTS) {
        s = "50";
    } else if (denom == ONE_DOLLAR) {
        s = "100";
    } else if (denom == TWO_DOLLARS) {
        s = "200";
    } else if (denom == FIVE_DOLLARS) {
        s = "500";
    } else if (denom == TEN_DOLLARS) {
        s = "1000";
    } else {
        s = "-1"; // handle error
    }
    return s;
}