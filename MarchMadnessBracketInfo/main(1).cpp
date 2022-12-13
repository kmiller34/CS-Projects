//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

void programStarterInfo(){
  cout << "Program 5: March Madness Frenzy\n"; 
  cout << "CS 141, Spring 2022, UIC\n\n";
  cout << "This program reads in data from NCAA Basketball Tournaments (aka March Madness). It provides overall information regarding the data, allows you to see the path taken to the championship, uses rankings of teams to determine which region is expected to win at a given round and to find the best underdog team, and calculates point differences within the games. You can also compare the actual brackets to your own predictions!\n\n";
  cout << "Enter the name of the file with the data for the NCAA tournament: \n";
}

void menuOptionDisplay(){
  cout << "Select a menu option: \n";
  cout << "   1. Display overall information about the data\n";
  cout << "   2. Display the path of the winning team to the championship\n";
  cout << "   3. Determine which region is expected to win the championship based on a given round\n";
  cout << "   4. Identify the best underdog within a given round\n";
  cout << "   5. Find the shoo-in and nail-biting games within a given round, or overall\n";
  cout << "   6. Compare the actual brackets to your predicted brackets\n";
  cout << "   7. Exit\n\n";
}

class MarchMadness{
  private:
    string region;
    int rank1;
    string team1;
    int score1;
    int rank2;
    string team2;
    int score2;
    string winningTeam;
    int roundNumber;
    int gameNumber;
  public:
    void setRegion(string regions){region = regions;}
    void setRank1(int newRank1){rank1 = newRank1;}
    void setTeam1(string newTeam1){team1 = newTeam1;}
    void setScore1(int newScore1){score1 = newScore1;}
    void setRank2(int newRank2){rank2 = newRank2;}
    void setTeam2(string newTeam2){team2 = newTeam2;}
    void setScore2(int newScore2){score2 = newScore2;}
    void setWinningTeam(string newWinningTeam){winningTeam = newWinningTeam;}
    void setRoundNumber(int newRoundNumber){roundNumber = newRoundNumber;}
    void setGameNumber(int newGameNumber){gameNumber = newGameNumber;}
    void readInData();
    

    string getRegion(){return region;}
    int getRank1(){return rank1;}
    string getTeam1(){return team1;}
    int getScore1(){return score1;}
    int getRank2(){return rank2;}
    string getTeam2(){return team2;}
    int getScore2(){return score2;}
    string getWinningTeam(){return winningTeam;}
    int getRoundNumber(){return roundNumber;}
    int getGameNumber(){return gameNumber;}
};

//---------------------------------------------------
//Option1 with recursion
// string recursiveChampionship(vector<MarchMadness> marchMadness){
//   for(int i = 0; i < marchMadness.size(); i++){
//     if(marchMadness.at(i).getRegion() == "Championship"){
//       return marchMadness.at(i).getWinningTeam();
//     }
//     else{
//       return recursiveChampionship(marchMadness);
//     }
//   }
// }


