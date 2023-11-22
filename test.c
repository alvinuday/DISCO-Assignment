#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Graph {
    int n; // Size of the graph
    int** adj; // Adjacency matrix
    char** station_names; // Array of station names
} Graph;

Graph* create_graph(int n, int m, int edges[][2]) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = n;
    g->adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->adj[i] = (int*)calloc(n, sizeof(int));
    }
    for (int i = 0; i < m; i++) {
        g->adj[edges[i][0]][edges[i][1]] = 1;
        g->adj[edges[i][1]][edges[i][0]] = 1;
    }
    return g;
}

bool maharaja_express_tour(Graph* g, int source, int current_city, int* visited, int count) {
    count++;

    if (count == g->n && g->adj[current_city][source]) {
        return true;
    }

    for (int next_city = 0; next_city < g->n; next_city++) {
        // Check if there is a path from current city to next city and it's not the previous city
        if (!visited[next_city] && g->adj[current_city][next_city]) {
            visited[next_city] = 1; // Mark next city as visited
            if (maharaja_express_tour(g, source, next_city, visited, count)) {
                return true;
            }
            visited[next_city] = 0; // Backtrack if no valid tour found
        }
    }

    return false;
}

bool maharaja_express(Graph* g, int source) {
    int* visited = (int*)calloc(g->n, sizeof(int));
    visited[source] = 1; // Mark source city as visited
    bool result = maharaja_express_tour(g, source, source, visited, 1);
    free(visited);
    return result;
}

int main() {
    int n = 6;
    int m = 6;
    int edges[6][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 4}, {4, 5}};
    Graph* g = create_graph(n, m, edges);

    for (int i = 0; i < n; i++) {
        bool possible = maharaja_express(g, i);
        printf("%d is the answer for station: %d\n", possible, i);
        if (possible) {
            printf("A Maharaja Express tour is possible starting from city %d.\n", i);
        } else {
            printf("No Maharaja Express tour is possible starting from city %d.\n", i);
        }
    }

    return 0;
}
