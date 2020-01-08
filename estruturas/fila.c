#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE 1000
struct prioridade
{
	int item;
	int pri;
};

struct coisa
{
	void* arr[MAX_QUEUE];
	int start;
	int size;
};
	
typedef struct coisa queue;
typedef struct prioridade ord;

void* dequeue(queue* coisa);
int enqueue(queue *coisa, void* item);
queue* make_queue();

void prio_sort(queue *fila);
void swap(void** one, void** two);
void print_pq(queue *fila);
void prio_enqueue(queue *fila, int item, int prio);
void i_enqueue(queue *fila, int i);
void compare(queue *prio, queue *fila);
void print_q(queue *fila);

int main()
{
	int entrada;
	scanf("%d", &entrada);

	int ha;
	for(ha = 0; ha < entrada; ha++)
	{
		queue* fila = make_queue();
		queue* prio = make_queue();
		
		int alunos;
		int i;
		
		scanf("%d", &alunos);
		for(i = 0; i < alunos; i++)
		{
			int nota;
			int new = i;
			scanf("%d", &nota);
			prio_enqueue(prio, new, nota);
			i_enqueue(fila, new);
		}
		compare(prio, fila);

	}
    return 0;
}

void compare(queue *prio, queue *fila)
{
	int start = prio->start;
	int size = prio->size;
	int count = 0;	
	int i;
	for(i=0; i<size; i++)
	{
		ord *p = (ord*)prio->arr[i];
		int *n = (int*)fila->arr[i];

		int comp1, comp2;
		comp1 = p->item;
		comp2 = *n;

		if(comp1 == comp2)
		{
			count++;
		}
	}
	printf("%d\n", count);
}

void prio_enqueue(queue *fila, int item, int prio)
{
	ord* p = (ord*)malloc(sizeof(ord));	
	p->item = item;
	p->pri = prio;
	enqueue(fila, p);
	prio_sort(fila);
}

void i_enqueue(queue *fila, int i)
{
	int* p;	
	*p = i;
	enqueue(fila, p);
}

ord* prio_dequeue(queue *fila)
{
	void* p = dequeue(fila);
	
	ord *coisa = (ord*)p;
	return coisa;
}

void print_pq(queue *fila)
{
	int start = fila->start;
	int size = fila->size;
	int i;

	ord *thing;
	for(i = start; i < size; i++)
	{
		thing = (ord*)fila->arr[i];
		printf("%d|%d\n", thing->item, thing->pri);
	}

	//thing = (ord*)fila->arr[(size-1)];
	//printf("%d\n", thing->item);
}

void print_q(queue *fila)
{
	int start = fila->start;
	int size = fila->size;
	int i;

	int *thing;
	for(i = start; i < size; i++)
	{
		thing = (int*)fila->arr[i];
		printf("%d\n",*thing);
	}

	//thing = (ord*)fila->arr[(size-1)];
	//printf("%d\n", thing->item);
}
void prio_sort(queue *fila)
{
	int start = fila->start;
	int size = fila->size;
	
		int sorted = 1;
	if(size > 1)
	{
		while(sorted)
		{
			int i;
			sorted = 0;
			for(i = start; i < size-1; i++)
			{
				ord *one = (ord*)fila->arr[i];
				ord *two = (ord*)fila->arr[(i+1)];

				if(one->pri < two->pri)
				{
					swap(&fila->arr[i], &fila->arr[(i+1)]);
					sorted = 1;
				}
			}
		}
	}
}

void swap(void **one, void **two)
{
	void* temp = *one;
	*one = *two;
	*two = temp;
}

queue* make_queue()
{
	queue *coisa = (queue*)malloc(sizeof(queue));
	coisa->start = 0;
	coisa->size = 0;
}

void* dequeue(queue* coisa)
{
	void* first = coisa->arr[coisa->start];
	coisa->start++;
	return first;
}

int enqueue(queue *coisa, void* item)
{
	coisa->arr[coisa->size] = item;
	coisa->size++;

	if(coisa->size >= MAX_QUEUE)
	{
		printf("overflow\n");
		return -1;
	}

	return 1;
}
