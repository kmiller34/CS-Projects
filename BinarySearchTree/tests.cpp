/* Keegan Miller CS 251 Data Structures
 * Professor Koehler Lab Wednesday 4pm
 * Using CLion on Windows
 * Program 5 Self balancing tree
 * 11/15/2022
 * Received help from myself netID kmill34
 * */

#include <iostream>
#include "mymap.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;

//-------------------------------------
//Tests the put function with integer values
void putTest() {
	mymap<int, int> map;
	int n = rand() % 10 + 1;
	for (int i = 0; i < n; i++) {//loops through n times inserting values into bst
		int key = rand() % 100 + 1;
		int value = rand() % 100 + 1;
		map.put(key, value);
	}
	if(n == map.Size()){
        cout << "putTest Passed\n";
        cout << "SizeTest passed\n";
    }
	map.clear();
}//end of function

//---------------------------
//Tests the put function with string values
void putTest2(){
    mymap<string, string> map;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};
    int n = rand() % 10 + 1;
    for (int i = 0; i < n; i++) {//loops through n times inserting values from the arr into bst
        map.put(arr[i], arr[i]);
    }
    if(n == map.Size()){
        cout << "putTest2 Passed\n";
        cout << "SizeTest2 passed\n";
    }
    map.clear();
}//end of function

//---------------------------------------------
//This function checks the put function with float values
void putTest3() {
    mymap<float, float> map;
    int n = rand() % 10 + 1;
    float a = 5.0;
    float arr[20];
    for (int i=0;i<20;i++)//creates 20 random float values
        arr[i] = (float(rand())/float((RAND_MAX)) * a);
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    if(n == map.Size()){
        cout << "putTest3 Passed\n";
        cout << "SizeTest3 passed\n";
    }
    map.clear();
}//end of function

//------------------------------------------------
//Tests the put function with char values
void putTest4() {
    mymap<char, char> map;
    srand (time(NULL));
    int n = rand() % 10 + 1;
    char arr[n];
    for (int i = 0; i < n; i++) {
        int value = rand() % 26;//creates a random char value
        char c = value + 'a';
        arr[i] = c;
        map.put(arr[i], arr[i]);
    }
    if(n == map.Size()){
        cout << "putTest4 Passed\n";
        cout << "SizeTest4 passed\n";
    }
    map.clear();
}//end of function

//--------------------------------------
//Tests default function with integer values
void defaultTest() {
    mymap<int, int> map;
    if(0 == map.Size()){
        cout << "defaultTestPassed\n";
    }
}//end of function

//--------------------------------------
//tests default function with string values
void defaultTest2() {
    mymap<string, string> map;
    if(0 == map.Size()){
        cout << "defaultTest2 Passed\n";
    }
}//end of function

//--------------------------------------
//Tests default function with float values
void defaultTest3() {
    mymap<float, float> map;
    if(0 == map.Size()){
        cout << "defaultTestPassed\n";
    }
}//end of function

//--------------------------------------
//Tests default function with char values
void defaultTest4() {
    mymap<char, char> map;
    if(0 == map.Size()){
        cout << "defaultTest4 Passed\n";
    }
}//end of function

