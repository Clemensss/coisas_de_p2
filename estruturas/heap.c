#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HEAP_MAX 1000

/*
    Nó de prioridade, possui um ponteiro pra void e um inteiro
    referente a prioridade do nó.
*/
struct _p_node
{
    void *item;
    int prio;
};

typedef struct _p_node p_node_t; 
 /*
    Estrutura de Heap; Possui um Array de p_node_t e um inteiro
    referente ao seu tamanho;
*/
struct _heap
{
    p_node_t* arr[HEAP_MAX];
    int size;
    int max_buffer_size;
};

typedef struct _heap heap_t;

void add_heap(heap_t *heap, void *p, int prio);

p_node_t* new_node(void *p, int prio);
heap_t* make_heap();

void max_heapify(heap_t *heap);
void heapify(heap_t *heap, int parent);

int get_right_son(int i);
int get_left_son(int i);

void swap(p_node_t **p_1, p_node_t **p_2);

p_node_t* pop_heap(heap_t *heap);
void print_heap(heap_t *heap);

p_node_t* cp_node(p_node_t *node);

void print_arr(int arr[], int n);
void heapsort(int arr[], int n);

int main()
{
    int num;
    int count = 0;
    int arr[HEAP_MAX];

    while(scanf("%d ", &num) != EOF)
    {
        arr[count] = num;
        count++;
    }

    printf("Estado inicial:");
    print_arr(arr, count);

    heapsort(arr, count);

    printf("Resultado Final:");
    print_arr(arr, count);
    return 0;
}

void heapsort(int arr[], int n)
{
    heap_t *heap = make_heap();
    void *p;
    int num;

    for(int i = 0; i < n; i++)
    {
        num = arr[i];
        add_heap(heap, p, num);
    }

    for(int i = (n-1); i >= 0; i--)
    {
        printf("Estado Atual da Heap:");
        print_heap(heap);
        p_node_t* node = pop_heap(heap);

        num = node->prio;
        if(i)printf("Maior elemento neste passo: %d\n", num);
        arr[i] = num;
    }
}

void print_arr(int arr[], int n)
{
    int i;
    for(i = 0; i < n-1; i++)
    {
        printf(" %d |", arr[i]);
    }
    printf(" %d\n", arr[(n-1)]);
}

p_node_t* pop_heap(heap_t *heap)
{
    if(heap->size)
    {
        p_node_t* n_node = cp_node(heap->arr[1]);

        if(heap->size > 1) 
            swap(&heap->arr[1], &heap->arr[heap->size]);

        heap->arr[heap->size] = NULL;
        heap->size--;

        max_heapify(heap);

        return n_node;
    }
    return NULL;
}

void print_heap(heap_t *heap)
{
    int i;
    for(i = 1; i < heap->size; i++)
    {
        printf(" %d |", heap->arr[i]->prio);
        
    }
    printf(" %d\n", heap->arr[heap->size]->prio);
}

p_node_t* cp_node(p_node_t *node)
{
    p_node_t* cp_node = new_node(node->item, node->prio);
    return cp_node;
}

void add_heap(heap_t *heap, void *p, int prio)
{
    heap->size++; 

    p_node_t *node = new_node(p, prio);
    heap->arr[heap->size] = node;

    if(heap->size > heap->max_buffer_size)
    {
        //realloc_heap(heap);
    }

    max_heapify(heap);
}

p_node_t* new_node(void *p, int prio)
{
    p_node_t *new_node = (p_node_t*)malloc(sizeof(p_node_t));
    new_node->item = p;
    new_node->prio = prio;

    return new_node;
}

heap_t* make_heap()
{
    heap_t *heap = (heap_t*)malloc(sizeof(heap_t));

    heap->size = 0;
    heap->max_buffer_size = HEAP_MAX;

    int i;
    for (i = 0; i < HEAP_MAX; i++)
    {
        heap->arr[i] = NULL;
    }
    
    return heap;
}

void max_heapify(heap_t *heap)
{
    if(heap->size > 3)
    {
        int i; 
        for(i = (heap->size -1)/2; i > 0 ; i--)
        {
            heapify(heap, i);
        }
    }
    else
    {
        heapify(heap, 1);
    }
}

void heapify(heap_t *heap, int parent)
{
    int left = get_left_son(parent);
    int right = get_right_son(parent);

    int largest = parent;

    if(left <= heap->size)
    {
        if(heap->arr[left]->prio > heap->arr[largest]->prio)
        {
            largest = left;
        }
    }

    if(right <= heap->size)
    {
        if(heap->arr[right]->prio > heap->arr[largest]->prio)
        {
            largest = right;
        }
    }

    if(largest != parent)
    {
        swap(&heap->arr[largest], &heap->arr[parent]);
        heapify(heap, largest);
    }
}

void swap(p_node_t **p_1, p_node_t **p_2)
{
    p_node_t *temp = *p_1;
    *p_1 = *p_2;
    *p_2 = temp; 
}

/*
    Retorna o filho a esquerda de i, que é o nó pai.
*/
int get_left_son(int i)
{
    return (i*2);
}

/*
    Retorna o filho a esquerda de i, que é o nó pai.
*/
int get_right_son(int i)
{
    return (i*2) + 1;
}
