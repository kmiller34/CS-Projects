#include <iostream> //This is used inorder to take in and display code
#include <string> //Included to work with strings
#include <sstream> //Allows my string which is called getLine to be treated as a stream
#include <vector>//This is used to be able to work with vectors
#include <fstream> //this is used in order to read in data
#include <algorithm> //This is used in order to use the count method and see which song had the most number one appearances
using namespace std;

//-------------------------------------------------------------------
//This is my display function that will show the the first three options
//The users gets to choose between which set of time they want to look through data for
//If 1,2,or 3 is not inputted the code ends
void displayScreen(){
  cout << "Program 4: BillBoard Analysis " << endl
      << "CS 141, Spring 2022, UIC \n " << endl
      << "This program will analyze weekly Billboard data" 
      << " spanning from 1960 - 2020.\n" << endl
      << "Select file option:" << endl
      << "   1. To analyze charts top 50: 1960 - 1980 data file"
      << endl
      << "   2. To analyze charts top 50: 1981 - 2000 data file"
      << endl
      << "   3. To analyze charts top 50: 2001 - 2020 data file"
      << endl;
}//end of function

//-------------------------------------------------------------------
//This is my menu function
//This function displays options for what the user could do with the csv file they have chosen
void menuOption(){
  cout << "Select a menu option: \n"
      << "   1. Display overall information about the data\n"
      << "   2. Display the Billboard info of the song with the "
      <<        "most #1 occurrences for a given decade or year\n"
      << "   3. Display the Billboard info for the most long-"
      <<   "lasting song on the charts for a given decade or year\n"
      << "   4. Display the Billboard info for the song with the "
      << "greatest weekly climb on the charts given a decade or year\n"
      << "   5. Artist Search - Return the Billboard info for" 
      <<     " records that matches user input for artist search\n"
      << "   6. Exit\n";
}//end of function

//------------------------------------------------------------------
//This is my BillBoard class that will handle all the elements in the csv file
class BillBoard{
  private:
    string song;
    int rank;
    string artist;
    int lastWeek;
    int peakRank;
    int weeksOnBillBoard;
    string date;
    int year;
  public:
  //These are my setters
    void setSong(string newSong){song = newSong;}
    void setRank(int newRank){rank = newRank;}
    void setArtist(string newArtist){artist = newArtist;}
    void setLastWeek(int newLastWeek){lastWeek = newLastWeek;}
    void setPeakRank(int newPeakRank){peakRank = newPeakRank;}
    void setWeeksOnBillBoard(int newWeeksOnBillBoard){weeksOnBillBoard = newWeeksOnBillBoard;}
    void setDate(string newDate){date = newDate;}
    void setYear(int newYear){year = newYear;}
  //This function will break up the csv into date,artist,song,etc(More info at the function)
    void getSongInfo(string dataValue);
//This function will display the song,artist,and weeks on billboard for option 3
    void displayTopWeeks() {
        cout << "The song with the highest number of weeks on the charts is: " << endl << "        " << song << " by " << artist << " with " <<weeksOnBillBoard <<" weeks on the chart."<< endl << endl;
    }
  //These are my getters
    string getSong(){ return song;}
    int getRank(){return rank;}
    string getArtist(){return artist;}
    int getLastWeek(){return lastWeek;}
    int getPeakRank(){return peakRank;}
    int getWeeksOnBillBoard(){return weeksOnBillBoard;}
    string getDate(){return date;}
    int getYear(){return year;}
};//end of class

