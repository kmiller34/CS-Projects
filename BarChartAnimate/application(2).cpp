/*
Keegan Miller
University of Illinois at Chicago
10-16-22
program 3: Animation Graph
Professor Koehler lab 3pm Wednesday
For the creative component I ask if the user wants
To see the info for only a given time period. If the 
user enters yes then I ask for the starting then the ending
point. Then the animation goes through the start and ending points
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;

int main() {
	string answer = "";
	string year1 = "";
	string year2 = "";
	string filename = "endgame.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);
	BarChartAnimate bca(title, xlabel, source);
	while (!inFile.eof()) {
    bca.addFrame(inFile);
	} 
	cout << "Would you like to see data for a specific time period?(Y/N)" << endl;
	cin >> answer;
	if(answer == "Y" || answer == "Yes" || answer == "YES" || answer == "y"||answer == "yes"){
		bca.timeSpanAnimate(cout, 12, -1);
	}
	else{
		bca.animate(cout, 12, -1);
	}
  return 0;
}
