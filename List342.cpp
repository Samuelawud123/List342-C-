#include "List342.h"

#ifndef LIST342_CPP
#define LIST342_CPP

using namespace std;

//default constructor
template <typename T>
List342<T>::List342(){
    this->_head = nullptr;
};

// Copy constructor that performs a deep copy of the list.
template <typename T>
List342<T>::List342(const List342& rhs) {
    _head = nullptr;  // Initialize _head to nullptr
    Node* rhsCurrentNode = rhs._head;
    Node* prevNode = nullptr;

    // Iterate through the right-hand side list and copy each node.
    while(rhsCurrentNode != nullptr) {
        Node* newNode = new Node;
        newNode->data = new T(*(rhsCurrentNode->data));  // Deep copy of the data
        newNode->next = nullptr;

        // Link the new node into the new list.
        if (_head == nullptr) {
            _head = newNode;
        } else {
            prevNode->next = newNode;
        }
        prevNode = newNode;
        rhsCurrentNode = rhsCurrentNode->next;
    }
};

// Destructor to clean up all the nodes and their associated data.
template<typename T>
List342<T>::~List342() {
    deleteList();
}

// Inserts an element into the list in sorted order without duplicates.
// Pre-condition: The object pointed by 'obj' should be fully initialized.
// Post-condition: Returns true if the object was successfully inserted.
template<typename T>
bool List342<T>::insert(T* obj) {
    if (obj == nullptr) {
        return false;
    }

    Node* newNode = new Node;
    newNode->data = new T(*obj);  // Memory allocation for new data

    Node* current = _head;
    Node* previous = nullptr;

    // Find the insertion point.
    while (current != nullptr && *current->data < *newNode->data) {
        previous = current;
        current = current->next;
    }

    // Ensure no duplicates.
    if (current != nullptr && *current->data == *newNode->data) {
        delete newNode->data; // Clean up new node
        newNode->data = nullptr; 
        delete newNode;
        newNode = nullptr;
        return false; // Duplicate found
    }

    // Insert the new node in its place.
    if (previous == nullptr) {
        newNode->next = _head;
        _head = newNode;
    } else {
        previous->next = newNode;
        newNode->next = current;
    }

    return true;
}

// Constructs the list from a file input.
// Post-condition: Returns true if at least one item was inserted successfully.
template<typename T>
bool List342<T>::BuildList(string file_name) {
    ifstream infile(file_name);
    if (!infile) {
        cout << "File could not be opened." << endl;
        return false; // File opening failure
    }

    T obj;
    bool inserted = false;
    bool anyInsertions = false;

    // Read objects from file and try inserting them into the list.
    while (infile >> obj) {
        inserted = insert(&obj);
        if (inserted) {
            anyInsertions = true;
        }
    }

    infile.close(); // Close the file after reading
    return anyInsertions;
}

// Removes an element from the list.
// Pre-condition: The target object must be comparable with elements in the list.
// Post-condition: If the element is found and removed, returns true.
template<typename T>
bool List342<T>::remove(T target, T& result) {
    Node* current = _head;
    Node* previous = nullptr;

    // Traverse the list to find the target element.
    while (current != nullptr) {
        if (*current->data == target) {
            if (previous == nullptr) {
                _head = current->next;
            } else {
                previous->next = current->next;
            }
            result = *current->data;  // Retrieve the data
            delete current->data;  // Clean up data
            delete current;  // Clean up node
            return true;  // Element removed
        }
        previous = current;
        current = current->next;
    }

    return false;  // Element not found
}

// Checks if an element is present in the list.
// Pre-condition: The target should be comparable with the list's elements.
// Post-condition: If the target is found, sets 'result' to the found element and returns true.
template<typename T>
bool List342<T>::peek(T target, T& result) const {
    Node* currentNode = _head;

    // Traverse the list to find the target.
    while (currentNode != nullptr) {
        if (*(currentNode->data) == target) {
            result = *(currentNode->data);  // Set the result
            return true;  // Target found
        }
        currentNode = currentNode->next;
    }

    return false;  // Target not found
}

// Returns the number of elements in the list.
template<typename T>
int List342<T>::size() const{
    Node* currentNode = _head;
    int counter = 0;
    while(currentNode != nullptr){
        counter++;
        currentNode = currentNode->next;
    }
    return counter;
}

// Deletes all elements in the list.
template<typename T>
void List342<T>::deleteList() {
    while (_head != nullptr) {
        Node* temp = _head;
        _head = _head->next;
        delete temp->data; // Clean up data
        delete temp;  // Clean up node
    }
}

// Merges another list into this list without duplicates.
// Pre-condition: 'list1' should not be this list (no self-merge).
// Post-condition: Elements from 'list1' are merged into this list.
template<typename T>
bool List342<T>::merge(List342& list1) {
    if (this == &list1) {
        return true; // Self-merge check
    }

    Node* current = this->_head;
    Node* merge = list1._head;
    Node* prev = nullptr;

    // Merge 'list1' into the current list, ensuring no duplicates.
    while (merge != nullptr) {
        while (current != nullptr && *current->data < *merge->data) {
            prev = current;
            current = current->next;
        }
        if (current != nullptr && *current->data == *merge->data) {
            Node* toDelete = merge;
            merge = merge->next;
            delete toDelete->data; // Clean up duplicate data
            delete toDelete;
            continue;
        }
        Node* temp = merge->next;
        if (prev == nullptr) {
            this->_head = merge;
        } else {
            prev->next = merge;
        }
        merge->next = current;
        prev = merge;
        merge = temp;
    }

    list1._head = nullptr;
    return true;
}

// Overloaded + operator to combine two lists.
template<typename T>
List342<T> List342<T>::operator+(const List342<T>& rhs) const {
    List342<T> result;
    result.merge(*this);  // Merge the current list into result
    result.merge(rhs);    // Merge the rhs list into result
    return result;
}

// Overloaded += operator to merge another list into this list.
template<typename T>
List342<T>& List342<T>::operator+=(List342<T>& rhs) {
    this->merge(rhs);
    return *this;
}

// Overloaded output operator to print the list.
template<typename T2>
std::ostream& operator<<(std::ostream& os, const List342<T2>& list) {
    typename List342<T2>::Node* current = list._head;
    while (current != nullptr) {
        os << *(current->data);  // Assuming that T has an overloaded operator<<
        current = current->next;
    }
    return os;
}

// Overloaded equality operator to compare two lists.
template<typename T>
bool List342<T>::operator==(const List342<T>& rhs) const {
    Node* left = this->_head;
    Node* right = rhs._head;
    while (left != nullptr && right != nullptr) {
        if (*left->data != *right->data) {
            return false;
        }
        left = left->next;
        right = right->next;
    }
    return (left == nullptr && right == nullptr);
}

// Overloaded inequality operator to check if two lists are not equal.
template<typename T>
bool List342<T>::operator!=(const List342<T>& rhs) const {
    return !(*this == rhs);
}

// Overloaded assignment operator to copy one list to another.
// Pre-condition: 'rhs' should not be this instance (check for self-assignment).
// Post-condition: This list contains a deep copy of 'rhs'.
template<typename T>
List342<T>& List342<T>::operator=(const List342<T>& rhs) {
    if (this != &rhs) {  // Check for self-assignment
        this->deleteList();  // Clear current list
        Node* source = rhs._head;
        // Copy each element from 'rhs' to this list.
        while (source != nullptr) {
            this->insert(new T(*(source->data)));  // Insert a copy of each element
            source = source->next;
        }
    }
    return *this;
}

#endif
