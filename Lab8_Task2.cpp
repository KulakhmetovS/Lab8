#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int** Creategraph(int **, int); //Создание графа
void BFS(int **, int *, int, int);

int size;   //Размер графа


struct Queue;   // Структура, отвечающая за элементы очереди
struct Queue *init(int);    // Инициализация очереди
void Push(struct Queue **, int);    // Добавление элемента в очередь
struct Queue *Pop(struct Queue *);   // Чтение элемента из очереди с последующим удалением

int res = 0;    // Результат извлеения из очереди


void bfs(struct Queue*, int**, int*, int, int);


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

    unsigned int start_time = clock();
    BFS(graph, visited, size, v);   //Native queue
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << "\nruntime = " << search_time / 1000.0;
    printf("\n\n");

    struct Queue *list = NULL;

    for(i = 0; i < size; i++)
        visited[i] = 0;

    start_time = clock();
    bfs(list, graph, visited, size, v); //My queue
    end_time = clock();
    search_time = end_time - start_time;
    cout << "\nruntime = " << search_time / 1000.0;
    printf("\n\n");

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



struct Queue
{
    int data;   // Числовой элемент очереди
    struct Queue *next; // Указатель на следующий элемент очереди
};

struct Queue *init(int element)
{
    struct Queue *p = NULL; // Создание указателя на структуру

    if((p = new struct Queue) == NULL)  // Выделение памяти под структуру
    {
        printf("Unable to allocate memory: ");
        exit(1);
    }

    p -> data = element;    // Присваивание введённого значения полю данных
    p -> next = NULL;   // Установка на нулевой указатель

    return p;
}

void Push(struct Queue **list ,int element)
{
    struct Queue *tmp = *list;  // Сохранение оригинального указателя на голову

    if(tmp != NULL) // Проверка на существование списка
    {
    struct Queue *new_element = init(element);  // Создание нового элемента

    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }

    tmp -> next = new_element;
    }
    else if(tmp == NULL)    // Инициализация списка, если его нет
    {
        *list = init(element);
    }
}

struct Queue *Pop(struct Queue *list)
{
    res = list -> data; // Получение элемента очереди

    struct Queue *to_delete = list; // Переназначение указателя на первый элемент
    list = list -> next;    //Переназначение первого указателя на следующий
    free(to_delete);    // Очистка памяти по предыдущему указателю

    return list;    // Возвращение нового указателя на вершину очереди
}

void bfs(struct Queue* list, int **graph, int *visited, int size, int v)
{
    Push(&list, v);
    visited[v] = 1;

    while(list != NULL)
    {
        list = Pop(list);
        v = res;
        printf("%d ", v);

        for(int i = 0; i < size; i++)
        {
            if((graph[v][i] == 1) && (visited[i] != 1))
            {
                Push(&list, i);
                visited[i] = 1;
            }
        }
    }
}
