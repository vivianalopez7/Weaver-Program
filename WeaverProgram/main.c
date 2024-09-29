#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define true 1 // Make true a synonym for 1



	// printf("Your word, 'sonf', is not a valid dictionary word. Try again.\n");
	// printf("Your starting word is: song.\n");
	// printf("Your ending word is: sink.\n");

	// printf("Your word, 'sinks', is not a 4-letter word. Try again.\n");
	// printf("Your word, 'sint', is not a valid dictionary word. Try again.\n");


	// printf("Congratulations! You changed 'song' into 'sink' in 3 moves.\n");

	// printf("\nEnter: \t1 to play again,\n");
 //    printf("\t2 to change the number of letters in the words and then play again, or\n");
 //    printf("\t3 to exit the program.\n");
 //    printf("Your choice --> ");



//This function displays a welcome message at the beginning of the program.
  //Input: none
  //Output: displays the welcome message
  void displayMessage() {
    printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
	printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
	printf("Enjoy!\n\n");
  }

int wordDifferent (char previousWord[], char newWord[], int wordSize){

  int diffLetterCount = 0;

  for (int i = 0; i < wordSize; i++){
    if (previousWord[i] != newWord[i]){
      diffLetterCount++;
    }
  }
  if (diffLetterCount == 1){
    return 1; //exactly one letter difference
  }
  else {
    printf("Your word, '%s', is not exactly 1 character different. Try again.\n", newWord);
    return 0;
  }

}

int validDictWord (char startWord[], char endWord[], char **dictionary, int counter){
  int startWordFound = 0;
  int endWordFound = 0;

  for (int i = 0; i < counter; i++){
    if (strcmp(dictionary[i], startWord) == 0){
      startWordFound = 1;
    }
    else if(strcmp(dictionary[i], endWord) == 0){
      endWordFound = 1;
    }
  }
  if (startWordFound != 1){
   printf("Your word, '%s', is not a valid dictionary word. Try again.\n", startWord);
  return 0;
  }
  else if (endWordFound != 1){
    printf("Your word, '%s', is not a valid dictionary word. Try again.\n", endWord);
  return 0;
  }

  return 1; //word is valid

}

int wordCorrectSize (char startWord[], char endWord[], int wordSize){
    if (strlen(startWord) != wordSize){
      printf("Your word, '%s', is not a %d-letter word. Try again.\n", startWord, wordSize);
      return 0; // word is not the correct size
    }
  else if (strlen(endWord) != wordSize){
    printf("Your word, '%s', is not a %d-letter word. Try again.\n", endWord, wordSize);

    return 0; // word is not the correct size
  }
  else {
    return 1; // word is the correct size
  }
}

void selectRandomWord(char storedWord[], char** dictionary, int counter) {
  int randomNum = rand() % counter;
  strcpy(storedWord, dictionary[randomNum]); //destination, source
}


int menuOpOne (){

}