//--------------------------------------------
//Option2
void pathToTheChampionship(vector<MarchMadness> marchMadness){
  string champion;
  //string team1;
  string firstOpponent;
  string secondOpponent;
  string thirdOpponent;
  string fourthOpponent;
  string fifthOpponent;
  string finalOpponent;
  int roundNumber;
  int gameNumber1;
  int gameNumber2;
  int gameNumber3;
  int gameNumber4;
  int gameNumber5;
  int gameNumber6;
  
  for(int i = 0; i < marchMadness.size(); i++){
    if(marchMadness.at(i).getRegion() == "Championship"){
      champion = marchMadness.at(i).getWinningTeam();
      finalOpponent = marchMadness.at(i).getTeam1();
      gameNumber6 = marchMadness.at(i).getGameNumber();
    }
    else if(marchMadness.at(i).getRegion() == "Final Four" && marchMadness.at(i).getWinningTeam() == champion){
      fifthOpponent = marchMadness.at(i).getTeam2();
      gameNumber5 = marchMadness.at(i).getGameNumber();
    }
    else if(marchMadness.at(i).getRoundNumber() == 4 && marchMadness.at(i).getWinningTeam() == champion){
      fourthOpponent = marchMadness.at(i).getTeam2();
      gameNumber4 = marchMadness.at(i).getGameNumber();
    }
    else if(marchMadness.at(i).getRoundNumber() == 3 && marchMadness.at(i).getWinningTeam() == champion){
      thirdOpponent = marchMadness.at(i).getTeam2();
      gameNumber3 = marchMadness.at(i).getGameNumber();
    }
    else if(marchMadness.at(i).getRoundNumber() == 2 && marchMadness.at(i).getWinningTeam() == champion){
      secondOpponent = marchMadness.at(i).getTeam2();
      gameNumber2 = marchMadness.at(i).getGameNumber();
    }
    else if(marchMadness.at(i).getRoundNumber() == 1 && marchMadness.at(i).getWinningTeam() == champion){
      //cout << "hello";
      firstOpponent = marchMadness.at(i).getTeam2();
      gameNumber1 = marchMadness.at(i).getGameNumber();
    }
  }
  cout << "Round 1, Game " << gameNumber1 << ": " << champion << " vs " << firstOpponent << ". Winner: " << champion << endl;
  cout << "Round 2, Game " << gameNumber2 << ": " << champion << " vs " << secondOpponent << ". Winner: " << champion << endl;
  cout << "Round 3, Game " << gameNumber3 << ": " << champion << " vs " << thirdOpponent << ". Winner: " << champion << endl;
  cout << "Round 4, Game " << gameNumber4 << ": " << champion << " vs " << fourthOpponent << ". Winner: " << champion << endl;
  cout << "Round 5, Game " << gameNumber5 << ": " << champion << " vs " << fifthOpponent << ". Winner: " << champion << endl;
  cout << "Round 6, Game " << gameNumber6 << ": " << finalOpponent << " vs " << champion << ". Winner: " << champion << endl << endl;
}

void expectedRegion(vector<MarchMadness> marchMadness){
  int selectedRound;
  vector<int> winnersRankSouth;
  vector<int> winnersRankWest;
  vector<int> winnersRankEast;
  vector<int> winnersRankMidwest;
  int totalValueSouth = 0;
  int totalValueWest = 0;
  int totalValueEast = 0;
  int totalValueMidwest = 0;
  vector<int> totalValue;
  int lowestValue = 999;
  vector<string> region;
  string predictedRegion;
  
  cout << "Enter a round to be evaluated: \n";
  cout << "   Select 2 for round 2\n";
  cout << "   Select 3 for round 3 'Sweet 16'\n";
  cout << "   Select 4 for round 4 'Elite 8'\n";
  cout << "   Select 5 for round 5 'Final 4'\n";
  cin >> selectedRound;
  cout << "Your choice --> \n";
  cout << "Analyzing round " << selectedRound << "...\n\n";
  
  for(int i = 0; i < marchMadness.size(); i++){
    if(marchMadness.at(i).getRoundNumber() == selectedRound){
      if(marchMadness.at(i).getRegion() == marchMadness.at(32).getRegion()){
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam1()){
          
          winnersRankSouth.push_back(marchMadness.at(i).getRank1());
        }
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam2()){
          winnersRankSouth.push_back(marchMadness.at(i).getRank2());
        }
      }
      if(marchMadness.at(i).getRegion() == marchMadness.at(16).getRegion()){
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam1()){
          winnersRankWest.push_back(marchMadness.at(i).getRank1());
        }
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam2()){
          winnersRankWest.push_back(marchMadness.at(i).getRank2());
        }
      }
      if(marchMadness.at(i).getRegion() == marchMadness.at(40).getRegion()){
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam1()){
          winnersRankEast.push_back(marchMadness.at(i).getRank1());
        }
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam2()){
          winnersRankEast.push_back(marchMadness.at(i).getRank2());
        }
      }
      if(marchMadness.at(i).getRegion() == marchMadness.at(50).getRegion()){
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam1()){
          winnersRankMidwest.push_back(marchMadness.at(i).getRank1());
        }
        if(marchMadness.at(i).getWinningTeam() == marchMadness.at(i).getTeam2()){
          winnersRankMidwest.push_back(marchMadness.at(i).getRank2());
        }
      }
    }
  }
  for(int i = 0; i < winnersRankWest.size(); i++){
    totalValueWest += winnersRankWest.at(i);
  }
  totalValue.push_back(totalValueWest);
  region.push_back(marchMadness.at(16).getRegion());
  
  for(int i = 0; i < winnersRankSouth.size(); i++){
    totalValueSouth += winnersRankSouth.at(i);
  }
  totalValue.push_back(totalValueSouth);
  region.push_back(marchMadness.at(32).getRegion());
  
  for(int i = 0; i < winnersRankEast.size(); i++){
    totalValueEast += winnersRankEast.at(i);
  }
  totalValue.push_back(totalValueEast);
  region.push_back(marchMadness.at(40).getRegion());
  
  for(int i = 0; i < winnersRankMidwest.size(); i++){
    totalValueMidwest += winnersRankMidwest.at(i);
  }
  totalValue.push_back(totalValueMidwest);
  region.push_back(marchMadness.at(50).getRegion());
  
  for(int i = 0; i < 4; i++){
    if(totalValue.at(i) < lowestValue){
      lowestValue = totalValue.at(i);
      predictedRegion = region.at(i);
    }
  }
  cout << "The region expected to win is: " << predictedRegion << endl << endl;
}

