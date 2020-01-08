#include <stdio.h>
#include <stdlib.h>

typedef struct Tree_node
{
	int item;
	struct Tree_node *right;
	struct Tree_node *left;
} 
tree_node;

void add_one(tree_node **root, int item);
void add_node(tree_node **root, int item);

void add_binary(tree_node **root, int item);
tree_node *create_tree(int item, tree_node *right, tree_node *left);
void print_tree(tree_node *root);
tree_node *make_tree();
tree_node *lisp_tree(char str[], int *index);
void isitbb(tree_node *root, int *fake);

int main()
{
	tree_node *root = make_tree();
	
	char *str;
	size_t len = 0;
	getline(&str, &len, stdin);

	int num = 0;
	root = lisp_tree(str, &num);
	
	int bool = 1;
	isitbb(root, &bool);
	printf(bool ? "VERDADEIRO\n" : "FALSO\n");

    return 0;
}

tree_node *make_tree()
{	
	return NULL;
}

void isitbb(tree_node *root, int *fake)
{
	if(root->left != NULL) 
	{
		if(root->left->item > root->item) 
		{
			*fake = 0;
			return;
		}
		isitbb(root->left, fake);
	}

	if(root->right != NULL) 
	{
		if(root->right->item > root->item) 
		{
			*fake = 0;
			return;
		}
		isitbb(root->right, fake);
	}
}

tree_node *lisp_tree(char str[], int *index)
{
	if(str[*index] == '(' && str[((*index)+1)] != ')')	
	{
		(*index)++;

		char num[5];
		char *ptr;

		int i = 0;
		while(str[*index] != '(')
		{
			num[i] = str[*index];
			(*index)++;
			i++;
		}
		num[i] = '\0';

		int item = strtol(num, &ptr, 10);

		tree_node *son1	= lisp_tree(str, index);
		tree_node *son2	= lisp_tree(str, index);

		return create_tree(item, son1, son2);
	}

	else if(str[(*index)] == '(' && str[((*index)+1)] == ')')	
	{
		*index = *index + 2;

		int i = 0;
		while(str[*index] != '(')
		{
			(*index)++;
		}

		return NULL;
	}
}

void add_binary(tree_node **root, int item)
{
	if((*root)!= NULL)	
	{	
		if((*root)->item > item)
		{
			if((*root)->left != NULL)
			{
				add_binary(&(*root)->left, item);
			}
			else 
			{
				(*root)->left = create_tree(item, NULL, NULL);
			}
		}
		else
		{
			if((*root)->right != NULL)
			{
				add_binary(&(*root)->right, item);
			}
			else 
			{
				(*root)->right = create_tree(item, NULL, NULL);
			}
		}
	}
}

tree_node *create_tree(int item, tree_node *left, tree_node *right)
{
	tree_node *new_tree = malloc(sizeof(tree_node));
	new_tree->item = item;
	new_tree->right = right;
	new_tree->left = left;
	return new_tree;
}

void print_tree(tree_node *root)
{
	if(root != NULL)	
	{
		printf("%d ", root->item);
		print_tree(root->left);
		print_tree(root->right);
	}
}

void add_node(tree_node **root, int item)
{
	if(*root != NULL)	
	{	
		if((*root)->item > item)
		{
			if((*root)->left != NULL)
			{	
				add_node(&(*root)->left, item);
			}
			else
			{
				add_one(&(*root)->left, item);
			}
		}
		else
		{
			if((*root)->right != NULL)
			{	
				add_node(&(*root)->right, item);
			}
			else
			{
				add_one(&(*root)->right, item);
			}
		}
	}
	add_one(root, item);
}

void add_one(tree_node **root, int item)
{
	tree_node *new_node = malloc(sizeof(tree_node));

	new_node->item = item;
	new_node->left= NULL;
	new_node->right= NULL;

	*root = new_node;
}
