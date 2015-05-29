#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int table[101][100001];

typedef struct tuple {
   int val;
   int weight;
} tuple;

int max(int a, int b) {
   if (a > b) {
      return a;
   } else {
      return b;
   }
}

void knapsack(tuple items[], int total, int size) {

   int i = 1;
   int current_weight;
   int current_val;
   int j;

   for (i; i <= total; i++) {
      current_val = items[i-1].val;
      current_weight = items[i-1].weight;

      j = 0;
      for (j; j <= size; j++) {

         if (current_weight > j) {
            table[i][j] = table[i-1][j];
         } else {
            table[i][j] = max( table[i-1][j], table[i-1][j-current_weight] + current_val );

         }
      }
   }
}

int main(int argc, char *argv[]) {
   FILE *gf;
   char line[20];

   // open the file, return -1 if there's some error
   if ( (gf = fopen("knapsack1.txt", "r")) == NULL ) {
      printf("Error reading file");
      return -1;
   }

   // create an array of (val, weight) tuples
   tuple items[100];

   // get the total size of yr knapsack and total # of items
   char s[2] = " ";
   char *first = fgets(line,20,gf);
   int size = atoi(strtok(first,s));
   int total = atoi(strtok(NULL,s));

   // populate the array of tuples
   int i=0;
   while ( fgets(line, 20, gf) != NULL ) {
      char *temp = line;
      items[i].val     = atoi(strtok(temp,s));
      items[i].weight  = atoi(strtok(NULL,s));
      i++;
   }

   // run the knapsack algorithm on our data
   knapsack(items, total, size);

   printf("Final answer: %d\n", table[total][size]);
   return 0;
}