void biggestUnderDog(vector<MarchMadness> marchMadness){
  int highestRank = 0;
  int selectedRegion;
  string underDog;
  cout << "Enter a round to be evaluated:\n";
  cout << "   Select 2 for round 2\n";
  cout << "   Select 3 for round 3 'Sweet 16'\n";
  cout << "   Select 4 for round 4 'Elite 8'\n";
  cout << "   Select 5 for round 5 'Final Four'\n";
  cout << "   Select 6 for round 6 'Championship'\n";
  cout << "Your choice --> \n";
  cin >> selectedRegion;
  for(int i = 0; i < marchMadness.size(); i++){
    if(marchMadness.at(i).getRoundNumber() == selectedRegion){
      if(marchMadness.at(i).getRank1() > highestRank){
        highestRank = marchMadness.at(i).getRank1();
        underDog = marchMadness.at(i).getTeam1();
      }
      if(marchMadness.at(i).getRank2() > highestRank){
        highestRank = marchMadness.at(i).getRank2();
        underDog = marchMadness.at(i).getTeam2();
      }
    }
  }
  cout << "The best underdog is " << underDog << " which has rank " << highestRank << endl << endl;
}

void shooInNailBiter(vector<MarchMadness> marchMadness){
  int shooIn = -1;
  int nailBiter = 999;
  int roundChoice;
  int shooInRound;
  int shooInGame;
  int nailBiterRound;
  int nailBiterGame;
  string team1;
  string team2;
  string winningTeamShooIn;
  string winningTeamNailBiter;
  string team1NailBiter;
  string team2NailBiter;

  cout << "Enter a round to be evaluated:\n";
  cout << "   Select 1 for round 1\n";
  cout << "   Select 2 for round 2\n";
  cout << "   Select 3 for round 3\n";
  cout << "   Select 4 for round 4 'Elite 8'\n";
  cout << "   Select 5 for round 5 'Final Four'\n";
  cout << "   Select 6 for round 6 'Championship'\n";
  cout << "   Select 7 for overall tournament\n";
  cin >> roundChoice;
  cout << "Analyzing round " << roundChoice << "...\n\n";
  for(int i = 0; i < marchMadness.size(); i++){
    if(roundChoice == marchMadness.at(i).getRoundNumber()){
      if(abs(marchMadness.at(i).getScore1() - marchMadness.at(i).getScore2()) > shooIn){
        shooIn = abs(marchMadness.at(i).getScore1() - marchMadness.at(i).getScore2());
        shooInRound = marchMadness.at(i).getRoundNumber();
        shooInGame = marchMadness.at(i).getGameNumber();
        team1 = marchMadness.at(i).getTeam1();
        team2 = marchMadness.at(i).getTeam2();
        winningTeamShooIn = marchMadness.at(i).getWinningTeam();
      }
      if (abs(marchMadness.at(i).getScore1()-marchMadness.at(i).getScore2()) < nailBiter){
        nailBiter = abs(marchMadness.at(i).getScore1()-marchMadness.at(i).getScore2());
        nailBiterRound = marchMadness.at(i).getRoundNumber();
        nailBiterGame = marchMadness.at(i).getGameNumber();
        team1NailBiter = marchMadness.at(i).getTeam1();
        team2NailBiter = marchMadness.at(i).getTeam2();
        winningTeamNailBiter = marchMadness.at(i).getWinningTeam();
      }
    }
  }
  cout << "The shoo-in game was:\n";
  cout << "Round " << roundChoice << ", Game " << shooInGame << ": " << team1 << " vs " << team2 << ". Winner: " << winningTeamShooIn << endl;
  cout << "The difference was " << shooIn << " points\n\n";

  cout << "The nail-biting game was:\n";
  cout << "Round " << roundChoice << ", Game " << nailBiterGame << ": " << team1NailBiter << " vs " << team2NailBiter << ". Winner: " << winningTeamNailBiter << endl;
  cout << "The difference was " << nailBiter << " points\n\n";
}


