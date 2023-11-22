/**
 * Group ID - 
 * Member 1 Name - 
 * Member 1 BITS ID - 
 * Member 2 Name - 
 * Member 2 BITS ID - 
 * Member 3 Name - 
 * Member 3 BITS ID - 
*/

// ---------------------------DO NOT MODIFY (Begin)------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef struct Graph {
    int n; // Size of the graph
    int** adj; // Adjacency matrix
    char** station_names; // Array of station names
} Graph;

/**
 * This function has been pre-filled. It reads the input testcase 
 * and creates the Graph structure from it.
*/
Graph* create_graph(char input_file_path[]) {
    FILE* f = fopen(input_file_path, "r");
    Graph* g = (Graph*)malloc(sizeof(Graph));
    // Size of graph
    fscanf(f, "%d", &(g->n));
    // Names of stations
    g->station_names = (char**)malloc(g->n * sizeof(char*));
    for(int i = 0; i < g->n; i++) {
        g->station_names[i] = (char*)malloc(100 * sizeof(char));
        fscanf(f, "%s", g->station_names[i]);
    }
    // Adjacency matrix
    g->adj = (int**)malloc(g->n * sizeof(int*));
    for(int i = 0; i < g->n; i++) {
        g->adj[i] = calloc(g->n, sizeof(int));
    }
    int edges;
    fscanf(f, "%d", &edges);
    for(int i = 0; i < edges; i++) {
        int x, y;
        fscanf(f, "%d%d", &x, &y);
        g->adj[x][y] = 1;
        g->adj[y][x] = 1;
    }
    fclose(f);
    return g;
}
// ---------------------------DO NOT MODIFY (End)------------------------------



// ------- Helper Functions --------- //
int minDistance(int dist[], int visited[], int n) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

int dijkstra(Graph* g, int src, int dest) {
    int n = g->n;
    int* dist = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && g->adj[u][v] && dist[u] != INT_MAX &&
                dist[u] + g->adj[u][v] < dist[v]) {
                dist[v] = dist[u] + g->adj[u][v];
            }
        }
    }

    int distance = dist[dest];
    free(dist);
    free(visited);
    return distance;
}   



// ---------------------------------- // 

/**
 * Q.1 
 * Return the number of junctions.
*/
int find_junctions(Graph* g) {
    
}

/**
 * Q.2
 * Return true if the tour specified in the question is possible for this 
 * graph, else return false.
 * Parameter SAME_STATION - If it is true, then question 2(a) must be solved. 
 * If false, then question 2(b) must be solved.
*/
bool sheldons_tour(Graph* g, bool SAME_STATION) {
    
}

/**
 * Q.3
 * Return closure, an n * n matrix filled with 0s and 1s as required. 
*/
int** warshall(Graph* g) {
    // Do not modify or delete pre-filled code!
    int** closure = (int**)malloc(g->n * sizeof(int*));
    for(int i = 0; i < g->n; i++) {
        closure[i] = calloc(g->n, sizeof(int));
    }

    // Code goes here
    
    return closure; // Do not modify
}

/**
 * Q.3
 * Return the number of impossible pairs.
*/
int find_impossible_pairs(Graph* g) {
    int** closure = warshall(g); // Do not modify
    
}

/**
 * Q.4
 * Return the number of vital train tracks.
*/
int find_vital_train_tracks(Graph* g) {
    
}

/**
 * Q.5
 * Return upgrades, an array of size n.
 * upgrades[i] should be 0 if railway station i gets a restaurant
 * upgrades[i] should be 1 if railway station i gets a maintenance depot
 * If it is not possible to upgrade, then return "-1" in the entire array
*/
int* upgrade_railway_stations(Graph* g) {
    int* upgrades = calloc(g->n, sizeof(int)); // Do not modify
    
    // Code goes here

    return upgrades; // Do not modify
}

/**
 * Q.6
 * Return distance between X and Y
 * city_x is the index of X, city_y is the index of Y
*/
int distance(Graph* g, int city_x, int city_y) {
    // Ensure valid indices
    if (city_x < 0 || city_x >= g->n || city_y < 0 || city_y >= g->n) {
        return -1; // Invalid indices
    }

    // Applying Dijkstra's algorithm to find the minimum distance
    return dijkstra(g, city_x, city_y);
}

/**
 * Q.7
 * Return the index of any one possible railway capital in the network
*/
int railway_capital(Graph* g) {
    int n = g->n;
    int* distances = (int*)calloc(n, sizeof(int));

    // Calculate cumulative distances from each city to all other cities
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                distances[i] += dijkstra(g, i, j);
            }
        }
    }

    int min_sum = INT_MAX;
    int capital_index = -1;

    // Find the city with the minimum sum of distances
    for (int i = 0; i < n; i++) {
        if (distances[i] < min_sum) {
            min_sum = distances[i];
            capital_index = i;
        }
    }

    free(distances);

    return capital_index;
}

/**
 * Helper function for Q.8
*/
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

/**
 * Q.8 
 * Return true if it is possible to have a Maharaja Express tour 
 * starting from source city, else return false. 
*/
bool maharaja_express(Graph* g, int source) {
    int* visited = (int*)calloc(g->n, sizeof(int));
    visited[source] = 1; // Mark source city as visited
    bool result = maharaja_express_tour(g, source, source, visited, 1);
    free(visited);
    return result;
}

int main() {
    char input_file_path[100] = "testcase_1.txt"; // Can be modified
    Graph* g = create_graph(input_file_path); // Do not modify
    //Q6. Driver Code
    // int result = distance(g, 4, 0);
    //     if (result == -1) {
    //         printf("No path exists between the cities.\n");
    //     } else {
    //         printf("The distance between City X and City Y is: %d\n", result);
    //     } 


    //Q7. Driver Code
    // int capital = railway_capital(g);
    // if (capital != -1) {
    //     printf("The railway capital is at index: %d\n", capital);
    // } else {
    //     printf("No railway capital found.\n");
    // }


    //Q8. Driver Code
    int source_city = 0; // Replace with the index of the source city
    bool possible = 0;
     for (int i = 0; i < 6; i++) {
        source_city = i;
        possible = maharaja_express(g, source_city);
        printf("%d is the answer for station: %d\n", possible, i);
        if (possible) {
            printf("A Maharaja Express tour is possible starting from city %d.\n", source_city);
        } else {
            printf("No Maharaja Express tour is possible starting from city %d.\n", source_city);
        }
    }
    // bool possible = maharaja_express(g, source_city);
    
    return 0;
}