//-----------------------------------
//Tests the contains function with integer values
void containsTest() {
    mymap<int, int> map;
    int n = rand() % 10 + 1;
    int arr[n];
    int counter = 0;

    for (int i = 0; i < n; i++) {//puts random ints into array
        int value = rand() % 1000 + 1;
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {//puts values into bst
        map.put(arr[i],arr[i]);
    }

    for (int i = 0; i < n; i++) {
        if (!map.contains(arr[i])) {//checks to see if an element is missing
            cout << "containsTest failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "containsTest passed\n";
    }
    map.clear();
}//end of function

//-------------------------------------
//Tests the contains function with string values
void containsTest2() {
    mymap<string, string> map;
    int n = rand() % 10 + 1;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};;
    int counter = 0;

    for (int i = 0; i < n; i++) {//puts the strings from the array into the bst
        map.put(arr[i],arr[i]);
    }

    for (int i = 0; i < n; i++) {
        if (!map.contains(arr[i])) {//checks to see if any string values are missing from the bst
            cout << "containsTest2 failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "containsTest2 passed\n";
    }
    map.clear();
}//end of function

//--------------------------------------
//Tests the contains function with float values
void containsTest3() {
    mymap<float, float> map;
    int n = rand() % 10 + 1;
    float arr[n];
    int counter = 0;
    float a = 5.0;
    for (int i = 0; i < n; i++) {
        float value = (float(rand())/float((RAND_MAX)) * a);//generates a random float value
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {//loops through and stores floats in bst
        map.put(arr[i],arr[i]);
    }

    for (int i = 0; i < n; i++) {
        if (!map.contains(arr[i])) {//checks to see if any values are missing
            cout << "containsTest3 failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "containsTest3 passed\n";
    }
    map.clear();
}//end of function

//--------------------------------------------
//Tests the contains function with char values
void containsTest4() {
    mymap<char, char> map;
    int n = rand() % 10 + 1;
    char arr[n];
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 26;
        char c = 'a'+ value;//generates a random character a-z
        arr[i] = c;
    }
    for (int i = 0; i < n; i++) {//loops though putting char in bst
        map.put(arr[i],arr[i]);
    }

    for (int i = 0; i < n; i++) {
        if (!map.contains(arr[i])) {//checks to see if a value is missing
            cout << "containsTest4 failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "containsTest4 passed\n";
    }
    map.clear();
}//end of function

//-------------------------------------
//Tests the get function with integer values
void getTest(){
    mymap<int, int> map;
    int n = rand() % 100 + 1;
    int arr[n];
    int counter = 0;
    for (int i = 0; i < n; i++) {//loops through creating random ints for array
        int value = rand() % 100 + 1;
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i],arr[i]);
    }
    for (int i = 0; i < n; i++) {
        if(map.get(arr[i]) != arr[i]) {//makes sure get returns the correct key
            cout << "getTest failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "getTest passed" << endl;
    }
    if(map.Size() == n){
        cout << "getTestSize passed" << endl;
    }
    map.clear();
}//end of function

//---------------------------------------------
//Tests the get function with float values
void getTest3(){
    mymap<float, float> map;
    int n = rand() % 100 + 1;
    float arr[n];
    int counter = 0;
    float a = 5.0;
    for (int i = 0; i < n; i++) {
        int value = (float(rand())/float((RAND_MAX)) * a);//creates a random float value
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i],arr[i]);
    }
    for (int i = 0; i < n; i++) {
        if(map.get(arr[i]) != arr[i]) {//makes sure the get function is returning the correct value
            cout << "getTest3 failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "getTest3 passed" << endl;
    }
    if(map.Size() == n){
        cout << "getTestSize3 passed" << endl;
    }
    map.clear();
}//end of function

//------------------------------------------------
//Tests the get function with string values
void getTest2(){
    mymap<string, string> map;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};
    int counter = 0;

    for (int i = 0; i < 10; i++) {
        map.put(arr[i],arr[i]);
    }

    for (int i = 0; i < 10; i++) {
        if(map.get(arr[i]) != arr[i]) {//makes sure get returns the correct value
            cout << "getTest failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "getTest2 passed" << endl;
    }
    if(map.Size() == 10){
        cout << "getTestSize2 passed" << endl;
    }
    map.clear();
}//end of function

//----------------------------------------
//tests the get function with char values
void getTest4(){
    mymap<char, char> map;
    int n = rand() % 100 + 1;
    char arr[n];
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 26;
        char c = 'a' + value;//generates a random char a-z
        arr[i] = c;
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i],arr[i]);
    }
    for (int i = 0; i < n; i++) {
        if(map.get(arr[i]) != arr[i]) {//makes sure get returns the correct value
            cout << "getTest4 failed";
            counter++;
        }
    }
    if(counter == 0){
        cout << "getTest4 passed" << endl;
    }
    if(map.Size() == n){
        cout << "getTestSize4 passed" << endl;
    }
    map.clear();
}//end of function

