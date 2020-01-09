#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define HASH_MAX 100

typedef struct _deque deque_t;
typedef struct _node   node_t;
typedef struct _hash   hash_t;

//Guarda um ponteiro pro node anterior, para o proximo node e o valor guardado
struct _node {
	node_t *prev;
  	node_t *next;
  	int    value;
};

//Guarda um ponteiro para o primeiro node, um ponteiro para o ultimo node, e o tamanho do deque
struct _deque {
  	node_t *front;
  	node_t  *rear;
  	int      size;
};

struct _hash
{
	deque_t *arr[HASH_MAX];
	int size;
};

//Cria um node que guarda os valores que s?o enfileirados no deque
node_t*  node_new     (int value);

//Cria um deque dinamicamente e retorna seu endere?o de memoria
deque_t* construct    ();

//Libera a mem?ria do conte?do e do pr?prio deque
void     destruct     (deque_t *deque);

//Retorna o tamanho do deque
int      size         (deque_t *deque);
//Retorna verdadeiro se o deque esta vazio, caso contr?rio, retorna falso
bool     empty        (deque_t *deque);

//Retorna o valor da frente da lista, retorna int_min quando a lista estiver vazia
int      front        (deque_t *deque);
//Retorna o valor do fim da lista, retorna int_min quando a lista estiver vazia
int      rear         (deque_t *deque);

//Cria um n? que guarda um valor e o adiciona ao fim do deque
void     enqueue_rear (deque_t *deque, int value);
//Cria um n? que guarda um valor e o adiciona ao inicio do deque
void     enqueue_front(deque_t *deque, int value);
//Retira o valor do final caso n?o esteja vazia
void     dequeue_rear (deque_t *deque);
//Retira o valor da frente caso n?o esteja vazia
void     dequeue_front(deque_t *deque);
//Limpa o conteudo do deque(deixa ele vazio)
void     erase        (deque_t *deque);

//Imprime o deque em uma unica linha, com os elementos separados por um espa?o,
//terminando com um \n, lembrando de respeitar os conceitos de fila.
void     print        (deque_t *deque);
int dispercao(int x, int size);
void print_hash(hash_t *table);
void add_hash(hash_t *table, int value);
void init_hash(hash_t *table);

int main() 
{
	int i, j;
	int coisa, thing;
	scanf("%d\n", &coisa);
	for(i=0; i < coisa; i++)
	{
		int size;
		scanf("%d %d\n", &size, &thing);

		hash_t *table;
		table->size = size;
		init_hash(table);
		for(j=0; j < thing; j++)
		{
			int num;
			scanf("%d", &num);
			add_hash(table, num);

		}

		print_hash(table);
		printf("\n");
	}
	return 0;
}

void print_hash(hash_t *table)
{
	int i;
	for(i=0; i < table->size; i++)
	{
		printf("%d -> ", i);
		print(table->arr[i]);
	}
}

void init_hash(hash_t *table)
{
	int i;
	for(i=0; i < table->size; i++)
	{
		table->arr[i] = construct();
	}
}

void add_hash(hash_t *table, int value)
{
	int index = dispercao(value, table->size);
	enqueue_rear(table->arr[index], value);
}

int dispercao(int x, int size)
{
	return x % size;
}

void erase(deque_t *deque)
{
	deque->front = NULL;	
	deque->rear = NULL;	
	deque->size = 0;
}

void print(deque_t *deque)
{
	node_t *temp = deque->front;

	while(temp != NULL)
	{
		printf("%d -> ", temp->value);
		temp = temp->next;
	}
	char c = 92;
	printf("%c", c);
	printf("\n");
}

void dequeue_front(deque_t *deque)
{
	if(!empty(deque))
	{
		node_t *temp = deque->front->next;
		if(temp != NULL)
		{
			temp->prev = NULL;
		}
		else
		{
			deque->rear = temp;		
		}

		deque->front = temp;
		deque->size--;
	}
}

void dequeue_rear(deque_t *deque)
{
	if(!empty(deque))
	{
		node_t *temp = deque->rear->prev;
		
		if(temp != NULL)
		{
			temp->next = NULL;
		}
		else
		{
			deque->front = temp;
		}

		deque->rear = temp;
		deque->size--;
	}
}

void enqueue_front(deque_t *deque, int value)
{
	node_t *new = node_new(value);
	node_t *temp = deque->front;
	node_t *rear = deque->rear;

	if(temp != NULL)
	{
		new->next = temp;
		temp->prev = new;
	}

	if(rear == NULL)
	{
		deque->rear = new;
	}
	
	deque->front = new;
	deque->size++;
}

void enqueue_rear(deque_t *deque, int value)
{
	node_t *new = node_new(value);
	node_t *temp = deque->rear;
	node_t *front = deque->front;
	
	if(temp != NULL)
	{
		new->prev = temp;
		new->next = temp->next;
		temp->next = new;
	}

	if(front == NULL)
	{
		deque->front = new;
	}

	deque->rear = new;
	deque->size++;
}

int rear(deque_t *deque)
{
	if(!empty(deque))
	{
		if(deque->rear != NULL)
		{
			int coisa = deque->rear->value;
			return coisa;
		}
		else return INT_MIN;
	}
	else return INT_MIN;
}

int front(deque_t *deque)
{
	if(!empty(deque))
	{
		if(deque->front != NULL)
		{
			int coisa = deque->front->value;
			return coisa;
		}
		else return INT_MIN;
	}
	else return INT_MIN;
}

bool empty(deque_t *deque)
{
	bool b = (deque->size == 0);
	return b;
}

int size (deque_t *deque)
{
	return (deque->size);
}

void destruct(deque_t *deque)
{
	free(deque);
}

deque_t* construct()
{
	deque_t *new = (deque_t*)malloc(sizeof(deque_t));
	new->front = NULL;	
	new->rear = NULL;	
	new->size = 0;

	return new;
}

node_t* node_new(int value)
{
	node_t *new = (node_t*)malloc(sizeof(node_t));
	new->next = NULL;	
	new->prev = NULL;	
	new->value = value;

	return new;
}


