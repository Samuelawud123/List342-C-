/**
 * List342 is a templated class implementing a sorted linked list that maintains elements in order
 * based on `operator<`. It supports operations such as adding, removing, and merging elements while
 * ensuring no duplicates and sorted order. Memory management is handled to prevent leaks.
 * Author: Samuel Awud
 *
 */

#ifndef LIST342_H
#define LIST342_H
#include <iostream>
#include <string>
#include <fstream>

//Templated sorted linked list for managing elements in sorted order.
template <typename T>
class List342{
public:
    // Default constructor initializes an empty list.
    List342();

    // Copy constructor creates a deep copy of an existing list.
    List342(const List342& rhs);

    // Destructor to clean up all nodes and data in the list.
    ~List342();

    // Builds a list from a file containing objects of type T.
    // Precondition: The file should be structured correctly to create objects of type T.
    // Postcondition: Elements are added to the list; returns true if at least one element was added, false otherwise.
    bool BuildList(std::string file_name);

    // Inserts a pointer to an object into the list in sorted order.
    // Postcondition: The list size is incremented by 1; returns true if the object is successfully inserted, false otherwise.
    bool insert(T* obj);

    // Removes an object equivalent to 'target' from the list.
    // Precondition: The object must exist in the list.
    // Postcondition: The object is removed; 'result' contains a copy of the removed object; returns true if successful.
    bool remove(T target, T& result);

    // Peeks to find if an object equivalent to 'target' exists in the list.
    // Postcondition: 'result' contains a copy of the found object if it exists; returns true if the object exists.
    bool peek(T target, T& result) const;

    // Returns the number of items in the list.
    int size() const;

    // Deletes all the elements in the list.
    // Postcondition: The list is empty.
    void deleteList();

    // Merges another list into this list and empties the merged list.
    // Postcondition: All unique elements from both lists are combined in this list; 'list1' is empty.
    bool merge(List342& list1);

    // Operator overlaods
    List342<T> operator+(const List342<T>& rhs) const;
    List342<T>& operator+=(List342<T>& rhs);
    bool operator==(const List342<T>& rhs) const;
    bool operator!=(const List342<T>& rhs) const;
    List342<T>& operator=(const List342<T>& rhs);

    // Allows the printing of the list to an ostream.
    template <typename T2>
    friend std::ostream& operator<<(std::ostream& os, const List342<T2>& obj);

private:
    struct Node {
        T* data;
        Node* next;
    };
    Node* _head; // Pointer to the head of the list
};


#include "List342.cpp"
#endif