//------------------------------
//Tests my toString function with int values
void toStringTest(){
    mymap<int, int> map;
    int n = rand() % 10 + 1;
    int arr[n];
    vector<int> order_vect;
    set<int> order;
    string sol = "";

    for (int i = 0; i < n; i++) {//this loop generates random values for the array
        int value = rand() % 10 + 1;
        arr[i] = value;
        order.insert(value);
    }
    for(auto i : order){//loops through inserting values from the set into the vector
        if(i != 0)
        order_vect.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        map.put(arr[i],arr[i]);
    }
    for(int i = 0; i < order_vect.size(); i++){
        sol += "key: ";
        sol += to_string(order_vect[i]);
        sol += " value: ";
        sol += to_string(order_vect[i]);
        sol += "\n";
    }
    if(sol == map.toString()){//makes sure both strings are equal
        cout << "toString test passed\n";
    }
    else{
        cout << "toString test failed\n";
        cout << sol << endl;
        cout << map.toString();
    }
    map.clear();
}//end of function

//------------------------------
//Tests my toString function with string values
void toStringTest2() {
    mymap<string, string> map;
    int n = rand() % 10 + 1;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};
    vector<string> order_vect;
    set<string> order;
    string sol = "";

    for (int i = 0; i < 10; i++) {//this loop generates random values for the array
        order.insert(arr[i]);
    }
    for (auto i: order) {//loops through inserting values from the set into the vector
        order_vect.push_back(i);
    }

    for (int i = 0; i < 10; i++) {
        map.put(arr[i], arr[i]);
    }
    for (int i = 0; i < order_vect.size(); i++) {
        sol += "key: ";
        sol += order_vect[i];
        sol += " value: ";
        sol +=order_vect[i];
        sol += "\n";
    }
    if (sol == map.toString()) {//makes sure both strings are equal
        cout << "toString2 test passed\n";
    } else {
        cout << "toString test failed\n";
        cout << sol << endl;
        cout << map.toString();
    }
    map.clear();
}
//end of function

//------------------------------
//Tests my toString function with char values
void toStringTest3(){
    mymap<float, float> map;
    vector<char> order_vect;
    set<char> order;
    int counter = 0;
    float a = 5.0;
    int n = rand() % 10 + 1;
    char arr[n];
    string sol = "";

    for (int i = 0; i < n; i++) {//this loop generates random values for the array
        int value = rand() % 26;//generates a random char value
        char c = value + 'a';
        arr[i] = c;
        order.insert(c);
    }
    for(auto i : order){//loops through inserting values from the set into the vector
        order_vect.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        map.put(arr[i],arr[i]);
    }
    for(int i = 0; i < order_vect.size(); i++){//generates a comparison string
        sol += "key: ";
        sol += to_string(order_vect[i]);
        sol += " value: ";
        sol += to_string(order_vect[i]);
        sol += "\n";
    }
    if(sol == map.toString()){//makes sure both strings are equal
        cout << "toString3 test passed\n";
    }
    else{
        cout << "toString test failed\n";
        cout << sol << endl;
        cout << map.toString();
    }
    map.clear();
}//end of function

//----------------------------------
//Tests the squareBracket function using int values
void testSquareBracket(){
    mymap<int, int> map;
    int n = rand() % 10 + 1;
    int arr[n];
    int order[n];
    string sol = "";
    int counter = 0;

    for (int i = 0; i < n; i++) {//this loop creates random values for the array
        int value = rand() % 1000 + 1;
        arr[i] = value;
        order[i] = value;
        map.put(arr[i],arr[i]);
    }

    for(int i = 0; i < n; i++){
        if(map[arr[i]] != order[i]){//makes sure the square bracket returns the correct value
            cout << "map value: "<< map[arr[i]] << endl;
            cout << "order value: " << order[i] << endl;
            cout << "squareBracketTest failed\n";
            counter++;
        }
    }
    if(counter == 0){
        cout << "squareBracketTest passed\n";
    }
    if(n == map.Size()){
        cout << "squareBracketTest size passed\n";
    }
    map.clear();
}//end of function