//----------------------------------------------------------------------------------------------
//This function will check the year the player inputs based on whether they want to look at year or decade and see if the year is in the time frame
bool checkYearAndDecade( vector<BillBoard> billBoard,int playerYearChoice,string playerTimeScale){
  string firstElement = billBoard.at(0).getDate();//The first element is the first date in the billBoard vector
  string lastElement = billBoard.at(billBoard.size()-1).getDate();//The last element is the last date in the billBoard vector
  int firstElementPosition;
  int lastElementPosition;
  
//This for loop will loop through the string date(date is in the class) and erase the string until just the year is left
  for(int i = 0; i < 2; i++){
    firstElementPosition = firstElement.find('/');
    firstElement.erase(0, firstElementPosition + 1);
  }
  //This for loop will do the same as the about for loop, just with the last date in the vector
  for(int i = 0; i<2; i++){
    lastElementPosition = lastElement.find('/');
    lastElement.erase(0, lastElementPosition + 1);
  }
  //year turns the string year into an int year
  int year = stoi(firstElement);
  int year2 = stoi(lastElement);

//This if statement will check to see if the user wanted to look at a decade
  if (playerTimeScale == "d" || playerTimeScale == "D"){
    //If the year the player put in is greater than the first year which would be the highest, or less than the last year which would be the start, then this if statement is invoked and the function returns false
    if(playerYearChoice / 10 > year /10 || playerYearChoice /10 < year2 /10){
      cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen.";
      return false;
    }
  }//This block of if statements does the same thing as the one above, but this one runs when the user wants to look at a specific year
  if(playerTimeScale == "y" || playerTimeScale == "Y"){
    if(playerYearChoice  > year  || playerYearChoice < year2 ){
      cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen.";
      return false;
    }
  }
  else{//If the player's year choice is in the valid range this function returns true
    return true;
  }
}//End of Function

//-----------------------------------------------------------------------------------------------------------
//Menu Option 2
//This function will loop through the billBoard vector and see which song had the most number ones(Ties are accounted for)
void songWithTheMostNumberOnes(vector<BillBoard> billBoard,int playerYearChoice,string playerTimeScale){
  vector<string> mostNumberOnes;//This will hold songs that have appeared number one
  vector<int> numberOfTopOccurances;//This will hold how many times each song occurred number 1
  vector<string> artist;//This vector will hold all of the artist names
  int maxNumber = 0;//maxNumber will be set to whatever value has the most number one occurances
  int index = 0;//This will hold the position of the song that has occurred the most times
  for(int i = 0; i < billBoard.size(); i++){
    if((playerTimeScale == "d") || (playerTimeScale == "D")){//These two statements check to see if the song year matches the player's year choice
      if(billBoard.at(i).getYear() / 10 == playerYearChoice / 10){ 
  
        if(billBoard.at(i).getRank() == 1){
          mostNumberOnes.push_back(billBoard.at(i).getSong());
          artist.push_back(billBoard.at(i).getArtist());
          //maxNumber is set to the number of times a song has occured in the given time from as number 1
          maxNumber = count(mostNumberOnes.begin(),mostNumberOnes.end(), billBoard.at(i).getSong());
          numberOfTopOccurances.push_back(maxNumber);
          for(int i = 0;i < numberOfTopOccurances.size(); i++){
            if(maxNumber < numberOfTopOccurances.at(i)){
              maxNumber = numberOfTopOccurances.at(i);//If numberOfOccurances is greater than maxNumber than the maxNumber is updated, so then the song with the most occurances is found
            }
          }
        }
      }
    }
    if((playerTimeScale == "y" || playerTimeScale == "Y")){//This does the same as the two if statements above except this one executes when the player wants to look over a specific year
      if(billBoard.at(i).getYear()  == playerYearChoice ){ 

        if(billBoard.at(i).getRank() == 1){
          mostNumberOnes.push_back(billBoard.at(i).getSong());
          artist.push_back(billBoard.at(i).getArtist());
          maxNumber =             
          count(mostNumberOnes.begin(),mostNumberOnes.end(), billBoard.at(i).getSong());
          numberOfTopOccurances.push_back(maxNumber);
          for(int i = 0;i < numberOfTopOccurances.size(); i++){
            if(maxNumber < numberOfTopOccurances.at(i)){
              maxNumber = numberOfTopOccurances.at(i);
            }
          }
        }
      }
    } 
  }
  cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is: " << endl;
  for(int i = 0; i < numberOfTopOccurances.size(); i++){//This for loop will loop through the amount of number one songs
    if (numberOfTopOccurances.at(i) == maxNumber){//This if statement is here to check for ties
    index = i;//index i allows for the position to change accordingly for each song
      cout << "        Song Title: " << mostNumberOnes.at(index) << endl << "        Artist: " << artist.at(index) << endl << "        # of occurrences: "<<maxNumber << endl << endl;
    }
  }
  cout << endl;
}//end of Function

