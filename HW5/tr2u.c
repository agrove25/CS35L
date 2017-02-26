#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

  char current[1];
  ssize_t state = read(0, current, 1);
  int i;
  
  while (state > 0) {
    for (i = 0; i < strlen(from); i++)
      if (*current == from[i]) {
	write(1,to+i,1);
	break;
      }
    
    if (i == strlen(from)) write(1, current, 1);
    state = read(0, current, 1);
  }

  return 0;
}
