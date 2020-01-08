#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _deque deque_t;
typedef struct _node   node_t;

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

int main() {
 	int i, num;
  	scanf("%d", &num);
  
  	deque_t* deque = construct();
  	int vector[num];
  	for(i = 0; i < num; ++i)
      	scanf("%d", &vector[i]);
  
  	for(i = 0; i < num; ++i)
      	enqueue_rear(deque, vector[i]);
  
 	printf("%d\n", front(deque));
  	printf("%d\n", rear (deque));
  
  	if(!empty(deque))
  		printf("The size of the deque %d\n", size(deque));
  	else
       	printf("The deque is empty\n");
  	
    scanf("%d", &num);
    for(i = 0; i < num; ++i)
       enqueue_front(deque, i);
  	print(deque);
    dequeue_front(deque);
    print(deque);
    dequeue_rear (deque);
    print(deque);
    
  	erase(deque);
  	for(i = 0; i < 3; ++i)
  		enqueue_rear(deque, i);
  		
  	print(deque);
    destruct(deque);
       
	return 0;
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

	while(temp->next != NULL)
	{
		printf("%d ", temp->value);
		temp = temp->next;
	}
	printf("%d\n", temp->value);
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