//----------------------------------------------------------------------------------------------------------
//MenuOption 4
//This function will check which song had the highest climb from one week to another
void greatestWeeklyClimb(vector<BillBoard> billBoard, string playerTimeScale, int playerYearChoice){
  vector<int> greatestWeeklyClimb;//Will hold the difference in rank from one week to another
  vector<string> song;//Will hold all the songs in a specific time frame
  vector<string> artist;//Will hold all the artists in a specific time frame
  vector<string> date;//Will hold all the dates in a specific time frame
  vector<int> previousRank;//Will hold all the previous ranks in a specific time frame
  vector<int> presentRank;//Will hold all the ranks in a specific time frame
  int highestClimb = 0;//This will check to see if a song has the highest climb
  int index;//This will make sure the correct position within the vectors is selected
  
  for(int i = 0; i < billBoard.size(); i++){//This will loop through the entire billBoard vector and depending on if the use wants to look at a decade or a specific year, the songs in that time range will be considered
    if(playerTimeScale == "d" || playerTimeScale == "D"){
      if(billBoard.at(i).getYear() / 10 == playerYearChoice / 10){
      greatestWeeklyClimb.push_back(billBoard.at(i).getLastWeek() - billBoard.at(i).getRank());//This will put the difference in ranks between weeks into a vector
      song.push_back(billBoard.at(i).getSong());
      artist.push_back(billBoard.at(i).getArtist());
      date.push_back(billBoard.at(i).getDate());
      previousRank.push_back(billBoard.at(i).getLastWeek());
      presentRank.push_back(billBoard.at(i).getRank());
        if(billBoard.at(i).getLastWeek() - billBoard.at(i).getRank() > highestClimb){//checks to see if highest week is greater than the difference between the two weeks an if not highestClimb is reassigned
        highestClimb = billBoard.at(i).getLastWeek() - billBoard.at(i).getRank();
        }
      }
    }  
    if(playerTimeScale == "y" || playerTimeScale == "Y"){
      if(billBoard.at(i).getYear() == playerYearChoice){
      greatestWeeklyClimb.push_back(billBoard.at(i).getLastWeek() - billBoard.at(i).getRank());
      song.push_back(billBoard.at(i).getSong());
      artist.push_back(billBoard.at(i).getArtist());
      date.push_back(billBoard.at(i).getDate());
      previousRank.push_back(billBoard.at(i).getLastWeek());    presentRank.push_back(billBoard.at(i).getRank());
        if(billBoard.at(i).getLastWeek() - billBoard.at(i).getRank() > highestClimb){
          highestClimb = billBoard.at(i).getLastWeek() - billBoard.at(i).getRank();
        }
      }
    }
  }
  
  cout << "\nThe song(s) with the greatest climb from previous week to current week position: " << endl;
  for(int i = 0; i < greatestWeeklyClimb.size(); i++){
    if (highestClimb == greatestWeeklyClimb.at(i)){//if a song's climb between weeks is equivalent to the highest climb it/they are displaye
      index = i;
      cout << "        Song Title: " << song.at(i) << endl;
      cout << "         Artist: " <<artist.at(i) << endl; 
      cout << "         Week of: " << date.at(i) << endl; 
      cout << "         Previous Week Position: " << previousRank.at(i) << endl;
      cout << "         Current Week Position: " <<presentRank.at(i) << endl; 
      cout << "         Difference of " << greatestWeeklyClimb.at(i) << "  between previous week and current week position" << endl;
    }
  }
}//End of Function

