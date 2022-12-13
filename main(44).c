//  bestWordle.c
//  Authors: Keegan Miller and Xavier Skinner
//  Program 3 Best Wordle Word
//  CS 211 Fall 2022. Tuesday 12pm lab
//  Using windows machine and replit
//  Links to wordle dictionary words at:
//    https://www.reddit.com/r/wordle/comments/s4tcw8/a_note_on_wordles_word_list/

#include <stdio.h>
#include <stdlib.h>   // for exit( -1)
#include <string.h>

//----------------------------------------------------
// this function adds spaces to the answers to reflect the second best word choice
void answerSpace(char topWords[6],char answers[6]){
  char copy[6];
	strcpy(copy, topWords);
	for(int k = 0; k < 5; k++){
    if(copy[k] == answers[k]){//adds a special character when values are the same
			copy[k] = '_';
			answers[k] = '-';
		}
	}
  for(int k = 0; k < 5; k++){
    for(int l =0; l < 5; l++){
      if(copy[l] == answers[k]){//adds a special character when letters are the same but in different spots
        copy[l] = '_';
        answers[k] = '-';
      }
    }
  }
}//end of function

//--------------
//This struct will hold the word and the word's score
typedef struct{
	char word[6]; 
	int score;
}Wordle;

//------------------------------------------------------------
//This function goes through and finds the best word out of the list of choices
int menuOption1(int position, int increment, Wordle* wordle,Wordle* answerList, Wordle* topAnswers, int bestAnswer){
	int max = 0;
	
	for(int i = 0; i < position; i++){//loops through words from both answer and guess text file
		for(int j = 0; j < increment; j++){//loops through words from just the answer text file
			char * copyAnswer = malloc(sizeof(char)*6);
			char * copyAllWords = malloc(sizeof(char)*6);
			strcpy(copyAnswer, answerList[j].word);
			strcpy(copyAllWords, wordle[i].word);
    	for(int k = 0; k < 5; k++){//loops through each character from the words
 		  	if(copyAnswer[k] == copyAllWords[k]){
					copyAllWords[k] = '_';
					wordle[i].score += 3;
					copyAnswer[k] = '-';
				}
			}
			for(int k = 0; k < 5; k++){
				for(int l = 0; l < 5; l++){
					if(copyAnswer[l] == copyAllWords[k]){
				      copyAllWords[k] = '_';
							wordle[i].score += 1;
              copyAnswer[l] = '-';
						}
					}
				}
			free(copyAnswer);
			free(copyAllWords);//freeing the arrays solved a signal kill issue we were running into
		}
	}
	for(int i = 0; i < position; i++){//loops through all words to find max score
		if(max < wordle[i].score){
			max = wordle[i].score;
		}
	}
	for(int i = 0; i < position; i++){
		if(max == wordle[i].score){ //adds the word with the max score to a struct that contains top words
			for(int j = 0; j < 6; j++){
				topAnswers[bestAnswer].word[j] = wordle[i].word[j];
				topAnswers[bestAnswer].score = wordle[i].score;
			}
			bestAnswer++;
		}
	}
	return bestAnswer;//size of my array that will hold the top first words
}

//----------------------------------------------------------------------
//This function will print the best word(s)
void printBestWord(int max, int* bestAnswer,char answersFileName[81], char guessesFileName[81], int counter, int increment, Wordle* wordle, Wordle* topAnswers, int position){
	for(int i = 0; i < position; i++){//finds the max score
		if(max < wordle[i].score){
			max = wordle[i].score;
		}
	}
	printf("%s has %d words\n",answersFileName,increment);
	printf("%s has %d words\n\n", guessesFileName, counter - increment);
	printf("Words and scores for top first words:\n");
	for(int i = 0; i < position; i++){
		if(max == wordle[i].score){ //prints all words with the max score
			printf("%s %d\n", wordle[i].word, wordle[i].score);
		}
	}
}

// -------------------------------------------------------
// This function will find the best second word choice
void menuOption2(int position, int increment, Wordle* wordle2,Wordle* answerList, Wordle* topAnswers, int bestAnswer, char answersFileName[81], char guessesFileName[81], int counter){
	int max2 = 0;
  
	printf("%s has %d words\n",answersFileName,increment);
	printf("%s has %d words\n\n", guessesFileName, counter - increment);
	printf("Words and scores for top first words and second words:\n");
  
	for(int b = 0; b < bestAnswer; b++){//This loops through the best answers
	  for(int i = 0; i < position; i++){//this loops through all the words
		  for(int j = 0; j < increment; j++){ // this loops through the answer words
				char * copyAnswer = malloc(sizeof(char)*6);
				char * copyAllWords = malloc(sizeof(char)*6);
				strcpy(copyAnswer, answerList[j].word);
				strcpy(copyAllWords, wordle2[i].word);
				answerSpace(topAnswers[b].word,copyAnswer);//adds spaces to the copy of the answer string
				for(int k = 0; k < 5; k++){
					if(copyAnswer[k] == copyAllWords[k]){
						copyAllWords[k] = '_';
						wordle2[i].score += 3;
						copyAnswer[k] = '-';
					}	
				}
  			for(int k = 0; k < 5; k++){
				 	for(int l = 0; l < 5; l++){
						if(copyAnswer[l] == copyAllWords[k]){
							copyAllWords[k] = '_';
							wordle2[i].score += 1;
							copyAnswer[l] = '-';
						}
					}
				}
				free(copyAnswer);
				free(copyAllWords);
			}
		}
		max2 = 0;
	  for(int i = 0; i < position; i++){
			if(max2 < wordle2[i].score){
				max2 = wordle2[i].score;
			}
		}
		printf("%s %d\n",topAnswers[b].word, topAnswers[b].score);
	  for(int i = 0; i < position; i++){
			if(max2 == wordle2[i].score){
				printf("\t%s %d", wordle2[i].word, wordle2[i].score);
		  }
			wordle2[i].score = 0;
		}
		printf("\n");
	}
}// end of function

