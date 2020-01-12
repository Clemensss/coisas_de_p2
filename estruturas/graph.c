#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct Node
{
	int item;
	struct Node *next;

} node;

typedef struct Graph
{
	int edges;
	node* adjlist[MAX_SIZE];
	short visited[MAX_SIZE];

} graph;

node *make_list();

void thing(int arr[], int size);
void add_node(node *curr, int item);
void push_list(node **head, int item);
void print_list(node *head);

node* dequeue(node **head);
int is_empty(node *queue);
void enqueue(node **head, int item);
//void bfs(graph *grafo, int start);
void bfs(graph *grafo, int start, int dist[], int befo[], int o);
void push(node **head, int item);
node* pop(node **head);
void dfs(graph *grafo, int start);

graph* make_graph();
void add_edge(graph *grafo, int vert1, int vert2);
void create_graph(graph *grafo, int size);
void print_graph(graph *grafo);
void print_visited(graph *grafo);
void sort(graph *grafo, int size);

void bubble_sort_list(node *head);
int bubble_sort_iter(node *head);
int swap(node *one, node *two);

int main()
{
	int size, vert, t;
	scanf("%d%d%d", &vert, &size, &t);

	graph *grafo = make_graph();
	create_graph(grafo, size);

	sort(grafo, vert);

	for (int i = 0; i < t; i++)
	{
		int before[size];
		int dist[size];
		thing(dist, size);
		thing(before, size);
		int v, o;

		scanf("%d%d", &v, &o);
		printf("%d\n", v);
		bfs(grafo, v, dist, before, o);
		print_visited(grafo);

		for (int j = 0; j < vert; j++)
		{
			printf("%d |", j);
			dist[j] != -1? printf(" %d |", dist[j])
						: printf(" - |");
			before[j] != -1? printf(" %d\n", before[j])
						: printf(" -\n");

		}
		
	}
	
    return 0;
}

int swap(node *one, node *two)
{
    int temp = one->item;    
    one->item = two->item;
    two->item = temp;
}

void thing(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = -1;
	}
}

graph* make_graph()
{
	int i;
	graph *grafo = (graph*)malloc(sizeof(graph));
	for(i=0; i<MAX_SIZE; i++)
	{
		grafo->adjlist[i] = NULL; 
		grafo->visited[i] = 0;
	}
	
	return grafo;
}

void create_graph(graph *grafo, int size)
{
	int vert1, vert2;
	for(int i = 0; i <size; i++)
	{
		scanf("%d%d", &vert1, &vert2);
		add_edge(grafo, vert1, vert2);
	}
}

void print_graph(graph *grafo)
{
	int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		if(grafo->adjlist[i] != NULL )	
		{
			printf("%d ", i);
			print_list(grafo->adjlist[i]);
		}
	}
}

void print_visited(graph *grafo)
{
	int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		grafo->visited[i] = 0;
	}
}

void bfs(graph *grafo, int start, int dist[], int befo[], int o)
{	
	node *queue = make_list();

	int check = 0;

	grafo->visited[start] = 1;
	enqueue(&queue, start);
	dist[start] = 0;
	while(!is_empty(queue))
	{
		int index = (dequeue(&queue))->item;
		node *temp = grafo->adjlist[index];

		int path;
		if(temp) path = temp->item;
		int before; 
		before = index;
	    printf("Iniciando busca em largura a partir de %d\n", index);
		while(temp != NULL)
		{
			int current = temp->item;

			if(current == o)
			{
				printf("%d ", o);
				path = -1;
			}

			if(!grafo->visited[current]) 
			{
				enqueue(&queue, current);
				grafo->visited[current] = 1;
				befo[current] = before; 
				dist[current] = dist[index] + 1;

			}

			temp = temp->next;
		}
		if(path != -1)printf("%d ", path);
	}
}

void sort(graph *grafo, int size)
{
    int i;
    for(i=0; i<size; i++) 
    {
	bubble_sort_list(grafo->adjlist[i]);
    }
}

void bubble_sort_list(node *head)
{
	if(!is_empty(head))
		while(bubble_sort_iter(head));
}

int bubble_sort_iter(node *head)
{
	int sorted = 0;
	node* temp = head;
	while(temp->next != NULL)
	{
		if(temp->item > temp->next->item)
		{	
			swap(temp, temp->next);
			sorted++;
		}
		else temp = temp->next;
	}
	return sorted;
}

void dfs(graph *grafo, int start)
{
	if(!grafo->visited[start])
	{
		grafo->visited[start] = 1;
		printf("%d ", start);
	}
	node *temp = grafo->adjlist[start];

	while(temp != NULL)
	{
		if(!grafo->visited[temp->item])
		{
			dfs(grafo, temp->item);
		}
		temp = temp->next;
	}
}

void add_edge(graph *grafo, int vert1, int vert2)
{
	push_list(&grafo->adjlist[vert1], vert2);
}

void print_list(node *head)
{
	if(head != NULL)
	{
		node *temp = head;
		while(temp->next != NULL)
		{
			printf("%d ", temp->item);
			temp = temp->next;
		}
		printf("%d\n", temp->item);
	}
	else printf("nil\n");
}

node *make_list()
{
	return NULL;
}

int is_empty(node *queue)
{
	return (queue == NULL);
}

void push_list(node **head, int item)
{
	if(*head != NULL)
	{
		node *temp = *head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		add_node(temp, item);
	}
	else
	{
		*head = malloc(sizeof(node));
		(*head)->item = item;
		(*head)->next = NULL;
	}
}

void enqueue(node **head, int item)
{
	push_list(head, item);
}

void push(node **head, int item)
{
	node *new = malloc(sizeof(node));
	new->next = *head;	
	new->item = item;
	*head = new;
}

node* pop(node **head)
{
	return dequeue(head);
}

node* dequeue(node **head)
{
	node *dequeue = *head;	
	node *new = malloc(sizeof(node));
	*head = (*head)->next;	
	return dequeue;
}

void add_node(node *curr, int item)
{
	node *new = malloc(sizeof(node));

	new->item = item;
	new->next = curr->next;
	curr->next = new;
}