//--------------------------------------------------
//This function tests the squareBracket function with char values
void testSquareBracket4(){
    mymap<char, char> map;
    int n = rand() % 10 + 1;
    char arr[n];
    char order[n];
    string sol = "";
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 26;
        char c = 'a' + value;
        arr[i] = c;
        order[i] = c;
        map.put(arr[i],arr[i]);
    }

    for(int i = 0; i < n; i++){
        if(map[arr[i]] != order[i]){//makes sure the square bracket function is returning the right value
            cout << "map value: "<< map[arr[i]] << endl;
            cout << "order value: " << order[i] << endl;
            cout << "squareBracketTest4 failed\n";
            counter++;
        }
    }
    if(counter == 0){
        cout << "squareBracketTest4 passed\n";
    }
    if(n == map.Size()){
        cout << "squareBracketTest4 size passed\n";
    }
    map.clear();
}//end of function

//--------------------------
//Tests the plus Operator with int values
void testPlusOperator(){
    mymap<int, int> map;
    int n = rand() % 10 + 1;
    int arr[n];
    vector<int> order_vect;
    set<int> order;
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 10 + 1;
        arr[i] = value;
        order.insert(value);
    }
    for(auto i : order){//pushes sorted elemenst into vector
        order_vect.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {//this for each loop makes sure all values returned are correct
        if(order_vect.at(i) != key){
            cout << "plusOperator failed" << endl;
            counter++;
        }
        i++;
    }
    if (counter == 0){
        cout << "plusOperator passed\n";
    }
    map.clear();
}//end of function

//---------------------------------
//Tests the plus operator with string values
void testPlusOperator2(){
    mymap<string, string> map;
    int n = rand() % 10 + 1;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};
    vector<string> order_vect;
    set<string> order;
    string sol = "";
    int counter = 0;

    for (int i = 0; i < n; i++) {
        order.insert(arr[i]);
    }
    for(auto i : order){
        order_vect.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {//makes sure the plus operator returns the correct values
        if(order_vect.at(i) != key){
            cout << "plusOperator2 failed" << endl;
            counter++;
        }
        i++;
    }
    if (counter == 0){
        cout << "plusOperator2 passed\n";
    }
    map.clear();
}//end of function

//---------------------------------
//Tests the plus Operator function with float values
void testPlusOperator3(){
    mymap<float, float> map;
    int n = rand() % 10 + 1;
    float arr[n];
    vector<float> order_vect;
    set<float> order;
    int counter = 0;
    float a = 5.0;

    for (int i = 0; i < n; i++) {
        float value = (float(rand())/float((RAND_MAX)) * a);//generates a random float value
        arr[i] = value;
        order.insert(value);
    }
    for(auto i : order){
        order_vect.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        if(order_vect.at(i) != key){
            cout << "plusOperator3 failed" << endl;
            counter++;
        }
        i++;
    }
    if (counter == 0){
        cout << "plusOperator3 passed\n";
    }
    map.clear();
}//end of fucntion

//-------------------------------
//Tests the plus operator function with char values
void testPlusOperator4(){
    mymap<char, char> map;
    int n = rand() % 10 + 1;
    char arr[n];
    vector<char> order_vect;
    set<char> order;
    string sol = "";
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 26;//generates a random char value
        char c = 'a' + value;
        arr[i] = c;
        order.insert(c);
    }
    for(auto i : order){
        order_vect.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        if(order_vect.at(i) != key){
            cout << "plusOperator4 failed" << endl;
            counter++;
        }
        i++;
    }
    if (counter == 0){
        cout << "plusOperator4 passed\n";
    }
    map.clear();
}//end of function

