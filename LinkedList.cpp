#include "LinkedList.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>


using std::cout;
using std::endl;

LinkedList::LinkedList() {
    head = nullptr;
    count = 0;
    purse = new Coin[10];
}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
    delete[] purse;
}

void LinkedList::addFront(FoodItem* data) {
    Node* newNode = new Node(data, head);
    this->head = newNode;
    count ++;
}

void LinkedList::addBack(FoodItem* data) {
    Node* newNode = new Node(data);
    if (head != nullptr) {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    } else {
        head = newNode;
    }
    count ++;
}

void LinkedList::addPopularItem(FoodItem* data) {
    // Check if the item is already in the popular items list
    Node* current = popularHead;
    while (current != nullptr) {
        if (current->data->name == data->name) {
            return; // Item is already in the popular list, do not add again
        }
        current = current->next;
    }

    // Item is not in the popular list, add it
    Node* newPopularNode = new Node(data);
    newPopularNode->next = popularHead;
    popularHead = newPopularNode;
}

Node* LinkedList::getBack() {
    Node* returnNode = head;
    if (head != nullptr) {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        returnNode = current;
    }
    return returnNode;
}

int LinkedList::getIndex(std::string itemID) {
    int index = 0;
    int returnIndex = 0;

    if (head != nullptr) {
        Node* current = head;
        while (current->next != nullptr) {
            if ((current->data->id) == itemID) {
                returnIndex = index;
            }
            current = current->next;
            index = index + 1;
        }
    }
    return returnIndex;
}

void LinkedList::addAt(FoodItem* data, unsigned index) {
    if (index <= count) {
        if (index == 0) {
            addFront(data);
        } else if (index == count) {
            addBack(data);
        } else {
            Node* newNode = new Node(data);
            Node* current = head;
            
            for (unsigned i = 1; i < index; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            count ++;
        }
    } else {
        throw std::runtime_error("Index out of range");
    }
}

void LinkedList::removeFront() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
        count--;
    } else {
        throw std::runtime_error("Can't remove from an empty LinkedList");
    }
}

void LinkedList::removeBack() {
    if (head != nullptr) {
        if (head->next == nullptr) {
            removeFront();
        } else {
            Node* current = head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next->data;
            delete current->next;
            current->next = nullptr;
            count--;
        }
    } else {
        throw std::runtime_error("Can't remove from an empty LinkedList");
    }
}

void LinkedList::removeAt(unsigned index) {
    if (index < count) {
        if (index == 0) {
            removeFront();
        } else if (index == count - 1) {
            removeBack();
        } else {
            Node* current = head;
            for (unsigned i = 1; i < index; ++i) {
                current = current->next;
            }
            Node* toRemove = current->next;
            current->next = toRemove->next;
            delete toRemove->data;
            delete toRemove;
            count--;
        }
    } else {
        throw std::runtime_error("Index out of range");
    }
}

FoodItem* LinkedList::get(std::string id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data->id == id) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::printItems() {
    if (head == nullptr) {
        cout << "Linked list is empty" << endl;
        return;
    }

    Node* current = head;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                    | Available | Price" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    while (current != nullptr) {
        // cout << "while (current != nullptr) passed" << endl;
        if (current->data == nullptr) {
            cout << "Error: Data pointer in node is nullptr" << endl;
            return;
        }

        cout << std::left << std::setw(5) << current->data->id
            << "|" << std::setw(40) << current->data->name
            << "|" << std::setw(11) << current->data->on_hand
            << "|$";
        if (current->data->price.dollars < 10) {
            cout << " ";
        }
        cout << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
            << std::setfill(' ')
            << endl;
        current = current->next;
    }
}

void LinkedList::printPopularItems() {
    if (popularHead == nullptr) {
        cout << "Linked list is empty" << endl;
        return;
    }

    Node* current = popularHead;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                    | Available | Price" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    while (current != nullptr) {
        // cout << "while (current != nullptr) passed" << endl;
        if (current->data == nullptr) {
            cout << "Error: Data pointer in node is nullptr" << endl;
            return;
        }

        cout << std::left << std::setw(5) << current->data->id
            << "|" << std::setw(40) << current->data->name
            << "|" << std::setw(11) << current->data->on_hand
            << "|$";
        if (current->data->price.dollars < 10) {
            cout << " ";
        }
        cout << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
            << std::setfill(' ')
            << endl;
        current = current->next;
    }
}

void LinkedList::printCoins(std::ostream& outfile) {
    /*
    1000,3
    */
    for (int i=0; i<8; i++) {
        outfile << purse->denomination_to_string(purse[i].denom)
            << "," << purse[i].count
            << endl;
    }
    
}

void LinkedList::printItems(std::ostream& outfile) {
    Node* current = head;
    for (unsigned i=0; i<count; ++i) {
        outfile << std::left << std::setw(5) << current->data->id
            << "|" << current->data->name
            << "|" << current->data->description
            << "|" << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
            << "|" << current->data->on_hand
            << endl;
        current = current->next;
    }
    
}