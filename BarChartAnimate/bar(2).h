/* Header:
	Keegan Miller
	University of Illinois at Chicago
	10/15/2022
	Program 3: Animation BarChart
	Using Windows 10 and replit
*/
// bar.h

#include <iostream>
#include <string>
#include "myrandom.h" // used in graders, do not remove
using namespace std;

//------------------------------
//This is my Bar class that will hold the value of a single bar
class Bar {
 private:
	string name; //city, country, character, or soccer club
	int value;//population, wins, or screentime
	string category;//region, or character
 public:
    //----------------------------------
		//This is my default constructor where all values are set to empty, 0.
		Bar() {
			name = "";
			value = 0;
			category = "";
		}

		//--------------------------------------------
		//Paramaterize constructor where private variables are set
    Bar(string name, int value, string category) {
      this->name = name;
			this->value = value;
			this->category = category;
 
    }

    // destructor for my bar class:
    virtual ~Bar() {  
     }

    // getName: will return the name set for the private variable
	string getName() {        
        return name;
	}

    // getValue: will return the value set for the private variable
	int getValue() {
    return value;
	}

    // getCategory: will return the category set for the private varibale
	string getCategory() {
        return category;
	}

	// operators
    // This allows you to compare two Bar
    // objects.  Comparison should be based on the Bar's value.  For example:
	bool operator<(const Bar &other) const {
        return this->value < other.value; 
	}

	bool operator<=(const Bar &other) const {
        return this->value <= other.value; 
	}

	bool operator>(const Bar &other) const {
        return this->value > other.value; 
	}

	bool operator>=(const Bar &other) const {
        return this->value >= other.value; 
	}
};

