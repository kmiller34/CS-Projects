//  wordleGuessSecretWord.c
//  Have the program do the guessing to discover the secret wordle word.
//
//  Author: Dale Reed, 11/6/22
//  System: CLion and XCode
//
//  Links to wordle dictionary words at:
//    https://www.reddit.com/r/wordle/comments/s4tcw8/a_note_on_wordles_word_list/
/*  Running the program looks like:
        Using file wordsLarge.txt with 12947 words. 
        -----------------------------------------------------------
        
        Enter a secret word or just r to choose one at random: dream
        Trying to find secret word: 
               d r e a m 
        
            1. s o r e s 
                   * *   
            2. s e r e r 
                 * *     
            3. r a r e r 
               * *   *   
            4. r a r e e 
               * *   *   
            5. s a r e e 
                 * * *   
            6. p a r e r 
                 * * *   
            7. c a r e r 
                 * * *   
            8. b a r e r 
                 * * *   
            9. f a r e r 
                 * * *   
           10. D a r e r 
                 * * *   
           11. D e a r e 
                 * * *   
           12. D e b A r 
                 *     * 
           13. D R E A r 
                       * 
           14. D R E A d 
                         
           15. D R E A M 
                         
        Got it!

     ... and then it runs two more times ...
 */
#include <stdio.h>    // for printf(), scanf()
#include <stdlib.h>   // for exit( -1)
#include <string.h>   // for strcpy
#include <assert.h>   // for assert() sanity checks
#include <ctype.h>    // for toupper()
#include <time.h>     // for time()
#include <stdbool.h>

// Declare globals
#define WORD_LENGTH 5     // All words have 5 letters, + 1 NULL at the end when stored
//#define WORDS_FILE_NAME "wordsLarge.txt"
#define WORDS_FILE_NAME  "wordsLarge.txt"
#define MAX_NUMBER_OF_WORDS 12947   // Number of words in the full set of words file
#define true 1   // Make boolean logic easier to understand
#define false 0  // Make boolean logic easier to understand

typedef struct wordCount wordCountStruct;
struct wordCount{
    char word[ WORD_LENGTH + 1];   // The word length plus NULL
    int score;// Score for the word
		bool dupWord;
};


//-----------------------------------------------------------------------------------------
// Read in words from file into array.  We've previously read the data file once to
// find out how many words are in the file.
void readWordsFromFile(
            char fileName[],        // Filename we'll read from
            wordCountStruct *words, // Array of words where we'll store words we read from file
            int *wordCount)          // How many words.  Gets updated here and returned
{
    FILE *inFilePtr  = fopen(fileName, "r");  // Connect logical name to filename
    assert( inFilePtr != NULL);               // Ensure file open worked correctly

    // Read each word from file and store into array, initializing the score for that word to 0.
    char inputString[ 6];
    *wordCount = 0;
    while( fscanf( inFilePtr, "%s", inputString) != EOF) {
        strcpy( words[ *wordCount].word, inputString);
        words[ *wordCount].score = 0;
        (*wordCount)++;
    }

    // Close the file
    fclose( inFilePtr);
} // end readWordsFromFile(..)


//-----------------------------------------------------------------------------------------
// Comparator for use in built-in qsort(..) function.  Parameters are declared to be a
// generic type, so they will match with anything.
// This is a two-part comparison.  First the scores are compared.  If they are the same,
// then the words themselves are also compared, so that the results are in descending
// order by score, and within score they are in alphabetic order.
int compareFunction( const void * a, const void * b) {
    // Before using parameters we have cast them into the actual type they are in our program
    // and then extract the numerical value used in comparison
    int firstScore = ((wordCountStruct *) a)->score;
    int secondScore = ((wordCountStruct *) b)->score;

    // If scores are different, then that's all we need for our comparison.
    if (firstScore != secondScore) {
        // We reverse the values, so the result is in descending vs. the otherwise ascending order
        // return firstScore - secondScore;   // ascending order
        return secondScore - firstScore;      // descending order
    }
    else {
        // Scores are equal, so check words themselves, to put them in alphabetical order
        return strcmp( ((wordCountStruct *)a)->word,  ((wordCountStruct *)b)->word );
    }
} //end compareFunction(..)