//---------------------------------------------------------------------------------------------------------
//MenuOption 3
//This function will check to see which song had the most weeks on the billBoard
int weeksOnBillBoard(vector<BillBoard> billBoard,int playerYearChoice,string playerTimeScale){
  int mostWeeksOnBillBoard = billBoard.at(0).getWeeksOnBillBoard();//Most weeks is set to the first element, but will change once new values are compared and found to be larger
  int indexOfMostWeeksOnBillBoard;//This is the index of the song with the most weeks on billBoard
  BillBoard b1;
  for (int i = 0; i < billBoard.size();i++){//This will loop through the billBoard vector and depending on how the user wants to compare songs will display songs in a given time period
    if(playerTimeScale == "d" || playerTimeScale == "D"){
      if(billBoard.at(i).getYear() / 10 == playerYearChoice / 10){
        if (billBoard.at(i).getWeeksOnBillBoard() > mostWeeksOnBillBoard){//If a song has the most weeks, then the position of the vector is saved to this int
          indexOfMostWeeksOnBillBoard = i;
          mostWeeksOnBillBoard = billBoard.at(i).getWeeksOnBillBoard();//This is done so then the largest term is always being compared
        }
      }
    }
    else if(playerTimeScale == "y" || playerTimeScale == "Y"){
      if(billBoard.at(i).getYear() == playerYearChoice){
        if (billBoard.at(i).getWeeksOnBillBoard() > mostWeeksOnBillBoard){
          indexOfMostWeeksOnBillBoard = i;
          mostWeeksOnBillBoard = billBoard.at(i).getWeeksOnBillBoard();
        }
      }
    }
  }
  return indexOfMostWeeksOnBillBoard;
}//End Of Function

//---------------------------------------------------------------------
//MenuOption 5
//This will check to see if a user inputed artist has any number one songs in a given time span
void artistSearch(vector<BillBoard> billBoard){
  string artistGuess;
  size_t found;
  cout << "Your choice --> Enter search text to retrieve first 10 records of #1 songs that match by artist name:\n";
  int index = 1;
  int objectFound = 0;//If the artist doesn't appear in the time frame and/or has no number songs, this variable willn't increment
  int occuranceCount = 0;//This will make sure that the retrieval next found below on line 286 only outputs once
  string artistName;
  getline(cin,artistGuess);
  getline(cin,artistGuess);
  for(int i = 0; i < artistGuess.size(); i++){//This will go through the user input and make it lower case
    artistGuess.at(i) = tolower(artistGuess.at(i));
  }
  for(int i = 0; i < billBoard.size(); i++){
    artistName = billBoard.at(i).getArtist();//I set the specific artist to a string in order to make it more simpler to myself
    for(int i = 0; i < artistName.size(); i++){//This goes through and makes all artists in the vector lowercase
    artistName.at(i) = tolower(artistName.at(i));
    }
    found = artistName.find(artistGuess);//This will not equal the hiddeous number you see below when the user input is in the vector
    if(found != 18446744073709551615){
      if(billBoard.at(i).getRank() == 1){
        if(occuranceCount == 0){cout << "Retrieval of first 10 #1 records found based upon search by artist name:\n";}
        occuranceCount++;
        cout << index << ") Song: " << billBoard.at(i).getSong() << endl;
        cout << "     Artist: " << billBoard.at(i).getArtist() << endl;
        cout <<"     Week of: " << billBoard.at(i).getDate() << endl;
        cout << "     Week Position: " <<billBoard.at(i).getRank() << endl;
        objectFound++;
        index++;
        if (index == 11){
          break;
        }
      }
    }    
  }
  if(objectFound == 0){
  cout << "No matching artists were found.\n\n";
  }
}//End Of Function

