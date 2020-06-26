//
//  Set.h
//  Lab 09: Pokémon
//
#ifndef SET_H
#define SET_H
#include <iostream>
#include <list>
#include "SetInterface.h"
using namespace std;

template<typename T>
class Set : public SetInterface<T> {
private:
    struct node {
        node(T data, node* leftChild, node* rightChild) {
            this->data = data;
            this->leftChild = leftChild;
            this->rightChild = rightChild;
        }
        T data;
        node* leftChild;
        node* rightChild;
    };
    node* root = NULL;
    int size_ = 0;
    
public:
    Set() {}
    ~Set() {
        clear();
    }
    
    /** Inserts item into the set, if the container doesn't
     already contain an element with an equivalent value.
     @return: pair.first = pointer to item
     pair.second = true if successfully inserted, else false. */
    //virtual Pair<T*, bool> insert(const T& item) = 0;
    bool insert(const T& item) {
        if (insert(root, item)) return true;
        else return false;
    }
    //Removes item from tree
    bool remove(const T& item) {
        if (remove(root, item)) {
            size_--;
            return true;
        }
        else return false;
    }
    
    /** Removes all items from the set. */
    void clear() {
        if (root != NULL) {
            while (root != NULL) {
                remove(root->data);
            }
        }
    }
    
    //Inserts item in set
    bool insert(node*& nodeValue, T item) {
        if (nodeValue == NULL) {
            nodeValue = new node(item, NULL, NULL);
            size_++;
            return true;
        }
        if (nodeValue->data == item) return false;
        if (item < nodeValue->data) return insert(nodeValue->leftChild, item);
        if (item > nodeValue->data) return insert(nodeValue->rightChild, item);
        return false;
    }
    
    //Removes item from set
    bool remove(node*& nodeValue, T item) {
        if (nodeValue == NULL) return false;
        if (nodeValue->data == item) {
            if (nodeValue->rightChild == NULL) {
                node* tempNode = nodeValue->leftChild;
                delete nodeValue;
                nodeValue = tempNode;
                return true;
            }
            else if (nodeValue->leftChild == NULL) {
                node* tempNode = nodeValue->rightChild;
                delete nodeValue;
                nodeValue = tempNode;
                return true;
            }
            else {
                node* tempNode = nodeValue->leftChild;
                while (tempNode->rightChild != NULL) {
                    tempNode = tempNode->rightChild;
                }
                T dataValue = tempNode->data;
                remove(root, tempNode->data);
                nodeValue->data = dataValue;
                return true;
            }
        }
        if (item < nodeValue->data) return remove(nodeValue->leftChild, item);
        if (item > nodeValue->data) return remove(nodeValue->rightChild, item);
        
        return true;
    }
    
    /** @return: the number of elements contained by the Set. */
    size_t size() const {
        return size_;
    }
    
    /** @return: return 1 if contains element equivalent to item, else 0. */
    size_t count(const T& item) {
        if (count(root, item) == true) return true;
        else return false;
    }
    
    //Finds item in set
    bool count (node*& nodeValue, const T& item) {
        if (nodeValue == NULL) {
            return false;
        }
        if (nodeValue->data == item) return true;
        if (item < nodeValue->data) return count(nodeValue->leftChild, item);
        if (item > nodeValue->data) return count(nodeValue->rightChild, item);
        return false;
    }
    
    //Prints set in order
    bool printInOrder(node* nodeValue, ostringstream& oSS) const {
        if (nodeValue == NULL) return false;
        printInOrder(nodeValue->leftChild, oSS);
        oSS << nodeValue->data << ",";
        printInOrder(nodeValue->rightChild, oSS);
        return true;
    }
    
    //Overloads insertion operator
    friend std::ostream& operator<< (ostream& os, const Set& myclass)
    {
        os << myclass.toString();
        return os;
    }
    
    /** @return: string representation of items in Set. */
    string toString() const {
        ostringstream oSS;
        if (root == NULL) oSS << " empty";
        else {
            printInOrder(root, oSS);
        }
        string output = oSS.str();
        output.pop_back();
        return output;
    }
};

#endif /* SET_H */
