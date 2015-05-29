#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct successors {
   int d;                 // number of successors
   int len;               // number of slots in array
   char is_sorted;        // is the list sorted?
   int dest[1000];        // list of dests
   int weight[1000];      // list of weights
};

struct graph {
   int V;                          // # of vertices
   int E;                          // # of edges
   struct successors *paths[1];    // the successor list
};

// type synonyms, cuz typing struct is a drag
typedef struct graph *Graph;
typedef struct successors Successors;

// Create a graph w/ n vertices and no edges
Graph create_graph(int n);

// Read a file of the form
//
//    #_Of_Nodes #_Of_Edges
//    <edge_1_src> <edge_1_dest> <edge_1_weight>
//    ...
//    <edge_n_src> <edge_n_dest> <edge_n_weight>
Graph graph_from_file(FILE *gf);

// free space used by a graph
void destroy_graph(Graph);

// add an edge to a graph
void graph_add_edge(Graph g, int source, int dest, int weight);


#endif
