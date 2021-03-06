#include <stdio.h>
#include <stdlib.h>

int frobcmp(const char* a, const char* b) {
  // loops through c string a and b, comparing each character to each other
  
  for (;; a++, b++) {
    if (*a == ' ' && *b == ' ') return 0;
    else if (*a == ' ' || (*a^42) < (*b^42)) return -1;
    else if (*b == ' ' || (*a^42) > (*b^42)) return 1;
  } 
}  

int cmp(const void *one, const void *two) {
  // passes the correct data structures into frobcmp (from void* to char*)
  
  const char* a = *(const char**)one;
  const char* b = *(const char**)two;
  return frobcmp(a, b); 
}

char** parseString(char delimiter, int *count) {
  // parses stdin by a given delimiter, returning the array
  // count is equal to the number of members within the returned array
  
  char* word = (char*)malloc(sizeof(char));
  char** wordArray = (char**)malloc(sizeof(char*));

  int wordIterator = 0;
  int wordArrayIterator = 0;

  int c = getchar();
  
  while (c != EOF) {
    if (c == delimiter) {
      // seperates the given words and entering them in different array indices
      wordIterator = 0;
     
      wordArray = realloc(wordArray, (wordArrayIterator+1)*sizeof(char*));

      if (wordArray == NULL) {
        fprintf(stderr, "Memory Allocation Error");
	exit(1);
      }
      
      wordArray[wordArrayIterator] = word;
      word = (char*)malloc(sizeof(char));
      
      wordArrayIterator++;

      while(c == delimiter) c = getchar();
      
      continue;
    }

    word = realloc(word, (wordIterator+1)*sizeof(char));

    if (word == NULL) {
      fprintf(stderr, "Memory Allocation Erorr");
      exit(1);
    }
    
    word[wordIterator] = c;
    
    wordIterator++;

    c = getchar();
  }
  
  if (word != NULL){
    // enters in the last word into the array
    wordArray = realloc(wordArray, (wordArrayIterator+1)*sizeof(char*));

    if (wordArray == NULL) {
      fprintf(stderr, "Memory Allocation Erorr");
      exit(1);
    }
    
    wordArray[wordArrayIterator] = word;
    wordArrayIterator++;
  }
  
  *count = wordArrayIterator;
  return wordArray;
}

int main (void)
{
  int wordArrayCount;
  char** wordArray = parseString(' ', &wordArrayCount);
  
  int i;
  
  qsort(wordArray, wordArrayCount, sizeof(char*), cmp);
  
  for (i = 0; i < wordArrayCount; i++)
    printf("%s ", wordArray[i]);

  for (i = 0; i < wordArrayCount; i++)
    // memory deallocation
    free(wordArray[i]);
}