int main() {
	srand(1);
  displayMessage();

  int wordSize = 0;
  char startWord[100];
  char endWord[100];
  char newWord[100];

  printf("How many letters do you want to have in the words? ");
  scanf("%d", &wordSize);

	char filename[] = "words.txt";
	FILE *filePtr  = fopen(filename, "r"); // "r" means we open the file for reading

	// Check that the file was able to be opened
	if(filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

  int dictSize = 10;
  char **dictionary = malloc(sizeof(char*)* dictSize);

  char inputString[81];
  int counter = 0;

  for (int i = 0; i < dictSize; i++){
    dictionary[i] = (char *) malloc (sizeof(char) * (wordSize+1));
  }

	while(fscanf(filePtr, "%s", inputString) != EOF) {
    if (strlen(inputString) == wordSize){
      if (dictSize == counter){
        // Increase the size of dictionary
        char **temp = malloc(sizeof(char*) * (dictSize * 10));
        for (int i = 0; i < (dictSize*10); i++){
          temp[i] = (char *) malloc (sizeof(char) * (wordSize+1));
        }
        // copy every word from  dictiomary
        for (int i = 0; i < dictSize; i++){
          strcpy(temp[i], dictionary[i]);
        }
        dictionary = temp;
        dictSize=dictSize*10;
      }
        // Allocating memory for every single character in your single string
      strcpy(dictionary[counter], inputString);
      counter++;
    }
  }
    // Close the file
    fclose(filePtr);

    printf("Number of %d-letter words found: %d.\n\n", wordSize, counter);

    printf("Enter starting and ending words, or 'r' for either for a random word: ");

    scanf("%s ", startWord);
    scanf("%s", endWord);

    if (strlen(startWord) == 1 && startWord[0] == 'r'){
      selectRandomWord(startWord, dictionary, counter);

    }
    if (strlen(endWord) == 1 && endWord[0] == 'r'){
      selectRandomWord(endWord, dictionary, counter);
    }

  int correctWord = 0;

    while (correctWord != 1){
      if (wordCorrectSize(startWord, endWord, wordSize) == 1){
        if (validDictWord(startWord, endWord, dictionary, counter) == 0){
          correctWord = 0;
          printf("Enter starting and ending words, or 'r' for either for a random word: ");
          scanf("%s ", startWord);
          scanf("%s", endWord);
        }
        else {
          printf("Your starting word is: %s.\n", startWord);
      	  printf("Your ending word is: %s.\n", endWord);
          correctWord = 1;
        }
      }
      else{
        correctWord = 0;
        printf("Enter starting and ending words, or 'r' for either for a random word: ");
        scanf("%s ", startWord);
        scanf("%s", endWord);
      }
    }

  int moveNumber = 1;
  printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
    printf("You may also type in 'q' to quit guessing.\n");

  while (strcmp(newWord, "q") != 0 && strcmp(newWord, endWord) != 0){

    printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", moveNumber, startWord, endWord);
    scanf("%s", newWord);
    if (strcmp(newWord, "q") == 0){
      break;
    }
    if (strcmp(newWord, endWord) == 0){
      printf("Congratulations! You changed 'song' into 'sink' in %d moves.\n", moveNumber);
      break;
    }

  int correctNewWord = 0;
  while (correctNewWord != 1){
      if (wordCorrectSize(newWord, endWord, wordSize) == 1){
        if (validDictWord(newWord, endWord, dictionary, counter) == 1){
          if(wordDifferent(startWord, newWord, wordSize) == 1){
            correctNewWord = 1;
            moveNumber++;
            strcpy(startWord, newWord);
          }
          else {
            correctNewWord = 0;
      printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", moveNumber, startWord, endWord);
        scanf("%s", newWord);
            if (strcmp(newWord, "q") == 0){
              break;
            }
            if (strcmp(newWord, endWord) == 0){
printf("Congratulations! You changed 'song' into 'sink' in %d moves.\n", moveNumber);              break;
            }
          }
        }
        else {
          correctNewWord = 0;
      printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", moveNumber, startWord, endWord);
        scanf("%s", newWord);
          if (strcmp(newWord, "q") == 0){
            break;
          }
          if (strcmp(newWord, endWord) == 0){
printf("Congratulations! You changed 'song' into 'sink' in %d moves.\n", moveNumber);            break;
          }
        }
      }
    else {
      correctNewWord = 0;
      printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", moveNumber, startWord, endWord);
        scanf("%s", newWord);
      if (strcmp(newWord, "q") == 0){
        break;
      }
      if (strcmp(newWord, endWord) == 0){
printf("Congratulations! You changed 'song' into 'sink' in %d moves.\n", moveNumber);        break;
      }
    }
  }
}


	// // Read each word from file, and print them one by one
	// char inputString[ 81];
	// while(fscanf(filePtr, "%s", inputString) != EOF) {
	// 	printf("%s\n", inputString);
	// }



  // for (int i = 0; i < counter; i++) {
  //       free(dictionary[i]);
  //   }
  //   free(dictionary);


	return 0;
}