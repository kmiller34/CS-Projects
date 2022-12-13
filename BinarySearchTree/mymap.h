/*
 * Keegan Miller CS 251 Data Structures
 * Professor Koehler Lab Wednesday 4pm
 * Using CLion with Windows
 * Program 5 Balancing BST
 * Recieved help from myself netID kmill34
 * */
#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
    private:
        NODE* curr;  // points to current in-order node for begin/end

    public:
        //int size;
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {
            if(curr -> isThreaded){
                curr = curr -> right;
            }
            else{
                curr = curr -> right;
                while(curr -> left != nullptr){
                    curr = curr -> left;
                }
            }
            return iterator(curr);
        }//end of function
    };

public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
        size = 0;
        root = nullptr;
    } // end of default constructor

    //-------------------------------------------------------------------------
    // put:
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    void put(keyType key, valueType value) {
        NODE* prev = nullptr;
        NODE* currPtr = root;

        //searches the bst to see if the key exists
        while(currPtr != nullptr){
            if(key == currPtr -> key){//if the key exists update the value and return
                currPtr -> value = value;
                return;
            }
            else if(key < currPtr -> key){//moves to the left node
                prev = currPtr;
                prev -> nL += 1;
                currPtr = currPtr -> left;
            }
            else{//moves to the right node
                prev = currPtr;
                prev -> nR += 1;
                if(currPtr -> isThreaded){//checks to see if at bottom of bst
                    currPtr = nullptr;
                }
                else{
                    currPtr = currPtr -> right;
                }
            }
            if(max(prev -> nL,prev -> nR) <= 2 * min(prev -> nL,prev -> nR) +1){
                
            }
        }
        NODE* n = new NODE();
        n->key = key;
        n-> right = nullptr;
        n->left = nullptr;
        n -> value = value;
        n-> isThreaded = false;

        if(prev == nullptr){//for first value
            root = n;
            n -> isThreaded = true;
            n -> right = nullptr;
        }
        else if(key < prev -> key){//inserts new node as a left child
            n -> right = prev;
            n -> isThreaded = true;
            prev -> left = n;
            currPtr = prev -> left;
        }
        else{//inserts new node as a right child
            n -> right = prev -> right;
            prev -> isThreaded = false;
            n -> isThreaded = true;
            prev -> right = n;
            currPtr = prev -> right;
        }
        size += 1;
    }//end of function

    //----------------------------------
    // goes through the bst using recursion
    // used for the equal operator and the copy constructor
    void preOrderTraversal(NODE* root){
        if(root == nullptr){
            return;
        }
        put(root -> key, root -> value);
        preOrderTraversal(root -> left);
        if (root->isThreaded) {
            return;
        }
        else {
            preOrderTraversal(root->right);
        }
    }//end of function

    // -----------------------------------------------------------
    // copy constructor:
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    mymap(const mymap& other) {
        size = 0;
        root = nullptr;
        preOrderTraversal(other.root);
    }//end of function

    // --------------------------------------------------------------------
    // operator=:
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    mymap& operator=(const mymap& other) {
        this -> clear();
        preOrderTraversal(other.root);
        return *this;
    }//end of function

    //-----------------------------------
    //Goes through the bst until at the bottom
    //used in the clear function
    void postOrderTraversal(NODE* root){
        if(root == nullptr){
            return;
        }
        else{
            postOrderTraversal(root -> left);
            if (root->isThreaded) {
                return;
            }
            else {
                postOrderTraversal(root->right);
            }
            delete root;
        }
    } // end of function

    // -------------------------------------------------------------------
    // clear:
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    void clear() {
        postOrderTraversal(root);
        root = nullptr;
        size = 0;
    }//end of function

    // ---------------------------------------------------------------
    // destructor:
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    ~mymap() {
        clear();
    }// end of function

    //----------------------------------------------------------------------
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    bool contains(keyType key) {
        NODE* prev = nullptr;
        NODE* currNode = root;

        while(currNode != nullptr){
            if(key == currNode -> key){
                return true;
            }
            else if(key < currNode -> key){
                prev = currNode;
                currNode = currNode -> left;
            }
            else{
                prev = currNode;
                if (currNode->isThreaded) {
                    currNode = nullptr;
                }
                else{
                    currNode = currNode->right;
                }
            }
        }
        return false;
    }// end of function

    // ----------------------------------------------------
    // get:
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    valueType get(keyType key) {
        NODE* prev = nullptr;
        NODE* currNode = root;

        while(currNode != nullptr){
            if(key == currNode -> key){
                return currNode -> value;
            }
            else if(key < currNode -> key){
                prev = currNode;
                currNode = currNode -> left;
            }
            else{
                prev = currNode;
                if (currNode->isThreaded) {
                    currNode = nullptr;
                }
                else{
                    currNode = currNode->right;
                }
            }
        }
        return valueType();
    } // end of function

    // -------------------------------------------------------------
    // operator[]:
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    valueType operator[](keyType key) {
        NODE* prev = nullptr;
        NODE* currNode = root;

        while(currNode != nullptr){
            if(key == currNode -> key){
                return currNode -> value;
            }
            else if(key < currNode -> key){
                prev = currNode;
                currNode = currNode -> left;
            }
            else{
                prev = currNode;
                if (currNode->isThreaded) {
                    currNode = nullptr;
                }
                else{
                    currNode = currNode->right;
                }
            }
        }
        NODE* n = new NODE();
        n->key = key;
        n-> right = nullptr;
        n->left = nullptr;
        n -> value = 0;

        if(prev == nullptr){
            root = n;
        }
        else if(key < prev -> key){
            n -> right = prev;
            n -> isThreaded = true;
            prev -> left = n;
        }
        else{
            n -> right = prev -> right;
            prev -> isThreaded = false;
            n -> isThreaded = true;
            prev -> right = n;
        }
        return n -> value;
    }// end of function

    // ------------------------------------------------------------
    // Size:
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    int Size() {
        return size;  // TODO: Update this return.
    } // end of function

    // ------------------------------------------------------------
    // begin:
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    iterator begin() {
        NODE* curr = root;
        while(curr -> left != nullptr){//moves to the furthest left node
            curr = curr -> left;
        }
        return iterator(curr);
    }// end of function

    // ---------------------------------------------------
    // end:
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // Time Complexity: O(1)
    iterator end() {
        return iterator(nullptr);
    } // end of function

    // ---------------------------------------------------
    // performs inorder traversal in order to print all the nodes in ascending order
    //Used in the toString function
    void toStringHelper(ostream &position, NODE* root){
        if(root == nullptr){
            return;
        }
        else{
            toStringHelper(position,root->left);
            position << "key: " << root -> key << " value: " << root -> value << "\n";
            if(root -> isThreaded){
                return;
            }
            else{
                toStringHelper(position, root->right);
            }
        }
    }// end of function

    //----------------------------------------------------------
    // toString:
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    string toString() {
        NODE* currNode = root;
        string positions = "";
        stringstream position;
        toStringHelper(position,currNode);
        positions = position.str();
        return positions;
    }//end of function

    // ---------------------------------------------------
    // toVector:
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    vector<pair<keyType, valueType> > toVector() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }

    // --------------------------------------------------------------
    // checkBalance:
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    string checkBalance() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }
};