//------------------------------------------------------------------
//This function will loop through and exectue each menu option
void dataSwitchCase(vector<BillBoard> billBoard){
  int playerOption;//This is the menu option the player wants to use to see information about the vector
  int playerYearChoice;//This is the year/decade the player wants to look at
  BillBoard aBillBoard;
  int indexForWeeksOnBillBoard;//This will hold the index of the song with the most weeks on the billBoard
  string playerTimeScale;//This will hold the value of decade or year
  int numberOfUniqueSongs = 0;//This value will increase per unique song in the vector
   vector<string> playlistSongs;//This will hold all the songs from the vector that are unique
  for(int i = 0; i < billBoard.size(); i++){//this will loop through the billBoard vector and if a song isn't added, then it will add it to the playlistsongs vector
    if(!count(playlistSongs.begin(),playlistSongs.end(), billBoard.at(i).getSong())){
      playlistSongs.push_back(billBoard.at(i).getSong());
      ++numberOfUniqueSongs;
    }
  } 
  do{//I have a do while loop because I want the code to execute at least once
    menuOption();//displays the menuOption function
    cin >> playerOption;
    switch(playerOption){
      case 1:
      cout << "Your choice --> \n";
        cout << "Total number of rows: " << billBoard.size() << endl;
        cout << "Number of unique songs represented in the dataset: " << numberOfUniqueSongs << endl << endl;
        break;
      case 2:
      cout << "Your choice --> \n";
        cout << "Enter D to select a decade or Y to select a year.";
        cin >> playerTimeScale;
        
        while((playerTimeScale != "y") && (playerTimeScale != "d") && (playerTimeScale != "D") && (playerTimeScale != "Y")){
          cout << "Your choice --> Invalid entry. Try again.\n";
          cout << "Enter D to select a decade or Y to select a year.\n";
          cin >> playerTimeScale;
        }
        cout << "Your choice --> \n";
        if (playerTimeScale == "d" || playerTimeScale == "D"){
          cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
      }
      if(playerTimeScale == "y" || playerTimeScale == "Y"){
        cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
      }
       
        cin >> playerYearChoice;
        if(checkYearAndDecade(billBoard,playerYearChoice,playerTimeScale)){
        songWithTheMostNumberOnes(billBoard,playerYearChoice, playerTimeScale);}
        
        //cout << indexForMostTopOccurances;
        break;
      case 3:
      cout << "Your choice --> \n";
        cout << "Enter D to select a decade or Y to select a year.";
        
      cin >> playerTimeScale;
      // cout << "Your choice --> \n";
      while((playerTimeScale != "y") && (playerTimeScale != "d") && (playerTimeScale != "D") && (playerTimeScale != "Y")){
          cout << "Your choice --> Invalid entry. Try again.\n";
          cout << "Enter D to select a decade or Y to select a year.\n";
          cin >> playerTimeScale;
      }
      cout << "Your choice --> ";
      if (playerTimeScale == "d"|| playerTimeScale == "D"){
      cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
      }
      if(playerTimeScale == "y" || playerTimeScale == "Y"){
      cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
  }   
        cin >> playerYearChoice;
        if(checkYearAndDecade(billBoard,playerYearChoice, playerTimeScale)){
          indexForWeeksOnBillBoard = weeksOnBillBoard(billBoard,playerYearChoice,playerTimeScale);
          billBoard.at(indexForWeeksOnBillBoard).displayTopWeeks();
        }
        break;
      case 4:
        cout << "Your choice --> \n";
        cout << "Enter D to select a decade or Y to select a year.";
        cin >> playerTimeScale;
       // cout << "Your choice --> \n";
        while((playerTimeScale != "y") && (playerTimeScale != "d") && (playerTimeScale != "D") && (playerTimeScale != "Y")){
          cout << "Your choice --> Invalid entry. Try again.\n";
          cout << "Enter D to select a decade or Y to select a year.\n";
          cin >> playerTimeScale;
        }
        cout << "Your choice --> \n";
        if (playerTimeScale == "d"|| playerTimeScale == "D"){
          cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
        }
        if(playerTimeScale == "y" || playerTimeScale == "Y"){
          cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
        }
         
        cin >> playerYearChoice;
      if(checkYearAndDecade(billBoard,playerYearChoice,playerTimeScale)){ 
           
        greatestWeeklyClimb(billBoard,playerTimeScale, playerYearChoice);
        }
          
        break;
      case 5:
      artistSearch(billBoard);
        break;
      case 6:
      cout << "Your choice --> ";
        break;
      default:
      cout << "Your choice --> \n";
        cout << "Invalid value.  Please re-enter a value from the menu options below.\n\n";
    }
    
    //menuOption();
  }
  
  while(playerYearChoice != 6);
}

