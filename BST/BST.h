#ifndef BST_H
#define BST_H
#include "BSTInterface.h"
#include <sstream>
#include <ostream>

using namespace std;

template <typename T>

/** A binary tree node with data, left and right child pointers */

class BST : public BSTInterface<T> {
private:
    
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node(const T& value) {
            key = value;
            right = NULL;
            left = NULL;
        }
    };
    Node* root;

    //struct BSTIterator {
    //    Node* iteratorNode;
    //    // Constructor for the class 
    //    BSTIterator(Node* node) {
    //        Node* iteratorNode = root;
    //    };
    //    ~BSTIterator() {};

    //    bool operator!=(const BSTIterator& rhs) const {
    //        return false;
    //    }
    //    bool equals(BSTIterator other) {
    //        return false;
    //    }

    //    BSTIterator& operator++() {
    //        return *this;
    //    }

    //    T& operator*() const {
    //        return iteratorNode->key;
    //    }
    //};


    //BSTIterator begin = BSTIterator(root);
    //BSTIterator end = BSTIterator(NULL);

public:

    BST() { this->root = NULL; }
    ~BST() { deleteTree(); }

    /*string returnTree() {
        stringstream out;
        BSTIterator position = BSTIterator(root);
        while (!position.equals(end)) {
            out << *position << " ";
            ++position;
        }
        return out.str();
    }*/

    int size(Node* root){
        if (root == NULL)
            return 0;
        else
            return(size(root->left) + 1 + size(root->right));
    }
    int getSize() {
        return size(root);
    }
    
    bool search(Node*& node, const T& value){
        // Base Cases: root is null or key is present at root 
        if (node == NULL) return false;
        else if (node->key == value) return true;

        // Key is greater than root's key 
        else if (node->key < value)
            return search(node->right, value);

        else if (node->key > value)
            // Key is smaller than root's key 
            return search(node->left, value);
        else return false;
    }

    string findNode(const T& value) {
        if (search(root, value)) {
            return "found";
        }
        else
            return "not found";
    }
    
    /* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
    Node* inOrderPredecessor(Node*& node) {
        Node* currNode = node->left;
        while (currNode->right != NULL) {
            currNode = currNode->right;
        }
        return currNode;
    }

    bool deleteNode(Node*& node, const T& value){
        // base case 
        if (node == NULL) return false;

        // If the key to be deleted is smaller than the root's key, 
        // then it lies in left subtree 
        if (value < node->key)
            return deleteNode(node->left, value);

        // If the key to be deleted is greater than the root's key, 
        // then it lies in right subtree 
        else if (value > node->key)
            return deleteNode(node->right, value);

        // if key is same as root's key, then This is the node 
        // to be deleted 
        else{
            // node with only one child or no child 
            if (node->left == NULL){
                Node* temp = node;
                node = node->right;
                delete temp;
                return true;
            }

            else if (node->right == NULL){
                Node* temp = node;
                node = node->left;
                delete temp;
                return true;
            }
            // node with two children: Get the inorder successor (smallest 
            // in the right subtree) 
            Node* temp = inOrderPredecessor(node);
            //Node* temp = minValue();

            // Copy the inorder successor's content to this node 
            node->key = temp->key;

            // Delete the inorder successor 
            return deleteNode(node->left, temp->key);
        }
        return false;
    }
    bool deleteTree(){
        while (root != NULL) {
            deleteNode(root, root->key);
        }
        return true;
    }

    bool recAdd(Node*& currNode, const T& value) {
        if (currNode == NULL) {
            currNode = new Node(value);
            return true;
        }
        if (value < currNode->key) {
            return recAdd(currNode->left, value);
        }
        else if (value > currNode->key){
            return recAdd(currNode->right, value);
        }
        else {
            return false;
        }
    }

    bool addNode(const T& value){
        return recAdd(root, value);
	}

	/** Return true if node removed from BST, else false */
	bool removeNode(const T& value) {
        if (deleteNode(root, value)) {
            return true;
        }
        else {
            return false;
        }
	}

	/** Return true if BST cleared of all nodes, else false */
	bool clearTree() {
        if (root == NULL) {
            return true;
        }
        else {
            return false;
        }
	}

	/** Return a level order traversal of a BST as a string */
   
    bool outLevel(Node* root, int level, stringstream& out) const{
        if (root == NULL) return false;
        if (level == 1){
            out << " " << root->key;
            if ((root->left != NULL) || (root->right != NULL)) return true;
            return false;
        }
        if ((level == 2) && !root->left && root->right) out << " _";
        bool left = outLevel(root->left, level - 1, out);
        bool right = outLevel(root->right, level - 1, out);
        if ((level == 2) && root->left && !root->right) out << " _";
        return left || right;
    }
    string toString() const{
        stringstream out;
        if (root == NULL) out << " empty";
        else
        {
            int level = 0;
            do {
                out << endl << "  " << ++level << ":";
            } while (outLevel(root, level, out));
        }
        return out.str();
    }

};
#endif	// BST


