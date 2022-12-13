/*
Keegan Miller Program 2 Search Engine CS 251
Professor Koehler 10/2/2022
Using Windows 10 Machine with Replit
*/

#pragma once

#include <iostream>
#include<bits/stdc++.h>//Used for Transform
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;


//-------------------------------------------
//This function takes in a string and outputs the string without any punction at the beginning and end of the string
string cleanToken(string s) { 
	string token;
	int position = 0;
	int secondPosition = 0;
	int checkForLetter = 0;
  for(int i = 0; i < s.size(); i++){//This loops through and finds where punctuation stops from the stop
		if(!ispunct(s.at(i))){
			position = i;//Grabs the position of the first nonpunctuated charatcer
			break;
		}
	}
	for(int i = s.size() - 1; i > 0; i--){//This for loop finds where the punctuation starts from the end.
		if(!ispunct(s.at(i))){
			secondPosition = i;
			break;
		}
	}
	for(int i = 0; i < s.size(); i++){//This loop makes sure that the string has a leter in it
		if(isalpha(s.at(i))){
			checkForLetter += 1;
		}
	}
	if(checkForLetter != 0){//If there is a letter then the punctuation at the start and end is removed
		s.erase(secondPosition + 1, s.size());
		s.erase(0,position);
		transform(s.begin(), s.end(), s.begin(), ::tolower);//changes letters to lowercase
		return s;
	}
	else{
		return "";
	}
}

//----------------------------------------------
//This function gathers all the words that have been cleaned and stores them in a set of strings
set<string> gatherTokens(string text) {
  set<string> tokens;
	string word = "";
	string newWord = "";

	for(int i = 0; i < text.size(); i++){//loops through the provided sentence
		if((text.at(i) == ' ') && (i != 0) || i + 1 == text.size()){//if there is a space or the text is at the last character
			if(i + 1 == text.size()){//adds the last character to the string word
				word += text.at(i);
			}
			newWord = cleanToken(word);
			if(newWord != ""){//makes sure blank space isn't added to the set
				tokens.insert(newWord);
			}
			word = "";
			newWord = "";
		}	
		else{
			word += text.at(i);
		}
	}
  return tokens;
}

//---------------------------------------------------------------------
//This function stores the key words and the urls into a map called Index
int buildIndex(string filename, map<string, set<string>>& index){
	fstream inFS;  
	string file;
	set<string> tokens;
	int count = 0;
	int lineNumber = 0;
	string word = "";
	inFS.open(filename);
	string url = "";
	if(!inFS.is_open()){
		return 0;
	}
	else{
		while(!inFS.eof()){
			getline(inFS, file);
			lineNumber++;
			if(lineNumber % 2 == 1 && file != ""){//Checks to see if the string is a url
				count++;
				url = file;
			}
			else{
				tokens = gatherTokens(file);
				for(auto word:tokens){//If the string isn't a url then each word is passed into the map with the current url set as the value
					index[word].insert(url);
				}
			}
		}
	return count;
	}
}

//---------------------------------------------------------------------------------
//This function gets user input and looks for which urls that word occurs in
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
  set<string> result;
	set<string> word1;
	set<string> word2;
	int count = 0;
	size_t found;
	vector<string> words;
	string word = "";
	found = sentence.find(" ");

	for(int i = 0; i < sentence.size(); i++){//loops through the user input of words and breaks them up
		if(sentence.at(i) == ' '){
			words.push_back(word);//pushes the individual word into a vector
			word = "";
		}
		else{
			word += sentence.at(i);
		}
	} 
	words.push_back(word);
	word1 = index[cleanToken(words.at(0))];//has the first word equal to the first word in the vector
	for(int i = 0; i < words.size(); i++){//loops through my vector of words
		if(found != string::npos){//if there were multiple words
			if(i != 0 && words.at(i).at(0) == '+'){
				word2 = index[cleanToken(words.at(i))];//sets the set to all urls found at a given word
				set_intersection(word1.begin(), word1.end(), word2.begin(), word2.end(), inserter(result, result.begin()));//grabs the intersection of the two sets
				word1 = result;
				result.clear();
			}
			else if(i != 0 && words.at(i).at(0) == '-'){
				word2 = index[cleanToken(words.at(i))];
				set_difference(word1.begin(), word1.end(), word2.begin(), word2.end(), inserter(result, result.begin()));//grabs the difference between the urls of the first and second word
				word1 = result;
				result.clear();
			}
			else if(i != 0 && words.at(i).at(0) != '-' && words.at(i).at(0) != '+'){
				word2 = index[cleanToken(words.at(i))];
				set_union(word1.begin(), word1.end(), word2.begin(), word2.end(), inserter(result, result.begin()));//grabs the union between the two sets of urls
				word1 = result;
				result.clear();
			}
		}
		else{
			word1 = index[cleanToken(words.at(i))];
		}
	}
  return word1;
}

//-------------------------------------------------
//This function will remove a few stop words
void stopWords(map<string, set<string>>& index){
	index.erase("to");
	index.erase("the");
	index.erase("so");
	index.erase("but");
}

//-------------------------------------------
//This function calls buildIndex and findQueryMatches and displays the output that these fucntions return
void searchEngine(string filename) {
	string sentence;
	string answer;
	map<string,set<string>> index;
	set<string> results;
	int count = buildIndex(filename, index);

	cout << "Would you like to remove filler words?(Enter yes or no)\n";
	cin >> answer;
	if(answer == "yes"){//if the user wants to remove stop words this will execute
		stopWords(index);
	}

	cout << "Stand by while building index...\n";
	cout << "Indexed " << count << " pages containing " << index.size() + 1 << " unique terms\n\n";
	cout << "Enter query sentence (press enter to quit):" << endl;
	getline(cin, sentence);
	while(sentence != ""){//loops through as long as the user doens't hit enter
		results = findQueryMatches(index,sentence);
		cout << "Found " << results.size() << " matching pages\n"; 
		for(auto word:results){//prints out all the urls
			cout << word << " " << endl;
		}
		cout << "\nEnter query sentence (press enter to quit):" << endl;
	  getline(cin, sentence);
	}
	cout << "Thank you for searching!";
}