//----------------------------------
//Tests the clear function with int values
void testClear(){
    mymap<int, int> map;
    int n = rand() % 10 + 1;
    int arr[n];

    for (int i = 0; i < n; i++) {
        int value = rand() % 10 + 1;
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();//clears tree
    if(map.Size() == 0){
        cout << "clearTest passed\n";
    }
}//end of function

//----------------------------------
//Tests the clear function with float values
void testClear3(){
    mymap<float, float> map;
    int n = rand() % 10 + 1;
    float arr[n];
    float a = 5.0;

    for (int i = 0; i < n; i++) {
        float value = (float(rand())/float((RAND_MAX)) * a);
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();//clears tree
    if(map.Size() == 0){
        cout << "clearTest3 passed\n";
    }
}//end of function

//----------------------------------
//Tests the clear function with string values
void testClear2(){
    mymap<string, string> map;
    int n = rand() % 10 + 1;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};

    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();//clears tree
    if(map.Size() == 0){
        cout << "clearTest2 passed\n";
    }
}//end of function

//----------------------------------
//Tests the clear function with char values
void testClear4(){
    mymap<char, char> map;
    int n = rand() % 10 + 1;
    char arr[n];

    for (int i = 0; i < n; i++) {
        int value = rand() % 26;
        char c = 'a' + value;
        arr[i] = c;
    }
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();//clears tree
    if(map.Size() == 0){
        cout << "clearTest4 passed\n";
    }
}//end of function

//-------------------------
//Tests the equalOperator function with int values
void equalOperatorTest(){
    mymap<int, int> map;
    mymap<int, int> map1;
    int n = rand() % 10 + 1;
    int arr[n];
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 100 + 1;
        arr[i] = value;
    }
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    map1 = map;//sets maps equal to one another
    for (int i = 0; i < n; i++) {//makes sure equal operation worked
        if(map.get(arr[i]) != map1.get(arr[i])) {
            counter++;
        }
    }
    if(counter == 0){
        cout<< "equalOperator passed\n";
    }
    map.clear();
    map1.clear();
}//end of function

//-------------------------
//Tests the equalOperator function with string values
void equalOperatorTest2(){
    mymap<string, string> map;
    mymap<string, string> map1;
    int n = rand() % 10 + 1;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};
    int counter = 0;

    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    map1 = map;//sets maps equal to one another
    for (int i = 0; i < n; i++) {//makes sure equal operation worked
        if(map.get(arr[i]) != map1.get(arr[i])) {
            counter++;
        }
    }
    if(counter == 0){
        cout<< "equalOperator2 passed\n";
    }
    map1.clear();
    map.clear();
}//end of function

//-------------------------
//Tests the equalOperator function with float values
void equalOperatorTest3(){
    mymap<float, float> map;
    mymap<float, float> map1;
    int n = rand() % 10 + 1;
    float arr[n];
    int counter = 0;
    float a = 5.0;

    for (int i = 0; i < n; i++) {
        float value = (float(rand())/float((RAND_MAX)) * a);
        arr[i] = value;
    }
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    map1 = map;//sets maps equal to one another
    for (int i = 0; i < n; i++) {//makes sure equal operation worked
        if(map.get(arr[i]) != map1.get(arr[i])) {
            counter++;
        }
    }
    if(counter == 0){
        cout<< "equalOperator3 passed\n";
    }
    map.clear();
    map1.clear();
}//end of function

//-------------------------
//Tests the equalOperator function with char values
void equalOperatorTest4(){
    mymap<char, char> map;
    mymap<char, char> map1;
    int n = rand() % 10 + 1;
    char arr[n];
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 26;
        char c = 'a' + value;
        arr[i] = c;
    }
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    map1 = map;//sets maps equal to one another
    for (int i = 0; i < n; i++) {//makes sure equal operation worked
        if(map.get(arr[i]) != map1.get(arr[i])) {
            counter++;
        }
    }
    if(counter == 0){
        cout<< "equalOperator4 passed\n";
    }
    map.clear();
    map1.clear();
}//end of function

