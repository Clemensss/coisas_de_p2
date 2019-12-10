#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int item;
	struct Node* next;

} node; 

node* make_list (void);
void  print_list(node *head);

void  add_node  (node *coisa, int item);
void remove_node(node *befo, node *unwan);

void  push_list (node *head, int item);
void pop_list(node *head);

int   add_list  (node *head, int item, int index);
int remove_list(node *head, int index);

void bubble_sort_list(node *head);
int bubble_sort_iter(node *head);

int swap_list(node *head, node *first, node *second);
void swap_nodes(node *before, node *first, node *second);

int linearsearch(node *head, int item);
node* get_node(node *head, int index);
int isitempty(node *head);

int intersection(node *list1, node *list2, node *inter);
int subset_list(node* A, node* B);

int get_size(node *head);
void inverting(node* head);

int main()
{
	node* head1 = make_list();
	
	int item;
	
	while(scanf("%d", &item) != EOF)
		push_list(head1, item);

	inverting(head1);
	print_list(head1);

    return 0;
}

node* make_list(void)
{
	node* head = malloc(sizeof(node));
	head->next = NULL;

	return head;
}

void print_list(node *head)
{
	node* temp = head->next;

	while(temp->next != NULL)
	{
		printf("%d ", temp->item);
		temp = temp->next;
	}
	printf("%d\n", temp->item);
}

void inverting(node* head)
{
	int size = get_size(head);
	
	int start = 1; 
	int end = size-2;
	
	while(start < end)
	{
		swap_list(head, get_node(head, start), get_node(head, end));
		printf("works\n");
		start++;
		end--;
	}
}

int subset_list(node* A, node* B)
{
	if(A->next != NULL && B->next != NULL)
	{
		node* temp = B->next;
		while(temp != NULL)
		{
			if(!linearsearch(A, temp->item))
			{
				return 0;
			}
			temp = temp->next;
		}
		return 1;
	}
	return 0;
}

/*
	iters through the first list, takes an item and checks if
	it is in the second list, if it is and the item is not inside
	the intersection list, the item gets pushed into the intersection
	list.
*/

int intersection(node *list1, node *list2, node *inter)
{	
	if(list1->next != NULL)
	{
		node* temp = list1->next;
		while(temp != NULL)
		{
			if(linearsearch(list2, temp->item) 
			  && !linearsearch(inter, temp->item))
			{
				push_list(inter, temp->item);
			}
			temp = temp->next;
		}
		return 1;
	}
	return -1;
}
/*
	returns how many times it appears in the list
*/
int linearsearch(node *head, int item)
{
	int count = 0;
	if(head->next != NULL)
	{
		node* temp = head->next;
		while(temp != NULL)
		{
			if(temp->item == item)
			{
				count++;
			}
			temp = temp->next;
		}
		return (count > 0);
	}
	return 0;
}


/*---------------------------------------*/

void bubble_sort_list(node *head)
{
	if(!isitempty(head))
		while(bubble_sort_iter(head) > 0);
}

int bubble_sort_iter(node *head)
{
	int sorted = 0;

	node* temp = head->next;
	while(temp->next != NULL)
	{
		if(temp == NULL)
		{
			printf("fodeu\n");
			return -1;
		}

		if(temp->item > temp->next->item)
		{	
			int a = swap_list(head, temp, temp->next);
			sorted++;
		}
		else temp = temp->next;
	}
	return sorted;
}
/* 
	A little weird, it takes two nodes, that must be adjacent
	goes through the whole list until it finds the node before 
	the first , and does a pointer swap using the function swap_nodes.
*/

int swap_list(node *head, node *first, node *second)
{
	if(head->next != NULL)
	{
		node* temp = head;

		if(head->next != first)
		{
			while(temp->next != first)
			{
				temp = temp->next;
				if(temp->next == NULL) return 0;
			}
		}
		swap_nodes(temp, first, second);
		return 1;
	}
	return -1;
}

/*
	Takes three nodes, the *before must come before first
	does a simples swap after that using a temporary variable.
*/

void swap_nodes(node *before, node *first, node *second)
{
	node *temp = second->next;

	before->next = second;

	second->next = first;
	first->next  = temp;
}

/* 
	queue operations
*/

void push_list(node *head, int item)
{
	if(head->next != NULL)
	{
		node* temp = head->next;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		add_node(temp, item);
	}
	else add_node(head, item);
}

void pop_list(node *head)
{
	node *temp = head->next;
	if(temp != NULL)
	{
		remove_node(head, temp);
		return;
	}
}

/* ------------------------------------ */

node* get_node(node *head, int index)
{
	if(head->next != NULL)
	{
		node* temp = head->next;

		int i;
		for(i=1; i <= index; i++)
		{
			temp = temp->next;
			if(temp == NULL)
			{
				printf("Index not found\n");
				return NULL;
			}
		}
		return temp;		
	}
	printf("Empty list\n"); 
	return NULL;
}

int get_size(node *head)
{
	int count = 1;
	if(head->next != NULL)
	{
		node* temp = head->next;
		while(temp != NULL)
		{
			count++;	
			temp = temp->next;
		}
		return count;
	}
	else return 0;
}

int isitempty(node *head)
{
	if(head->next == NULL) return 1;
	return 0;
}

/* 
    if the list is empty it returns -1, if the node isn't there
    it returns 0, and if the operation is a success it returns 1.
*/

int remove_list(node *head, int index)
{
	if(head->next != NULL)
	{
		node *temp = get_node(head, index);
		remove_node(temp, temp->next);
		return 1;
	}
	return -1;
}

void remove_node(node *befo, node *unwan)
{
	befo->next = unwan->next;
	unwan->next = NULL;
}

/* 
    if the list is empty it returns -1, if the index suparsses the limit
    it returns 0, and if the operation is a success it returns 1.
*/

int add_list(node *head, int item, int index)
{
	if(head->next != NULL)
	{
		node* temp = get_node(head, index);
		add_node(temp, item);
		
		return 1;
	}
	return -1;
}

void add_node(node *coisa, int item)
{
	node *temp;
	node* new_node = malloc(sizeof(node));

	new_node->next = coisa->next;
	new_node->item = item;

	coisa->next = new_node;
}


