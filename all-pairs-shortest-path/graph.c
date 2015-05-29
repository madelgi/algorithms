#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h"

Graph create_graph(int n)
{
   Graph g;
   int i;

   g = malloc(sizeof(struct graph) + sizeof(Successors *) * n);
   assert(g);

   g->V = n;
   g->E = 0;

   for (i = 0; i < n; i++) {
      g->paths[i] = malloc(sizeof(Successors));
      assert(g->paths[i]);

      // for each i, no interesting edge stuf is added
      g->paths[i]->d = 0;
      g->paths[i]->len = 1;
      g->paths[i]->is_sorted = 1;

   }

   return g;
}

Graph graph_from_file(FILE *gf)
{
   char line[20];
   char s[2] = " ";

   char *first = fgets(line,20,gf);
   int size = atoi(strtok(first,s));
   int edges = atoi(strtok(NULL,s));

   int src, dest, weight;
   char *temp;

   Graph g = create_graph(size+1);

   // add edges in loop
   while ( fgets(line, 20, gf) != NULL ) {
      temp = line;
      src = atoi(strtok(temp,s));
      dest = atoi(strtok(NULL,s));
      weight = atoi(strtok(NULL,s));

      graph_add_edge(g, src, dest, weight);
   }

   return g;
}


void destroy_graph(Graph g)
{
   int i;

   for(i = 0; i < g->V; i++) free(g->paths[i]);
   free(g);
}

void graph_add_edge(Graph g, int u, int v, int w)
{
   // Check that our inputs make sense
   assert(u >= 0);
   assert(u < g->V);
   assert(v >= 0);
   assert(v < g->V);

   while (g->paths[u]->d >= g->paths[u]->len) {
      g->paths[u]->len *= 2;
      g->paths[u] =
         realloc(g->paths[u],
               sizeof(Successors) + sizeof(int)*2*(g->paths[u]->len - 1));
   }

   int index = g->paths[u]->d++;

   // Add the edge to the correct list
   g->paths[u]->dest[index]   = v;
   g->paths[u]->weight[index] = w;
   g->paths[u]->is_sorted = 0;

   g->E++;
}
