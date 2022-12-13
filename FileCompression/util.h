//
// Keegan Miller CS 251 Data Structure
// Professor Koehler Lab Wednesday 4pm
// Project 6 File Compression
// Using Windows 10 and Clion
// 11/ 27/ 2022
// TODO:  Write your own header
//
#include <hash_map>
#include <unordered_map>
#include "hashmap.h"
#include "bitstream.h"
#include <fstream>
#include <queue>

#pragma once
 using namespace std;

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

struct HuffmanNode { // This struct deals with the nodes for the tree structure
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

struct compare //This compare function makes sure the priority queue is in descending order
{
    bool operator()(const HuffmanNode *lhs,
        const HuffmanNode *rhs)
    {
        return lhs->count > rhs->count;
    }
};

// -------------------------------------------------------------
// *This method frees the memory allocated for the Huffman tree.
void freeTree(HuffmanNode* node) {
    if(node == nullptr){
        return;
    }
    else{
        freeTree(node -> zero);
        freeTree(node -> one);
        delete(node);
    }
} //end of function

// -------------------------------------------------------------------------
// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
    int key;
    int value;
    if(isFile){ //checks to see if the string is a file name
        ifstream infs(filename);
        if(!infs.is_open()){
            cout << "Can't open file" << endl;
        }
        char c;
        while(infs.get(c)){ //loops through and grabs each character
            if(!map.containsKey(c)){
                value = 1;
            }
            else{
                value = map.get(c) + 1;
            }
            key = c;
            map.put(key,value);
        }
    }
    else{
        for(char c : filename){
            if(!map.containsKey(c)){
                value = 1;
            }
            else{
                value = map.get(c) + 1;
            }
            key = c;
            map.put(key,value);
        }
    }
    map.put(PSEUDO_EOF,1);
}

// -------------------------------------------------------------
// *This function builds an encoding tree from the frequency map.
HuffmanNode* buildEncodingTree(hashmapF &map) {
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, compare> pq;
    int counter = map.keys().size();
    for (int i = 0; i < counter; i++) {
        HuffmanNode *newNode = new HuffmanNode();
        newNode->character = map.keys().at(i);
        newNode->count = map.get(map.keys().at(i));
        newNode -> one = nullptr;
        newNode -> zero = nullptr;
        pq.push(newNode);
    }
    HuffmanNode *lastNode;
    while(pq.size() > 1) {//loops through to make lastNode the root node
        HuffmanNode *notAChar = new HuffmanNode();
        notAChar -> count = 0;
        notAChar -> character = NOT_A_CHAR;
        notAChar -> zero = pq.top();
        notAChar -> count += pq.top() -> count;
        pq.pop();
        notAChar -> one = pq.top();
        notAChar -> count += pq.top() -> count;
        pq.pop();
        pq.push(notAChar);
        lastNode = notAChar;
    }
    return lastNode;
} //end of function

// ---------------------------------------------------------
// *Recursive helper function for building the encoding map.
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str,
                       HuffmanNode* prev) {
    if(node -> character != NOT_A_CHAR){//if the node is a leaf node
        encodingMap[node -> character] = str;
        return;
    }
    else{
        _buildEncodingMap(node -> zero, encodingMap, str + "0", node);
        _buildEncodingMap(node -> one, encodingMap, str + "1", node);

    }
} //end of function

// -------------------------------------------------------------
// *This function builds the encoding map from an encoding tree.
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;
    string value = "";
    _buildEncodingMap(tree,encodingMap,value,tree);//calls recursion function
    return encodingMap;
}

// --------------------------------------------------------------------------
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    string finalString;
    int fileChar;

    while(!input.eof()){//loops through entire file
        string pushIn;
        fileChar = input.get();
        pushIn = encodingMap[fileChar];
        finalString += pushIn;
        if(makeFile){
            for(int i = 0; i < pushIn.size(); i++){
                if(pushIn.at(i) == '0'){
                    output.writeBit(0);
                }
                else if(pushIn.at(i) == '1'){
                    output.writeBit(1);
                }
            }
        }
    }
    //this final bit of code is to grab the eof character
    string psuedoString;
    fileChar = PSEUDO_EOF;
    psuedoString = encodingMap[fileChar];
    finalString += psuedoString;

    if(makeFile){
        for(int i = 0; i < psuedoString.size(); i++){
            if(psuedoString.at(i) == '0'){
                output.writeBit(0);
            }
            else if(psuedoString.at(i) == '1'){
                output.writeBit(1);
            }
        }
    }
    size = finalString.size();
    return finalString;
}//end of function


// ----------------------------------------------------------------------------
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    string finalString = "";
    HuffmanNode* temp = encodingTree;
    while(!input.eof()){
        int bit = input.readBit();
        if(bit == 1){
            encodingTree = encodingTree -> one;
        }
        else if(bit == 0){
            encodingTree = encodingTree -> zero;
        }
        else if(bit == -1){
            continue;
        }
        if(encodingTree -> character == PSEUDO_EOF){
            encodingTree = temp;
            break;
        }
        if(encodingTree -> character != NOT_A_CHAR){
            output.put(encodingTree -> character);
            finalString += encodingTree -> character;
            encodingTree = temp;
        }
    }
    return finalString;
} //end of fucntion

// ------------------------------------------------------------------------
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
string compress(string filename) {
    bool isFile = true;
    string value = "";
    hashmapF map;
    hashmapE encodingMap;
    HuffmanNode* tree;
    int size = 0;
    buildFrequencyMap(filename, isFile, map);
    tree = buildEncodingTree(map);
    encodingMap = buildEncodingMap(tree);
    ofbitstream output(filename + ".huf");
    output << map;
    ifstream input(filename);
    value = encode(input, encodingMap, output,
                   size, isFile);
    freeTree(tree);
    return value;

} //end of function

// ---------------------------------------------------------------------------
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
string decompress(string filename) {
    bool isFile = true;
    HuffmanNode* tree;
    hashmapF map;
    size_t pos = filename.find(".huf");
    string textFile = filename.substr(0, pos);
    cout << textFile << endl;
    string value = "";
    string newFile = textFile + "_unc.txt";
    ifbitstream input(filename);
    ofstream output(newFile);
    buildFrequencyMap(textFile, isFile, map);
    tree = buildEncodingTree(map);
    input >> map;
    value = decode(input, tree, output);
    freeTree(tree);
    return value;
} //end of function