//----------------------------------------------------
//This run function reads through the files and also calls menuOption 1 and menuOption2
void run(char answersFileName[81],char guessesFileName[81],Wordle wordles,Wordle wordles2,Wordle answers,	int check,int max,int max2,	int numberOfGuesses,int bestAnswers,	int counter,	int position,	int increment,  int bestAnswer, char inputString[ 81],							char inputString2[81], FILE *inFilePtr,	FILE *inFilePtr2,int menuOption){
	while( fscanf( inFilePtr, "%s", inputString)!= EOF) {
		counter++;
	}//looping through file to grab its size
	Wordle* answerList = malloc(sizeof(Wordle) * counter);
	Wordle* topAnswers = malloc(sizeof(Wordle) * 15);
  while( fscanf( inFilePtr2, "%s", inputString2)!= EOF) {
		counter++;
	}
	Wordle* wordle = malloc(sizeof(Wordle) * counter);
	Wordle* wordle2 = malloc(sizeof(Wordle) * counter);

  fclose( inFilePtr);
	fclose(inFilePtr2);
	inFilePtr  = fopen(answersFileName, "r");
	inFilePtr2 = fopen(guessesFileName, "r");
	while( fscanf( inFilePtr, "%s", inputString)!= EOF) {//for answers
		strcpy(wordles.word, inputString);
		wordles.score = 0;
		wordle[position] = wordles;
		wordle2[position] = wordles;
		position++;
	}//looping through the file again in order to assign values to the struct array
	while( fscanf( inFilePtr2, "%s", inputString2)!= EOF) {//for answers
		strcpy(wordles.word, inputString2);
		wordles.score = 0;
		wordle[position] = wordles;
		wordle2[position] = wordles;
		position++;
	}
	fclose( inFilePtr);
	fclose(inFilePtr2);
	
	inFilePtr  = fopen(answersFileName, "r");
	while(fscanf(inFilePtr, "%s", inputString)!= EOF){
		strcpy(answers.word, inputString);
		answers.score = 0;
		answerList[increment] = answers;
		increment++;
  }//loop through the file a third time to populate my struct array that will hold the answer words
  
	fclose(inFilePtr);
	if(menuOption == 1){
		menuOption1(position, increment, wordle, answerList, topAnswers, bestAnswer);
		printBestWord(max, bestAnswer,answersFileName, guessesFileName, counter, increment, wordle, topAnswers, position);
	}
	else if(menuOption == 2){
		int bestAnswers = menuOption1(position,increment,wordle,answerList,topAnswers, bestAnswer);
		menuOption2(position, increment, wordle2,answerList,topAnswers, bestAnswers,answersFileName,guessesFileName,counter);
	}
	printf("Done");
}//end of function

//------------------------------------------------------------------------------
//Main function
int main() {
	char answersFileName[81] = "answersTiny.txt";  // Stores the answers file name
	char guessesFileName[81] = "guessesTiny.txt";  // Stores the guesses file name
	Wordle wordles;//this is the struct;
	Wordle wordles2;
	Wordle answers;
	int check = 0;
	int max = 0;
	int max2 = 0;
	int numberOfGuesses = 0;
	int bestAnswers = 0;
	int counter = 0;
	int position = 0;
	int increment = 0;
  int bestAnswer = 0;
	
	printf("Default file names are %s and %s\n", answersFileName, guessesFileName);
    // Display menu, to allow partial credit for different program components
	int menuOption = 0;
	do {
		printf("\n");
		printf("Menu Options:\n");
		printf("  1. Display best first words only\n");
		printf("  2. Display best first and best second words\n");
		printf("  3. Change answers and guesses filenames\n");
		printf("  4. Exit\n");
		printf("Your choice: ");
		scanf("%d", &menuOption);
		if (menuOption == 4) {
				exit(1); // Exit the program
		} else if (menuOption == 3) {
				printf("Enter new answers and guesses filenames: ");
				scanf("%s %s", answersFileName, guessesFileName);
		}
	} while( menuOption == 3);
    // Sample code to read in from a file
	FILE *inFilePtr  = fopen(answersFileName, "r");
	FILE *inFilePtr2 = fopen(guessesFileName, "r");// Connect logical name to filename
	char inputString[ 81];
	char inputString2[81];

    // Sanity check: ensure file open worked correctly
	if( inFilePtr == NULL ) {
			printf("Error: could not open %s for reading\n", answersFileName);
			exit(-1);  
	}
	run(answersFileName,guessesFileName,wordles,wordles2,answers,check,max,max2,numberOfGuesses,bestAnswers,counter,position,increment, bestAnswer, inputString, inputString2,inFilePtr,inFilePtr2, menuOption);
  return 0;
} // end main()
