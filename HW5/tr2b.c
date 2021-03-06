#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]) {
  char* from = argv[1];
  char* to = argv[2];

  //error checking for different sizes
  if (strlen(from) != strlen(to)) {
    fprintf(stderr, "arg1 and arg2 must be the same size");
    exit(1);
  }

  //error checking for duplicate chars
  for (int i = 0; i < strlen(from); i++)
    for (int j = i+1; j < strlen(from); j++)
      if (from[i] == from[j]) {
	fprintf(stderr, "arg1 must not have duplicate chars");
	exit(1);
      }

  int current = getchar();
  int i;
  
  while (current != EOF) {
    for (i = 0; i < strlen(from); i++)
      if (current == from[i]) {
	putchar(to[i]);
	break;
      }
    
    if (i == strlen(from)) putchar(current);
    current = getchar();
  }

  return 0;
}
