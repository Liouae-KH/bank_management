#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ramdom (min, max) number function:
int random_num(int max, int min) {
  int number = (rand() % (max - min + 1)) + min;
  return number;
}
//----------------------------------

int main() {
  srand(time(NULL));
  int pro;
  while (pro != 0) {
    printf("\n <> enter: \n   0 to exit the program.");
    printf("\n --> 1 to generate a random number from an interval.");
    // printf("\n --> 2 ");
    // printf("\n --> 3 ");
    // printf("\n --> 4 ");
    // printf("\n --> 5 ");
    // printf("\n --> 6 ");

    printf("\n");
    scanf("%d", &pro);
    switch (pro) {
      case 0:
        break;

      // to generate a random number from an interval:
      case 1:
        int max, min;
        printf("\n enter the maximum and the minimum: ");
        scanf("%d %d", &max, &min);
        printf("%d", random_num(max, min));
        break;
        //----------------------------------------------

      default:
        printf("\n '%d' invalid input", pro);
    }
  }
  return 0;
}
