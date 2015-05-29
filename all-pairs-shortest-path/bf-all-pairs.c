// TODO: Implement Floyd-Warshall

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h"

#define MAX 1000;

// prints an array, mostly for debugging purposes
void print_arr(int *arr, int size)
{
   int i=0;
   printf("[");
   for (i; i<size; i++) {
      printf("%d,", arr[i]);
   }

   printf("]\n");
}

// get the minimum value of an array
int array_min(int *arr, int size)
{
   int min = arr[0];
   int i;
   for (i=1; i <= size; i++) {
      if (arr[i] < min) min = arr[i];
   }

   return min;
}

// bellman-ford implementation
int *bellman_ford(Graph g, int source)
{
   int size = g->V;
   int *dist = malloc(sizeof(int) * size);

   // initialize our distance array
   int i;
   for (i = 0; i < size; i++) {
      dist[i] = MAX;
   }
   dist[source] = 0;

   i = 1;

   for (i; i < size; i++) {
      int u = 1;

      for (u; u < size; u++) {
         int j=0;

         for (j; j < g->paths[u]->d; j++) {
            int v = g->paths[u]->dest[j];
            int w = g->paths[u]->weight[j];

            if ( dist[u] + w < dist[v] ) {
               dist[v] = dist[u] + w;
            }
         }
      }
   }

   return dist;
}

// dumb way to determine the shortest path between all pairs of vertices:
// uses repeated iterations of bellman-ford rather than floyd-warshall
int all_pairs(Graph g)
{
   int size = g->V;
   int min = array_min(bellman_ford(g,1), size);

   int i;
   for (i=2; i <= size; i++) {
      int candidate = array_min(bellman_ford(g,i), size);
      if (candidate < min) min = candidate;
   }

   return min;
}

int main(int argc, char *argv[])
{
   FILE *gf;

   // open the file, return -1 if there's some error
   if ( (gf = fopen("g1.txt", "r")) == NULL ) {
      printf("Error reading file");
      return -1;
   }

   Graph g = graph_from_file(gf);

   printf("%d\n", all_pairs(g));

   return 0;
}