//------------------------------
//This function tests the copyConstructor with int values
void copyConstructortest(){
    mymap<int, int> map;
    int n = rand() % 10 + 1;
    int arr[n];
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 10 + 1;
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {
        map.put(i, arr[i]);
    }
    mymap<int, int> map1 = map;//calls copy constructor
    for (int i = 0; i < n; i++) {//makes sure copy constructor works
        if(map.get(arr[i]) != map1.get(arr[i])) {
            cout<< "copyOperator failed\n";
            counter++;
        }
    }
    if(counter == 0){
        cout<< "copyOperator passed\n";
    }
    map.clear();
    map1.clear();
}//end of function

//------------------------------
//This function tests the copyConstructor with int values
void copyConstructortest2(){
    mymap<string, string> map;
    int n = rand() % 10 + 1;
    string arr[10] = {"keegan", "same", "yo", "hello", "dude", "sup","food", "rude", "like","ill"};
    int counter = 0;

    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    mymap<string, string> map1 = map;//calls copy constructor
    for (int i = 0; i < n; i++) {//makes sure copy constructor works
        if(map.get(arr[i]) != map1.get(arr[i])) {
            cout<< "copyOperator2 failed\n";
            counter++;
        }
    }
    if(counter == 0){
        cout<< "copyOperator2 passed\n";
    }
    map.clear();
    map1.clear();
}// end of function

//------------------------------
//This function tests the copyConstructor with int values
void copyConstructortest3(){
    mymap<float, float> map;
    int n = rand() % 10 + 1;
    float arr[n];
    int counter = 0;
    float a = 5.0;

    for (int i = 0; i < n; i++) {
        float value = (float(rand())/float((RAND_MAX)) * a);
        arr[i] = value;
    }
    for (int i = 0; i < n; i++) {
        map.put(i, arr[i]);
    }
    mymap<float, float> map1 = map;//call copy constructor
    for (int i = 0; i < n; i++) {//makes sure copy constructor works
        if(map.get(arr[i]) != map1.get(arr[i])) {
            cout<< "copyOperator failed\n";
            counter++;
        }
    }
    if(counter == 0){
        cout<< "copyOperator3 passed\n";
    }
    map.clear();
    map1.clear();
}//end of function

//------------------------------
//This function tests the copyConstructor with char values
void copyConstructortest4(){
    mymap<char, char> map;
    int n = rand() % 10 + 1;
    char arr[n];
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int value = rand() % 26;
        char c = 'a' + 26;
        arr[i] = c;
    }
    for (int i = 0; i < n; i++) {
        map.put(i, arr[i]);
    }
    mymap<char, char> map1 = map;//call copy constructor
    for (int i = 0; i < n; i++) {//makes sure copy constructor works
        if(map.get(arr[i]) != map1.get(arr[i])) {
            cout<< "copyOperator4 failed\n";
            counter++;
        }
    }
    if(counter == 0){
        cout<< "copyOperator4 passed\n";
    }
    map.clear();
    map1.clear();
}//end of function

int main() {
    for(int i = 0; i < 100; i++){//this is where I call my test cases
        putTest();
        putTest2();
        putTest3();
        putTest4();
        defaultTest();
        defaultTest2();
        defaultTest3();
        defaultTest4();
        containsTest();
        containsTest2();
        containsTest3();
        containsTest4();
        getTest();
        getTest2();
        getTest3();
        getTest4();
        toStringTest();
        toStringTest2();
        toStringTest3();
        testClear();
        testClear2();
        testClear3();
        testClear4();
        testPlusOperator();
        testPlusOperator2();
        testPlusOperator3();
        testPlusOperator4();
        testSquareBracket();
        testSquareBracket4();
        equalOperatorTest();
        equalOperatorTest2();
        equalOperatorTest3();
        equalOperatorTest4();
        copyConstructortest();
        copyConstructortest2();
        copyConstructortest3();
        copyConstructortest4();
    }
    return 0;
}
