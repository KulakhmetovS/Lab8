#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40

using namespace std;

int** Creategraph(int **, int); //Создание графа
void BFS(int **, int *, int, int);  //Обход в ширину

int size;   //Размер графа


struct Queue
{
    int items[SIZE];
    int Front;
    int rear;
};

struct Queue* createQueue();
void enqueue(struct Queue* q, int);
int dequeue(struct Queue* q);
int isEmpty(struct Queue* q);

struct node
{
    int vertex;
    struct node* next;
};

struct node* createNode(int);

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int* visited;
};

struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
void bfs(struct Graph* graph, int startVertex);


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
    BFS(graph, visited, size, v);
    // <---------- ! ---------->
    printf("\n\n");


    struct Graph* Graph = createGraph(size);

    for(i = 0; i < size; i++)
    {
        for(j = i; j < size; j++)
        {
            if(graph[i][j] == 1)
            {
                addEdge(Graph, i, j);
            }
        }
    }

    printGraph(Graph);

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    bfs(Graph, v);
    // <---------- ! ---------->



    return 0;
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


//------------------------------------------------------


    void bfs(struct Graph* graph, int startVertex)
    {
        struct Queue* q = createQueue();

        graph->visited[startVertex] = 1;
        enqueue(q, startVertex);

        while(!isEmpty(q))
        {
            int currentVertex = dequeue(q);
            printf("%d ", currentVertex);

           struct node* temp = graph->adjLists[currentVertex];

           while(temp)
           {
                int adjVertex = temp->vertex;
                if(graph->visited[adjVertex] == 0)
                {
                    graph->visited[adjVertex] = 1;
                    enqueue(q, adjVertex);
                }
                temp = temp->next;
           }
        }
    }


    struct node* createNode(int v)
    {
        struct node* newNode = new struct node;
        newNode->vertex = v;
        newNode->next = NULL;
        return newNode;
    }

    struct Graph* createGraph(int vertices)
    {
        struct Graph* graph = new struct Graph;
        graph->numVertices = vertices;

        graph->adjLists = new struct node*[vertices];
        graph->visited = new int[vertices];


        int i;
        for (i = 0; i < vertices; i++)
        {
            graph->adjLists[i] = NULL;
            graph->visited[i] = 0;
        }

        return graph;
    }

    void addEdge(struct Graph* graph, int src, int dest)
    {
        // Add edge from src to dest
        struct node* newNode = createNode(dest);
        newNode->next = graph->adjLists[src];
        graph->adjLists[src] = newNode;

        // Add edge from dest to src
        newNode = createNode(src);
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
    }
    struct Queue* createQueue()
    {
        struct Queue* q = new struct Queue;
        q->Front = -1;
        q->rear = -1;
        return q;
    }
    int isEmpty(struct Queue* q)
    {
        if(q->rear == -1)
            return 1;
        else
            return 0;
    }
    void enqueue(struct Queue* q, int value)
    {
        if(q->rear == SIZE-1)
            printf("\nQueue is Full!!");
        else {
            if(q->Front == -1)
                q->Front = 0;
            q->rear++;
            q->items[q->rear] = value;
        }
    }
    int dequeue(struct Queue* q)
    {
        int item;
        if(isEmpty(q))
        {
            printf("Queue is empty");
            item = -1;
        }
        else{
            item = q->items[q->Front];
            q->Front++;
            if(q->Front > q->rear)
            {
                //printf("Resetting queue");
                q->Front = q->rear = -1;
            }
        }
        return item;
    }

    void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("%d:  ", v);
        while (temp)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