void BillBoard::getSongInfo(string dataValue){
  ifstream songInfo(dataValue);
  string line;
  vector<BillBoard> billBoard;
  //int i = 0;
  while(getline(songInfo,line)){
    if(line.substr(0,4) != "date"){
    BillBoard b1;
    //cout << endl << line;
     
    int firstComma = line.find(',');
    date = line.substr(0,firstComma);
    line.erase(0, firstComma + 1);
    string theYear = date;
    int firstSlash = theYear.find("/");
    theYear.erase(0,firstSlash + 1);
    int secondSlash = theYear.find("/");
    theYear.erase(0, secondSlash + 1);
    year = stoi(theYear);
    
    
    
    firstComma = line.find(',');
    //cout << endl << endl << line;
    rank = stoi(line.substr(0,firstComma));
    line.erase(0, firstComma + 1);
      
    firstComma = line.find(',');
    //cout << endl << line<< endl;
    song = line.substr(0, firstComma);
    //cout << "hello" << line << endl;
    line.erase(0, firstComma + 1);
    //cout << line << endl;

    firstComma = line.find(',');
    artist = line.substr(0, firstComma);
    
    line.erase(0,firstComma + 1);
    //cout << line << endl;
    
    firstComma = line.find(',');
    string lastWeeks = line.substr(0, firstComma);
    if(lastWeeks.empty()){
      lastWeek = 0;
    }
    else{
      lastWeek = stoi(line.substr(0, firstComma));
    }
    line.erase(0, firstComma + 1);

    firstComma = line.find(',');
    peakRank = stoi(line.substr(0,firstComma));
    line.erase(0, firstComma + 1);

    weeksOnBillBoard = stoi(line);

    //cout << weeksOnBillBoard;
      
    b1.setDate(date);
    b1.setRank(rank);
    b1.setSong(song);
    b1.setArtist(artist);
    b1.setLastWeek(lastWeek);
    b1.setPeakRank(peakRank);
    b1.setWeeksOnBillBoard(weeksOnBillBoard);
    b1.setYear(year);
    //cout << endl << endl << rank;
    // if (i == 1){
    //   break;
    // }
    // b1(date,rank,song,artist,lastWeek,peakRank,weeksOnBillBoard,year); 
    billBoard.push_back(b1);
    //i++;
    }
  }
  dataSwitchCase(billBoard);
}

int main() {
  int playerYearChoice;
  BillBoard b1;
  displayScreen();
  //ifstream songInfo;
  //b1.getSongInfo();
  cin >> playerYearChoice;
  

  switch(playerYearChoice){
    case 1:
      //ifstream songInfo("1960-1980.csv");
      cout << "Your choice --> \n\n";
      b1.getSongInfo("charts_top50_1960_1980.csv");
      
      break;
    case 2:
      cout << "Your choice --> \n\n";
      b1.getSongInfo("charts_top50_1981_2000.csv");
      
      break;
    case 3:
      cout << "Your choice --> \n\n";
      b1.getSongInfo("charts_top50_2001_2020.csv");
      
      break;
    default:
      cout << "Your choice --> \n";
      cout << "Invalid value. Exiting Program.";
      
      break;
    
  }
  
}