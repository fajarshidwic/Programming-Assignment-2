#include "LinkedList.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>


using std::cout;
using std::endl;

LinkedList::LinkedList() {
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList() {
    // TODO
}

void LinkedList::addFront(FoodItem* data) {
    Node* newNode = new Node(data, head);
    this->head = newNode;
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
        }
    } else {
        throw std::runtime_error("Index out of range");
    }
}

void LinkedList::printItems() {
    Node* current = head;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                    | Available | Price" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (unsigned i=0; i<count; ++i) {
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