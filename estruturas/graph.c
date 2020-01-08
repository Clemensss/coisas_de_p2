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
void add_node(node *curr, int item);
void push_list(node **head, int item);
void print_list(node *head);

node* dequeue(node **head);
int is_empty(node *queue);
void enqueue(node **head, int item);
void bfs(graph *grafo, int start);

void push(node **head, int item);
node* pop(node **head);
void dfs(graph *grafo, int start);

graph* make_graph();
void add_edge(graph *grafo, int vert1, int vert2);
void create_graph(graph *grafo);
void print_graph(graph *grafo);
void print_visited(graph *grafo);

int main()
{

	graph *grafo = make_graph();
	create_graph(grafo);
	print_graph(grafo);

	dfs(grafo, 0);
	printf("\n");


    return 0;
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

void create_graph(graph *grafo)
{
	int vert1, vert2;
	while(scanf("%d%d", &vert1, &vert2) != EOF)
	{
		add_edge(grafo, vert1, vert2);
	}
}

void print_graph(graph *grafo)
{
	int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		if(grafo->adjlist[i] != NULL )print_list(grafo->adjlist[i]);
	}
}

void print_visited(graph *grafo)
{
	int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		printf("%d %d\n", i, grafo->visited[i]);
	}
}

void bfs(graph *grafo, int start)
{	
	node *queue = make_list();
	grafo->visited[start] = 1;
	enqueue(&queue, start);

	while(!is_empty(queue))
	{
		node *temp = grafo->adjlist[(dequeue(&queue))->item];

		while(temp != NULL)
		{
			int current = temp->item;
			
			if(!grafo->visited[current]) 
			{
				enqueue(&queue, current);
				grafo->visited[current] = 1;
				printf("%d ", current);
			}

			temp = temp->next;
		}
	}
	printf("\n");
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

