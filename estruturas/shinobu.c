#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack();

//Recebe um elemento e cria e retorna um novo node
// com o elemento passado
NODE* create_node(int element);

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack);

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack);

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element);

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char operation);

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size);

void print_list(NODE *head);
int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));
}

void Calculadora(STACK* stack, int size)
{
	int i;
	int f;
	char str[40];
	fgets(str, sizeof(str), stdin);
	for(i=0; i<size; i++)	
	{
		fgets(str, sizeof(str), stdin);
		//print_list(stack->head);

		if(str[0] < 48 && str[0] > 40)
		{
			result(stack, str[0]);
		}
		else if(str[0] < 58)
		{
			int num;
			sscanf(str, "%d", &num);
			PUSH(stack, num);
		}
	}
}

void result(STACK *stack, char op)
{
	int a, b, c;
	b = POP(stack);
	a = POP(stack);

	if(op == '*')	
	{
		c = a * b;			
		PUSH(stack, c);
	}

	else if(op == '+')	
	{
		c = a + b;			
		PUSH(stack, c);
	}

	else if(op == '/')	
	{
		c = a / b;		
		PUSH(stack, c);
	}

	else if(op == '-')	
	{
		c = a - b;
		PUSH(stack, c);
	}
}

int IS_EMPTY(STACK *stack)
{
	return (stack->head == NULL);
}

STACK* Create_stack()
{
	STACK *new = (STACK*)malloc(sizeof(STACK));
	new->head = NULL;
	return new;
}

void PUSH(STACK *stack, int value) 
{
	NODE *new = (NODE*)malloc(sizeof(NODE));
	new->next = stack->head;
	new->element = value;
	stack->head = new;
}

int POP(STACK *stack)
{ 
	if(stack->head != NULL)
	{
		int i = stack->head->element;
		stack->head = stack->head->next;
		return i;
	}
	return 0;
}

void print_list(NODE *head)
{
	if(head != NULL)
	{
		NODE *temp = head;
		while(temp->next != NULL)
		{
			printf("%d ", temp->element);
			temp = temp->next;
		}
		printf("%d\n", temp->element);
	}
	else printf("nil\n");
}


NODE* create_node(int value)
{
	NODE *new = (NODE*)malloc(sizeof(NODE));
	new->next = NULL;	
	new->element = value;

	return new;
}