void predictionComparison(vector<MarchMadness>marchMadness,vector<MarchMadness>marchMadnessPrediction){
  int correctGuesses = 0;
  int playerScore = 0;
  for(int i = 0; i < marchMadness.size();i++){
    if (marchMadness.at(i).getWinningTeam() == marchMadnessPrediction.at(i).getWinningTeam()){
      correctGuesses++;
      playerScore += (5 * marchMadness.at(i).getRoundNumber()); 
    }
  }
  cout << "You correctly predicted the winner for " << correctGuesses << " games." << endl;
  cout << "This means you have a score of " << playerScore << "." << endl;
  if(playerScore >= 250){
    cout << "Great job! You could consider entering your predictions to make money!\n\n";
  }
  else{
    cout << "You may want to learn more about basketball to improve your predictions next year.\n\n";
  }
  
}

void userProjection(vector<MarchMadness> marchMadness){
  string region;
  int rank1;
  string team1;
  int score1;
  int rank2;
  string team2;
  int score2;
  string winningTeam;
  int roundNumber;
  int gameNumber;
  string line;
  string desiredPredictionBracket;
  
  cout << "Enter the name of the file with your predicted brackets:\n";
  cin >> desiredPredictionBracket;
  
  ifstream bracketInfo(desiredPredictionBracket);
  vector<MarchMadness> marchMadnessPrediction;
  int firstComma;
  while (getline(bracketInfo,line)){
    if(line.substr(0,6) != "region"){
      MarchMadness m1;
      firstComma = line.find(',');
      region = line.substr(0,firstComma);
      line.erase(0,firstComma + 1);
      
      firstComma = line.find(',');
      rank1 = stoi(line.substr(0,firstComma));
      line.erase(0,firstComma + 1);
      
      firstComma = line.find(',');
      team1 = line.substr(0,firstComma);
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      string scored1 = line.substr(0,firstComma);
      if(scored1.empty()){
        score1 = 0;
      }
      else{
        score1 = stoi(scored1);
      }
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      rank2 = stoi(line.substr(0,firstComma));
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      team2 = line.substr(0,firstComma);
      line.erase(0,firstComma + 1);
      
      firstComma = line.find(',');
      string scored2 = line.substr(0,firstComma);
      if(scored2.empty()){
        score2 = 0;
      }
      else{
        score2 = stoi(scored2);
      }
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      winningTeam = line.substr(0, firstComma);
      line.erase(0,firstComma + 1);
      //cout << winningTeam << endl;

      firstComma = line.find(',');
      roundNumber = stoi(line.substr(0,firstComma));
      line.erase(0,firstComma + 1);

      gameNumber = stoi(line);
      m1.setRegion(region);
      m1.setRank1(rank1);
      m1.setTeam1(team1);
      m1.setScore1(score1);
      m1.setRank2(rank2);
      m1.setTeam2(team2);
      m1.setScore2(score2);
      m1.setWinningTeam(winningTeam);
      m1.setRoundNumber(roundNumber);
      m1.setGameNumber(gameNumber);
      marchMadnessPrediction.push_back(m1);
    }
  }
  predictionComparison(marchMadness,marchMadnessPrediction);
}

