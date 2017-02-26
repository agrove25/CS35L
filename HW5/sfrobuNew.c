#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int optf = 0;

int frobcmp(const char* a, const char* b) {
  // loops through c string a and b, comparing each character to each other
  
  for (;; a++, b++) {
    char x = *a;
    char y = *b;
    
    if (optf == 1) {
      if (x < UCHAR_MAX && x > 0)
	x = toupper(x);
      if (y < UCHAR_MAX && y > 0)
	y = toupper(y);
    }
    
    if (x == ' ' && y == ' ') return 0;
    else if (x == ' ' || (x^42) < (y^42)) return -1;
    else if (y == ' ' || (x^42) > (y^42)) return 1;
  } 
}  

int cmp(const void *one, const void *two) {
  // passes the correct data structures into frobcmp (from void* to char*)
  
  const char* a = *(const char**)one;
  const char* b = *(const char**)two;
  return frobcmp(a, b); 
}

int main(int argc, char* argv[]) {
  // setting optional arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp("-f", argv[i]) == 0)
      optf = 1;
    else {
      fprintf(stderr, "invalid option/n");
      exit(1);
    }
  }


  struct stat fileStat;
  if (fstat(0, &fileStat) < 0) {
    fprintf(stderr, "fstat error");
    exit(1);
  }

  char* rawInput;
  int wordCount = 0;
  char** words;
  
  if(S_ISREG(fileStat.st_mode)) {
    rawInput = (char*)malloc((fileStat.st_size+1) * sizeof(char));
    ssize_t state = read(0, rawInput, fileStat.st_size);
    // fprintf (stderr, "%s",  rawInput);
    
    if (state > 0) {
      for (size_t i = 0; i < fileStat.st_size; i++) {
	// counts number of words based on spaces
	if (rawInput[i] == ' ') {
	  while (rawInput[i] == ' ') i++;
	  wordCount++;
	}
      }

      // adds a space to the end of the rawInput string
      rawInput[fileStat.st_size] = ' ';
      if (rawInput[fileStat.st_size -1] != ' ') {
	wordCount++;
      }
    }
    else {
      fprintf(stderr, "state <= 0");
      exit(1);
    }

    words = (char**)malloc(wordCount*sizeof(char*));
    
    int count = 0;
    words[count] = &rawInput[0];
    for (size_t i = 0; i < fileStat.st_size; i++) {
      
      if (rawInput[i] == ' ') {
	  while (rawInput[i] == ' ') i++;
	  count++;
	  if (i != fileStat.st_size-1) words[count] = &rawInput[i];
      }
    }

    
  }
  else {
    words = (char**)malloc(sizeof(char*));
    long int letterCounter = 0;
    long int wordCounter = 0;
    ssize_t state = 1;
    words[wordCounter] = (char*)malloc(sizeof(char));
    
    for (long int i = 0; state > 0; i++) {
      char buffer[1];
      state = read(0, buffer, 1);
      if (state <= 0) break;
      words[wordCounter][letterCounter] = buffer[0];
      letterCounter++;

      // seperates words based upon spaces
      if (words[wordCounter][letterCounter-1] == ' ') {
	letterCounter = 0;
	wordCounter++;

	int dump[1];
	
	do {
	  state = read(0, dump, 1);
	} while (dump[0] == ' ' && state != 0);

	words = realloc(words, (wordCounter+1)*sizeof(char*));
	words[wordCounter] = (char*)malloc(sizeof(char));
	words[wordCounter][letterCounter] = dump[0];
	letterCounter++;
	dump[0] = ' ';
      }

      
      words[wordCounter] = realloc(words[wordCounter], (letterCounter+1)*sizeof(char));
    }

    // adds a space to the last word
    words[wordCounter][letterCounter] = ' ';
    wordCounter++;
    wordCount = wordCounter;
  }

  qsort(words, wordCount, sizeof(char*), cmp);
  
  // printing the output
  for (size_t i = 0; i < wordCount; i++) {
    long wordSize = 0;

    for (size_t j = 0;; j++) {
      wordSize++;
      if (words[i][j] == ' ') break;
    }
    
    if (wordSize > 1) write(1, words[i], wordSize);
  }
  
  free(words);
}
