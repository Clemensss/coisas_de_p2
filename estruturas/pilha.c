#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	void *item;
	struct Node *next;
};

typedef struct Node node;

void* pop(node **head);
void push(node **head, void *p);
void print_list(node *head);
node* make_stack();
void compare(char *str);
int check(char *str);
int isemp(node *stack);
int count_stack(node *stack);
void empty_stack(node **stack);

int main()
{
	int max;
	scanf("%d\n", &max);
	int i;
	node *forward = make_stack();
	node *back = make_stack();
	
	char str[255];
	for()
	{
		if(!strcmp(str, "ENTER\n") || !strcmp(str, "ENTER"))
		{
			push(&back, 0);
			empty_stack(&forward);
		}

		else if(!strcmp(str, "BACK\n") || !strcmp(str, "BACK"))
		{
			push(&forward, 0);
			pop(&back);
		}

		else if(!strcmp(str, "FORWARD\n") || !strcmp(str, "FORWARD"))
		{
			//push(&back, 0);
			pop(&forward);
		}
	}

	printf("BACK: %d\n", count_stack(back));
	printf("FORWARD: %d\n", count_stack(forward));

    return 0;
}

void empty_stack(node **stack)
{
	*stack = NULL;	
}

int isemp(node *stack)
{
	return (stack == NULL);
}

node* make_stack()
{
	return NULL;
}

int count_stack(node *stack)
{
	node *temp = stack;
	int count = 0;

	while(temp != NULL)
	{
		count++;
		temp = temp->next;
	}

	return count;
}

void push(node **head, void *p) 
{
	node *new = (node*)malloc(sizeof(node));
	new->next = (*head);
	new->item = p;
	*head = new;
}

void* pop(node **head)
{ 
	if(*head != NULL)
	{
		void *p = (*head)->item;
		*head = (*head)->next;
		return p;
	}
	return NULL;
}

void print_list(node *head)
{
	if(head != NULL)
	{
		node *temp = head;
		while(temp != NULL)
		{
			char *s = (char*)temp->item;
			printf("%c", *s );
			temp = temp->next;
		}
	}
	else printf("nil\n");
}