void menuOptions(vector<MarchMadness> marchMadness){
  int menuOptionChoice;
  string westWinner;
  string eastWinner;
  string southWinner;
  string midwestWinner;
  for(int i = 0; i < marchMadness.size();i++){
    if((marchMadness.at(i).getRegion() == marchMadness.at(16).getRegion()) && (marchMadness.at(i).getRoundNumber() == 4)){
      westWinner = marchMadness.at(i).getWinningTeam();
    }
    if(marchMadness.at(i).getRoundNumber() == 4 && marchMadness.at(i).getRegion()==marchMadness.at(32).getRegion()){
      southWinner = marchMadness.at(i).getWinningTeam();
    }
    if(marchMadness.at(i).getRoundNumber() == 4 && marchMadness.at(i).getRegion()==marchMadness.at(40).getRegion()){
      eastWinner = marchMadness.at(i).getWinningTeam();
    }
    if(marchMadness.at(i).getRoundNumber() == 4 && marchMadness.at(i).getRegion()==marchMadness.at(50).getRegion()){
      midwestWinner = marchMadness.at(i).getWinningTeam();
    }
  }
  menuOptionDisplay();
  cin >> menuOptionChoice;
  if(menuOptionChoice == 7){
    cout << "Exiting program...";
  }
  while(menuOptionChoice != 7){
    
    switch(menuOptionChoice){
      case 1:
        
        cout << "Total number of games played in the tournament: " << marchMadness.size() << endl;
        cout << "The final four contestants are: \n";
        cout << "        "<<marchMadness.at(16).getRegion() << " region:    " << westWinner<<endl;
        cout << "        " << marchMadness.at(32).getRegion() << " region:   " << southWinner <<endl;
        cout << "        " << marchMadness.at(40).getRegion() << " region:    " << eastWinner <<endl;
        cout << "        " << marchMadness.at(50).getRegion() << " region: " << midwestWinner << endl << endl << endl;
        break;
      case 2:
        pathToTheChampionship(marchMadness);
        break;
      case 3:
        expectedRegion(marchMadness);
        break;
      case 4:
        biggestUnderDog(marchMadness);
        break;
      case 5:
        shooInNailBiter(marchMadness);
        break;
      case 6:
        userProjection(marchMadness);
        break;
      default:
        break;
    }
  menuOptionDisplay();
  cin >> menuOptionChoice;
  if(menuOptionChoice == 7){
    cout << "Exiting program...";
  }
  }
}

void MarchMadness::readInData(){
  string line;
  string desiredBracket;
  cin >> desiredBracket;
  ifstream bracketInfo(desiredBracket);
  vector<MarchMadness> marchMadness;
  int firstComma;
  while (getline(bracketInfo,line)){
    if(line.substr(0,6) != "region"){
      MarchMadness m1;
      firstComma = line.find(',');
      region = line.substr(0,firstComma);
      line.erase(0,firstComma + 1);
      
      firstComma = line.find(',');
      rank1 = stoi(line.substr(0,firstComma));
      line.erase(0,firstComma + 1);
      
      firstComma = line.find(',');
      team1 = line.substr(0,firstComma);
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      string scored1 = line.substr(0,firstComma);
      if(scored1.empty()){
        score1 = 0;
      }
      else{
        score1 = stoi(scored1);
      }
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      rank2 = stoi(line.substr(0,firstComma));
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      team2 = line.substr(0,firstComma);
      line.erase(0,firstComma + 1);
      
      firstComma = line.find(',');
      string scored2 = line.substr(0,firstComma);
      if(scored2.empty()){
        score2 = 0;
      }
      else{
        score2 = stoi(scored2);
      }
      line.erase(0,firstComma + 1);

      firstComma = line.find(',');
      winningTeam = line.substr(0, firstComma);
      line.erase(0,firstComma + 1);
      //cout << winningTeam << endl;

      firstComma = line.find(',');
      roundNumber = stoi(line.substr(0,firstComma));
      line.erase(0,firstComma + 1);

      gameNumber = stoi(line);
      m1.setRegion(region);
      m1.setRank1(rank1);
      m1.setTeam1(team1);
      m1.setScore1(score1);
      m1.setRank2(rank2);
      m1.setTeam2(team2);
      m1.setScore2(score2);
      m1.setWinningTeam(winningTeam);
      m1.setRoundNumber(roundNumber);
      m1.setGameNumber(gameNumber);
      marchMadness.push_back(m1);
    }
  }
  menuOptions(marchMadness);
}

int main(){
  //int menuOptionChoice;
  programStarterInfo();
  MarchMadness m1;
  m1.readInData();

  return 0;
}