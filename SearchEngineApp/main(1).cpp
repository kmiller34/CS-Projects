/*
Keegan Miller Program 2 Search Engine CS 251
Professor Koehler 10/2/2022
Using Windows 10 Machine with Replit
*/

#include <iostream>
#include "search.h"
using namespace std;

int main() {
	//Test for module 1
	// string s= "7heLlo's";
 //  cout << cleanToken(s) << endl; 
	// cout << s;
	// cout << endl <<ispunct('a') << endl;
	// cout << ispunct('@');

	
	//Test for module 2
	// set<string> tokens = gatherTokens("EGGS! milk, fish,      @  bread cheese");
	// set<string> token;
	// token.insert("eggs");
	// token.insert("milk");
	// token.insert("fish");
	// token.insert("bread");
	// token.insert("cheese");
	// int i = 0;
	// int j = 0;
	// for (auto& person : token)
 //    {
	// 		j++;
 //      std::cout << person << " " << j;
 //    }
	// cout << endl;
	// for(auto& persons : tokens){
	// 	i++;
	// 	cout << i << "" << persons;
	// } 
	// cout << endl;
	// cout << (tokens.size() == 5) << endl;
	// cout << (tokens == token) << endl;

	//Testing module 3
	// string filename = "cplusplus.txt";
	// map<string,set<string>> index;
	//buildIndex(filename, &index);
	//gatherTokens("hello");

	//testing for module 4
	// int i = buildIndex(filename, index);
	// cout << index.size();
	// string sentence= "vector +container -pointer";
	// set<string> results = findQueryMatches(index,sentence);
	// for(auto word:results){
	// 	cout << word << " " << endl;
	// }
	// cout << results.size();
	// cout << i;

	//module 5
	searchEngine("cplusplus.txt");


    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.
	//search.h.cleanToken("..hello");
  return 0;
}