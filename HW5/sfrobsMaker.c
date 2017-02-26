#include <stdio.h>

int main() {
  for (int i = 0; i <= 255; i++) {
    long int dec = i^42;
   
    //scanf("%d",&dec);

    printf("\\%o",dec);

    
  }

}
