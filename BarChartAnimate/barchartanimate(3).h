/*
Keegan Miller, University of Illinois, 10,15,2022
Project 3 Animation Graph
Using Windows 10 and Replit
*/
// barchartanimate.h


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h"
  
using namespace std;

//---------------------------------------------
// BarChartAnimate
// This is where I have the bars move to display animation
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
		string title;
		string xlabel;
		string source;
		int position;
 public:

		//--------------------------------------------------------------------------
		//BarChartAnimate
    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
			this->capacity = 4;
			barcharts = new BarChart[4];
			this->position = 0;
			map<string, string> colorMap;
			this->size = 0;
			this->title = title;
			this->xlabel = xlabel;
			this->source = source;
    }

		//----------------------------------------------------------------
    // BarChartAnimate
    // destructor:
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    virtual ~BarChartAnimate() {
      delete[] barcharts;  
			barcharts = nullptr;
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, the capacity is doubled
    void addFrame(ifstream &file) {
			string name,fileLine,category,tempValue;
			int value;
			string frame = "";
			int tempSize = 0;
			string Size = "";
			vector<string> colors {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};//holds all the colors
			file >> fileLine;//reads in the file line
			if(file.eof()){//checks to make sure the file isn't on the last line
				return;
			}
			if(fileLine != ""){//checks to make sure I am not passing through a blank string
				Size = fileLine;
				tempSize = stoi(Size);//turns the string into an integer
			}
			BarChart bc1(tempSize);
			if(size == capacity){//checks to see if the size has reached the capacity of my dynamic array
				capacity = capacity * 2;
				BarChart* bc = new BarChart[capacity];
				for(int i = 0; i < size; i++){
					bc[i] = barcharts[i];
				}
				delete[] barcharts;
				barcharts = bc;
			}
			size_t found;
			for(int i = 0; i <= tempSize; i++){//loops through an entire section of the file
				getline(file,fileLine);
				found = fileLine.find(",");
				if(fileLine != ""){
					if(fileLine.substr(5,1) != "-"){//checks to see if I am working with a date or time
						found = fileLine.find(",");
						frame = fileLine.substr(0,found);
					}
					else{
						frame = fileLine.substr(0,4);
					}
					fileLine.erase(0,found + 1);
					found = fileLine.find(",");//I use .find in order to parse the text file
					name = fileLine.substr(0,found);
					fileLine.erase(0,found + 1);
					found = fileLine.find(",");
					fileLine.erase(0,found + 1);
					found = fileLine.find(",");
					tempValue = fileLine.substr(0,found);
					value = stoi(tempValue);
					fileLine.erase(0,found + 1);
					category = fileLine;
					bc1.addBar(name,value,category);
					if(colorMap.count(category) == 0){//checks to see if the category has been added to the map
						colorMap[category] = colors.at(position);
						position++;
					}
					if(position == colors.size()){//checks to make sure position doesn't go past the size of the color array
						position = 0;
					}
					bc1.setFrame(frame);
				}
			}
		barcharts[size] = bc1;
		size++;
	}//end of addframe

		//------------------------------------------------------------------------------------
    // animate:
    // this function plays each frame stored in barcharts. This function is responsible for the motion that is seen on the screen
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
		string answer = "";
		string year1 = "";
		string year2 = "";
		if(endIter == -1){//checks to see if the user wants the entire array display
			endIter = size;
		}
		
		for(int i = 0; i < endIter && i < size; i++){ //loops through the entire barcharts array and displays the graph
			usleep(3 * microsecond);
			output << CLEARCONSOLE;
			output << WHITE << title << endl << source << endl;
			this -> barcharts[i].graph(output, colorMap, top);//call to graph function has graphs display
			output << WHITE << xlabel << endl;
		}
	}//end of animate

	//---------------------------------------------------------------------------
	//timeSpanAnimate:
	//This is my creative component and displays the animated graph for a specific time period
	void timeSpanAnimate(ostream &output, int top, int endIter){
		unsigned int microseconds = 50000;
		string year1 = "";
		string year2 = "";
		if(endIter == -1){
			endIter = size;
		}
		cout << "Please give me the starting time followed by the ending time and make sure they are in order!!!";
		cin >> year1;
		cin >> year2;
		for(int i = 0; i < endIter && i < size; i++){
			if((year1 <= this -> barcharts[i].getFrame()) && (year2 >= this -> barcharts[i].getFrame())){//checks to see if the frame is between time span
				usleep(3 * microseconds);
				output << CLEARCONSOLE;
				output << WHITE << title << endl << source << endl;
				this -> barcharts[i].graph(output, colorMap, top);
				output << WHITE << xlabel << endl;
			}
		}
	}//end of timeSpanAnimate

    //-----------------------------------------------------------------
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    int getSize(){ 
      return size; 
    }//end of getSize()

    // --------------------------------------------------------------------
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    BarChart& operator[](int i){
      BarChart bc;
      if(i > size || i < 0){//checks to see if the user is trying to access a value that is out of bounds
					throw out_of_range("BarChartAnimate: i out of bounds");
				}
				else{
					return this->barcharts[i];
				}  
    }//end of BarChart& operator
};//end of barChartAnimate class
