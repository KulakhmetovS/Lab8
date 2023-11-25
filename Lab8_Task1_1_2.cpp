#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int** Creategraph(int **, int); //Создание графа
void DFS(int **, int *, int, int);  //Обход в глубину
void BFS(int **, int *, int, int);

int size;   //Размер графа


int main()
{
    int i, j, v, num;
    int **graph = NULL, *visited = NULL, *List = NULL;

    printf("\t# Graphs #\n\n");
    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);
    num = size - 1;

    // Creating the graph
    graph = Creategraph(graph, size);
    visited = (int *)(malloc(sizeof(int *) * size));  // Array for visited vertices
    List = (int *)(malloc(sizeof(int *) * size));

    // Printing the matrix
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    DFS(graph, visited, size, v);
    // <---------- ! ---------->
    printf("\n\n");

    for(i = 0; i < size; i++)
        visited[i] = 0;

    BFS(graph, visited, size, v);
    printf("\n\n");

    return 0;
}

void DFS(int **graph, int *visited, int size, int v)
{
    int i;
    visited[v] = 1;
    printf("%d ", v);

    for(i = 0; i < size; i++)
    {
        if((graph[v][i] == 1) && (visited[i] == 0)) DFS(graph, visited, size, i);
    }
}

void BFS(int **graph, int *visited, int size, int v)
{
    queue<int> q;
    q.push(v);
    visited[v] = 1;

    while(!q.empty())
    {
        v = q.front();
        printf("%d ", v);
        q.pop();

        for(int i = 0; i < size; i++)
        {
            if((graph[v][i] == 1) && (visited[i] != 1))
            {
                q.push(i);
                visited[i] = 1;
            }
        }
    }

}

int** Creategraph(int **graph, int size)
{
    srand(time(NULL));

    int i = 0, j = 0;

    // Memory allocation
    graph = (int **)(malloc(sizeof(int *) * size));
    for(i = 0; i < size; i++)
        graph[i] = (int *)(malloc(sizeof(int *) * size));

    // Filling the matrix
    for(i = 0; i < size; i++)
        for(j = i; j < size; j++)
        {
            graph[i][j] = rand() % 2;
            graph[j][i] = graph[i][j];
            if(i == j) graph[i][j] = 0;
            if(graph[i][j] == 1);
        }

    return graph;
}