// -----------------------------------------------------------------------------------------
// Find a secret word
void findSecretWord(
        wordCountStruct allWords[],    // Array of all the words
        int wordCount,                  // How many words there are in allWords
        char secretWord[])              // The word to be guessed
{
    char computerGuess[ 6];  // Allocate space for the computer guess
		char duplicateWord[50][6];
	char secretCopy[6];
		int randomIndex = rand() % wordCount;
		int letterFound = 0;
		char firstLetter = ' ';
		char secondLetter = ' ';
		char thirdLetter = ' ';
		char fourthLetter = ' ';
		char fifthLetter = ' ';
		char badLetters[10000];
		char goodLetters[10000];
		int index = 0;
		int index1 = 0;
		int dupIndex = 0;
    if( strlen( secretWord) <= 1) {
			// Randomly select a secret word to be guessed.
			
			strcpy( secretWord, allWords[ randomIndex].word);
		}
    printf("Trying to find secret word: \n");
    // Display secret word with a space between letters, to match the guess words below.
    printf("       ");
    for( int i=0; i<WORD_LENGTH; i++) {
        printf("%c ", secretWord[ i]);
    }
    printf("\n");
    printf("\n");
    
    // Loop until the word is found
    int guessNumber = 1;
		int counter = 0;
		int i = 0;
		int counter1 = 0;
		int counter2 = 0;
		int goodCounter = 0; 
		int checkDup = 0;

		for(int i = 0; i < wordCount; i++){
			allWords[i].dupWord = false;
		}
    while( true) {
        // Lots of code to go here ...
        // ...
			
			printf("%5d. ", guessNumber);
			while(true){
				//printf("hello");
				randomIndex = rand() % wordCount;
				strcpy(computerGuess, allWords[randomIndex].word);

				while(allWords[randomIndex].dupWord){
					randomIndex = rand() % wordCount;
					strcpy(computerGuess, allWords[randomIndex].word);
				}
        for(int i = 0; i < 5; i++){
					for(int j = 0; j < index; j++){
						if(computerGuess[i] == badLetters[j]){
							counter1++;
						}
					}
				}
				for(int i = 0; i < 5; i++){
					for(int j = 0; j < index1; j++){
						if(computerGuess[i] == goodLetters[j]){
							counter2++;
						}
					}
				}

				if(counter1 == 0){
					if (index1 != 0){
						if(counter2 == 0){
							continue;				
						}
						if (counter2 >= index1){
							// printf("\n\ncounter: %d\n\n", counter2);
							if(computerGuess[0] == firstLetter && computerGuess[1] == secondLetter && thirdLetter == computerGuess[2] 
								&& fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(computerGuess[0] == firstLetter && secondLetter == ' ' && thirdLetter == ' ' && fourthLetter == ' ' && fifthLetter == ' '){
								counter2 = 0;
								break;		
							}
							else if(computerGuess[0] == firstLetter && secondLetter == ' ' && thirdLetter == ' ' && fourthLetter == ' ' && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;		
							}
							else if(computerGuess[0] == firstLetter && secondLetter == ' ' && thirdLetter == ' ' && fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;		
							}
							else if(computerGuess[0] == firstLetter && secondLetter == ' ' && thirdLetter == ' ' && fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;		
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == ' ' && fourthLetter == ' ' && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == ' ' && fourthLetter == ' ' && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == ' ' 
								&& fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == ' ' 
								&& fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == ' '&& fourthLetter == ' ' && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == ' '&& fourthLetter == ' ' && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == ' '&& fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == ' '&& fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == computerGuess[2] && fourthLetter == ' ' && computerGuess[4]== fifthLetter){
								counter2 = 0;
								break;
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == computerGuess[2] && fourthLetter == ' ' && ' '== fifthLetter){
								counter2 = 0;
								break;
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == computerGuess[2] 
								&& fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(computerGuess[1] == secondLetter && firstLetter == ' ' && thirdLetter == computerGuess[2] 
								&& fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == computerGuess[0] && thirdLetter == computerGuess[2] && fourthLetter == ' ' && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == computerGuess[0] && thirdLetter == computerGuess[2] && fourthLetter == ' ' && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == computerGuess[0] && thirdLetter == computerGuess[2] 
								&& fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == computerGuess[0] && thirdLetter == computerGuess[2] 
								&& fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == computerGuess[2] && fourthLetter == ' ' && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == computerGuess[2] && fourthLetter == ' ' && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == computerGuess[2] 
								&& fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == ' ' && firstLetter == ' ' && thirdLetter == computerGuess[2] 
								&& fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == computerGuess[1] && firstLetter == computerGuess[0] && thirdLetter == ' ' && fourthLetter == ' ' && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == computerGuess[1] && firstLetter == computerGuess[0] && thirdLetter == ' ' && fourthLetter == ' ' && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(secondLetter == computerGuess[1] && firstLetter == computerGuess[0] && thirdLetter == ' ' 
								&& fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							else if(secondLetter == computerGuess[1] && firstLetter == computerGuess[0] && thirdLetter == ' ' 
								&& fourthLetter == computerGuess[3] && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;
							}
							else if(computerGuess[0] == firstLetter && secondLetter == computerGuess[1] && thirdLetter == computerGuess[2] && fourthLetter == ' ' && fifthLetter == ' '){
								counter2 = 0;
								break;		
							}
							else if(computerGuess[0] == firstLetter && secondLetter == computerGuess[1] && thirdLetter == computerGuess[2] && fourthLetter == ' ' && fifthLetter == computerGuess[4]){
								counter2 = 0;
								break;		
							}
							else if(computerGuess[0] == firstLetter && secondLetter == computerGuess[1] && thirdLetter == computerGuess[2] && fourthLetter == computerGuess[3] && fifthLetter == ' '){
								counter2 = 0;
								break;
							}
							
							else{
								counter2 = 0;
							}
						}
					}
					else{
						break;
					}
				}				
				
				counter1 = 0;
				counter2 = 0;
			}

			strcpy(duplicateWord[dupIndex], computerGuess);
			// printf("Word: %s\n",duplicateWord[dupIndex]);
			allWords[randomIndex].dupWord = true;
			dupIndex++;
			strcpy(secretCopy, secretWord);
				
				for(int i = 0; i < 5; i++){
					if(computerGuess[i] == secretWord[i]){
						// index1++;
						if(i == 0){
							firstLetter = secretWord[i];
							printf("%c ", toupper(computerGuess[i]));
							computerGuess[i] = '-';
							secretCopy[i] = '_';
						}
						if(i == 1){
							secondLetter = secretWord[i];
							printf("%c ", toupper(computerGuess[i]));
							computerGuess[i] = '-';
							secretCopy[i] = '_';
						}
						if(i == 2){
							thirdLetter = secretWord[2];
							printf("%c ", toupper(computerGuess[i]));
							computerGuess[i] = '-';
							secretCopy[i] = '_';
						}
						if(i == 3){
							fourthLetter = secretWord[3];
							printf("%c ", toupper(computerGuess[i]));
							computerGuess[i] = '-';
							secretCopy[i] = '_';
						}
						if(i == 4){
							fifthLetter = secretWord[4];
							printf("%c ", toupper(computerGuess[i]));
							computerGuess[i] = '-';
							secretCopy[i] = '_';
							
						}
						counter++;
					}
					else if(computerGuess[i] != secretWord[i]){
						printf("%c ", computerGuess[i]);
					}
					for(int j = 0; j < 5; j++){
						if(computerGuess[i] == secretWord[j]){
							for(int k = 0; k < index1; k++){
								if(goodLetters[k] == computerGuess[i]){
									goodCounter++;
								}
							}
							if(goodCounter == 0){
								goodLetters[index1] = computerGuess[i];
								index1++;
								// printf("\n\nIndex1: %d\n\n", index1);
							}
							goodCounter = 0;
							//goodLetters[index1] = computerGuess[i];
							// index1++;
								
							letterFound += 1;
							break;
						}
					}
					
					if(letterFound == 0){
						badLetters[index] = computerGuess[i];
						index++;
					}
					// if(letterFound != 0){
					// 	goodLetters[index1] = computerGuess[i];
					// 	index1++;
					// 	printf("\n%d\n", index1);
					// }
					letterFound = 0;
				}
			printf("\n");
			printf("       ");
			int spaceCount = 0;
			for(int i = 0; i < 5; i++){
				
				for(int j = 0; j < 5; j++){
					if(computerGuess[i] == secretCopy[j] && j != i && counter != 5){
						// printf("j: %d, i: %d", j,i);
						printf("* ");
						computerGuess[i] = '-';
						secretCopy[j] = '_';
						spaceCount++;
						break;
					}
					
					// break;
				}
				if(spaceCount == 0){
						printf("  ");
				}
				spaceCount = 0;
			}
			// printf("yo");
				// for(int i = 0; i < 5; i++){
				// 	printf("%c", computerGuess[i]);
				// }
				if(counter == 5){
					printf("\nGot it!\n");
					return;
				}
				counter = 0;
				printf("\n");
			
        // Update guess number
				
        guessNumber++;

			// for(int a = 0; a<index1; a++) {
			// 	printf("%c", goodLetters[a]);
			// }
			// printf("\n");
    } //end for( int i...)
} //end findSecretWord


// -----------------------------------------------------------------------------------------
int main() {
    char wordsFileName[81];                   // Stores the answers file name
    strcpy(wordsFileName, WORDS_FILE_NAME);   // Set the filename, defined at top of program.
    srand( (unsigned) time( NULL));           // Seed the random number generator to be current time
    // Declare space for all the words, of a maximum known size.
    wordCountStruct allWords[ MAX_NUMBER_OF_WORDS];
    // Start out the wordCount to be the full number of words.  This will decrease as
    //    play progresses each time through the game.
    int wordCount = 0;
    // The secret word that the computer will try to find, plus the return character from fgets.
    char secretWord[ WORD_LENGTH + 1];
    char userInput[ 81];                // Used for menu input of secret word

    // Read in words from file, update wordCount and display information
    readWordsFromFile( wordsFileName, allWords, &wordCount);
    printf("Using file %s with %d words. \n", wordsFileName, wordCount);

    // Run the word-guessing game three times
    for( int i=0; i<3; i++) {
        // Reset secret Word
        strcpy( secretWord, "");
        // Display prompt
        printf("-----------------------------------------------------------\n");
        printf("\n");
        printf("Enter a secret word or just r to choose one at random: ");
        scanf(" %s", userInput);
        // Eliminate the return character at end or userInput if it is there
			
        int length = (int) strlen( userInput);
        if( userInput[ length] == '\n') {
            userInput[ length] = '\0';
        }
        strcpy( secretWord, userInput);   // Store the secret word from user input
                
        // If input was 'r' then choose a word at random.
        
        
        // Run the game once with the current secret word
        findSecretWord( allWords, wordCount, secretWord);
    }

    printf("Done\n");
    printf("\n");
    return 0;
} // end main()