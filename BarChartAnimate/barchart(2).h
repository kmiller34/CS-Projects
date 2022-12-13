/*Keegan Miller
University of Illinois at Chicago
10/15/2022
Project 3 Animation Graph
Using windows 10 on Replit*/
// barchart.h


#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in graders, do not remove
#include "bar.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <bits/stdc++.h>

using namespace std;

// Constants used for bar chart animation.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RESET("\033[0m");


//
// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL
// 
// Color codes for light mode terminals
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
// const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for darker mode terminals
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
// const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

// ----------------------------------------------
//This is the barchart class that will deal with adding all the bars into a single frame
class BarChart {
 private:
    Bar* bars;  // pointer to a C-style array
    int capacity; //keeps track of how large the array can be
    int size; //keeps track of the current size of the array
		string frame; //keeps track of time of the frame
    
 public:
		//-------------------------------------------------------------------
    // default constructor: sets values to either 0, empty string or null
    BarChart() {
      bars = nullptr; 
      capacity = 0;
			size = 0;
      frame = "";  
    }

		//---------------------------------------------------------------------
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
      bars = new Bar[n] ;  
      this->capacity = n;
			this->size = 0;
			this->frame = "";// TO DO:  Write this constructor.
    }

    // ----------------------------------------------------------------------
    // copy constructor:
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    BarChart(const BarChart& other) {
			bars = new Bar [other.size];//creates a new array pointer
			capacity = other.capacity;
			size = other.size;
			frame = other.frame;
      for(int i = 0; i < other.size; i++){ //this for loop goes through and assigns the values of the old array to the new array
				bars[i] = other.bars[i];
			}
    }

		//-------------------------------------------------------------------------
    // copy operator=
    // Called when you assign one BarChart into another, i.e. barchart1 = barchart2;
    BarChart& operator=(const BarChart& other) {
      BarChart bc;
      if(bars != nullptr){//this helps to prevent memory leaks
				delete[] bars;
			}
      this->bars = new Bar [other.capacity];
			this->capacity = other.capacity;
			this->size = other.size;
			this->frame = other.frame;
      for(int i = 0; i < other.size; i++){//assigns objects from one barchart object into another
				this->bars[i] = other.bars[i];
			}
      return *this;
    }

		//------------------------------------------------------------------------
    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
			delete[] bars;//deletes array preventing memory leaks
      capacity = 0; 
			frame = "";
			size = 0;// TO DO:  Write this operator.
      bars = nullptr;  
    }
    
    // -------------------------------------------------------------------
    // destructor:
    // Called automatically by C++ to free the memory associated by the BarChart.
    virtual ~BarChart() {
      clear();  
    }

    // ---------------------------------------------------------------------------
    // setFrame
		// Adds a value to frame
    void setFrame(string frame) {
      this->frame = frame;
    }

		//---------------------------------------------------------------------------
    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {
      return frame;
    }

    // addBar
    // adds a Bar to the BarChart. Returns true if successful. Returns false if there is not room
    bool addBar(string name, int value, string category) {
			if(capacity > size){//If the size is within the array
				Bar bar(name,value,category);
				bars[size] = bar;
				size += 1;
				return true;
			}
			else{
				return false;
			}
    }

		//----------------------------------------------------------
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {  
      return size;
    }

		//------------------------------------------------------------
		//getCapacity()
		//returns the capacity of the array
		int getCapacity(){
			return capacity;
		}

		//-------------------------------------------------------------
		//returns the array pointer(used to make sure bars is set properly)
		Bar* getBars(){
			return bars;
		}

		//------------------------------------------------------------
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
        Bar b;
        if(i >= size){//if size goes over I throw and out_of_range error
					throw out_of_range("BarChart: i out of bounds");
				}
				else{
					return this->bars[i];//returns the element within the array
				}
    }

    //----------------------------------------------------------------------------------
    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
		output << "frame: " << frame << endl;
		sort (bars, bars+size,greater<Bar>());//sorts the bar charts in descending order
    for(int i = 0; i < size; i++){
			output << bars[i].getName() << " " << bars[i].getValue() << " " << bars[i].getCategory() << endl;
			}
    }

		//---------------------------------------------------------------------------------------------------
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	double lenMax = 60.0;  // this is number of BOXs that should be printed
			sort (bars, bars+size,greater<Bar>());
			int maxLen = bars[0].getValue();
			string color = "";
			string barstr = "";

			for(int i = 0 ; i < top; i++){//loops through each bar with a single frame
				lenMax = ((double)bars[i].getValue()/(double)maxLen) * 60.0;//set the number of bars to the value/value of the largest multipled by 60
				color = colorMap[bars[i].getCategory()];//sets the color to whatever it is in the color map
				// color = WHITE;
				barstr = "";
				for(double j = 0.0; j < lenMax; j++){//loops through the appropriate amout of boxes the bar should have
					barstr += BOX;
				}
				output << color << barstr << " " << this->bars[i].getName() << " " << this->bars[i].getValue() << endl;
				barstr = "";
			}
			lenMax = 0.0;
			output << WHITE << "Frame: " << getFrame() << endl;
    }
};

